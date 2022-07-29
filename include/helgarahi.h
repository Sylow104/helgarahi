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
#include <expat.h>

// forward delcaration for parent structure
typedef struct row row_t;
typedef struct sheet sheet_t;
typedef struct xlsx xlsx_t;

// tags and functions related to it
typedef struct tag
{
	char *name;
	int (*callback)(void *, void *);
} tag_t;

typedef struct tag_callback
{
	size_t num_tag;
	tag_t *tags;
} tag_callback_t; 

// xml def and functions
typedef struct xml
{
	char *buffer;
	zip_uint64_t size;
} xml_t;
xml_t *xml_load(const char *file, zip_t *zip);
int xml_free(xml_t *obj);


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
sheet_t *sheet_generate(zip_t *xlsx_file);
int sheet_destroy(sheet_t *obj);


typedef struct workbook
{
	sheet_t *sheets;
	size_t num_sheets;
} workbook_t;
workbook_t *workbook_generate(xlsx_t *target);

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