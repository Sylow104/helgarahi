#include "helgarahi.h"
#include <stdlib.h>

int workbook_generate(xlsx_t *target);
int workbook_clean(workbook_t *obj);

xlsx_t *xlsx_open(const char *filename)
{
	xlsx_t *to_ret;

	if (!filename) {
		return 0x0;
	}
	
	to_ret = (xlsx_t *) malloc(sizeof(xlsx_t));
	int zip_rc = 0;
	if (!to_ret) {
		goto exit;
	}
	to_ret->zip = zip_open(filename, 0, &zip_rc);
	if (zip_rc != ZIP_ER_OK) {
		free(to_ret);
		goto exit;
	}

	to_ret->workbook.num_sheets = 0;
	if (workbook_generate(to_ret)) {
		free(to_ret);
		to_ret = 0x0;
	}
exit:
	return to_ret;
}

int xlsx_close(xlsx_t *obj)
{
	int rc;
	if (!obj) {
		return -1;
	}
	if (obj->zip) {
		rc = zip_close(obj->zip);
	}
	rc = workbook_clean(&obj->workbook);
	free(obj);
	return rc;
}