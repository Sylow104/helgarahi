#pragma once
#include "cell.hpp"
#include "header.hpp"

class sheet;

class row
{
	public:
	row(xmlNodePtr node, row *previous, int index);
	row(size_t num_cells, sheet *parent);
	row();
	~row();

	int init(xmlNodePtr node, size_t num_cells, sheet *parent, 
		header *head);
	int set(xmlNodePtr node);

	protected:

	private:
	int _index;

	row *next = 0x0;
	cell *head = 0x0;

	cell *top;
	sheet *parent;
};