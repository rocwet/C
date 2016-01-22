/*
The bench.c file contains the top level function to be called to test
the memory management system. 

@author  Minh Khuu
@author  Mathew Braun
@date    2015.11.18
*/

 /* include libraries */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include "mem.h"

/* define constants */
#define NTRIALS 10000
#define PCTGET 50
#define PCTLARGE 10
#define SMALL_LIMIT 200
#define LARGE_LIMIT 20000

/* 
The report() function prints out statistics of the free list at the current
moment. It displays total size allocated on heap, number of free blocks,
average number of bytes per block, and total number of free blocks. 

@param count The report number.
@param time The current elapsed time.
*/
void report(int count, int time) {
  /* Initialize stat variables */
  uintptr_t total_size = 0;
  uintptr_t total_free = 0;
  uintptr_t n_free_blocks = 0;
  /* retrieve stats of the current freelist*/
  get_mem_stats(&total_size, &total_free, &n_free_blocks);
  /* Print statistics */
  printf("REPORT %d:\n", count);
  printf("    Elapse Time: %lf\n", (double)time/CLOCKS_PER_SEC);
  printf("    Total size allocated on heap:  %lu\n", total_size);
  printf("    Total number of free size:     %lu\n", total_free);
  printf("    Total number of free blocks:   %lu\n", n_free_blocks);
  if (n_free_blocks == 0) {  // divide by 0 case
    printf("    Average bytes per free blocks: 0\n");
  } else {
    printf("    Average bytes per free blocks: %lu\n", total_free / n_free_blocks);
  }
  printf("---------------------------------------------------------\n");
}

/**
The main() function benches the memory management system.

@param argc The amount of arguments (includes the bench call).
@param argv The command-line arguments.
       Optional arguments:
            bench [ntrials [pctget [pctlarge [small_limit [large_limit [random_seed ]]]]]]
            ntrials:      total number of getmem and freemem calls (default: 10000);
            pctget:       percent getmem/freemem calls (default: 50)
            pctlarge:     precent getmem calls that should request largeblocks
                          with a size greater than SMALL_LIMIT (default: 10)
            small_limit:  largest size in bytes of a small block (default: 200)
            large_limit:  largest size in bytes of a larger block (default: 20000)
            random_seed:  initial seed for random generator (default: random number based on time)

@return The return status.
        0 = Success
        1 = Fail
*/
int main (int argc, char *argv[]) {
  /* Initialize paramters with default values */
  int ntrials = NTRIALS;
  int pctget = PCTGET;
  int pctlarge = PCTLARGE;
  int small_limit = SMALL_LIMIT;
  int large_limit = LARGE_LIMIT;
  /* intialize random generator */
  srand(time(NULL));
  /* iterate through each arguement and changing parameter accordingly */
  for (int i = 0; i < argc; i++) {
    if (i == 1) ntrials = atoi(argv[1]);
    if (i == 2) pctget = atoi(argv[2]);
    if (i == 3) pctlarge = atoi(argv[3]);
    if (i == 4) small_limit = atoi(argv[4]);
    if (i == 5) large_limit = atoi(argv[5]);
    if (i == 6) srand(atoi(argv[6]));      
  }
  /* Book keeping variables */
  int choice;
  int memCount;
  int randomSize;
  /* Create an array for pointers for getmem return values - used to freemem */
  uintptr_t* list = (uintptr_t*)malloc(ntrials*sizeof(uintptr_t));
  /* getmem count - used to determine where to call freemem */
  memCount = 0;
  /* Ensure 10 reports */
  int timeToReport = ntrials / 10 + (ntrials % 10 / 10);
  int reportTimer = ntrials - timeToReport;
  /* Initialize time variables, to calculate run time */
  int startTime = clock();
  int currentTime;
  /* keep tracks of how many reports */
  int counter = 0;
  /* ntrial calls of getmem or freemem */
  for (int i = ntrials; i > 0; i--) {
    /* Flip a coin - determines if getmem or freemem call */
    choice = rand() % 100 + 1;
    /* GETMEM case */
    if (choice > pctget) {
      //printf("getmeming...\n");
      /* Flip a coin - determines allocation size */
      choice = rand() % 100 + 1;
      /* Select random size to allocate */
      if (choice <= pctlarge) {           
        randomSize = rand() % (large_limit - small_limit) + 1;
      } else {
        randomSize = rand() % (small_limit) + 1;
      }
      /* store getmem pointer into the array for future */
      list[memCount++] = (uintptr_t) getmem(randomSize);
    /* FREEMEM case*/
    } else {
      /* call freemem on a random pointer if there has been allocation */
      if (memCount > 0) {
        int randomIndex = rand() % memCount;
        freemem((uintptr_t*) list[randomIndex]);
        memCount--;
        if (memCount != randomIndex) {
          list[randomIndex] = list[memCount];
        }
      }
    }
    currentTime = clock() - startTime;
    /* At 10%, 20%, 30%, ... , 90% of ntrials display report*/
    if (i == reportTimer) {
      report(++counter, currentTime);
      reportTimer -= timeToReport;
    }
  }    
  /* last report, 100% of ntrials */
  report(++counter, currentTime);
  return 0;
}
