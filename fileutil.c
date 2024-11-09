#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fileutil.h"

// DIRECTIONS
// Choose whether you are doing the 2D array or
// the array of arrays.
// For the 2D array,
//    implement loadFile2D, substringSearch2D, and free2D.
// For the array of arrays, 
//    implement loadFileAA, substringSearchAA, and freeAA.


// Load the text file from the given filename.
// Return a pointer to the array of strings.
// Sets the value of size to be the number of valid
// entries in the array (not the total array length).
char ** loadFileAA(char *filename, int *size)
{
	FILE *in = fopen(filename, "r");
	if (!in)
	{
	    perror("Can't open file");
	    exit(1);
	}

	int capacity = 10; //sets the capacity of the array of strings to 10 to start
	char ** arr = malloc(capacity * sizeof(char *)); //array of stings
	

	*size = 0; //will be used as index in the arr array and how many lines are read
	char *lineRead = malloc(1000 * sizeof(char)); //each line read in (1000 is arbitrary)

	//reading all lines in files
	while(fgets(lineRead, 1000, in) != NULL){

		//trimming new line
		if(lineRead[strlen(lineRead)-1] == '\n'){
            lineRead[strlen(lineRead)-1] = '\0';
        }

		//expand capacity if the size already hit the capacity
		if(*size == capacity){
			capacity += capacity/2.0;
			arr = realloc(arr, capacity*sizeof(char *));
		}

		//dynamically allocate space for the line to be put into arr
		arr[*size] = malloc((strlen(lineRead)+1) * sizeof(char)); //+1 for the '/0'
		
		//copy the line from the file into arr
		strcpy(arr[*size], lineRead);

		++*size; //pre increment needed because the dereferencing stopped the incrementation
	}

	//close file
	fclose(in);

	// Return pointer to the array of strings.
	return arr;
}

// char (*loadFile2D(char *filename, int *size))[COLS]
// {
// 	FILE *in = fopen(filename, "r");
// 	if (!in)
// 	{
// 	    perror("Can't open file");
// 	    exit(1);
// 	}
	
// 	// TODO
// 	// Allocate memory for an 2D array, using COLS as the width.
// 	// Read the file line by line into a buffer.
//     //   Trim newline.
// 	//   Expand array if necessary (realloc).
// 	//   Copy each line from the buffer into the array (use strcpy).
//     // Close the file.
	
// 	// The size should be the number of entries in the array.
// 	*size = 0;
	
// 	// Return pointer to the array.
// 	return NULL;
// }

// Search the array for the target string.
// Return the found string or NULL if not found.
char * stringMatchAA(char *target, char **arr, int size)
{
	for(int i=0; i<size; i++){
		if(strcmp(arr[i], target) == 0){
			return arr[i];
		}
	}

	return NULL;
}

char * substringSearchAA(char *target, char **arr, int size)
{
	for(int i=0; i<size; i++){
		if(strstr(arr[i], target) != NULL){
			return arr[i];
		}
	}

	return NULL;
}

// char * substringSearch2D(char *target, char (*lines)[COLS], int size)
// {
    
//     return NULL;
// }

// Free the memory used by the array
void freeAA(char ** arr, int size)
{
	for(int i = 0; i<size; i++){
		free(arr[i]);
	}
	free(arr);
}

// void free2D(char (*arr)[COLS])
// {

// }