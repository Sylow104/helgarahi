#include "helgarahi.h"

typedef struct parser
{
	XML_Parser parser;
	xml_t *raw;
	enum XML_Status p_status;
	parser_e i_status;
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
	to_ret->i_status = PARSER_READY;
	return to_ret;
}

parser_e parser_step(parser_t *obj)
{
	if (!obj->i_status) {
		obj->p_status = XML_Parse(obj->parser, obj->raw->buffer, 
			obj->raw->read_size, 0);
	} else if (obj->i_status == PARSER_DATA) {
		obj->p_status = XML_ResumeParser(obj->parser);
	}

	switch (obj->p_status) {
		case XML_STATUS_OK:
			return PARSER_OK;
		case XML_STATUS_SUSPENDED:
			return PARSER_DATA;
		default:
		case XML_STATUS_ERROR:
			return PARSER_ERROR;
	}
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