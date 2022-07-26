#include "table.hpp"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

table::table(const char *name, const char *xml_buffer, uint64_t size) :
	sheet(xml_buffer, size)
{
	columns = new column_t[num_columns];
	this->name = strdup(name);
}

table::~table()
{
	delete[] columns;
	free(this->name);
}

int table::add_column(const char *target, transform_e in_flags)
{
	ssize_t index = find_header(target);

	if (index < 0) {
		return -1;
	}
	columns[num_selected].index = index;
	columns[num_selected].type = column_type(index);
	switch (columns[num_selected].type) {
		case CE_MIXED:
		case CE_NONE:
			columns[num_selected].type = CE_TEXT;
			break;
	}
	

	switch (in_flags) {
		case T_IS_DATE:
			excel_date_to_unix(index);
		case T_IS_NUMBER:
			exponential_to_int(index);
		case T_PRIMARY_KEY:
			columns[num_selected].primary_key = true;
		default:
			break;
	}
	num_selected++;
	
	return 0;
}

int table::import_schema(sqlite3 *db)
{
	sqlite3_stmt *stmt;
	char buffer[128];
	if (num_selected < 1) {
		return -1;
	}
	int primary_key_index = -1;

	strcpy(buffer, "create table if not exists ");
	strcat(buffer, name);
	strcat(buffer, " (");
	for (size_t i = 0; i < num_selected; i++) {
		cell *cur = (cell *) &header[columns[i].index];
		strcat(buffer, cur->content);
		switch (columns[i].type) {
			case CE_NONE:
			case CE_TEXT:
			case CE_MIXED:
				strcat(buffer, " text");
				break;
			case CE_NUM:
				strcat(buffer, " int");
				break;
			default:
				throw 1;
		}
		if (columns[i].primary_key) {
			primary_key_index = columns[i].index;
		}
		if (i + 1 < num_selected) {
			strcat(buffer, ", ");
		}
	}
	if (primary_key_index > -1) {
		strcat(buffer, ", primary key (");
		strcat(buffer, header[primary_key_index].content);
		strcat(buffer, ")");
	}
	strcat(buffer, ");");
#ifndef NDEBUG
	printf("Create sql: %s\n", buffer);
#endif
	sqlite3_prepare(db, buffer, -1, &stmt, 0x0);
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);
	return 0; 
}

int table::import_data(sqlite3 *db)
{
	char buffer[512];
	sqlite3_stmt *stmt;
	int ret_code = 0;
	char *debug = 0x0;

	strcpy(buffer, "insert into ");
	strcat(buffer, name);
	strcat(buffer, " values (");
	for (size_t j = 0; j < num_selected; j++) {
		strcat(buffer, "?");
		if (j + 1 < num_selected) {
			strcat(buffer, ",");
		}
	}
	strcat(buffer, ");");
	ret_code = sqlite3_prepare(db, buffer, -1, &stmt, 0x0);

	if (ret_code) {
		return ret_code;
	}

	for (size_t i = 1; i < num_rows; i++) {
		cell *row = cells[i];
		for (size_t j = 0; j < num_selected; j++) {
			ret_code = sqlite3_bind_text(stmt, j + 1, 
				row[columns[j].index].content, -1, 0x0);
			if (ret_code) {
				goto exit;
			}
		}
#ifndef NDEBUG
		debug = sqlite3_expanded_sql(stmt);
		printf("Current SQL Statement: %s\n", 
				debug);
		if (debug) {
			sqlite3_free(debug);
		}
#endif
		ret_code = sqlite3_step(stmt);
		if (ret_code != SQLITE_DONE) {
			// usually primary key constraint error
			printf("PKey: constraint error on row %d\n", i);
		} 
		sqlite3_reset(stmt);
		sqlite3_clear_bindings(stmt);
	};

	
exit:
	sqlite3_finalize(stmt);
	return ret_code;
}