#include "header.hpp"
#include <string.h>

h_entry::h_entry()
{
	;
}

h_entry::~h_entry()
{
	if (_column) {
		free(_column);
	}
}

void h_entry::set(xmlNodePtr node)
{
	xmlNodePtr target = search_children(node, "t");
	if (target) {
		if (target->children) {
			_column = strdup((char *) target->children->content);
		}
		else {
			throw -2;
		}
	} else {
		throw -1;
	}
}


header::header(xmlNodePtr node)
{
	num_entries = count_layer(node->children, "c");
	if (num_entries < 1) {
		throw -10;
	}

	columns = new h_entry[num_entries];

	xmlNodePtr cur = search_layer(node->children, "c");

	for (int i = 0; i < num_entries; i++) {
		columns[i].set(cur);
		cur = search_layer(cur, "c");
		if (!cur) {
			throw -11;
		}
	}

}

const h_entry *header::operator[](size_t index)
{
	return &columns[index];
}

header::~header()
{
	delete[] columns;
}