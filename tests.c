// For reference
// https://www.gnu.org/software/libc/manual/html_mono/libc.html#Line-Input
#include <acutest.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
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

	TEST_CHECK(chars_read == (sizeof exp - 1));
	TEST_MSG("getline returned %ld, rather than %ld", chars_read, (sizeof exp - 1));

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

void
getline_reallocates(void) {
	char original[] = "aaaaaaaaaaaaaaaaaaaaaaa";
	size_t line_len = 5;
	char* out = malloc(line_len);
	FILE* file = tmpfile();

	fputs(original, file);
	rewind(file);

	getline(&out, &line_len, file);

	TEST_CHECK(line_len >= sizeof original);
	TEST_MSG("Orig %zd, dest %zd", sizeof original, line_len);

	fclose(file);
	free(out);
}

void
getline_larger_then_intern_buffer(void) {
	char source[200];
	for (unsigned i = 0; i < sizeof source; i++)
		source[i] = 'c';
	source[sizeof source - 2] = '\n';
	source[sizeof source - 1] = '\0';
	size_t line_len = LINE_LEN;
	char* out = malloc(line_len);
	FILE* file = tmpfile();

	fputs(source, file);
	rewind(file);

	getline(&out, &line_len, file);

	TEST_CHECK(strcmp(source, out) == 0);
	TEST_MSG("Src: %s : dest: %s", source, out);

	fclose(file);
	free(out);
}

void
getline_allocates_on_null(void) {
	char source[] = "pizza pizza pizza pizzzzzzzzzzzaeps";
	size_t line_len = 0;
	char* out = NULL;
	FILE* file = tmpfile();

	fputs(source, file);
	rewind(file);

	getline(&out, &line_len, file);

	TEST_CHECK(strcmp(source, out) == 0);
	TEST_MSG("Src: %s : dest: %s", source, out);

	fclose(file);
	free(out);
}

void
getline_gives_error_lineptr_null_but_n_not_0(void) {
	char source[] = "mike";
	size_t line_len = 666;
	char* out = NULL;
	FILE* file = tmpfile();

	fputs(source, file);
	rewind(file);

	intmax_t result = getline(&out, &line_len, file);
	TEST_CHECK(result < 0);
	TEST_MSG("result %s (" PRIdMAX ")", out, result);

	fclose(file);
}

void
getline_gives_error_n_0_but_lineptr_not_null(void) {
	char source[] = "mike";
	size_t line_len = 0;
	char* out = (char*)0x1;
	FILE* file = tmpfile();

	fputs(source, file);
	rewind(file);

	intmax_t result = getline(&out, &line_len, file);
	TEST_CHECK(result < 0);
	TEST_MSG("result %s (" PRIdMAX ")", out, result);

	fclose(file);
}

TEST_LIST = {
	{ "Basic usage", getline_basic },
	{ "getline fails for empty file input", getline_fails_with_no_input },
	{ "getline reallocs if dest buffer to small", getline_reallocates },
	{ "getline works for string larger than internal buffer", getline_larger_then_intern_buffer },
	{ "Allocates when passed null + 0", getline_allocates_on_null },
	{ "getline fails when passed null but !0", getline_gives_error_lineptr_null_but_n_not_0 },
	{ "getline fails when passed 0 but not null", getline_gives_error_n_0_but_lineptr_not_null },
	{ NULL, NULL },
};
