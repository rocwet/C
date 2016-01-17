#!/bin/bash

CC = gcc
CFLAGS = -Wall -g -std=c99

convert: convert.c
	$(CC) $(CFLAGS) -o convert convert.c

clean: 
	rm -f convert
	@echo Cleaning...
