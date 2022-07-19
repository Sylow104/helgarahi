#include "xlsx.hpp"
#include "xml.h"
int main(int argc, const char *argv[])
{
	xlsx file;

	file.open(argv[1]);
	file.analyze();

	printf("%d hello\n", letter_to_x("ZZ", 2));
	cell_coord testing = cell_coordinates("A1");
	return 0;
}