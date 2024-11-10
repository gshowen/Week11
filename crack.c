#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "md5.h"

#if __has_include("fileutil.h")
#include "fileutil.h"
#endif

#define PASS_LEN 50     // Maximum length any password will be.
#define HASH_LEN 33     // Length of hash plus one for null.

int cmpqsort(const void *a, const void *b);


int main(int argc, char *argv[])
{
    if (argc < 3) 
    {
        printf("Usage: %s hash_file dictionary_file\n", argv[0]);
        exit(1);
    }

    //Read the hashes file into an array.
    int size;
    char **hashes = loadFileAA(argv[1], &size);
    printf("File loaded.\n");
    
    //Sort the hashes using qsort.
    qsort(hashes, size, sizeof(char *), cmpqsort);
    
    // Open the dictionary file for reading.
    FILE *dictFile = fopen(argv[2], "r");

    // TODO
    // For each password, hash it, then use the array search
    // function from fileutil.h to find the hash.
    // If you find it, display the password and the hash.
    // Keep track of how many hashes were found.
    // CHALLENGE1: Use binary search instead of linear search.
    
    //loop each pass
    //hash password

    //test arr search

    //allocating memory to hold password
    char *password = malloc(PASS_LEN * sizeof(char));
    
    
    int crackedPassCount = 0; //to count cracked passwords

    // //Grabbing every viable password from dictFile and testing
    while(fgets(password, PASS_LEN, dictFile) != NULL){

        //trimming off \n
        if(password[strlen(password)-1] == '\n'){
            password[strlen(password)-1] = '\0';
        }

        //finding the hash within the hash_file or getting NULL
        char *hashVal = md5(password, strlen(password));
        char **foundHash = stringBSearchAA(hashVal, hashes, size, sizeof(char **));

        //if there was a hash found, display it
        if(foundHash != NULL){
            printf("%s %s\n", *foundHash, password);
            crackedPassCount++;
        }
    }

    // fgets(password, PASS_LEN, dictFile);
    // char *hashVal = md5(password, strlen(password));
    // char *foundHash = stringBSearchAA(hashVal, hashes, size, sizeof(char **));

    // Display the number of hashes that were cracked.
    printf("%d passwords cracked\n", crackedPassCount);


    //free up memory and close files
    fclose(dictFile);
    free(password);
    freeAA(hashes, size);

}

//comparison method for quicksort and binary search
int cmpqsort(const void *a, const void *b){
    //cast to a pointer of a pointer
    char ** aa = (char **)a;
    char ** bb = (char **)b;

	// printf("%s, %s\n", *aa, *bb);

    return strcmp(*aa, *bb);
}


