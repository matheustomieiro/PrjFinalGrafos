#ifndef FILA_H
#define FILA_H

#define ERRO -404

typedef int tipo;

typedef struct Fila fila;
typedef struct No no;

/* criar_fila:
	Cria uma fila dinâmica;
@Retorno:
	Ponteiro para a fila criada;
*/
fila *fila_criar(void);

/* fila_apagar:
	Libera a memória alocada dinamicamente por uma fila;
@Argumentos:
	Ponteiro para a fila;
*/
void fila_apagar(fila *F);

/* fila_inserir:
	insere um item na fila;
@Argumentos:
	Ponteiro para a fila;
	Item a ser inserido;
*/
void fila_inserir(fila *F, tipo item);

/* fila_retirar:
	Retira um item da fila;
@Argumentos:
	Ponteiro para a fila;
@Retorno:
	O item;	
*/
tipo fila_retirar(fila *F);

/* fila_vazia:
	Verifica se uma fila está vazia;
@Retorno:
	Inteiro com 1 se está vazia ou com 0 caso contrário;
*/
int fila_vazia(fila *F);

#endif