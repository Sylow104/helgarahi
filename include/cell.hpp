#pragma once
#include "xml.h"
#include "header.hpp"

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
	cell();
	~cell();
	
	const char *get();
	int init(xmlNodePtr node, h_entry *col);
	cell *next = 0x0;

	protected:
	
	void set(const char *to_use);

	private:
	h_entry *header_col;
	cell_e type;
	char *contents = 0x0;
	
};
