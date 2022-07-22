#pragma once
#include "xml.h"

enum cell_e
{
	CE_UNK,
	CE_TEXT,
	CE_NUMBER
};

class cell_t
{
	protected:
	cell_e type = CE_UNK;
	void *contents = 0x0;

	public:
	const char *get();
	void print();
};

class cell : public cell_t
{
	public:
	cell(xmlNodePtr node);
	cell(xmlNodePtr node, cell *previous);
	~cell();

	protected:

	private:
	xmlNodePtr _cell;
	cell *next = 0x0;
};