#include "header.hpp"
#include "cell.hpp"
#include <string.h>
#include <stdio.h>

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

void h_entry::print()
{
	printf("Header: %s\n", _column);
	cell *cur;
	for (cur = head; cur; cur = cur->next) {
		printf("%s\n", cur->get());
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
		cur = search_layer(cur->next, "c");
	}
}

h_entry *header::operator[](size_t index)
{
	return &columns[index];
}

header::~header()
{
	delete[] columns;
}