#include "helgarahi.h"

typedef struct cell_new
{
	char *content;
	size_t max_size;
} cell_new_t;

typedef struct row
{
	cell_new_t *cells;
	size_t num_cells;
} row_t;

row_t *row_init(size_t num_cols, size_t i_max_size)
{
	row_t *to_ret = (row_t *) malloc(sizeof(row_t));
	cell_new_t *cur;
	if (!to_ret) {
		return to_ret;
	}

	to_ret->num_cells = num_cols;
	to_ret->cells = (cell_new_t *) malloc(sizeof(cell_new_t) * num_cols);
	if (!to_ret->cells) {
		free(to_ret);
		return 0x0;
	}

	for (size_t i = 0; i < num_cols; i++) {
		cur = &to_ret->cells[i];
		cur->content = (char *) malloc(sizeof(char) * i_max_size);
		if (cur->content) {
			abort();
		}
		cur->max_size = i_max_size;
	}
	return to_ret;
}

int row_free(row_t *obj)
{
	if (!obj) {
		return -1;
	}

	for (size_t i = 0; i < obj->num_cells; i++) {
		cell_new_t *cur = &obj->cells[i];
		free(cur->content);
	}
	free(obj->cells);
	free(obj);

	return 0;
}