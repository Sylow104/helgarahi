#pragma once
#include "xml.h"

enum cell_e
{
	CE_UNK,
	CE_TEXT,
	CE_NUMBER
};

class cell
{
	public:
	cell(xmlNodePtr node);
	cell(xmlNodePtr node, cell *previous);
	~cell();

	protected:

	private:
	xmlNodePtr _cell;
	cell *next;
	cell_e type = CE_UNK;
};