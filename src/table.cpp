#include "table.hpp"
#include <string.h>

table::table(sheet *main, sheet *aux) :
	_main(main), _aux(aux)
{
	;
}

table::table(size_t num_columns)
{
	columns = new column[num_columns];
};

table::~table()
{
	if (columns) {
		delete[] columns;
	}
}


int table::find_index(sheet *to_check, const char *column)
{
	size_t i;
	for (i = 0; i < to_check->_header->num_entries; i++) {
		if (!strcmp(column, (*to_check->_header)[i]->column())) {
			return i;
		}
	}
	return -1;
}

merge_point table::relation(const char *main, const char *aux)
{
	merge_point t;
	size_t i;

	t.main_index = find_index(_main, main);
	t.aux_index = find_index(_aux, aux);

	return t;
}