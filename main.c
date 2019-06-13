#include "grafo.h"

void imprimir_menu_1();
void imprimir_menu_2();
void login(Grafo *G);

int main(){

	//Processo de criação do grafo:
	Grafo *G = criar_grafo();
	FILE *arquivo_base = fopen("data.csv", "r");
	FILE *arquivo_preenchimento = fopen("", "r");
	recuperar_usuarios_base(G, arquivo_base);
	recuperar_usuarios_preenchimento(G, arquivo_preenchimento);
	
	//Menu:
	int opc;
	
	do{	
		imprimir_menu_1();
		scanf(" %d", &opc);
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

	char username[256], amigo[256];
	int pin, entrou = 0, pos_logado, pos_amigo, opc;
	
	do{
		printf("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
		printf("Username:");
		scanf("%s%*c", username);
		if((pos_logado = posicao_vertice(G, username)) >= 0){
			printf("Pin:");
			scanf("%d", &pin);
			if(get_pin(acessar_usuario(G, pos_logado)) == pin){
				entrou = 1;
			}else printf("Senha Incorreta!\n");
		}else printf("Não existe este usuário!\n");
	}while(!entrou);
	
	do{	
		imprimir_menu_2(username);
		scanf(" %d", &opc);
		switch(opc){
			case 0:
				pos_logado = posicao_vertice(G, username);
				listar_amigos(G, pos_logado);
				break;
			case 1:
				printf("Digite o username de seu amigo:");
				scanf("%s%*c", amigo);
				pos_logado = posicao_vertice(G, username);
				if((pos_amigo = posicao_vertice(G, amigo)) >= 0){
					inserir_aresta_amigo(G, pos_logado, pos_amigo);
					printf("%s agora é seu amigo!\n", amigo);
				}else printf("o usuário %s não existe\n", amigo);
				break;
			case 2:
				pos_logado = posicao_vertice(G, username);
				listar_sugeridos(G, pos_logado);
				break;
			/*case 3:
				break;*/
			default:
				printf("***ERRO***\nDigite uma opção existente.\n");							
		}
	}while(opc != 4);	

}