#pragma once
#include "xml.h"

enum cell_e
{
	CE_NONE,
	CE_TEXT = 0b01,
	CE_NUM = 0b10,
	CE_MIXED = CE_TEXT | CE_NUM,
	CE_UNK = 0b100
};

struct cell
{
	cell();
	~cell();

	int set(xmlNodePtr node);
	char *content;
	cell_e type;
};