CC=gcc
CFLAGS=-g -Wall
LDFLAGS=-lcrypto -lssl
SRC=hash.c collide.c myhashlib.c shredder.c
BIN=hash collide shredder
OBJ=myhashlib.o


all: $(BIN)

shredder: shredder.c
	$(CC) $(CFLAGS) shredder.c -o shredder

hash: hash.c myhashlib.o myhashlib.h
	$(CC) $(CFLAGS) hash.c myhashlib.c $(LDFLAGS) -o hash

myhashlib.o: myhashlib.c myhashlib.h

collide: collide.c myhashlib.o myhashlib.h
	$(CC) $(CFLAGS) collide.c myhashlib.o $(LDFLAGS) -o collide

clean:
	rm -f $(BIN) *~ *.o
	rm -rf *.dSYM