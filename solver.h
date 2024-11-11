/**
 * @file solver.h
 *
 * @brief Header file for the Latin square puzzle-solving algorithm.
 *
 * This file declares functions for solving a Latin square puzzle using backtracking.
 * It includes functions for placing numbers within the puzzle, checking the validity of
 * placements, and backtracking when necessary by using a stack.
 *
 * Authors:
 * - Panagiotis Tsembekis
 * - Rafael Tsekouronas
 */

#ifndef SOLVER_H
#define SOLVER_H
#include "stack.h"
#include "file.h"

/**
 * @brief Solves the Latin square puzzle using backtracking.
 *
 * Attempts to solve the Latin square by placing numbers in empty cells
 * while adhering to row and column uniqueness rules. If no valid placement
 * is possible, it backtracks by reverting to previous states in the stack.
 *
 * @param stack A stack used to store puzzle states for backtracking.
 * @param square The Latin square to be solved as a 2D array.
 * @param size The size of the Latin square (n x n).
 * @param numPush Pointer to an integer tracking the number of pushes to the stack.
 * @param numPop Pointer to an integer tracking the number of pops from the stack.
 *
 * @return `true` if the puzzle is solved, `false` if no solution exists.
 */
bool puzzleSolver(STACK *stack, int **square, int size, int *numPush, int *numPop);

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