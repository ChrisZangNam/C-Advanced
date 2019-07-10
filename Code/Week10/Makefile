CFLAGS = -c -Wall
CC = gcc
LIBS = -lm

all: WeightGraph

WeightGraph: WeightGraph.o libfdr/dllist.o libfdr/jval.o libfdr/jrb.o
	$(CC) WeightGraph.o libfdr/dllist.o libfdr/jval.o libfdr/jrb.o -o WeightGraph

WeightGraph.o: WeightGraph.c
	$(CC) $(CFLAGS) WeightGraph.c

jval.o: libfdr/jval.c
	$(CC) $(CFLAGS) libfdr/jval.c

jrb.o: libfdr/jrb.c
	$(CC) $(CFLAGS) libfdr/jrb.c

dllist.o: libfdr/dllist.c
	$(CC) $(CFLAGS) libfdr/dllist.c

clean:
	rm -f *.o *-
