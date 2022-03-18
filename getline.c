#include <string.h>
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

		strcpy(*lineptr, in_line);
		read_length = strlen(*lineptr);
	} while (feof(stream) == 0 && *lineptr[read_length] != '\n');


	return read_length;
}
