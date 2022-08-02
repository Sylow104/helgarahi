#pragma once
#ifdef __cplusplus
extern "C" {
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdbool.h>
#include <zip.h>
#include <expat.h>

// forward delcaration for parent structure
typedef struct xlsx xlsx_t;

// xml def and functions
typedef struct xml
{
	char *buffer;
	zip_uint64_t read_size, buffer_size;
} xml_t;
xml_t *xml_load(const char *file, zip_t *zip);
int xml_free(xml_t *obj);


// cell def and functions
typedef struct cell
{
	char *content;
} cell_t;

// sheet def and functions
typedef struct sheet
{
	cell_t *cells;
	size_t num_rows;
	size_t num_cols;
} sheet_t;

typedef struct workbook
{
	sheet_t *sheets;
	size_t num_sheets;
} workbook_t;
int workbook_generate(xlsx_t *target);


// xlsx def and functions
typedef struct xlsx
{
	zip_t *zip;
	workbook_t workbook;
} xlsx_t;
xlsx_t *xlsx_open(const char *filename);
int xlsx_close(xlsx_t *obj);

#ifdef __cplusplus
}
#endif