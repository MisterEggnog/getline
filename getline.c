#include <string.h>
#include "getline.h"

#define LINE_SIZE 85

ssize_t
getline_shim(char** lineptr, size_t* n, FILE* stream) {
	char in_line[LINE_SIZE] = "";
	void* result;

	do {
		result = fgets(in_line, sizeof in_line, stream);

		if (result == NULL && strlen(in_line) == 0) {
			**lineptr = '\0';
			return -1;
		}

		strcpy(*lineptr, in_line);
	} while (feof(stream) == 0 && *lineptr[strlen(*lineptr)] != '\n');


	return strlen(*lineptr);
}
