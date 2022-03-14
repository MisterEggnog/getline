#ifndef INCLUDE_GETLINE_H_C
#define INCLUDE_GETLINE_H_C

#if __unix__

#include <unistd.h>

#else // not __unix__

#include <stdint.h>

typedef ssize_t intmax_t;

#endif // __unix__


#include <stdio.h>

#define getline getline_shim

ssize_t getline_shim(char** lineptr, size_t* n, FILE* stream);

#endif // INCLUDE_GETLINE_H_C
