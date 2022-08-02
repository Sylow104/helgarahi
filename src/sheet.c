#include "helgarahi.h"
#include <string.h>
#include <stdio.h>

void XMLCALL sheet_import_start(void *data, const char *tag, const char **attr)
{
	sheet_t *_data = (sheet_t *) data;
	if (!strcmp("t", tag) || !strcmp("v", tag)) {
		_data->is_element = true;
	}
	return;
}

void XMLCALL sheet_import_handler(void *data, const XML_Char *s, int len)
{
	sheet_t *_data = (sheet_t *) data;
	if (_data->is_element) {
		if (len > 0) {
			_data->cells[_data->ctr].content = strndup(s, len);
		} else {
			_data->cells[_data->ctr].content = 0x0;
		}
		_data->is_element = false;
	}
	return;
}

void XMLCALL sheet_import_end(void *data, const char *tag)
{
	sheet_t *_data = (sheet_t *) data;
	if (!strcmp(tag, "t") || !strcmp(tag, "v")) {
		if (_data->is_element) {
			_data->cells[_data->ctr].content = 0x0;
			_data->is_element = false;
		}
		_data->ctr++;
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
	target->cells = (cell_t *) malloc(sizeof(cell_t) * target->num_cols *
		target->num_rows);
	if (!target->cells) {
		abort();
	}
	target->cur_cell = target->cells;
	target->ctr = 0;
	target->is_element = false;
	XML_ParserReset(parser, "US-ASCII");
	XML_SetUserData(parser, target);
	XML_SetElementHandler(parser, sheet_import_start, sheet_import_end);
	XML_SetCharacterDataHandler(parser, sheet_import_handler);
	if (!XML_Parse(parser, raw->buffer, raw->read_size, 0)) {
		printf("Error Parsing: %s\n", 
			XML_ErrorString(XML_GetErrorCode(parser)));
			goto cleanup;
	}
	target->cur_cell = target->cells;
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
				//printf("%p\n", obj->cells[i].content);
				free(obj->cells[i].content);
			}
		}
		free(obj->cells);
	}
	return 0;
}