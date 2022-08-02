#include "helgarahi.h"
#include <string.h>
#define WORKBOOK_INFO "xl/workbook.xml"
#define WORKBOOK_SHEET "xl/worksheets/sheet%d.xml"

void XMLCALL workbook_start(void *data, const char *tag, const char **attr)
{
	size_t *_data = (size_t *) data;

	if (!strcmp(tag, "sheet")) {
		(*_data)++;
	}
	return;
}

void XMLCALL workbook_end(void *data, const char *tag)
{
	return;
}

size_t workbook_num_sheets(xml_t *raw)
{
	XML_Parser parser = XML_ParserCreate("US-ASCII");
	size_t num_sheets = 0;
	enum XML_Status status;
	if (!parser) {
		return 0;
	}

	XML_SetElementHandler(parser, workbook_start, workbook_end);
	XML_SetUserData(parser, &num_sheets);
	status = XML_Parse(parser, raw->buffer, raw->read_size, 0);
	if (status == XML_STATUS_ERROR) {
		printf("Error Parsing: %s\n", 
			XML_ErrorString(XML_GetErrorCode(parser)));
	}
	XML_ParserFree(parser);
	return num_sheets;
}

workbook_t *workbook_generate(xlsx_t *target)
{
	workbook_t *to_ret = (workbook_t *) malloc(sizeof(workbook_t));
	xml_t *workbook_raw;
	xml_t *cur_xml = 0x0;
	char buffer[128];
	if (!to_ret) {
		goto exit;
	}

	workbook_raw = xml_load(WORKBOOK_INFO, target->zip, 0x0);
	if (!workbook_raw) {
		goto on_fail;
	}
	// get the number of sheets in the workbook
	to_ret->num_sheets = workbook_num_sheets(workbook_raw);
	
	if (!to_ret->num_sheets) {
		goto on_fail;
	}

	// generate sheets
	to_ret->sheets = (sheet_t *) 
		malloc(sizeof(sheet_t) * to_ret->num_sheets);
	if (!to_ret->sheets) {
		goto on_fail;
	}

	for (size_t i = 0; i < to_ret->num_sheets; i++) {
		snprintf(buffer, 128, WORKBOOK_SHEET, i + 1);
		cur_xml = xml_load(buffer, target->zip, cur_xml);
		if (sheet_generate(&to_ret->sheets[i], cur_xml)) {
			xml_free(cur_xml);
			goto on_fail;
		}
	}

	xml_free(cur_xml);
	
exit:
	return to_ret;
on_fail:
	free(to_ret);
	to_ret = 0x0;
	goto exit;
}

int workbook_clean(workbook_t *obj)
{
	if (obj->num_sheets) {
		for (size_t i = 0; i < obj->num_sheets; i++) {
			//sheet_clean(obj->sheets);
		}
		//free(obj->sheets);
	}
	return 0;
}