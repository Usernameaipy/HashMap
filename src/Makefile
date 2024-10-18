CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c11
BUILDDIR = ../build/

all : test start

test : hash_map.o test_hash.o
	$(CC) $(CFLAGS) hash_map.o test_hash.o -o $(BUILDDIR)test

hash_map.o : hash_map.c hash_map.h
	$(CC) $(CFLAGS) -c hash_map.c -o hash_map.o

test_hash.o : test_hash.c test_hash.h
	$(CC) $(CFLAGS) -c test_hash.c -o test_hash.o

start :
	$(BUILDDIR)test

clean :
	rm -rf *.o
	rm -rf $(BUILDDIR)*

rebuild : clean all