#include <string.h>
#include <stdlib.h>
#include "getline.h"

#define LINE_SIZE 85

ssize_t
getline_shim(char** lineptr, size_t* n, FILE* stream) {
	char in_line[LINE_SIZE] = "";
	void* result = NULL;
	size_t read_length = 0;

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

		strcpy(*lineptr, in_line);
		read_length = strlen(*lineptr);
	} while (feof(stream) == 0 && *lineptr[read_length - 1] != '\n');


	return read_length;
}
