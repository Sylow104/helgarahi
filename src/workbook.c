#include "helgarahi.h"
#define WORKBOOK_INFO "xl/workbook.xml"

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
	
exit:
	return to_ret;
on_fail:
	free(to_ret);
	to_ret = 0x0;
	goto exit;
}