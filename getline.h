
#ifndef INCLUDE_GETLINE_H_C
#define INCLUDE_GETLINE_H_C

#if __unix__

#include <unistd.h>

#else // __unix__

#include <stdint.h>

// #include <limits.h>
// #if SIZE_WIDTH == BITS_WIDTH
// typedef ssize_t intBITS_t;

typedef ssize_t intmax_t;

#ifndef GETLINE_DOES_NOT_EXIST
#	define GETLINE_DOES_NOT_EXIST
#endif // GETLINE_DOES_NOT_EXIST

#endif // __unix__


#ifdef GETLINE_DOES_NOT_EXIST

#include <stdio.h>

ssize_t getline(char** lineptr, size_t* n, FILE* stream);

#endif // GETLINE_DOES_NOT_EXIST

#endif // INCLUDE_GETLINE_H_C
