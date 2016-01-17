# Memory Management
---

## Authors
Minh Khuu

### Date
2015.11.17 to 2015.12.03

#### Files

* mem.h
* mem_impl.h
* getmem.c
* check_heaps.c
* freemem.c
* get_mem_stats.c
* print_heap.c
* Makefile
* bench.c
* README.md

#### Description
* This project is an implementation of a simple memory management unit. It contains functions that allocates memory and free memories. 
* The free memory space is organized in a linked list data structure, each node containing two 8 byte fields for size and the pointer to the next free memory space.
* For each memory request, a default size is malloc, if the memory request is larger than a special malloc call will be used instead. The user can use this space to store anything up to the size requested.
* For each memory free, the function will free the block of data, and adjust pointers accordingly. It will also combine neighboring blocks when possible.
* This implementation of the memory management unit, keeps tracks of basic statistics of the status of the memory management unit and is capable of printing the contents. It also contains a simple check fucntion to make sure that the memory allocation is within spec.
* The memory management unit can be tested using our bench file.

#### Testing
* Using our bench program, our implementation of the memory management unit seems to work about 90% of the time. We occasionally get segment faults 1/10 times, but we cannot identify exactly where it occurs. 
* We also noticed, that our minimum size for free blocks has to be 16, any larger then the front free block will be free smaller. We can identify exactly where this is happening, but it seems to be occuring due to the freemem.

#### What needs to be fixed
* Fix the rare segmentation faults.
* Fix the small minimum size free block limitation.
