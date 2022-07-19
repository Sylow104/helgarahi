#include "sheet.hpp"
#include <string.h>

sheet::sheet(zip_t *zip_ref, const char *i_name, const char *i_filename)
{
	name = new char[64];
	filepath = new char[64];
	strncpy(name, i_name, 64);
	snprintf(filepath, 64, "xl/worksheets/%s.xml", i_filename);

	_sheet = zip_fopen(zip_ref, filepath, 0);
	if (!_sheet) {
		throw -1;
	} 
}



sheet::~sheet()
{
	if (_sheet) {
		zip_fclose(_sheet);
	}
}