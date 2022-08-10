#include "helgarahi.h"

typedef struct sheet_new
{
	size_t num_cols;
	xml_t *to_parse;
} sheet_new_t;

sheet_new_t *sheet_new(xml_t *to_parse)
{
	sheet_new_t *to_ret = (sheet_new_t *) malloc(sizeof(sheet_new_t));
	if (!to_ret) {
		return to_ret;
	}
	/* read number of cols */
	

	return to_ret;
}
