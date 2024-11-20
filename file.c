/**
 * @file file.h
 * @brief Provides utility functions to read a Latin square from a file and manage memory for 2D integer arrays.
 *
 * This file includes functions to dynamically allocate, read, and deallocate memory for a 2D array representing 
 * a Latin square. The main functionalities are:
 * - Reading a Latin square from a file.
 * - Safely freeing the memory allocated for a 2D array.
 *
 * The functions in this file ensure robust error handling for file operations and memory allocation.
 *
 * @authors
 * - Panagiotis Tsembekis
 * - Rafael Tsekouronas
 * 
 * @bug No known bugs.
 */

#include "file.h"

// Frees a dynamically allocated 2D integer array
void free2DArray(int **array, int size) {
    if (array != NULL) {
        for (int i = 0; i < size; i++) {
            free(array[i]); // free each column
        }
        
        free(array); // free every row
    }
}

// Reads the latin square values from the specified file and stores them in a 2D array which is returned
int **readLatinSquare(const char *filename, int *size)
{   
    // Open file for reading
    FILE *fp = fopen(filename, "r");

    // Check file pointer after attempting to open file
    if (fp == NULL)
    {
        perror("Error occurred while attempting to read from file.\n");
        return NULL;
    }

    // Check n (size of latin square)
    if (fscanf(fp, "%d", size) != 1 || *size <= 0 || *size > N) // check fscanf return code and size's value
    { 
        perror("Invalid size of Latin Square!\n");
        fclose(fp);
        return NULL; // close file and exit
    }

    // Allocate memory for 2D array
    int **array = (int **)malloc(*size * sizeof(int *));
    if (array == NULL) // check for incorrect memory allocation for rows
    {
        perror("Memory allocation for rows of 2D array failed.\n");
        fclose(fp);
        return NULL;
    }

    for (int i = 0; i < *size; i++) // allocate memory for columns
    {
        array[i] = (int *)malloc(*size * sizeof(int));
        if (array[i] == NULL) // check for incorrect memory allocation for columns
        {
            perror("Memory allocation failed for columns.\n");
            free2DArray(array, i); // free previously allocated rows
            fclose(fp);
            return NULL;
        }
    }

    // Read initial latin square values from file
    for (int i = 0; i < *size; i++)
    {
        for (int j = 0; j < *size; j++)
        {
            if (fscanf(fp, "%d", &array[i][j]) != 1) // if read more than 1 argument => incorrect
            {
                perror("Error reading data from file.\n");
                free2DArray(array, *size); // free allocated space for array
                fclose(fp);
                return NULL;
            }
        }
    }

    fclose(fp);
    return array;
}


#ifdef DEBUG_FILE

int main() {
    int size = 0;

    // Provide a test file name
    const char *testFile = "testLatinSquare.txt";
    
    // Call readLatinSquare function
    int **latinSquare = readLatinSquare(testFile, &size);

    if (latinSquare == NULL) {
        printf("Failed to read the Latin square from file '%s'.\n", testFile);
    } else {
        printf("Successfully read a %d x %d Latin square from file '%s':\n", size, size, testFile);

        // Print the Latin square
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                printf("%d ", latinSquare[i][j]);
            }
            printf("\n");
        }

        // Free the allocated memory
        free2DArray(latinSquare, size);
    }

    return 0;
}
#endif