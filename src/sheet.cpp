#include "sheet.hpp"
#include <string.h>

sheet::sheet(const char *buffer, uint64_t size)
{
	root = xmlParseMemory(buffer, size);
}

sheet::~sheet()
{
	xmlFreeDoc(root);
}

