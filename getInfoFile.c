#include "getInfoFile.h"
#include <stdio.h>
#include <stdlib.h>
#define TAM_INICIAL_VETOR 100

void iniciaVetor(VETOR_PESSOAS *VET){
		VET->tamanho = TAM_INICIAL_VETOR;
		VET->vetor = malloc(sizeof(PESSOA*) * TAM_INICIAL_VETOR);
		for(int i=0; i<TAM_INICIAL_VETOR; i++){
			VET->vetor[i] = malloc(sizeof(PESSOA));
		}
}

void salvaDados(char aux[], VETOR_PESSOAS *vet, int pos){
	int i = 0, j = 0; char aux2[16], aux3[16];
	while(aux[i] != ','){
		vet->vetor[pos]->nome[i] = aux[i];
		i++;
	}
	vet->vetor[pos]->nome[i] = '\0';
	i++;

	while(aux[i] != ','){
		vet->vetor[pos]->username[j] = aux[i];
		i++;
		j++;
	}
	vet->vetor[pos]->username[j] = '\0';
	i++;
	j = 0;

	while(aux[i] != ','){
		aux2[j] = aux[i];
		i++;
		j++;
	}
	aux2[j] = '\0';
	vet->vetor[pos]->PIN = atoi(aux2);
	i++;
	j = 0;

	while(aux[i] != ','){
		aux2[j] = aux[i];
		i++;
		j++;
	}
	aux2[j] = '\0';
	vet->vetor[pos]->idade = atoi(aux2);
	i++;
	j = 0;

	while(aux[i] != ','){
		vet->vetor[pos]->cidade[j] = aux[i];
		i++;
		j++;
	}
	vet->vetor[pos]->cidade[j] = '\0';
	i++;
	j = 0;

	while(aux[i] != ','){
		vet->vetor[pos]->filme[j] = aux[i];
		i++;
		j++;
	}
	vet->vetor[pos]->filme[j] = '\0';
	i++;
	j = 0;

	while(aux[i] != ','){
		vet->vetor[pos]->time[j] = aux[i];
		i++;
		j++;
	}
	vet->vetor[pos]->time[j] = '\0';
	i++;
	j = 0;

	while(aux[i] != ','){
		vet->vetor[pos]->cor[j] = aux[i];
		i++;
		j++;
	}
	vet->vetor[pos]->cor[j] = '\0';
	return;
}

VETOR_PESSOAS *getVetorPessoas(char filepath[]){
	char aux[256];
	int i = -1;
	VETOR_PESSOAS *vet = malloc(sizeof(VETOR_PESSOAS));
	iniciaVetor(vet);
	FILE *data = fopen(filepath, "r");
	fscanf(data, "%s\n", &aux); //DESPREZANDO PRIMEIRA LINHA
	fscanf(data, "%s\n", &aux); //LENDO PRIMEIRA LINHA DE DADOS
	while(aux != EOF){
		i++;
		if(i >= vet->tamanho){
			vet->tamanho += TAM_INICIAL_VETOR;
			vet->vetor = realloc(vet->vetor, vet->tamanho);
		}
		salvaDados(aux, vet, i);
		fscanf(data, "%s\n", &aux);
	}	
	fclose(data);
	return vet;
}
