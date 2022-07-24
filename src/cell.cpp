#include "cell.hpp"
#include <string.h>

cell::cell()
{
	;
}

cell::~cell()
{
	if (content) {
		free(content);
	}
}

int cell::set(xmlNodePtr node)
{
	xmlNodePtr target = search_children(node, "t");
	if (target) {
		type = CE_TEXT;
	} else {
		target = search_children(node, "v");
		if (target) {
			type = CE_NUM;
		} else {
			throw -1;
		}
	}
	if (!target->children) {
		return 1;
	}

	content = strdup((char *) target->children->content);

	return 0;
}