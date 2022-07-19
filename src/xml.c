#include "xml.h"
#include <math.h>


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

int cell_coordinates(const char *coordinate, struct cell *out)
{
	char *ptr = (char*) coordinate;
	int letter_count = 0;
	char *number = (char *) coordinate;
	// check if valid
	while (*ptr >= 'A' && *ptr <= 'Z') {
		ptr++;
		letter_count++;
	}

	out->x = letter_to_x(coordinate, letter_count);
	out->y = strtol(&ptr[letter_count], 0x0, 0);

	return 0;
}