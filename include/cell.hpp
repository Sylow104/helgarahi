#pragma once
#include "xml.h"

class h_entry;

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
	cell();
	~cell();
	
	const char *get();
	int init(xmlNodePtr node, const h_entry *col);
	cell_e type;

	protected:
	
	void set(const char *to_use);

	private:
	h_entry *header_col;
	cell *next = 0x0;
	char *contents = 0x0;
};
