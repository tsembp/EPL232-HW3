#include "file.h"
#define N 9

void free2DArray(int **array, int size) {
    if (array != NULL) {
        for (int i = 0; i < size; i++) {
            free(array[i]);
        }
        
        free(array);
    }
}

int **readLatinSquare(const char *filename, int *size)
{   
    // Open file for reading
    FILE *fp = fopen(filename, "r");

    // Check file pointer
    if (fp == NULL)
    {
        perror("Error occurred while attempting to read from file.\n");
        return NULL;
    }

    // Check n (size of latin square)
    if (fscanf(fp, "%d", size) != 1 || *size <= 0 || *size > N)
    { // check fscanf return code and size's value
        perror("Invalid size of Latin Square!\n");
        fclose(fp);
        return NULL; // close file and exit
    }

    int **array = (int **)malloc(*size * sizeof(int *));
    if (array == NULL)
    {
        perror("Memory allocation for rows of 2D array failed.\n");
        fclose(fp);
        return NULL;
    }

    for (int i = 0; i < *size; i++)
    {
        array[i] = (int *)malloc(*size * sizeof(int));
        if (array[i] == NULL)
        {
            perror("Memory allocation failed for columns.\n");
            // Free previously allocated rows
            free2DArray(array, i);
            fclose(fp);
            return NULL;
        }
    }

    for (int i = 0; i < *size; i++)
    {
        for (int j = 0; j < *size; j++)
        {
            if (fscanf(fp, "%d", &array[i][j]) != 1)
            {
                perror("Error reading data from file.\n");
                // Free memory on failure
                free2DArray(array, *size);
                fclose(fp);
                return NULL;
            }
        }
    }

    fclose(fp);
    return array;
}

