#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fileutil.h"
int compare(const void *key, const void *data);


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


// Search the array for the target string.
// Return the found string or NULL if not found.
char * stringSearchAA(char *target, char **arr, int size)
{
	for(int i=0; i<size; i++){
		if(strcmp(arr[i], target) == 0){
			return arr[i];
		}
	}

	return NULL;
}

char ** stringBSearchAA(char *target, char **arr, int size, int sizeOfElem)
{
	char **result = bsearch(&target, arr, size, sizeOfElem, compare);
	// printf("%s (in fileUtil)\n", *result);


	return result;
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

// Free the memory used by the array
void freeAA(char ** arr, int size)
{
	for(int i = 0; i<size; i++){
		free(arr[i]);
	}
	free(arr);
}


//comparison method for quicksort and binary search
int compare(const void *key, const void *data){
    //cast to a pointer of a pointer

    return strcmp(*(char **)key, *(char **)data);
}