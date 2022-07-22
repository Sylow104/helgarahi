#pragma once
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
	row *header = 0x0;
	row *data = 0x0;
};