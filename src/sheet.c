#include "helgarahi.h"

typedef struct _sheet
{
	sheet_t *a;
	cell_t *cur_cell;
	bool is_element;
} _sheet_t;

void XMLCALL sheet_import_start(void *data, const char *tag, const char **attr)
{
	_sheet_t *_data = (_sheet_t *) data;
	if (!strcmp("t", tag) || !strcmp("v", tag)) {
		_data->is_element = true;
	}
	return;
}

void XMLCALL sheet_import_handler(void *data, const XML_Char *s, int len)
{
	_sheet_t *_data = (_sheet_t *) data;
	if (_data->is_element) {
		if (len > 0) {
			_data->cur_cell->content = strndup(s, len);
		} else {
			_data->cur_cell->content = 0x0;
		}
		_data->is_element = false;
	}
	return;
}

void XMLCALL sheet_import_end(void *data, const char *tag)
{
	_sheet_t *_data = (_sheet_t *) data;
	if (!strcmp(tag, "t") || !strcmp(tag, "v")) {
		if (_data->is_element) {
			_data->cur_cell->content = 0x0;
			_data->is_element = false;
		}
		_data->cur_cell++;
	}
	return;
}

void XMLCALL sheet_count_start(void *data, const char *tag, const char **attr)
{
	sheet_t *_data = (sheet_t *) data;
	
	if (!strcmp(tag, "row")) {
		_data->num_rows++;
	}
	if (_data->num_rows < 2 && !strcmp(tag, "c")) {
		_data->num_cols++;
	}

	return;
}

void XMLCALL sheet_count_end(void *data, const char *tag)
{
	return;
}

int sheet_generate(sheet_t *target, xml_t *raw)
{
	XML_Parser parser = XML_ParserCreate("US-ASCII");
	enum XML_Status status;
	_sheet_t _sheet = {target, 0x0, false};
	if (!parser || !target) {
		return -1;
	}
	target->num_cols = 0;
	target->num_rows = 0;

	// count the number of cells for header

	XML_SetElementHandler(parser, sheet_count_start, sheet_count_end);
	XML_SetUserData(parser, target);
	if (!XML_Parse(parser, raw->buffer, raw->read_size, 0)) {
		printf("Error Parsing: %s\n", 
			XML_ErrorString(XML_GetErrorCode(parser)));
			goto cleanup;
	}

	// build data into the program
	_sheet.a->cells = (cell_t *) malloc(sizeof(cell_t) * target->num_cols *
		target->num_rows);
	if (!_sheet.a->cells) {
		abort();
	}
	_sheet.cur_cell = _sheet.a->cells;
	XML_ParserReset(parser, "US-ASCII");
	XML_SetUserData(parser, &_sheet);
	XML_SetElementHandler(parser, sheet_import_start, sheet_import_end);
	XML_SetCharacterDataHandler(parser, sheet_import_handler);
	if (!XML_Parse(parser, raw->buffer, raw->read_size, 0)) {
		printf("Error Parsing: %s\n", 
			XML_ErrorString(XML_GetErrorCode(parser)));
			goto cleanup;
	}
cleanup:
	XML_ParserFree(parser);
	return 0;
}

int sheet_clean(sheet_t *obj)
{
	size_t num_cells = obj->num_rows * obj->num_cols;
	if (obj->cells) {
		for (size_t i = 0; i < num_cells; i++) {
			if (obj->cells[i].content) {
				free(obj->cells[i].content);
			}
		}
		free(obj->cells);
	}
	return 0;
}