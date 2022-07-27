#pragma once
#include "sheet.hpp"
#include <sqlite3.h>

enum transform_e
{
	T_NONE,
	T_IS_DATE,
	T_IS_NUMBER,
	T_PRIMARY_KEY
};

struct column_t
{
	size_t index;
	cell_e type;
	bool primary_key = false;
};

struct table : protected sheet
{
	table(const char *name, const char *xml_buffer, uint64_t size);
	~table();

	int add_column(const char *target, transform_e flags);
	int add_all();
	int edit_column(const char *target, transform_e flags);
	int import_schema(sqlite3 *db);
	int import_data(sqlite3 *db);
	
	private:
	ssize_t search(const char *target);
	int edit_column(size_t index, transform_e in_flags);
	int add_column(size_t index, transform_e flags);
	column_t *columns;
	size_t num_selected = 0;
	char *name;
};