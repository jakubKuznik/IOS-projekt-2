// Solution for IOS-proj2, 15.4.2021
// File:        proj2.h
// Author:      Jakub Kuzník, FIT
// Compiled:    gcc 9.9.3.0
// header file for proj2.c


/**
 * Parse arguments. 
 * return -1 error 
 * return -2 if there are no args 
 */
long int arg_parser(int argc, char *argv[], short *ne, short *nr, short *te, short *tr);



/**
 * Return true if string is digit, else return false.
*/
bool is_number(char *str);