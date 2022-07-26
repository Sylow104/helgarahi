#include "xlsx.hpp"


int main(int argc, const char *argv[])
{
	xlsx file;

	file.open(argv[1]);
	file.analyze();

	table *test = file.get_table("test", 1);
	table *best = file.get_table("best", 2);

	test->add_column("Code", T_NONE);
	test->add_column("Appointment", T_IS_DATE);

	char *create_sql = test->create();
	printf("SQL Statement created: %s\n", create_sql);
	delete[] create_sql;
	delete test;
	delete best;
	return 0;
}