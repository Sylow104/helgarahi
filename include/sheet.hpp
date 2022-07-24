#pragma once
#include "cell.hpp"
#include <stdint.h>

struct sheet
{
	sheet(const char *xml_buffer, uint64_t size);
	~sheet();

	size_t num_columns;
	size_t num_rows;

	cell **cells;
	const cell *header;

	void print(bool row, size_t index);
	void print_header();
	int excel_date_to_unix(size_t column);
	cell_e column_type(size_t column);
};
