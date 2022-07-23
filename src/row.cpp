#include "row.hpp"

row::row(xmlNodePtr node, row *previous, int index)
{
	if (previous) {
		previous->next = this;
	}
	_index = index;
	int children = count_layer(node->children, "c");
	int i;
	cell *prev = 0x0;
	cell *cur;
	xmlNodePtr load_data = search_layer(node->children, "c");

	while (load_data) {
		cur = new cell(load_data, prev);
		if (!head) {
			head = cur;
		}
		prev = cur;
		load_data = search_layer(load_data->next, "c");
	}
}

row::row(size_t num_cells, sheet *parent)
{
	top = new cell[num_cells];
	this->parent = parent;
}

row::row()
{
	;
}

int row::init(xmlNodePtr node, size_t num_cells, sheet *parent, header *head)
{
	top = new cell[num_cells];
	cell *cur;
	xmlNodePtr cur_node = search_children(node, "c");
	this->parent = parent;
	for (size_t i = 0; i < num_cells; i++) {
		if (top[i].init(cur_node, (*head)[i])) {
			return -1;
		}
		cur_node = search_layer(node->next, "c");
	}
	return 0;
}


row::~row()
{
	if (next) {
		delete next;
	}
	if (head) {
		delete head;
	}
}

int row::set(xmlNodePtr node)
{
	xmlNodePtr cur = search_layer(node, "row");
	if (!node) {
		return -1;
	}

	for (size_t i = 0; i; i++) {
		;
	}

	return 0;
}