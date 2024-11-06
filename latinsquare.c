/** 
 * @file latinsquare.c
 * @brief Implementation of a Latin Square game.
 * 
 * This file contains the core functionality for handling a Latin Square game.
 * It provides options to load a Latin Square from a file, display it, accept
 * user inputs to modify the square, and save the final state to a file.
 * 
 * @author  Panagiotis Tsembekis
 * @since   21/09/2024
 * @bug     No known bugs
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 9 /**< Maximum size of a Latin Square. */

/**
 * @brief Reads the Latin Square from a given file.
 * 
 * The function reads the size and values of a Latin Square from the input file.
 * It ensures that the file contains valid values and appropriate dimensions for the square.
 * 
 * @param filename The name of the input file containing the Latin Square.
 * @param square 2D array representing the Latin Square.
 * @param size Pointer to store the size of the Latin Square.
 */
void readLatinSquare(const char *filename, short square[N][N], int *size);

/**
 * @brief Displays the Latin Square in a formatted grid.
 * 
 * Prints the values of the Latin Square in a tabular format, highlighting pre-given values
 * using parentheses.
 * 
 * @param square 2D array representing the Latin Square.
 * @param size Size of the Latin Square.
 */
void displayLatinSquare(short square[N][N], int size);

/**
 * @brief Main function to play the Latin Square game.
 * 
 * This function serves as the main game loop, where user inputs are taken,
 * validated, and processed until the user chooses to exit or the game is completed.
 * 
 * @param square 2D array representing the Latin Square.
 * @param size Size of the Latin Square.
 * @param filename The name of the input file (used for saving state).
 */
void play(short square[N][N], int size, const char *filename);


/**
 * @brief Main entry point of the program.
 * 
 * This function initializes the game by loading the Latin Square from a file
 * and then starting the game loop.
 * 
 * @param argc Argument count.
 * @param argv Argument vector containing the filename.
 * @return EXIT_SUCCESS if the program completes successfully, otherwise EXIT_FAILURE.
 */
int main(int argc, char *argv[]){

    if(argc != 2){ // check if arguments contain 2 inputs, ./latinsquare and input file name
        printf("Missing arguments.\n");
        printf("Usage: ./latinsquares <game-file>\n");
        return EXIT_FAILURE;
    }

    const char *filename = argv[1]; // retrieve file name from arguments (2nd input)
    short square[N][N];
    int size;

    // Read values from file
    readLatinSquare(filename, square, &size);

    // Start game execution
    play(square, size, filename);

}

void readLatinSquare(const char *filename, short square[N][N], int *size){
    // Open file for reading
    FILE *fp = fopen(filename, "r");

    // Check file pointer
    if(fp == NULL){
        perror("Error occurred while attempting to read from file.\n");
        exit(EXIT_FAILURE); // exit
    }

    // Check n (size of latin square)
    if(fscanf(fp, "%d", size) != 1 || *size <= 0 || *size > N){ // check fscanf return code and size's value
        printf("Invalid size of Latin Square!\n");
        fclose(fp);
        exit(EXIT_FAILURE); // close file and exit
    }
    
    // Read numbers of square from file
    for(int i = 0; i < *size; i++){
        for(int j = 0; j < *size; j++){
            if(fscanf(fp, "%hd", &square[i][j]) != 1){ // check fscanf return code for error
                printf("Error reading Latin Square values.\n");
                fclose(fp);
                exit(EXIT_FAILURE); // close file and exit
            } else if(square[i][j] > *size || square[i][j] < -(*size)){ // check if values of latin square are in [1, size]
                printf("File contains invalid values!\n");
                fclose(fp);
                exit(EXIT_FAILURE); // close file and exit
            }
        }
    }

    // Check for extra data (rows/columns)
    int extraValue;
    if(fscanf(fp, "%d", &extraValue) == 1){  // check if there are extra rows or columns in the file
        printf("File contains more data than expected!\n");
        fclose(fp);
        exit(EXIT_FAILURE); // close file and exit
    }

    fclose(fp); // close file if every check is passed
}

void displayLatinSquare(short square[N][N], int size){
    // Print top border
    for (int i = 0; i < size; i++) {
        printf("+-----");
    }
    printf("+\n");

    // Print rest of values with borders
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            if(square[i][j] < 0){ // check if value at i,j is negative (pre-given value)
                printf("| (%-1d) ", -square[i][j]); // print number in parenthesis in space of two
            } else{ // print other values (given by user)
                printf("|  %-2d ", square[i][j]);
            }
        }
        printf("|\n"); // change line every finished row

        // Print bottom border
        for (int k = 0; k < size; k++) {
            printf("+-----");
        }
        printf("+\n");
    }

}

int checkUserInput(int i, int j, int val, int size, short square[N][N]){
    // If 0,0=0 go back to play(), save and exit the game
    if(i == 0 && j == 0 && val == 0){
        return 0;
    }

    // Check bounds of i, j and val
    if(i > size || i <= 0 || j > size || j <= 0 || val > size || val < 0){
        printf("\nError: i,j or val are outside the allowed range [1..%d]!\n", size);
        return 1;
    }

    // Check if cell has pre-given value (can't be cleared)
    if(square[i - 1][j - 1] < 0){
        printf("\nError: illegal to modify pre-given cell\n");
        return 1;
    }

    // Check if cell is occupied
    if(val != 0 && square[i - 1][j - 1] !=  0){
        printf("\nError: cell is already occupied!\n");
        return 1;
    }

    // Calculate total occurrences of val in square
    int totalOccurrences = 0;
    for(int row = 0; row < size; row++){
        for(int col = 0; col < size; col++){
            if(val!= 0 && abs(square[row][col]) == val){ // count number of occurances
                totalOccurrences++;
            }
        }
    }

    // If total occurrences are equal or more than "size", user's move can't be executed
    if(totalOccurrences >= size){
        printf("\nError: Illegal value insertion! | Number already appears %d times.\n", size);
        return 1;
    }

    // Check if the value already exists in the same row
    for(int col = 0; col < size; col++){
        if(val!= 0 &&  abs(square[i - 1][col]) == val){
            printf("\nError: Illegal value insertion! | Value already exists in row %d!\n", i);
            return 1;
        }
    }

    // Check if the value already exists in the same column
    for(int row = 0; row < size; row++){
        if(val!= 0 && abs(square[row][j - 1]) == val){
            printf("\nError: Illegal value insertion! | Value already exists in column %d!\n", j);
            return 1;
        }
    }

    return 0; // if every check is passed, return 0 for valid input
}
