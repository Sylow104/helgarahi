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
	public:
	const char *get();
	cell_e type;

	protected:
	~cell_t();
	void set(const char *to_use);

	private:
	char *contents = 0x0;
};

class cell : public cell_t
{
	public:
	cell(xmlNodePtr node);
	cell(xmlNodePtr node, cell *previous);
	~cell();

	protected:

	private:
	cell *next = 0x0;
};
