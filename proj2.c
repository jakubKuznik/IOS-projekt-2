// Solution for IOS-proj2, 15.4.2021
// File:        proj2.c
// Author:      Jakub Kuzník, FIT
// Compiled:    gcc 9.9.3.0


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>


#include "proj2.h"

int main(int argc, char *argv[])
{
    short ne, nr, te, tr;
    ne = nr = te = tr = 0;

    if(arg_parser(argc, argv, &ne, &nr, &te, &tr) != 0)
        return 1;
    
    printf("hello");
    return 0;
}


/**
 * Parse arguments. 
 * return -1 error bad file format 
 * return -2 if there are no args 
 */
long int arg_parser(int argc, char *argv[], short *ne, short *nr, short *te, short *tr)
{
    if (argc != 5) 
        goto error_1; //bad input arguments 

    // Check if input argument are numbers 
    for(int i = 1; i < argc; i++)
        if(is_number(argv[i]) == false)
            goto error_2;


    return 0;



//////////////ERRORS
error_1:
    fprintf(stderr, "Bad input argumetns format.\n");
    return -1;
error_2:
    fprintf(stderr, "Wrong input these are no numbers. \n");
    return -1;

/*
error_3:
    return -1;
*/
}

/**
 * Return true if string is digit, else return false.
*/
bool is_number(char *str)
{
    for (int i = 0 ; str[i] != '\0' ; i++)
    {
        if(!(isdigit(str[i])))
        {
            return false;
        }
    }
    return true;
}