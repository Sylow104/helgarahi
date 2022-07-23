#include "cell.hpp"
#include <string.h>

cell::cell()
{
	;
}

cell::~cell()
{
	if (contents) {
		free(contents);
	}
}

int cell::init(xmlNodePtr node, h_entry *col)
{
	header_col = (h_entry *) col;
	xmlNodePtr target = search_children(node, "t");
	if (target) {
		type = CE_TEXT;
	} else {
		target = search_children(node, "v");
		if (target) {
			type = CE_NUMBER;
		} else {
			return -1;
		}
	}
	if (target->children) {
		set((char *) target->children->content);
	} else {
		type = CE_UNK;
	}
	
	if (!col->head) {
		col->head = this;
		col->tail = this;
	} else {
		col->tail->next = this;
		col->tail = this;
	}

	
	return 0;
}

void cell::set(const char *to_use)
{
	if (!to_use) {
		contents = 0x0;
		return;
	}
	contents = strdup(to_use);

	return;
}
