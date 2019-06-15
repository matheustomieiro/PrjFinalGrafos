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

int get_pin(Pessoa *P){
	return P->pin;
}	

void imprimir_pessoa(Pessoa *P){
	if(P){
		printf("-----------------------------------\n");
		printf("Nome: %s\n", P->nome);
		printf("Username: %s\n", P->username);
		printf("Pin: %d\n", P->pin);
		printf("Idade: %d\n", P->idade);
		printf("Cidade: %s\n", P->cidade);
		printf("Filme: %s\n", P->filme);
		printf("Time: %s\n", P->futebol);
		printf("Cor: %s\n", P->cor);
		printf("-----------------------------------\n");
	}	

}

int nomes_iguais(Pessoa *P, Pessoa *Q){
	return (strcmp(P->nome, Q->nome) == 0);
}

double faixa_etaria(Pessoa *P, Pessoa *Q){
	int diferenca = fabs((float)P->idade - (float)Q->idade);
	if(diferenca == 0)
		return 50;
	if(diferenca <= 5)
		return (30 - diferenca);
	if(diferenca <= 10) 
		return (20 - diferenca);
	return 0;
}

int cidades_iguais(Pessoa *P, Pessoa *Q){
	return (strcmp(P->cidade, Q->cidade) == 0);
}

int filmes_iguais(Pessoa *P, Pessoa *Q){
	return (strcmp(P->filme, Q->filme) == 0);
}

int times_iguais(Pessoa *P, Pessoa *Q){
	return (strcmp(P->futebol, Q->futebol) == 0);
}

int cores_iguais(Pessoa *P, Pessoa *Q){
	return (strcmp(P->cor, Q->cor) == 0);
}

Pessoa *registrar_pessoa(){
	Pessoa *P = criar_pessoa();
	printf("Digite os valores dos seguintes campos:\n");
	printf("Nome:");
	scanf("%[^\n]%*c", P->nome);
	printf("Username:");
	scanf("%[^\n]%*c", P->username);
	printf("Pin:");
	scanf("%d%*c", &(P->pin));
	printf("Idade:");
	scanf("%d%*c", &(P->idade));
	printf("Cidade:");
	scanf("%[^\n]%*c", P->cidade);
	printf("Filme:");
	scanf("%[^\n]%*c", P->filme);
	printf("Time:");
	scanf("%[^\n]%*c", P->futebol);
	printf("Cor:");
	scanf("%[^\n]%*c", P->cor);
	return P;
}