#include "sheet.hpp"
#include <string.h>

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
	header = cells[0];

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
		printf("%s\n", header[j].content);
	}
}

int sheet::double_to_int(size_t index, double (callback)(double)) {
	double in;
	long long out;
	char *tail;
	char **src_dest;

	for (size_t i = 0; i < num_rows; i++) {
		src_dest = &cells[i][index].content;
		if (!*src_dest) {
			continue;
		}
		in = strtod(*src_dest, &tail);
		if (*tail) {
			continue;
			// may need to throw here
		}
		if (callback) {
			out = (long long) callback(in);
		} else {
			out = (long long) in;
		}
		free(*src_dest);
		asprintf(src_dest, "%lld", out);
	}
	return 0;
}



double callback_time(double in) 
{
	return ((in - 25569) * 86400);
}

int sheet::excel_date_to_unix(size_t index)
{
	return double_to_int(index, callback_time);
}

int sheet::exponential_to_int(size_t index)
{
	return double_to_int(index, 0x0);
}


cell_e sheet::column_type(size_t column)
{
	cell_e to_ret;
	cell *cur;

	printf("Column: %s\n", cells[0][column].content);
	to_ret = cells[1][column].type;
	for (size_t i = 2; i < num_rows; i++) {
		cur = &cells[i][column];
		if (cur->type) {
			to_ret = (cell_e) ((int) to_ret | (int) cur->type);
		}
	}
	
	///*
	printf("Type: ");
	switch (to_ret) {
		case CE_NONE:
			printf("None\n");
			break;
		case CE_NUM:
			printf("Number\n");
			break;
		case CE_TEXT:
			printf("Text\n");
			break;
		case CE_MIXED:
			printf("Mixed\n");
			break;
		default:
			throw 2;
	}
	//*/

	return to_ret;
}

int sheet::rename(const char *to, const char *label)
{
	char **cur;
	ssize_t target = find_header(label);
	if (target < 0) {
		return -1;
	}

	cur = &cells[target]->content;

	free(*cur);

	asprintf(cur, "%s", to);

	printf("Renamed %s to %s\n", target, *cur);

	return 0;
}

ssize_t sheet::find_header(const char *label)
{
	ssize_t index = 0;
	for (size_t i = 0; i < num_columns; i++) {
		if (!strcmp(header[i].content, label)) {
			return i;
		}
	}

	return -1;
}