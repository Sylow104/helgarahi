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
	cell(xmlNodePtr node, cell *previous);
	~cell();
	
	const char *get();
	cell_e type;

	protected:
	
	void set(const char *to_use);

	private:
	cell *next = 0x0;
	char *contents = 0x0;
};
