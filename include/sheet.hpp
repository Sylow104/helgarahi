#pragma once
#include "xml.h"
#include <stdint.h>

class sheet
{
	public:
	sheet(const char *buffer, uint64_t size);
	~sheet();

	protected:

	private:
	xmlDocPtr root;
};