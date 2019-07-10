CFLAGS = -c -Wall
CC = gcc
LIBS = -lm

all: timbus

timbus: bus.o libfdr/dllist.o libfdr/jval.o libfdr/jrb.o libfdr/fields.o
	$(CC) bus.o libfdr/dllist.o libfdr/jval.o libfdr/jrb.o libfdr/fields.o -o timbus

bus.o: bus.c
	$(CC) $(CFLAGS) bus.c

jval.o: libfdr/jval.c
	$(CC) $(CFLAGS) libfdr/jval.c

jrb.o: libfdr/jrb.c
	$(CC) $(CFLAGS) libfdr/jrb.c

dllist.o: libfdr/dllist.c
	$(CC) $(CFLAGS) libfdr/dllist.c

fields.o: libfdr/fields.c
	$(CC) $(CFLAGS) libfdr/fields.c
clean:
	rm -f *.o *-
