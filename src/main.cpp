#include "xlsx.hpp"


int main(int argc, const char *argv[])
{
	xlsx file;
	sqlite3 *db;
	if (sqlite3_open("fish.db", &db)) {
		return -1;
	}
	sqlite3_extended_result_codes(db, 1);

	file.open(argv[1]);
	file.analyze();

	table *test = file.get_table("test", 1);
	table *best = file.get_table("best", 2);

	test->add_column("Code", T_NONE);
	test->add_column("Appointment", T_IS_DATE);
	if (test->import_schema(db)) {
		exit(-1);
	}
	if (test->import_data(db)) {
		exit(-2);
	}
	delete test;
	delete best;
	return sqlite3_close(db);
}