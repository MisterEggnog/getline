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
	ssize_t chars_read;
	char* out = malloc(line_len);
	FILE* tmp_out = tmpfile();

	fputs(exp, tmp_out);
	rewind(tmp_out);

	chars_read = getline(&out, &line_len, tmp_out);

	TEST_CHECK(strcmp(exp, out) == 0);
	TEST_DUMP("Expected:", exp, sizeof exp);
	TEST_DUMP("Produced:", out, strlen(out));

	TEST_CHECK(chars_read == sizeof exp);
	TEST_MSG("getline returned %ld, rather than %ld", chars_read, sizeof exp);

	fclose(tmp_out);
	free(out);
}

void
getline_fails_with_no_input(void) {
	size_t line_len = LINE_LEN;
	char* out = malloc(line_len);
	FILE* tmp_out = tmpfile();

	ssize_t ret_code = getline(&out, &line_len, tmp_out);

	TEST_CHECK(ret_code == -1);
	TEST_MSG("getline did not return -1 for empty input.\n"
			 "returned %ld.", ret_code);

	fclose(tmp_out);
	free(out);
}

TEST_LIST = {
	{ "Basic usage", getline_basic },
	{ "getline fails for empty file input", getline_fails_with_no_input },
	{ NULL, NULL },
};
