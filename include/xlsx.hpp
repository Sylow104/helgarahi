#pragma once
#include "table.hpp"
#include <zip.h>

class xlsx
{
	public:
	xlsx();
	~xlsx();

	int open(const char *filename);
	int analyze();
	table *get_table(const char *name, size_t index);

	protected:

	private:
	zip_t *_zip = 0x0;
	int num_sheets = 0;
};
