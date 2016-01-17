/*
The getmem.c file contains the implementation of the getmem function.

@author  Minh Khuu
@date    2015.11.18
*/

/* included libraries */
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "mem.h"
#include "mem_impl.h"

/* INTIALIZE GLOBAL VARIABLES*/
Block* front = NULL;
uintptr_t totalMalloc = 0;

/*
The divide() function will take in a block and size to divide the block into
a smaller block and returns the pointer to that smaller block.

@param b The block.
@param size The size the block will be divide to.
@return The pointer to the divided block.
*/
Block* divide(Block* b, uintptr_t size) {
  
  /* Make sure newBlock, is larger than minimum size */
  if (size + MIN_SIZE + HEADER_SIZE >= b->size) {
    return b->next;
  } else { 
  
    /* Create a new block pointer, which divides the original block */
    Block* newBlock = (Block*)((uintptr_t)b + size + HEADER_SIZE);
    newBlock->size = b->size - size - HEADER_SIZE;
    newBlock->next = b->next;
    b->size = size;
    b->next = NULL;
    return newBlock;
  }
}

/*
The getmem() function takes a given size and allocates memory of that size,
then returns the void pointer to the head of the memory block.

@param size The size of memory that will be allocated.
@return The void pointer to the head of the memory block.
*/
void* getmem(uintptr_t size) {
  
  /* Must allocate size greater than zero */
  if (size <= 0) {
    return NULL;
  }
  
  /* Check heap for errors... */
  check_heap();
  
  /* Make sure size is alligned by 16 */
  uintptr_t allignSize = size;
  if (size % 16 != 0) {
    allignSize = (size/16 + 1) * 16;  // ceil size value
  }
  
  /* book keeping variables */ 
  Block* newBlock;
  Block* temp;
  uintptr_t sizeToMalloc_BIG = allignSize + HEADER_SIZE;
  uintptr_t sizeToMalloc_SMALL = MALLOC_SIZE + HEADER_SIZE;
  
  /* EMPTY free list*/
  if (front == NULL) {
    
    /* Get mem size is big*/
    if (sizeToMalloc_BIG > MALLOC_SIZE) {
      
      /* define and initialize the first block */
      newBlock = (Block*)malloc(sizeToMalloc_BIG);
      newBlock->size = allignSize;
      newBlock->next = NULL;
      
      /* keep track of how much malloc */
      totalMalloc += sizeToMalloc_BIG;
      return (void*)((uintptr_t)newBlock + HEADER_SIZE);
      
      /* Get mem size is small */
    } else {
      
      /* define and initialize the first block */
      newBlock = (Block*)malloc(sizeToMalloc_SMALL);
      newBlock->size = (uintptr_t)MALLOC_SIZE;
      newBlock->next = NULL;
      
      /* declare that the first block is the front of the free list */
      front = newBlock;
      temp = front;
      
      /* keep track of how much malloc */
      totalMalloc += sizeToMalloc_SMALL;
      
      /* divide up the block according to size */
      front = divide(front, allignSize);
      return (void*)((uintptr_t)temp + HEADER_SIZE); // always
    } 
    
  /* NON empty free list*/
  } else {
    
    /* Case when the front of list is larger than user declared size */
    if (front->size >= allignSize + HEADER_SIZE) {
      temp = front;
      front = divide(front, allignSize);
      return (void*)((uintptr_t)temp + HEADER_SIZE);
    }
    
    /* find biggest block */
    Block* current = front;
    while (current->next != NULL && 
           current->next->size < allignSize + HEADER_SIZE) {
      current = current->next;
    } 
    
    /* allocates space on the biggest block */
    if (current->next != NULL) {
      temp = current->next;
      current->next = divide(current->next, allignSize);
      return (void*)((uintptr_t)temp + HEADER_SIZE);
    }
    
    /* Large user memory request case */
    if (allignSize + HEADER_SIZE > MALLOC_SIZE) {
      newBlock = (Block*)malloc(sizeToMalloc_BIG);
      newBlock->size = allignSize;
      newBlock->next = NULL;
      
      /* keep track of how much malloc */
      totalMalloc += sizeToMalloc_BIG;
      return (void*)((uintptr_t)newBlock + HEADER_SIZE);
    }
    
    /* Case for need new block for space and SORT */
    newBlock = (Block*)malloc(sizeToMalloc_SMALL);
    newBlock->size = MALLOC_SIZE;
    newBlock->next = NULL;
    
    /* keep track of how much malloc */
    totalMalloc += sizeToMalloc_SMALL;
    
    /* FRONT case, make address sorted from least to most*/
    if (newBlock < front) {
      temp = front;
      front = newBlock;
      newBlock->next = temp;
      front = divide(front, allignSize);
      return (void*)((uintptr_t)temp + HEADER_SIZE); 
    }
    
    /* GENERAL case */
    current = front;
    
    /* Go through all blocks, and make sure address sorted */
    while (current->next != NULL && current->next < newBlock) {
      current = current->next;
    }
    
    /* Put newly allocated block into the end of list since it's largest */
    if (current->next == NULL) {
      current->next = newBlock;
      
      /* In between case, new block is larger but smaller than another */
    } else {
      Block* temp2 = current->next;
      current->next = newBlock;
      newBlock->next = temp2;
    }
    temp = current->next;
    current->next = divide(current->next, allignSize);
    return (void*)((uintptr_t)temp + HEADER_SIZE);
  }
}
