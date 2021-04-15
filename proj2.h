// Solution for IOS-proj2, 15.4.2021
// File:        proj2.h
// Author:      Jakub Kuzník, FIT
// Compiled:    gcc 9.9.3.0
// header file for proj2.c



// Postion in arguments 
#define NE 1
#define NR 2
#define TE 3
#define TR 4

//Maximum argument size for variable 
#define MAX_NE 999
#define MAX_TE_RE 1000
#define MAX_NR 19

//Argument minimum
#define MIN_NE_NR 1
#define MIN_TE_RE 0


/**
 * Parse arguments. 
 * return -1 error 
 * return -2 if there are no args 
 */
int arg_parser(int argc, char *argv[], short *ne, short *nr, short *te, short *tr);


/**
 * Store char number to if lt and gt conditons are meet 
 * else return false 
 * <range_from, range_to>
*/
bool store_if_gt_lt(char *from, short *to, int range_from, int range_to);

/**
 * Return true if string is digit, else return false.
*/
bool is_number(char *str);