#pragma once
#include "sheet.hpp"


enum transform_e
{
	T_NONE,
	T_IS_DATE,
	T_IS_NUMBER
};

struct column_t
{
	size_t index;
	cell_e type;
};

struct table : protected sheet
{
	table(const char *name, const char *xml_buffer, uint64_t size);
	~table();

	int add_column(const char *target, transform_e flags);
	char *create();
	
	private:
	column_t *columns;
	size_t num_selected = 0;
	char *name;
};