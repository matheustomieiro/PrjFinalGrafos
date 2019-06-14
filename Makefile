all: pessoa.o fila.o grafo.o main.o
	gcc pessoa.o fila.o grafo.o main.o -g -Wall -o main -lm

pessoa.o:
	gcc -c pessoa.c

fila.o:
	gcc -c fila.c

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