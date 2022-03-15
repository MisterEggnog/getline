#include <acutest.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "getline.h"

#define LINE_LEN 85

void
getline_basic(void) {
	char exp[] = "Tiwlers\n";
	size_t line_len = LINE_LEN;
	char* out = malloc(line_len);
	FILE* tmp_out = tmpfile();

	fputs(exp, tmp_out);
	rewind(tmp_out);

	getline(&out, &line_len, tmp_out);

	TEST_CHECK(strcmp(exp, out) == 0);

	fclose(tmp_out);
	free(out);
}

TEST_LIST = {
	{ "Basic usage", getline_basic },
	{ NULL, NULL },
};
