#pragma once
#include "header.hpp"
#include "row.hpp"
#include <stdint.h>

class sheet
{
	public:
	sheet(const char *buffer, uint64_t size);
	~sheet();

	void print_column(size_t index);
	header *_header = 0x0;

	row *operator[](size_t index);

	protected:

	private:
	
	row *data = 0x0;
};