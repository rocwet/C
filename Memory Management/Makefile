#!/bin/bash

CC = gcc
CFLAGS = -Wall -g -std=c11
OBJFILES = bench.o check_heaps.o freemem.o getmem.o get_mem_stats.o print_heap.o
SRCFILES = bench.c check_heaps.c freemem.c getmem.c get_mem_stats.c print_heap.c
HEADFILES = mem.h mem_impl.h

bench: $(OBJFILES)
	$(CC) $(CFLAGS) -o bench $(OBJFILES)

bench.o: bench.c $(HEADFILES)
	$(CC) $(CFLAGS) -c bench.c

check_heaps.o: check_heaps.c mem_impl.h
	$(CC) $(CFLAGS) -c check_heaps.c

freemem.o: freemem.c $(HEADFILES)
	$(CC) $(CFLAGS) -c freemem.c

getmem.o: getmem.c $(HEADFILES)
	$(CC) $(CFLAGS) -c getmem.c

get_mem_stats.o: get_mem_stats.c $(HEADFILES)
	$(CC) $(CFLAGS) -c get_mem_stats.c

print_heap.o: print_heap.c $(HEADFILES)
	$(CC) $(CFLAGS) -c print_heap.c

clean:
	@echo Cleaning...
	rm -f *.o *~

dist:
	@echo Creating distribution file...
	git log > git.log
	tar -cf hw6.tar $(SRCFILES) $(HEADFILES) Makefile git.log README.md

test:
	@echo Testing...
	./bench



