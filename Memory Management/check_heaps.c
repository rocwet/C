/*
The check_heap.c file contains the implementation of the check_heap() function.

@author  Minh Khuu
@date    2015.11.18
 */

/* included libraries */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "mem_impl.h"

/*
The check_heap() function checks for possible problems with the free
list data structure. When called asserts to verify that it has the
following properties:
  - Blocks are ordered with strictly increasing memory addresses.
  - Block sizes are positive and are no smaller than the initial minimum size.
  - Blocks are not touching or overlapping other blocks.
*/
void check_heap() {
  if (front != NULL) {
    Block* temp = front;
    /* Test for increasing order order */
    while (temp->next != NULL) {
      assert ((uintptr_t)temp < (uintptr_t)temp->next);
      temp = temp->next;
    }
    temp = front;
    /* Test for size are positive and greater than minimum size*/
    while (temp->next != NULL) {
      assert (temp->size >= MIN_SIZE);
      temp = temp->next;
    }
    temp = front;
    /* Test for non-overlapping blocks*/
    while (temp->next != NULL) {
      uintptr_t address_initial = (uintptr_t)temp + HEADER_SIZE + temp->size;
      uintptr_t address_next = (uintptr_t)temp->next;
      assert (address_initial <= address_next);
      temp = temp->next;
    }
  }
}
