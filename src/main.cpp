#include "xlsx.hpp"
#include "xml.h"
int main(int argc, const char *argv[])
{
	xlsx file;

	file.open(argv[1]);
	file.analyze();

	sheet *test = file.get_sheet(1);
	sheet *best = file.get_sheet(2);
	delete test;
	delete best;
	return 0;
}