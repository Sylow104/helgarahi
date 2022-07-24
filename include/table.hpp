#pragma once
#include "sheet.hpp"

enum flags_e
{
	NONE,
	EXCEL_DATE
};

struct merge_point
{
	int main_index;
	int aux_index;
};

struct column
{
	sheet *src;
	size_t index;
	flags_e flags;
};

class table
{
	public:
	table(sheet *main, sheet *aux);

	merge_point relation(const char *main_column, const char *aux_column);

	table(size_t num_columns);
	~table();

	void add_column(sheet *src, size_t src_index, flags_e flags = NONE);
	void add_column(sheet *src, const char *name, flags_e flags = NONE);

	protected:

	private:
	column *columns;

	static int find_index(sheet *to_check, const char *column); 
	sheet *_main, *_aux;
};