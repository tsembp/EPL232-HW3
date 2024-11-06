#ifndef SOLVER_H
#define SOLVER_H
#include "stack.h"
#include "file.h"

bool puzzleSolver(STACK *stack, int **square, int size);

/**
 * Checks if placing a number at the given row and column is valid in the current Latin square.
 *
 * @param square The current state of the Latin square as a 2D array.
 * @param row The row in which the number is to be placed.
 * @param col The column in which the number is to be placed.
 * @param num The number to check.
 * @param size The size of the Latin square (n x n).
 * @return true if placing the number does not violate any rules, false otherwise.
 */
bool isSafe(int **square, int row, int col, int num, int size);

/**
 * Finds the next empty position in the Latin square.
 *
 * @param square The current state of the Latin square as a 2D array.
 * @param size The size of the Latin square (n x n).
 * @param row Pointer to store the row of the next empty position.
 * @param col Pointer to store the column of the next empty position.
 * @return true if an empty position is found, false if the Latin square is complete.
 */
bool findEmptyPosition(int **square, int size, int *row, int *col);

#endif // SOLVER_H