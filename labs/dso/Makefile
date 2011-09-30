CC = gcc
CFLAGS = -Wall

all: fmgmt

libmyio.so: libmyio.c myio.h
	$(CC) $(CFLAGS) -g -shared libmyio.c -o libmyio.so

fmgmt.o: libmyio.so
	$(CC) $(CFLAGS) -c fmgmt.c

fmgmt: fmgmt.o
	$(CC) $(CFLAGS) fmgmt.o -L. -lmyio -o fmgmt

.PHONY: clean

clean:
	rm *.o *.so fmgmt

test: fmgmt
	echo "hello world! ;)" > hello.txt
	LD_LIBRARY_PATH=. ./fmgmt hello.txt
	rm hello.txt
