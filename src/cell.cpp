#include "cell.hpp"
#include <string.h>

cell::cell(xmlNodePtr node, cell *previous)
{
	if (previous) {
		previous->next = this;
	}

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
		set((char *) target->children->content);
	} else {
		type = CE_UNK;
	}
}

cell::~cell()
{
	if (next) {
		delete next;
	}
}

/*
void cell_t::print()
{
	switch (type) {
		case CE_UNK:
			printf("No value\n");
			break;
		case CE_NUMBER:
			printf("Float value: %s\n", contents);
			break;
		case CE_TEXT:
			printf("String value: %s\n", (char *) contents);
			break;
	}
	
}
*/

void cell_t::set(const char *to_use)
{
	if (!to_use) {
		contents = 0x0;
		return;
	}
	contents = strdup(to_use);

	return;
}

cell_t::~cell_t()
{
	if (contents) {
		free(contents);
	}
}
