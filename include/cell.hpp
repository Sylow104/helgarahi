#pragma once
#include "xml.h"

enum cell_e
{
	CE_NONE,
	CE_TEXT,
	CE_NUM,
	CE_UNK
};

struct cell
{
	cell();
	~cell();

	int set(xmlNodePtr node);
	char *content = 0x0;
	cell_e type;
};