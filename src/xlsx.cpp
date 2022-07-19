#include "xlsx.hpp"
#include <libxml2/libxml/parser.h>

xlsx::xlsx()
{
	;
}

int xlsx::open(const char *filename)
{
	int ret_code;
	if (_zip) {
		return -1;
	}
	_zip = zip_open(filename, ZIP_RDONLY, &ret_code);
	return ret_code;
}

/* count amount of sheets and store them in memory */
int xlsx::analyze()
{
	int ret_code = 0;
	zip_stat_t stat;
	char *xml_raw;
	zip_file_t *info;
	zip_uint64_t read_size;

	ret_code = zip_stat(_zip, "xl/workbook.xml", 0, &stat);
	if (ret_code) {
		throw -1;
	}
	xml_raw = new char[stat.size + 1];

	info = zip_fopen(_zip, "xl/workbook.xml", 0);
	if (!info) {
		throw -2;
	}

	read_size = zip_fread(info, xml_raw, stat.size);
	if (read_size != stat.size) {
		throw -3;
	}
	
	{
		// read xml file and count number of sheets
		xmlDocPtr ptr = xmlParseMemory(xml_raw, stat.size);
		xmlNodePtr cur;
		xmlAttrPtr attr;
		if (!ptr) {
			throw -4;
		}

		cur = xmlDocGetRootElement(ptr);
		if (xmlStrcmp(cur->name, (xmlChar *) "workbook")) {
			throw -5;
		}
		cur = cur->children;

		sheet_info *cur_sheet, *prev_sheet = 0x0;

		xmlChar *key;
		xmlChar *value;

		while (cur) {
			if (!xmlStrcmp(cur->name, (xmlChar *) "sheets")) {
				printf("%s\n", xmlGetProp(cur, (xmlChar *) "name"));
			}
			cur = cur->next;
		}

		// cleanup
		xmlFreeDoc(ptr);
	}
	delete[] xml_raw;
	zip_fclose(info);
	return 0;
}

sheet *xlsx::get_sheet(size_t index)
{
	return 0x0;
}

xlsx::~xlsx()
{
	if (_zip) {
		zip_close(_zip);
	}
}