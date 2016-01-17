/*
The mem.h header file contains the functions to be implemented for the
memory management system project.

@author  Minh Khuu
@date    2015.11.17
*/

/* included libraries */
#include <stdio.h>
#include <stdint.h>

#ifndef MEM_H
#define MEM_H

/* Removes all allocation of memory */
void freemem(void* p);

/* Retrieves statics of memory management system */
void get_mem_stats(uintptr_t* total_size, uintptr_t* total_free, uintptr_t* n_free_blocks);

/* Prints formatted listing on FILE F, showing blocks on free list */
void print_heap(FILE* F);

/* Allocates memory */
void* getmem(uintptr_t size);

#endif


