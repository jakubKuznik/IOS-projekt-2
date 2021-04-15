// Solution for IOS-proj2, 15.4.2021
// File:        proj2.c
// Author:      Jakub Kuzník, FIT
// Compiled:    gcc 9.9.3.0

/* start 
    ./proj2 NE NR TE TR 
*/

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
 * return -1 if there is error  
 */
int arg_parser(int argc, char *argv[], short *ne, short *nr, short *te, short *tr)
{
    if (argc != 5) 
        goto error_1; //bad input arguments 

    // Check if input argument are numbers 
    for(int i = 1; i < argc; i++)
        if(is_number(argv[i]) == false) // Check if argv[i] is regular number 
            goto error_2;

    // store args to given variables and chceck if it is in good range if not go to error3 
    //NE
    if(store_if_gt_lt(argv[NE], ne, MIN_NE_NR, MAX_NE) == false) 
        goto error_3;
    //NR
    if(store_if_gt_lt(argv[NR], nr, MIN_NE_NR, MAX_NR) == false) 
        goto error_3;
    //TE
    if(store_if_gt_lt(argv[TE], te, MIN_TE_RE, MAX_TE_RE) == false) 
        goto error_3;
    //TR
    if(store_if_gt_lt(argv[TR], tr, MIN_TE_RE, MAX_TE_RE) == false) 
        goto error_3;

    return 0;

//ERRORS
// bad argument format 
error_1:
    fprintf(stderr, "ERROR: Bad input argumetns format.\n");
    return -1;
// No number input 
error_2:
    fprintf(stderr, "ERROR: Wrong input these are no numbers. \n");
    return -1;
// To big or to small number 
error_3:
    fprintf(stderr, "ERROR: Number is to small or to big. \n");
    return -1;
}


/**
 * Store char number to if lt and gt conditons are meet 
 * else return false 
 * <range_from, range_to>
*/
bool store_if_gt_lt(char *from, short *to, int range_from, int range_to)
{
    short temp = atoi(from);
    if(temp < range_from)
        return false;
    else if(temp > range_to)
        return false;

    *to = temp;
    return true;
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