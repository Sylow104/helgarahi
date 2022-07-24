#pragma once
#ifdef __cplusplus
extern "C" {
#endif
#include <libxml/parser.h>

struct cell_coord
{
	size_t x;
	size_t y;
};

xmlNodePtr search_layer(xmlNodePtr layer, const char *name);
xmlNodePtr search_children(xmlNodePtr node, const char *name);
int count_layer(xmlNodePtr layer, const char *name);
struct cell_coord cell_coordinates(const char *coordinate);
int letter_to_x(const char *region, size_t size);
#ifdef __cplusplus
}
#endif