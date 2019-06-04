#include "getInfoFile.h"
#include <stdio.h>
#include <stdlib.h>
#define TAM_INICIAL_VETOR 1000

void iniciaVetor(VETOR_PESSOAS *VET){
		VET->tamanho = TAM_INICIAL_VETOR;
		VET->vetor = malloc(sizeof(PESSOA*) * TAM_INICIAL_VETOR);
		for(int i=0; i<TAM_INICIAL_VETOR; i++){
			VET->vetor[i] = malloc(sizeof(PESSOA));
		}
}

VETOR_PESSOAS getVetorPessoas(char filepath[]){
	char aux[256];
	VETOR_PESSOAS vet;
	iniciaVetor(&vet);
	FILE *data = fopen(filepath, "r");
	fscanf(data, "%s", &aux);
	while(aux != EOF){

		fscanf(data, "%s", &aux);
	}	

}
