#include "table.hpp"
#include <string.h>
#include <sqlite3.h>

table::table(const char *name, const char *xml_buffer, uint64_t size) :
	sheet(xml_buffer, size)
{
	columns = new column_t[num_columns];
	this->name = strdup(name);
}

table::~table()
{
	delete[] columns;
	free(this->name);
}

int table::add_column(const char *target, transform_e in_flags)
{
	ssize_t index = find_header(target);

	if (index < 0) {
		return -1;
	}
	columns[num_selected].index = index;
	columns[num_selected].type = column_type(index);
	switch (columns[num_selected].type) {
		case CE_MIXED:
		case CE_NONE:
			columns[num_selected].type = CE_TEXT;
			break;
	}
	num_selected++;

	switch (in_flags) {
		case T_IS_DATE:
			return excel_date_to_unix(index);
		case T_IS_NUMBER:
			return exponential_to_int(index);
		case T_NONE: 
		default:
			break;
	}
	
	return 0;
}

char *table::create()
{
	char *to_ret = 0x0;
	if (num_selected < 1) {
		return to_ret;
	}

	to_ret = new char[4096];

	strcpy(to_ret, "create table ");
	strcat(to_ret, name);
	strcat(to_ret, " (");
	for (size_t i = 0; i < num_selected; i++) {
		cell *cur = (cell *) &header[columns[i].index];
		strcat(to_ret, cur->content);
		switch (columns[i].type) {
			case CE_NONE:
			case CE_TEXT:
			case CE_MIXED:
				strcat(to_ret, " text");
				break;
			case CE_NUM:
				strcat(to_ret, " int");
				break;
			default:
				throw 1;
		}
		if (i + 1 < num_selected) {
			strcat(to_ret, ", ");
		}
	}
	strcat(to_ret, ");");
	
	return to_ret;
}
	