/*
The mem_impl.h header file contains the private implementation of 
the functions for the memory management system project.

@author  Minh Khuu
@date    2015.11.17
*/

/* included libraries */
#include <stdint.h>

#ifndef MEM_IMPL_H
#define HEADER_SIZE 16
#define MALLOC_SIZE 4096
#define MIN_SIZE 16
#define MEM_IMPL_H

/*
The block structure contains the block struct used as
the basic building block for the implementation of the
free list for the memory management system.
*/
struct block {
  uintptr_t size;
  struct block* next;
};

/* Alias for struct block */
typedef struct block Block;

/* Global Variable for pointer to the front of free list */
extern Block* front;

/* Global Variable to keep track of how much malloc so far for free list*/
extern uintptr_t totalMalloc;

/* checks for errors in the free list */
void check_heap();

#endif
