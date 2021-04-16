// Solution for IOS-proj2, 15.4.2021
// File:        proj2.h
// Author:      Jakub Kuzník, FIT
// Compiled:    gcc 9.9.3.0
// header file for proj2.c

/*******SEMAPHORES**********/
// semaphore names 
#define SEM_SANTA "/xkuzni04_ios_projekt2_santa"
#define SEM_RD "/xkuzni04_ios_projekt2_rd"
#define SEM_ELF "/xkuzni04_ios_projekt2_elf"
#define SEM_SHARED_MEM "/xkuzni04_ios_projekt2_shared_mem"

sem_t *sem_santa;   //semaphore for santa
sem_t *sem_rd;      //rd semaphore 
sem_t *sem_elf;     //elf semaphore 
sem_t *shared_mem;  //semaphore for entering shared memory
/**************************/

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


// 1 stands for santa process 
#define PROCESS_SUM (1 + nr + ne)


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



/**
 *  1. Po spuštění vypíše: A: Santa: going to sleep
 *  2. Po probuzení skřítky jde pomáhat elfům---vypíše: A: Santa: helping elves
 *  3. Poté, co pomůže skřítkům jde spát (bez ohledu na to, jestli před dílnou čekají další skřítci)
 *      a vypíše: A: Santa: going to sleep
 *  4. Po probuzení posledním sobem uzavře dílnu a vypíše: A: Santa: closing workshop
 *  a pak jde ihned zapřahat soby do saní.
 *  5. Ve chvíli, kdy jsou zapřažení všichni soby vypíše: A: Santa: Christmas started
 *      a ihned proces končí.
*/
int santa();


/**
 * 1. Každý skřítek je unikátně identifikován číslem elfID. 0<elfID<=NE
 * 2. Po spuštění vypíše: A: Elf elfID: started
 * 3. Samostatnou práci modelujte voláním funkce usleep na náhodný čas v intervalu <0,TE>.
 * 4. Když skončí samostatnou práci, potřebuje pomoc od Santy. Vypíše: A: Elf elfID: need help
 *    a zařadí se do fronty před Santovou dílnou.
 * 5. Pokud je třetí ve frontě před dílnou, dílna je prázdná a na dílně není cedule „Vánoce – zavřeno“,
 *    tak společně s prvním a druhým z fronty vstoupí do dílny a vzbudí Santu.
 * 6. Skřítek v dílně dostane pomoc a vypíše: A: Elf elfID: get help (na pořadí pomoci skřítkům v
 *    dílně nezáleží)
 * 7. Po obdržení pomoci ihned odchází z dílny a pokud je dílna již volná, tak při odchodu z dílny
 *    může upozornit čekající skřítky, že už je volno (volitelné).
 * 8. Pokud je na dveřích dílny nápis „Vánoce – zavřeno“ vypíše: A: Elf elfID: taking holidays
 *    a proces ihned skončí.
 * 
 * index = elf index as it was created in loop
*/
int elf(const unsigned short index);


/**
 *  1. Každý sob je identifikován číslem rdID, 0<rdID<=NR2. Po spuštění vypíše: A: RD rdID: rstarted
 *  3. Čas na dovolené modelujte voláním usleep na náhodný interval <TR/2,TR>
 *  4. Po návratu z letní dovolené vypíše: A: RD rdID: return home
 *      a následně čeká, než ho Santa zapřáhne k saním. Pokud je posledním sobem, který se vrátil z
 *      dovolené, tak vzbudí Santu.
 *  5. Po zapřažení do saní vypíše: A: RD rdID: get hitched
 *      a následně proces končí.
 *
 *  index = reindeer index as it was created in loop
*/
int reindeer(const unsigned char index);