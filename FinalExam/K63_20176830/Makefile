CFLAGS = -c -Wall
CC = gcc
LIBS = -lm

all: main

main : main.o
	$(CC) -w main.o Graph.c libfdr/libfdr.a -o main

main.o: main.c
	$(CC) -w $(CFLAGS) main.c

clean:
	rm -f *.o *-
