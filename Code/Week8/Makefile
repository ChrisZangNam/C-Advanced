CFLAGS = -c -Wall
CC = gcc
LIBS = -lm

all: DirectedGraph

DirectedGraph: DirectedGraph.o libfdr/dllist.o libfdr/jval.o libfdr/jrb.o
	$(CC) DirectedGraph.o libfdr/dllist.o libfdr/jval.o libfdr/jrb.o -o DirectedGraph

DirectedGraph.o: DirectedGraph.c
	$(CC) $(CFLAGS) DirectedGraph.c

jval.o: libfdr/jval.c
	$(CC) $(CFLAGS) libfdr/jval.c

jrb.o: libfdr/jrb.c
	$(CC) $(CFLAGS) libfdr/jrb.c

dllist.o: libfdr/dllist.c
	$(CC) $(CFLAGS) libfdr/dllist.c

clean:
	rm -f *.o *-
