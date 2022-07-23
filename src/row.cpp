#include "row.hpp"

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

int row::init(xmlNodePtr node, size_t num_cells, sheet *parent, header *head)
{
	top = new cell[num_cells];
	cell *cur;
	xmlNodePtr cur_node = search_layer(node->children, "c");
	this->parent = parent;
	for (size_t i = 0; i < num_cells; i++) {
		if (top[i].init(cur_node, (*head)[i])) {
			return -1;
		}
		cur_node = search_layer(cur_node->next, "c");
	}
	return 0;
}


