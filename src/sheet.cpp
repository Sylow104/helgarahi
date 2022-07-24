#include "sheet.hpp"

sheet::sheet(const char *xml_buffer, uint64_t size)
{
	xmlDocPtr root = xmlParseMemory(xml_buffer, size);
	xmlNodePtr load_data = xmlDocGetRootElement(root);
	xmlNodePtr row_data, column_data;
	size_t i, j;

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
	
	num_rows = count_layer(load_data, "row");
	num_columns = count_layer(load_data->children, "c");

	cells = new cell *[num_rows];

	row_data = load_data;
	for (i = 0; i < num_rows; i++) {
		cells[i] = new cell[num_columns];
		column_data = search_layer(row_data->children, "c");
		for (j = 0; j < num_columns; j++) {
			cells[i][j].set(column_data);
			column_data = search_layer(column_data->next, "c");
		}
		row_data = search_layer(row_data->next, "row");
	}
	header = cells[i];

	xmlFreeDoc(root);
}

sheet::~sheet()
{
	size_t i;
	for (i = 0; i < num_rows; i++) {
		delete[] cells[i];
	}
	delete[] cells;
}

void sheet::print_header()
{
	for (size_t j = 0; j < num_columns; j++) {
		printf("%s\n", cells[0][j].content);
	}
}