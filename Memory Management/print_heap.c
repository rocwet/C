/*
The print_heap.c file contains the implementation of the print_heap 
function

@author  Minh Khuu
@date    2015.11.18
*/

/* included libraries */
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include "mem.h"
#include "mem_impl.h"

/*
The print_heap() function prints a formatted list to the file f that shows
the blocks on the free list.

@param f The file that the function will print to.
*/
void print_heap(FILE * f) {
  Block* list_ptr = front;
  while (list_ptr != NULL) {
    fprintf(f, "Address of block: 0x%" PRIXPTR " ", (uintptr_t)list_ptr);
    fprintf(f, "Length of block: 0x%" PRIXPTR "\n", list_ptr->size);
    list_ptr = list_ptr->next;
  } 
}
