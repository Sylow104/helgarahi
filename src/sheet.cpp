#include "sheet.hpp"
#include <string.h>

sheet::sheet(const char *buffer, uint64_t size)
{
	root = xmlParseMemory(buffer, size);
	xmlNodePtr node_root = xmlDocGetRootElement(root);
	xmlNodePtr tmp = search_layer(node_root, "worksheet");
	xmlNodePtr sheet_data = search_layer(tmp->children, "sheetData");

	// generate rows
	row *cur;
	row *prev = 0x0;
	xmlNodePtr load_data;

	load_data = search_layer(sheet_data->children, "row");
	if (!load_data) {
		throw -2;
	}
	_header = new header{load_data};


	load_data = search_layer(load_data->next, "row");

	int i = 1;
	while (load_data) {
		cur = new row{load_data, prev, i};
		if (!data) {
			data = cur;
		}
		prev = cur;
		load_data = search_layer(load_data->next, "row");
		i++;
	}
	xmlFreeDoc(root);
}

sheet::~sheet()
{
	delete _header;
	delete data;
}

