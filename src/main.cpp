#include "xlsx.hpp"

int main(int argc, const char *argv[])
{
	xlsx file;

	file.open(argv[1]);
	file.analyze();
	return 0;
}