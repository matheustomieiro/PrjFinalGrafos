#ifndef PESSOA_H
#define PESSOA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct pessoa Pessoa;

Pessoa *criar_pessoa();
void remover_pessoa(Pessoa *P);
void ler_informacoes(Pessoa *P, FILE *arquivo);
char *get_username(Pessoa *P);
int get_pin(Pessoa *P);
void imprimir_pessoa(Pessoa *P);
int nomes_iguais(Pessoa *P, Pessoa *Q);
double faixa_etaria(Pessoa *P, Pessoa *Q);
int cidades_iguais(Pessoa *P, Pessoa *Q);
int filmes_iguais(Pessoa *P, Pessoa *Q);
int times_iguais(Pessoa *P, Pessoa *Q);
int cores_iguais(Pessoa *P, Pessoa *Q);
Pessoa *registrar_pessoa();

#endif