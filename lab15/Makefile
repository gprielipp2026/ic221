CC=clang
CFLAGS=-g -Wall
SRC=write-log.c read-log.c
BIN=$(SRC:.c=)

all: $(BIN)
	chmod u+s $^

clean:
	rm -f $(BIN) *~
