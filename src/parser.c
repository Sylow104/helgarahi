#include "helgarahi.h"

typedef struct parser
{
	XML_Parser parser;
	xml_t *raw;
} parser_t;

parser_t *parser_setup(void (* start)(void *, const char *, const char **),
	void (* end)(void *, const char *), 
	void (* handler)(void *, const XML_Char *, int),
	void *user_data,
	xml_t *raw)
{
	parser_t *to_ret = malloc(sizeof(parser_t));
	if (!to_ret) {
		return to_ret;
	}

	XML_Parser parser = XML_ParserCreate("US_ASCII");
	if (!to_ret->parser) {
		free(to_ret);
		return 0x0;
	}

	if (start && end) {
		XML_SetElementHandler(parser, start, end);
	}
	if (user_data) {
		XML_SetUserData(parser, user_data);
	}
	if (handler) {
		XML_SetCharacterDataHandler(parser, handler);
	}
	to_ret->parser = parser;
	to_ret->raw = raw;
	return to_ret;
}

int parser_step(parser_t *obj)
{
	if (XML_Parse(obj->parser, obj->raw->buffer, obj->raw->read_size,
		0)) {
		return -1;
	}

	return 0;
}

int parser_free(parser_t *obj)
{
	if (obj) {
		XML_ParserFree(obj->parser);
		return 0;
	} else {
		return -1;
	}
}