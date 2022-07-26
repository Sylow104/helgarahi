#include "helgarahi.h"
#include <string.h>
#define WORKBOOK_INFO "xl/workbook.xml"
#define WORKBOOK_SHEET "xl/worksheets/sheet%d.xml"

int sheet_generate(sheet_t *target, xml_t *raw);
int sheet_clean(sheet_t *obj);

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

int workbook_generate(xlsx_t *target)
{
	int to_ret = 0;
	workbook_t *to_use = &target->workbook;
	xml_t *workbook_raw;
	xml_t *cur_xml = 0x0;
	char buffer[128];

	workbook_raw = xml_load(WORKBOOK_INFO, target->zip);
	if (!workbook_raw) {
		goto on_fail;
	}
	// get the number of sheets in the workbook
	to_use->num_sheets = workbook_num_sheets(workbook_raw);
	
	if (!to_use->num_sheets) {
		goto on_fail;
	}
	xml_free(workbook_raw);

	// generate sheets
	to_use->sheets = (sheet_t *) 
		malloc(sizeof(sheet_t) * to_use->num_sheets);
	if (!to_use->sheets) {
		goto on_fail;
	}

	for (size_t i = 0; i < to_use->num_sheets; i++) {
		snprintf(buffer, 128, WORKBOOK_SHEET, i + 1);
		cur_xml = xml_load(buffer, target->zip);
		if (sheet_generate(&to_use->sheets[i], cur_xml)) {
			goto on_fail;
		}
		xml_free(cur_xml);
	}
	
exit:
	return to_ret;
on_fail:
	to_ret = -1;
	if (cur_xml) {
		xml_free(cur_xml);
	}
	goto exit;
}

int workbook_clean(workbook_t *obj)
{
	if (obj->num_sheets) {
		for (size_t i = 0; i < obj->num_sheets; i++) {
			sheet_clean(&obj->sheets[i]);
		}
		free(obj->sheets);
	}
	return 0;
}