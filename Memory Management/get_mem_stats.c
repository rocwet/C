/*
The get_mem_stats.c file contains the implementation of the get_mem_stats
function

@author  Mathew Braun
@date 2015.11.18
 */

 /* included libraries */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "mem.h"
#include "mem_impl.h"

/*
The get_mem_stats() function takes three pointers and stores statistics
about the current state of the memory manager.
 
@param total_size Pointer that will be set to the amount of bytes 
       available in the memory manager.
@param total_free Pointer that will be set to the total amount of memory 
       that is currently in the free list.
@param n_free_blocks Pointer that will be set to the total number of 
       individual blocks currently stored on the free list.
*/
void get_mem_stats(uintptr_t* total_size, uintptr_t* total_free, uintptr_t* n_free_blocks) {
  
  /* Initialize stats */
  uintptr_t free;
  free = 0;
  uintptr_t blocks;
  blocks = 0;
  Block* list_ptr = front;
  
  /* Iterate through the free list, count blocks and free space */
  while (list_ptr != NULL) {
    free = free + list_ptr->size;
    blocks = blocks + 1;
    list_ptr = list_ptr->next;
  }
  
  /* Update parameters */
  *total_size = totalMalloc;
  *total_free = free;
  *n_free_blocks = blocks;
}
