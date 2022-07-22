#pragma once
#include "cell.hpp"

class row
{
	public:
	row(xmlNodePtr node, row *previous, int index);
	~row();

	protected:

	private:
	int _index;

	row *next = 0x0;
	cell *head = 0x0;
};