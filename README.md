@mainpage
# EPL232 - Assignment 3 - Latin Square Solver

## Overview
A collaborative project by Panagiotis Tsembekis (UC1070326) and Rafael Tsekouronas (UC1070153).

This project implements a backtracking algorithm using a stack to solve the Latin Square puzzle. A Latin Square is an \( n \times n \) grid where each row and column contains the numbers from 1 to \( n \) exactly once. The program reads an initial puzzle configuration from a file, solves it, and outputs the solution step-by-step.

---

## Features
- Backtracking algorithm for puzzle solving.
- Dynamically allocated 2D arrays for grid representation.
- Stack-based backtracking to explore possible solutions.
- Handles puzzles of various sizes as specified in the input file.
- Reports all memory usage and leaks using `valgrind`.
- Modular structure with separate `.c` and `.h` files for:
  - Stack management.
  - File handling.
  - Solver logic.
- Clear and informative error messages and outputs.
- Handling of invalid .txt files passed in arguments for initial tableau.

---

## File Structure
### Source Files
- **`file.c` / `file.h`**: Handles reading the puzzle from a file and memory management of dynamic arrays.
- **`stack.c` / `stack.h`**: Manages the stack operations (push, pop, and memory deallocation).
- **`solver.c` / `solver.h`**: Implements the backtracking algorithm to solve the Latin Square.
- **`latinSolver.c`**: Contains the main function and integrates the modules.

### Input Files (Testers)
- **`lsq2.txt`**: Another example input file for a 4x4 Latin Square.
  ```text
  4
  0 0 0 -4
  0 -2 0 0
  0 0 0 0
  0 0 0 -2
  ```
- **`lsq3.txt`**: Example input file for a 4x4 Latin Square with some cells pre-filled.
  ```text
  7
  0 0 0 -4 0 -6 0
  0 -2 0 0 -1 -7 0
  0 -1 0 0 0 -3 0
  0 0 0 -2 0 0 0
  -6 -4 0 0 0 0 -1
  0 0 0 0 0 0 0
  -1 0 0 0 -5 0 -7
  ```

### Output
- The program prints the step-by-step solution to the console, including:
  - Current grid state for each step.
  - Push and pop operations on the stack.
  - Number of total `push` and `pop` operations performed when the puzzle is solved.

---

## Compilation and Execution
### Compilation
To compile the program, use the provided `Makefile`:
```bash
make
```

### Execution
Run the solver with an input file:
```bash
./latinSolver <input_file.txt>
```
Example:
```bash
./latinSolver lsq1.txt
```

---

## Memory Management
All dynamically allocated memory is freed before program termination. Use `valgrind` to verify memory safety:
```bash
valgrind --leak-check=full ./latinSolver <input_file>
```

---

## Doxygen Documentation
Doxygen comments are included throughout the source files. To generate documentation:
1. Run the following command:
   ```bash
   doxygen Doxyfile
   ```
2. Open the `html/index.html` file in your browser for detailed documentation.

---

## Example Outputs
### Input (`lsq1.txt`):
```text
4
0 -2 0 -4
-2 -3 0 0
0 0 -1 -2
0 0 0 -3
```
### Output:
```text
PUSH: STEP 1
+-----+-----+-----+-----+
|  1  | (2) |  0  | (4) |
+-----+-----+-----+-----+
...

Congrats! Puzzle solved!
PUSH NUM: 9
POP NUM: 0
```

---

## Testing
Test the solver with provided input files (`lsq2.txt` and `lsq3.txt`) or create your own. Ensure the input format matches:
1. The first line specifies the size \( n \) of the grid.
2. Subsequent lines contain \( n \) integers per line, separated by spaces.

---