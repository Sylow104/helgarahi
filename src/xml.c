#include "helgarahi.h"

xml_t *xml_load(const char *file, zip_t *zip)
{
	xml_t *to_ret;
	zip_file_t *to_dump;
	zip_uint64_t read_size;
	zip_stat_t stat;
	int rc;

	to_ret = (xml_t *) malloc(sizeof(xml_t));
	if (!to_ret) {
		goto exit;
	}

	rc = zip_stat(zip, file, 0, &stat);
	if (rc) {
		goto exit;
	}

	to_ret->buffer = (char *) malloc(sizeof(char) * (1 + stat.size));
	if (!to_ret->buffer) {
		goto on_fail;
	}

	to_dump = zip_fopen(zip, file, 0);
	if (!to_dump) {
		goto on_fail;
	}

	read_size = zip_fread(to_dump, to_ret->buffer, stat.size);
	zip_fclose(to_dump);
	if (read_size != stat.size) {
		goto on_fail;
	}

exit:
	return to_ret;
on_fail:
	if (to_ret->buffer) {
		free(to_ret->buffer);
	}
	if (to_ret) {
		free(to_ret);
		to_ret = 0x0;
	}
	goto exit;
}

int xml_free(xml_t *obj)
{
	if (obj->buffer) {
		free(obj->buffer);
	}
	free(obj);
	return 0;
}