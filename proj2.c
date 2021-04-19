// Solution for IOS-proj2, 15.4.2021
// File:        proj2.c
// Author:      Jakub Kuzník, FIT
// Compiled:    gcc 9.9.3.0

// ./proj2 NE NR TE TR 

#include "proj2.h"

// global semaphore variables 
sem_t *sem_santa;       //semaphore for santa
sem_t *sem_rd;          //rd semaphore 
sem_t *sem_elf;         //elf semaphore 
sem_t *sem_shared_mem;  //semaphore for entering shared memory

/**
 * Program is oriented to work with process using semaphore. 
 * return 1 if there is some error. 
 */
int main(int argc, char *argv[])
{
    // Here i ll store fork() output 
    pid_t pid_ret_code;
    // variables indicates how many process will i create 
    short ne, nr, te, tr;
    ne = nr = te = tr = 0;

    if(arg_parser(argc, argv, &ne, &nr, &te, &tr) != 0)
        return 1;

    FILE *f = NULL; 
    if((f = fopen("proj2.out", "w")) == NULL)
        goto error_4;

    //semaphore initialization
    if((semaphore_constructor()) == false)
        goto error_6; //if not succes 

    // shared memory initialization
    if((shared_mem_constructor()) == false)
        goto error_7; //if not succes
    


    // fork 0 is child proces 
    pid_ret_code = fork(); //create proces from main 
    if(pid_ret_code == 0) //Santa process runs and end in santa() function 
        santa();
    else if(pid_ret_code == -1)
        goto error_5;  


    pid_ret_code = fork(); //Create procces from main
    if(pid_ret_code == 0) //branch for elves 
    {
        for(unsigned short i = 0; i < ne; i++)
        {
            pid_ret_code = fork();
            
            if(pid_ret_code == 0) //Santa process runs and end in santa() function 
                elf(i);
            else if(pid_ret_code == -1)
                goto error_5;   
        }
    }
    else if(pid_ret_code > 0) // branch for  
    {
        for(unsigned char i = 0; i < nr; i++)
        {
            pid_ret_code = fork();
            if(pid_ret_code == 0) //Santa process runs and end in santa() function 
                reindeer(i);
            else if(pid_ret_code == -1)
                goto error_5;  
        }
    }
    else //pid is -1
        goto error_5;   




    for (unsigned short i = 0; i < PROCESS_SUM ; i++) 
        wait(NULL);

    if((shared_mem_destructor()) == false)
        goto error_8;
    semaphore_destructor();
    fclose(f);    
    return 0;


// ERRORS 
error_4:  //FILE ERROR     
    fprintf(stderr, "Error can't open file proj2.out\n");
    return 1;

error_5: //FORK ERROR 
    fprintf(stderr, "Error fork was no succesfull\n");
    semaphore_destructor();
    fclose(f);    
    return 1;

error_6: //SEMAPHORE ERROR 
    fprintf(stderr, "Error semaphore creating.\n");
    semaphore_destructor();
    fclose(f);    
    return 1;

error_7: //MMAP ERROR
    fprintf(stderr, "Error mmap failed.\n");
    semaphore_destructor();
    fclose(f);    
    return 1;
error_8: //MUN_MAP ERROR
    fprintf(stderr, "Error munmap failed.\n");
    semaphore_destructor();
    fclose(f);    
    return 1;
}


/**
 * Alocate shared memory 
 * return true if succes 
 * return false if not  
 */
bool shared_mem_constructor()
{
    if((shared_mem = mmap(NULL, sizeof(shared_mem_t), PROT_READ | PROT_WRITE, MAP_SHARED \
    | MAP_ANONYMOUS, SH_MEM_ID, 0)) == MAP_FAILED)
        return false;
    
    shared_mem->elf_count = 0;
    shared_mem->rein_count = 0;
    return true;
}

/**
 * Dealocate shared memory 
 * retunr false if not succes
 */
bool shared_mem_destructor()
{
    if(munmap(shared_mem, sizeof(shared_mem_t)))
        return false;
    return true;
}

/**
 * Close semaphores.
 */
void semaphore_destructor()
{
    sem_unlink(SEM_SANTA);
    sem_unlink(SEM_RD);
    sem_unlink(SEM_ELF);
    sem_unlink(SEM_SHARED_MEM);
}

/**
 * Create semaphores using sem_open()
 * return false if not succesfull  
 * Uses some #DEFINES proj2.h
 */
bool semaphore_constructor()
{   
    sem_santa = sem_open(SEM_SANTA, O_CREAT, 0666, 0);   
    sem_rd = sem_open(SEM_RD, O_CREAT, 0666, 0);   
    sem_elf = sem_open(SEM_ELF, O_CREAT, 0666, 0);   
    sem_shared_mem = sem_open(SEM_SHARED_MEM, O_CREAT, 0666, 0);   

    // If one of the sem_open failed 
    if( sem_santa == SEM_FAILED || \
        sem_rd == SEM_FAILED    || \
        sem_elf == SEM_FAILED   || \
        sem_shared_mem == SEM_FAILED)
    {
/**
 * 
 */
        return false;
    }
    return true;
} 

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
int santa()
{
    printf("Santa: going to sleep\n");
    exit(1);
}

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
int elf(const unsigned short index)
{
    printf("A: Elf %d: rstarted\n",index);
    exit(1);
}


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
int reindeer(const unsigned char index)
{
    printf("A: RD %d: rstarted\n",index);
    exit(1);
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