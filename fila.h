#ifndef FILA_H
#define FILA_H

#define ERRO -404

typedef int tipo;

typedef struct Fila fila;
typedef struct No no;


fila *fila_criar(void);
void fila_apagar(fila *F);
void fila_inserir(fila *F, tipo item);
tipo fila_retirar(fila *F);
int fila_vazia(fila *F);

#endif