#include "xlsx.hpp"


int main(int argc, const char *argv[])
{
	xlsx file;

	file.open(argv[1]);
	file.analyze();

	sheet *test = file.get_sheet(1);
	sheet *best = file.get_sheet(2);
	//test->print_column(1);
	//auto rest = (*test)[0][0];
	test->print_header();
	for (size_t j = 0; j < test->num_columns; j++) {
		test->column_type(j);
	}
	test->rename("Internal Code", "Code");
	test->print_header();
	delete test;
	delete best;
	return 0;
}