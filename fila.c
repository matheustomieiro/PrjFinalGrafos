#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

struct Fila{
	no* cabeca;
	no* fim;
	int tamanho;
};

struct No{
	tipo item;
	no *proximo;
};


fila *fila_criar(void){
	fila *novo = (fila *)malloc(sizeof(fila));
	if(novo != NULL){		
		novo->cabeca = (no *) malloc(sizeof(no));
		novo->cabeca->proximo = NULL;
		novo->fim = NULL;
		novo->tamanho = 0;
	}
	return novo;
}

void fila_apagar(fila *F){
	no *aux, *apaga;
	if(F != NULL){
		aux = F->cabeca;
		do{
			apaga = aux;
			aux = aux->proximo;
			free(apaga);
		}while(aux != NULL);
		free(F);
	}
}

void fila_inserir(fila *F, tipo item){
	no *novo;
	if(F != NULL){
	 	novo = (no *)malloc(sizeof(no));
	 	if(novo != NULL){
	 		novo->item = item;
	 		novo->proximo = NULL;
	 		if(fila_vazia(F)){
	 			F->cabeca->proximo = novo;
	 			F->fim = novo;
	 		}else{
	 			F->fim->proximo = novo;
	 			F->fim = novo; 	
			}
			F->tamanho++;
		}
	}
}

tipo fila_retirar(fila *F){
	/*RETIRAR O PRIMEIRO E MOVER TODOS OS PŔOXIMOS UMA POSIÇÃO PARA TRÁS*/
	tipo item = 0;
	no *aux;
	if(F != NULL && !fila_vazia(F)){
		item = F->cabeca->proximo->item;
		aux = F->cabeca->proximo;
		F->cabeca->proximo = F->cabeca->proximo->proximo;
		free(aux);
		F->tamanho--;	
	}
	return item;
}

int fila_vazia(fila *F){
	return(F->tamanho == 0);
}
