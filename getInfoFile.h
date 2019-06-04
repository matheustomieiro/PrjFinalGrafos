typedef struct pss{
	char nome[256];
	char username[256];
	int PIN;
	int idade;
	char cidade[256];
	char filme[256];
	char cor[256];
}PESSOA;

typedef struct vector{
	int tamanho;
	PESSOA **vetor;
}VETOR_PESSOAS;


void iniciaVetor(VETOR_PESSOAS *VET);
VETOR_PESSOAS getVetorPessoas(char filepath[]);
