CC=gcc
CFLAGS=-g -Wall -o

tree.o: tree.c
	$(CC) $(CFLAGS) $@ $^
