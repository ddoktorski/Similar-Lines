CC       = gcc
CFLAGS   = -Wall -Wextra -std=c11 -O2

.PHONY: all clean

all: similar_lines

similar_lines: main.o parser.o functions.o memory_handling.o
	$(CC) -o similar_lines main.o parser.o functions.o memory_handling.o
parser.o: parser.c parser.h
	$(CC) $(CFLAGS) -c parser.c
functions.o: functions.c functions.h
	$(CC) $(CFLAGS) -c functions.c
memory_handling.o: memory_handling.c memory_handling.h
	$(CC) $(CFLAGS) -c memory_handling.c 
main.o: main.c parser.h functions.h memory_handling.h structs.h
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f *.o similar_lines
