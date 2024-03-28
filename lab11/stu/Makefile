src=$(wildcard *.c)
tgts=$(src:%.c=%)

all: $(tgts)

%: %.c
	gcc -o $@ $< -lpthread -lcrypto
