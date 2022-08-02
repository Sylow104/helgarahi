#include "helgarahi.h"

xml_t *xml_load(const char *file, zip_t *zip, xml_t *to_reload)
{
	xml_t *to_ret;
	zip_file_t *to_dump;
	zip_stat_t stat;
	int rc;

	if (!(file && zip)) {
		return 0x0;
	}

	if (to_reload) {
		to_ret = to_reload;
	} else {
		to_ret = (xml_t *) malloc(sizeof(xml_t));
		to_ret->read_size = 0;
		to_ret->buffer_size = 0;
		to_ret->buffer = 0x0;
	}

	if (!to_ret) {
		goto exit;
	}

	if (zip_stat(zip, file, 0, &stat)) {
		printf("Unable to open %s : %s\n", file,
			zip_error_strerror(zip_get_error(zip)));
		goto exit;
	}

	if (to_ret->buffer_size < stat.size) {
		to_ret->buffer = (char *) 
			realloc(to_ret->buffer, sizeof(char) * (stat.size));
		to_ret->buffer_size = stat.size;
	}

	to_dump = zip_fopen(zip, file, 0);
	if (!to_dump) {
		goto on_fail;
	}

	to_ret->read_size = zip_fread(to_dump, to_ret->buffer, stat.size);
	zip_fclose(to_dump);
	if (to_ret->read_size != stat.size) {
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