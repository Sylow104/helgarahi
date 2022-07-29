#include "helgarahi.h"
#define WORKBOOK_INFO "xl/workbook.xml"

size_t workbook_num_sheets(xml_t *raw)
{
	XML_Parser parser = XML_ParserCreate(raw->buffer);
	size_t num_sheets;
	if (!parser) {
		return 0;
	}

	XML_ParserFree(parser);
	return num_sheets;
}

workbook_t *workbook_generate(xlsx_t *target)
{
	workbook_t *to_ret = (workbook_t *) malloc(sizeof(workbook_t));
	xml_t *workbook_raw;
	if (!to_ret) {
		goto exit;
	}

	workbook_raw = xml_load(WORKBOOK_INFO, target->zip);
	if (!workbook_raw) {
		goto on_fail;
	}
	// get the number of sheets in the workbook
	to_ret->num_sheets = workbook_num_sheets(workbook_raw);
	if (!to_ret->num_sheets) {
		xml_free(workbook_raw);
		goto on_fail;
	}
	
	xml_free(workbook_raw);
exit:
	return to_ret;
on_fail:
	free(to_ret);
	to_ret = 0x0;
	goto exit;
}