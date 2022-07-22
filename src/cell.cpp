#include "cell.hpp"

cell::cell(xmlNodePtr node, cell *previous)
{
	if (previous) {
		previous->next = this;
	}
	_cell = node;

	xmlNodePtr target = search_children(node, "t");
	if (target) {
		type = CE_TEXT;
	} else {
		target = search_children(node, "v");
		if (target) {
			type = CE_NUMBER;
		} else {
			throw 1;
		}
	}
	if (target->children) {
		contents = target->children->content;
	} else {
		type = CE_UNK;
	}
	print();
}

cell::~cell()
{
	if (next) {
		delete next;
	}
}

void cell_t::print()
{
	char *str;
	switch (type) {
		case CE_UNK:
			str = "No value\n";
			break;
		case CE_NUMBER:
			str = "Float value : %s\n";
			break;
		case CE_TEXT:
			str = "String value : %s\n";
			break;
	}
	printf(str, contents);
}