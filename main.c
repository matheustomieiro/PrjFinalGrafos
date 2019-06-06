#include "grafo.h"

void imprimir_menu_1();
void imprimir_menu_2();
void login(Grafo *G);

int main(){

	Grafo *G = criar_grafo();
	FILE *arquivo = fopen("data.csv", "r");
	recuperar_usuarios(G, arquivo);
	int opc;
	
	do{	
		imprimir_menu_1();
		scanf("%d", &opc);
		switch(opc){
			case 0:
				login(G);
				break;	
		}
		if(opc != 1){
			printf("***ERRO***\nDigite uma opção existente.\n");
		}
	}while(opc != 1);
	
	fclose(arquivo);

	return 0;
}


void imprimir_menu_1(){
	printf("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
	printf("\t\tFriendbook\n");
	printf("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
	printf("Escolha uma das opções a seguir:\n");
	printf("#Opção (0): Fazer Login.\n");
	printf("#Opção (1): Sair do Programa.\n");
	//printf("#Opção (2): Cadastrar-se.\n");
	printf("Digite o número correspondente:");
}

void imprimir_menu_2(char *username){
	printf("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
	printf("\tFriendbook - %s\n", username);
	printf("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
	printf("Escolha uma das opções a seguir:\n");
	printf("#Opção (0): Listar amigos.\n");
	printf("#Opção (1): Adicionar amigo.\n");
	printf("#Opção (2): Recomendações de amizade VERDADEIRA.\n");
	printf("#Opção (3): Listar amigos 'maçãs podres'.\n");
	printf("#Opção (4): Sair da conta.\n");
	printf("Digite o número correspondente:");
}

void login(Grafo *G){

	char username[256];
	int pin, entrou = 0;
	
	do{
		printf("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
		printf("Username:");
		scanf("%s", username);
		int pos_no_grafo;
		if((pos_no_grafo = existe_usuario(G, username)) >= 0){
			printf("Pin:");
			scanf("%d", &pin);
			if(getPin(acessar_usuario(G, pos_no_grafo) == pin){
				entrou = 1;
			}else printf("Senha Incorreta!\n");
		}else printf("Não existe este usuário!\n");
	}while(!entrou);

	int opc;
	
	do{	
		imprimir_menu_2(username);
		scanf("%d", &opc);
		switch(opc){
			case 0:
				break;
			case 1:
				break;
			case 2:
				break;
			case 3:
				break;
			case 4:
				break;
			default:
				printf("***ERRO***\nDigite uma opção existente.\n");							
		}
	}while((opc < 0 || opc > 4);	

}