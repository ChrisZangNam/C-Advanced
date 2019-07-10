CFLAGS = -c -Wall
CC = gcc
LIBS = -lm

all: BFS

BFS: BFS.o jval.o jrb.o dllist.o
	$(CC) BFS.o jval.o jrb.o dllist.o -o BFS

BFS.o: BFS.c
	$(CC) $(CFLAGS) BFS.c

jval.o: jval.c
	$(CC) $(CFLAGS) jval.c

jrb.o: jrb.c
	$(CC) $(CFLAGS) jrb.c

dllist.o: dllist.c
	$(CC) $(CFLAGS) dllist.c

clean:
	rm -f *.o *-
