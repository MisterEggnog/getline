#include <string.h>
#include "getline.h"

#define LINE_SIZE 85

ssize_t
getline_shim(char** lineptr, size_t* n, FILE* stream) {
	char in_line[LINE_SIZE] = "";

	if (fgets(in_line, sizeof in_line, stream) == NULL && strlen(in_line) == 0) {
		**lineptr = '\0';
		return -1;
	}

	strcpy(*lineptr, in_line);

	return strlen(*lineptr);
}
