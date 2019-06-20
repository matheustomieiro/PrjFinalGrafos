#ifndef PESSOA_H
#define PESSOA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct pessoa Pessoa;

/* criar_pessoa:
	Cria uma pessoa;
@Retorno:
	Ponteiro para a pessoa criada;
*/
Pessoa *criar_pessoa();

/* remover_pessoa:
	Desaloca dinamicamente uma pessoa;
@Argumentos:
	Ponteiro para a pessoa;
*/
void remover_pessoa(Pessoa *P);

/* ler_informacoes:
	Lê todas as informações de uma pessoa de um arquivo csv;
@Argumentos:
	Ponteiro para a pessoa;
	Ponteiro para o arquivo csv;
*/
void ler_informacoes(Pessoa *P, FILE *arquivo);

/* get_username:
	Retorna o username de uma pessoa;
@Argumentos:
	Ponteiro para a pessoa;
@Retorno:
	String com o username;
*/
char *get_username(Pessoa *P);

/* get_pin:
	Retorna o pin de uma pessoa;
@Argumentos:
	Ponteiro para a pessoa;
@Retorno:
	Inteiro com o pin;
*/
int get_pin(Pessoa *P);

/* imprimir_pessoa:
	Imprime todos os dados de uma pessoa;
@Argumentos:
	Ponteiro para a pessoa;
*/
void imprimir_pessoa(Pessoa *P);

/* nomes_iguais:
	Confere se os nomes de duas pessoas são iguais;
@Argumentos:
	Ponteiros para as pessoas;
@Retorno:
	Inteiro com 1 se os nomes forem iguais ou com 0 caso contrário;
*/
int nomes_iguais(Pessoa *P, Pessoa *Q);

/* faixa_etaria:
	Faz uma pesagem se duas pessoas estão em uma mesma faixa etária;
@Argumentos:
	Ponteiros para as pessoas;
@Retorno:
	Double com a pesagem;
*/
double faixa_etaria(Pessoa *P, Pessoa *Q);

/* cidades_iguais:
	Verifica se as cidades de duas pessoas são iguais;
@Argumentos:
	Ponteiros para as pessoas;
@Retorno:
	Inteiro com 1 se forem iguais ou com 0 caso contrário;
*/
int cidades_iguais(Pessoa *P, Pessoa *Q);

/* filmes_iguais:
	Verifica se os filmes de duas pessoas são iguais;
@Argumentos:
	Ponteiros para as pessoas;
@Retorno:
	Inteiro com 1 se forem iguais ou com 0 caso contrário;
*/
int filmes_iguais(Pessoa *P, Pessoa *Q);

/* times_iguais:
	Verifica se os times de duas pessoas são iguais;
@Argumentos:
	Ponteiros para as pessoas;
@Retorno:
	Inteiro com 1 se forem iguais ou com 0 caso contrário;
*/
int times_iguais(Pessoa *P, Pessoa *Q);

/* cores_iguais:
	Verifica se as cores de duas pessoas são iguais;
@Argumentos:
	Ponteiros para as pessoas;
@Retorno:
	Inteiro com 1 se forem iguais ou com 0 caso contrário;
*/
int cores_iguais(Pessoa *P, Pessoa *Q);

/* registra_pessoa:
	Cria uma pessoa lendo todos seus dados;
@Retorno:
	Ponteiro para a pessoa registrada;
*/
Pessoa *registrar_pessoa();

#endif