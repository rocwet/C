#!/bin/bash

CC = gcc
CFLAGS = -Wall -g -std=c11
OBJFILES = t9.o node.o t9

t9: t9.o node.o
	$(CC) $(CFLAGS) -o t9 t9.o node.o

t9.o: node.h t9.c
	$(CC) $(CFLAGS) -c t9.c

node.o: node.h node.c
	$(CC) $(CFLAGS) -c node.c

clean: 
	rm -f $(OBJFILES)
	@echo Cleaning...
