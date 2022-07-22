#pragma once
#include "header.hpp"
#include "row.hpp"
#include <stdint.h>

class sheet
{
	public:
	sheet(const char *buffer, uint64_t size);
	~sheet();

	protected:

	private:
	xmlDocPtr root;
	header *_header = 0x0;
	row *data = 0x0;
};