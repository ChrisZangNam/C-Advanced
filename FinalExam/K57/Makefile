CFLAGS = -c -Wall
CC = gcc
LIBS = -lm

all: k57

k57 : K57.o libfdr/dllist.o libfdr/jval.o libfdr/jrb.o libfdr/fields.o Graph.o
	$(CC) -w K57.o libfdr/dllist.o libfdr/jval.o libfdr/jrb.o libfdr/fields.o Graph.o -o k57

K57.o: K57.c
	$(CC) -w $(CFLAGS) K57.c

jval.o: libfdr/jval.c
	$(CC) -w $(CFLAGS) libfdr/jval.c

jrb.o: libfdr/jrb.c
	$(CC) -w $(CFLAGS) libfdr/jrb.c

dllist.o: libfdr/dllist.c
	$(CC) -w $(CFLAGS) libfdr/dllist.c

fields.o: libfdr/fields.c
	$(CC) -w $(CFLAGS) libfdr/fields.c

Graph.o: Graph.c
	$(CC) -w $(CFLAGS) Graph.c

clean:
	rm -f *.o *-
