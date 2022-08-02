#include <stdio.h>
#include "helgarahi.h"

int main(int argc, const char **argv)
{
	xlsx_t *to_use = xlsx_open(argv[1]);
	
	if (!to_use) {
		exit(-1);
	}

	workbook_generate(to_use);

	return xlsx_close(to_use);
}