/**
 * @file file.h
 *
 * @brief Header file for reading and managing a Latin square.
 *
 * This file contains function declarations for reading a Latin square from a file
 * and freeing a dynamically allocated 2D array used to store the Latin square data.
 *
 * @authors
 * - Panagiotis Tsembekis
 * - Rafael Tsekouronas
 */

#ifndef FILE_H
#define FILE_H
#include <stdio.h>
#include <stdlib.h>

#define N 9 /**< Maximum size of the Latin square */

/**
 * @brief Frees a dynamically allocated 2D array.
 *
 * This function deallocates memory for a 2D array of integers. It is
 * assumed that each row of the array was dynamically allocated separately.
 *
 * @param array A pointer to the 2D array to be freed.
 * @param size The number of rows in the array.
 */
void free2DArray(int **array, int size);

/**
 * @brief Reads a Latin square from a file.
 *
 * This function reads a Latin square from a given file. The file should contain
 * the size of the square (as the first integer) followed by the elements of the
 * square in row-major order. If an error occurs, such as invalid size or memory
 * allocation failure, the function returns NULL.
 *
 * @param filename The name of the file containing the Latin square.
 * @param size A pointer to an integer where the function will store the size
 *             of the Latin square upon successful read.
 *
 * @return A dynamically allocated 2D array representing the Latin square, or
 *         NULL if an error occurs.
 */
int **readLatinSquare(const char *filename, int *size);

#endif // FILE_H