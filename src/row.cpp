#include "row.hpp"
#include "sheet.hpp"

row::row()
{
	;
}

row::~row()
{
	if (top) {
		delete[] top;
	}
}

int row::init(xmlNodePtr node, sheet *_parent)
{
	parent = _parent;
	top = new cell[parent->_header->num_entries];
	cell *cur;
	xmlNodePtr cur_node = search_layer(node->children, "c");
	for (size_t i = 0; i < parent->_header->num_entries; i++) {
		if (top[i].init(cur_node, (*parent->_header)[i])) {
			return -1;
		}
		cur_node = search_layer(cur_node->next, "c");
	}
	return 0;
}

cell *row::operator[](size_t index)
{
	return &top[index];
}