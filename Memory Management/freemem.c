/*
The freemem.c file contains the implementation of the freemem function

@author Minh Khuu
@date 2015.11.18
*/
 
 /* included libraries */
#include<stdint.h>
#include<stdlib.h>
#include"mem.h"
#include"mem_impl.h"

/* 
The combine() function takes two blocks and combines them. Their
sizes are combined and the pointer to the combined block is returned.

@param b1 The first block.
@param b2 The second block.
@return The pointer to the combined block (b1 and b2).
*/
Block* combine(Block* b1, Block* b2) {
  Block* newBlock = b1;
  newBlock->next = b2->next;
  newBlock->size = b1->size + b2->size + HEADER_SIZE;
  return newBlock;
}

/*
The place_in_list() function takes the pointer to a block of memory from
the freemem() function and places it in the appropriate place in memory.

@param p The pointer to the block of memory from freemem().
*/
void freemem(void* p) {
  
  /* NULL parameter ends function call */
  if (p == NULL) {
    return;
  }
  
  /* Book keeping variables */
  Block* removeBlock = p - HEADER_SIZE;
  Block* current = front;
  
  /* Front case of free list, where removeBlock address is smaller */
  if (current != NULL && removeBlock < current) {
    removeBlock->next = current;
    front = removeBlock; 
    return; 
  }
  
  /* Finds the block at the end of the free list, where removeBlock address is larger */
  while (current != NULL && current->next != NULL && removeBlock > current->next) {
    current = current->next;
  }
  
  /* END CASE, where freelist reach the end of free list, insert removeBlock at the end */ 
  if (current->next == NULL) {
    current->next = removeBlock;
    return;
  }
  
  /* GENERAL CASE, insert removeBlock somewhere in the middle of freeList */
  removeBlock->next = current->next;
  current->next = removeBlock;
  
  /* Combining Blocks... */
  current = front;
  Block* prev = front;
  
  /* Go through free list */
  while (current != NULL && current->next != NULL) {
    
    /* Check if there is an empty block next to the current block */
    if (((uintptr_t)current + (uintptr_t)current->size) + 16 == (uintptr_t)current->next) {
      
      /* Combine the blocks */
      current = combine(current, current->next);
      
      /* Ignoring front case */
      if (prev != front) {  
        prev->next = current;
      } else {
        front = current;
      }
      
    /* Next block, keep track of previous block for error checking */
    } else {
      prev = current; 
      current = current->next;
    }
  }
}
