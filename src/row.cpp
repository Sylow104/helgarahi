#include "row.hpp"

row::row(xmlNodePtr node, row *previous, int index)
{
	previous->next = this;
	_row = node;
	_index = index;
}

row::~row()
{
	;
}