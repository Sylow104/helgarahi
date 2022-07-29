#pragma once
#ifdef __cplusplus
extern "C" {
#endif
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <zip.h>
#include <sqlite3.h>
#include <csv.h>

// forward delcaration for parent structure
typedef struct row row_t;
typedef struct sheet sheet_t;
typedef struct xlsx xlsx_t;

// xml def and functions
typedef struct xml
{
	char *buffer;
	size_t size;
} xml_t;


// cell def and functions
typedef struct cell
{
	char *contents;
	row_t *parent;
} cell_t;


// row def and functions
typedef struct row
{
	cell_t *cells;
	sheet_t *parent;
} row_t;


// sheet def and functions
typedef struct sheet
{
	row_t *rows;
	size_t num_rows;
	size_t num_cols;
	xlsx_t *parent;
} sheet_t;

int sheet_destroy(sheet_t *obj);


// xlsx def and functions
typedef struct xlsx
{
	zip_t *zip;
	sheet_t *sheets;
	size_t num_sheets;
} xlsx_t;
xlsx_t *xlsx_open(const char *filename);
int xlsx_close(xlsx_t *obj);

#ifdef __cplusplus
}
#endif