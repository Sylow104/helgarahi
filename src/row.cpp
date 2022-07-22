#include "row.hpp"

row::row(xmlNodePtr node, row *previous, int index)
{
	if (previous) {
		previous->next = this;
	}
	_index = index;
	int children = count_children(node, "c");
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

row::~row()
{
	if (next) {
		delete next;
	}
	if (head) {
		delete head;
	}
}