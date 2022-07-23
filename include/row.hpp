#pragma once
#include "cell.hpp"

class sheet;

class row
{
	public:
	row();
	~row();

	int init(xmlNodePtr node, size_t num_cells, sheet *parent, 
		header *head);

	protected:

	private:

	cell *top;
	sheet *parent;
};