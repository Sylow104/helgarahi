#include "xml.h"
#include <math.h>


xmlNodePtr search_children(xmlNodePtr node, const char *name)
{
	xmlNodePtr to_ret = 0x0;
	xmlNodePtr cur;

	cur = node;
	while (cur) {
		if (!xmlStrcmp(cur->name, (xmlChar *) name)) {
			to_ret = cur;
			break;
		}
		cur = cur->children;
	}

	return to_ret;
}

xmlNodePtr search_layer(xmlNodePtr layer, const char *name)
{
	xmlNodePtr to_ret = 0x0;
	xmlNodePtr cur;

	cur = layer;
	while (cur) {
		if (!xmlStrcmp(cur->name, (xmlChar *) name)) {
			to_ret = cur;
			break;
		}
		cur = cur->next;
	}

	return to_ret;
}

int count_children(xmlNodePtr layer, const char *name)
{
	xmlNodePtr cur = layer->children;
	int to_ret = 0;
	while(cur) {
		if (!xmlStrcmp(cur->name, (xmlChar *) name)) {
			to_ret++;
		}
		cur = cur->next;
	}

	return to_ret;
}

int letter_to_x(const char *region, size_t size)
{
	int to_ret = 0;
	int letter_val = 0;

	for (int i = size; i > 0; i--) {
		letter_val = region[i - 1] - 'A' + 1;
		to_ret += ((int) pow(26, size - i)) * letter_val;
	}

	return to_ret;
}

struct cell_coord cell_coordinates(const char *coordinate)
{
	char *ptr = (char*) coordinate;
	int letter_count = 0;
	char *number = (char *) coordinate;
	struct cell_coord to_ret;
	// check if valid
	while (*ptr >= 'A' && *ptr <= 'Z') {
		ptr++;
		letter_count++;
	}

	to_ret.x = letter_to_x(coordinate, letter_count);
	to_ret.y = strtol(ptr, 0x0, 0);

	return to_ret;
}