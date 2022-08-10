#include "helgarahi.h"

typedef struct row
{
	void *external_data;
	char **content;
	size_t content_max_size;
	size_t num_contents;

	size_t content_counter;
	bool cur_is_ele;
	row_callback_f row_callback;
} row_t;

void XMLCALL row_start_handler(void *user_data, const char *tag, 
		const char **attr)
{
	row_t *row = (row_t *) user_data;
	if (!strcmp("t", tag) || !strcmp("v", tag)) {
		row->cur_is_ele = true;
	}
	return;
}

void XMLCALL row_end_handler(void *user_data, const char *tag)
{
	row_t *row = (row_t *) user_data;
	if (!strcmp(tag, "t") || !strcmp(tag, "v")) {
		row->cur_is_ele = false;
	}
	// goto next cell
	if (!strcmp("row", tag)) {
		if (row->row_callback) {
			row->row_callback(row->external_data, 
				(const char **) row->content, 
				row->num_contents);
		}
		row->content_counter = 0;
	}

}

void XMLCALL row_data_handler(void *user_data, const XML_Char *s, int len)
{
	row_t *row = (row_t *) user_data;
	char *target = row->content[row->content_counter];
	// imports data into the cells
	if (row->cur_is_ele) {
		if (len > 0) {
			strncpy(target, (char *) s, row->content_max_size);
		} else {
			*target = '\0';
		}
	}
	row->content_counter++;
	return;
}

row_t *row_init(size_t num_cols, size_t i_max_size, void *in_ext_data, 
	row_callback_f row_callback)
{
	row_t *to_ret = (row_t *) malloc(sizeof(row_t));
	if (!to_ret) {
		return to_ret;
	}

	to_ret->num_contents = num_cols;
	to_ret->content = (char **) malloc(sizeof(char *) * num_cols);
	if (!to_ret->content) {
		free(to_ret);
	}

	to_ret->content_max_size = i_max_size;
	for (size_t i = 0; i < num_cols; i++) {
		char **cur = &to_ret->content[i];
		*cur = (char *) malloc(sizeof(char) * i_max_size);
		if (!*cur) {
			abort();
		}
	}

	to_ret->cur_is_ele = false;
	to_ret->external_data = in_ext_data;
	to_ret->content_counter = 0;
	to_ret->row_callback = row_callback;
	return to_ret;
}

int row_free(row_t *obj)
{
	if (!obj) {
		return -1;
	}

	for (size_t i = 0; i < obj->num_contents; i++) {
		char **cur = &obj->content[i];
		free(*cur);
	}
	free(obj->content);
	free(obj);

	return 0;
}