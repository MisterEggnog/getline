#include <string.h>
#include <stdlib.h>
#include "getline.h"

#define LINE_SIZE 85

ssize_t
getline_shim(char** lineptr, size_t* n, FILE* stream) {
	char in_line[LINE_SIZE];
	*in_line = '\0';
	void* result = NULL;
	size_t read_length = 0;

	if ((*lineptr == NULL) ^ (*n == 0)) {
		// No definition in the gnu c documentation about what to do in this context.
		fprintf(stderr, "%s passed lineptr (%p) & n (%zd)\n", __func__, *lineptr, *n);
		fprintf(stderr, "This should be NULL & 0.\n");
		return -1;
	}

	do {
		result = fgets(in_line, sizeof in_line, stream);

		if (result == NULL && strlen(in_line) == 0) {
			**lineptr = '\0';
			return -1;
		}

		if (read_length + strlen(in_line) >= *n) {
			size_t new_len = read_length + strlen(in_line) + 1;
			char* new_line = realloc(*lineptr, new_len);
			if (new_line == NULL) {
				return -1;
			}
			*lineptr = new_line;
			*n = new_len;
		}

		strcpy(*lineptr + read_length, in_line);
		read_length = strlen(*lineptr);
	} while (feof(stream) == 0 && (*lineptr)[read_length - 1] != '\n');


	return read_length;
}
