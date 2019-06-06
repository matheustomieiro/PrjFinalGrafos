#ifndef PESSOA_H
#define PESSOA_H

#include <stdio.h>
#include <stdlib.h>

typedef struct pessoa Pessoa;

Pessoa *criar_pessoa();
void remover_pessoa(Pessoa *P);
void ler_informacoes(Pessoa *P, FILE *arquivo);
char *get_username(Pessoa *P);
void imprimir_pessoa(Pessoa *P);

#endif