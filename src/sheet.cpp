#include "sheet.hpp"
#include <string.h>

int gen_row_list(xmlNodePtr layer, xmlNodePtr *out)
{
	int num_entries = count_children(layer, "row");
	xmlNodePtr cur;
	if (num_entries < 1) {
		return -1;
	}
	out = new xmlNodePtr[num_entries];

	cur = search_layer(layer->children, "row");
	if (!cur) {
		return -2;
	}
	for (int i = 0; i < num_entries; i++) {
		out[i] = cur;
		cur = cur->next;
	}

	return num_entries;
}

sheet::sheet(const char *buffer, uint64_t size)
{
	root = xmlParseMemory(buffer, size);
	xmlNodePtr node_root = xmlDocGetRootElement(root);
	xmlNodePtr sheet_data = search_layer(node_root, "sheetData");

	// generate rows
	row *cur;
	row *prev = 0x0;
	xmlNodePtr *list;
	int num_entries = gen_row_list(sheet_data, list);
	if (num_entries < 0) {
		throw 1;
	}

	for (int i = 0; i < num_entries; i++) {
		cur = new row{list[i], prev, i};
		prev = cur;
	}


	delete list;  
}

sheet::~sheet()
{
	xmlFreeDoc(root);
}

