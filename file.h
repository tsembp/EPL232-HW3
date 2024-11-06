#ifndef FILE_H
#define FILE_H
#include <stdio.h>
#include <stdlib.h>

int **readLatinSquare(const char *filename, int *size);
void free2DArray(int **array, int size);

#endif // FILE_H