#pragma once
#include <zip.h>
#include <libxml/parser.h>

struct sheet_info
{
	char name[64];
	char filepath[64];
	sheet_info *prev = 0x0;
};

class sheet
{
	public:
	sheet(zip_t *zip_ref, const char *i_name, const char *filename);
	~sheet();

	protected:

	private:
	zip_file_t *_sheet;
	char *name;
	char *filepath;
};