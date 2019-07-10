CFLAGS = -c -Wall
CC = gcc
LIBS = -lm

all: k55

k55 : K55.o libfdr/dllist.o libfdr/jval.o libfdr/jrb.o libfdr/fields.o
	$(CC) -w K55.o libfdr/dllist.o libfdr/jval.o libfdr/jrb.o libfdr/fields.o -o k55

K55.o: K55.c
	$(CC) -w $(CFLAGS) K55.c

jval.o: libfdr/jval.c
	$(CC) -w $(CFLAGS) libfdr/jval.c

jrb.o: libfdr/jrb.c
	$(CC) -w $(CFLAGS) libfdr/jrb.c

dllist.o: libfdr/dllist.c
	$(CC) -w $(CFLAGS) libfdr/dllist.c

fields.o: libfdr/fields.c
	$(CC) -w $(CFLAGS) libfdr/fields.c
clean:
	rm -f *.o *-
