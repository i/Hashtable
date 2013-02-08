FILES=hash.c wordstat.c
CFLAGS=-ansi -pedantic -Wall -Werror

.PHONY: debug all

all:
	gcc $(FILES) $(CFLAGS) -o test
	./test l.txt

debug:
	gcc $(FILES) $(CFLAGS) -g -o test

clean:
	rm wordstat.o
	rm hash.o
	rm test
