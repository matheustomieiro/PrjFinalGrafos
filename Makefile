all: pessoa.o grafo.o main.o
	gcc pessoa.o grafo.o main.o -g -Wall -o main

pessoa.o:
	gcc -c pessoa.c

grafo.o:
	gcc -c grafo.c

main.o:
	gcc -c main.c

clear:
	rm *.o main

run: clear all
	./main

memcheck:
	valgrind --leak-check=full ./main