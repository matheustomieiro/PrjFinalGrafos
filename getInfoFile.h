typedef struct pss{
	char nome[128];
	char username[16];
	int PIN;
	int idade;
	char cidade[32];
	char filme[32];
	char time[32];
	char cor[16];
}PESSOA;

typedef struct vector{
	int tamanho;
	PESSOA **vetor;
}VETOR_PESSOAS;


void iniciaVetor(VETOR_PESSOAS *VET);
VETOR_PESSOAS *getVetorPessoas(char filepath[]);