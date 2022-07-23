#include "sheet.hpp"
#include <string.h>

sheet::sheet(const char *buffer, uint64_t size)
{
	xmlDocPtr root = xmlParseMemory(buffer, size);
	xmlNodePtr load_data = xmlDocGetRootElement(root);

	if (!load_data) {
		throw -1;
	}
	load_data = search_layer(load_data, "worksheet");
	load_data = search_layer(load_data->children, "sheetData");

	/*
	xmlNodePtr node_root = xmlDocGetRootElement(root);
	xmlNodePtr tmp = search_layer(node_root, "worksheet");
	xmlNodePtr sheet_data = search_layer(tmp->children, "sheetData");
	*/

	// generate rows
	

	load_data = search_layer(load_data->children, "row");
	if (!load_data) {
		throw -2;
	}
	_header = new header{load_data};


	row_count = count_layer(load_data, "row");
	if (row_count < 1) {
		throw -3;
	}
	data = new row[row_count];

	load_data = search_layer(load_data->next, "row");
	for (size_t i = 0; i < row_count; i++) {
		if (data[i].init(load_data, row_count, this, _header)) {
			throw -4;
		}
		load_data = search_layer(load_data->next, "row");
	}
	/*

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
	*/
	xmlFreeDoc(root);
}

sheet::~sheet()
{
	delete _header;
	delete data;
}

