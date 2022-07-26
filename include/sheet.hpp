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
	cell_e column_type(size_t column);

	int rename(const char *to, const char *target);

	// find and replace
	
	int excel_date_to_unix(const char *label);
	int exponential_to_int(const char *label);

	private:
	int double_to_int(const char *label, double (callback)(double));
	ssize_t find_header(const char *label);
};
