#include "helgarahi.h"
#include <stdlib.h>

xlsx_t *xlsx_open(const char *filename)
{
	xlsx_t *to_ret = (xlsx_t *)
		malloc(sizeof(xlsx_t));
	int zip_rc;
	if (!to_ret) {
		goto exit;
	}
	to_ret->zip = zip_open(filename, 0, &zip_rc);
	if (zip_rc != ZIP_ER_OK) {
		free(to_ret);
		goto exit;
	}

exit:
	return to_ret;
}

int xlsx_close(xlsx_t *obj)
{
	int rc;
	if (obj->zip) {
		rc = zip_close(obj->zip);
	}
	if (obj->sheets) {
		rc = sheet_destroy(obj->sheets);
	}
	return rc;
}