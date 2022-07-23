#include "sheet.hpp"
#include <string.h>

sheet::sheet(const char *buffer, uint64_t size)
{
	xmlDocPtr root = xmlParseMemory(buffer, size);
	xmlNodePtr load_data = xmlDocGetRootElement(root);
	size_t row_count;

	if (!load_data) {
		throw -1;
	}
	load_data = search_layer(load_data, "worksheet");
	if (!load_data) {
		throw -2;
	}
	load_data = search_layer(load_data->children, "sheetData");
	if (!load_data) {
		throw -3;
	}
	

	load_data = search_layer(load_data->children, "row");
	if (!load_data) {
		throw -4;
	}
	_header = new header{load_data};


	row_count = count_layer(load_data->next, "row");
	if (row_count < 1) {
		throw -5;
	}
	data = new row[row_count];

	load_data = search_layer(load_data->next, "row");
	for (size_t i = 0; i < row_count; i++) {
		if (data[i].init(load_data, _header->num_entries, 
				this, _header)) {
			throw -6;
		}
		load_data = search_layer(load_data->next, "row");
	}

	xmlFreeDoc(root);
}

sheet::~sheet()
{
	delete _header;
	delete[] data;
}

