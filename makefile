all: hash main
	gcc -o test hash.o main.o -pedantic -ansi -Wall -Werror
	./test

hash:
	gcc -c -o hash.o hash.c

main:
	gcc -c -o main.o main.c
