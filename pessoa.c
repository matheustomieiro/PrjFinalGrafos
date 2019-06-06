#include "pessoa.h"

struct pessoa{
	char nome[128];
	char username[16];
	int pin;
	int idade;
	char cidade[32];
	char filme[32];
	char futebol[32];
	char cor[16];
};


Pessoa *criar_pessoa(){
	Pessoa *nova = (Pessoa *) calloc(1, sizeof(Pessoa));
	return nova;
}

void remover_pessoa(Pessoa *P){
	free(P);
}

void ler_informacoes(Pessoa *P, FILE *arquivo){
	if(P){
		fscanf(arquivo, "%[^,]%*c", P->nome);
		fscanf(arquivo, "%[^,]%*c", P->username);
		fscanf(arquivo, "%d%*c", &(P->pin));
		fscanf(arquivo, "%d%*c", &(P->idade));
		fscanf(arquivo, "%[^,]%*c", P->cidade);
		fscanf(arquivo, "%[^,]%*c", P->filme);
		fscanf(arquivo, "%[^,]%*c", P->futebol);
		fscanf(arquivo, "%[^\n]%*c", P->cor);
	}	
}

char *get_username(Pessoa *P){
	return P->username;
}	

void imprimir_pessoa(Pessoa *P){
	if(P){
		printf("-----------------------------------\n");
		printf("nome: %s\n", P->nome);
		printf("username: %s\n", P->username);
		printf("pin: %d\n", P->pin);
		printf("idade: %d\n", P->idade);
		printf("cidade: %s\n", P->cidade);
		printf("filme: %s\n", P->filme);
		printf("time: %s\n", P->futebol);
		printf("cor: %s\n", P->cor);
		printf("-----------------------------------\n");
	}	

}



