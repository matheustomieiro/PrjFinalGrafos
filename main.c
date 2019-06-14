#include "grafo.h"

void imprimir_menu_1();
void imprimir_menu_2();
void login(Grafo *G);
void espera();
void easter_egg(char *username);

int main(){

	//Processo de criação do grafo:
	Grafo *G = criar_grafo();
	FILE *arquivo_base = fopen("inicial.csv", "r");
	FILE *arquivo_preenchimento = fopen("adicao.csv", "r");
	recuperar_usuarios_base(G, arquivo_base);
	recuperar_usuarios_preenchimento(G, arquivo_preenchimento);
	ordenar_vertices(G);

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
	
	fclose(arquivo_base);
	fclose(arquivo_preenchimento);

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
	//printf("#Opção (3): Remover Conta.\n");
	printf("Digite o número correspondente:");
}

void imprimir_menu_2(char *username){
	printf("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
	printf("\tFriendbook - %s\n", username);
	printf("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
	printf("Escolha uma das opções a seguir:\n");
	printf("#Opção (0): Listar Amigos.\n");
	printf("#Opção (1): Adicionar Amigo.\n");
	printf("#Opção (2): Recomendações de Amizade VERDADEIRA.\n");
	printf("#Opção (3): Listar Amigos 'Maçãs Podres'.\n");
	printf("#Opção (4): Sair da Conta.\n");
	printf("Digite o número correspondente:");
}

void login(Grafo *G){

	char username[256], amigo[256], c;
	int pin, entrou = 0, pos_logado, pos_amigo, opc;
	double afinidade;

	do{
		printf("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
		printf("Username:");
		scanf("%s%*c", username);
		if((pos_logado = posicao_vertice(G, username)) >= 0){
			printf("(dica de hacker:%d) Pin:", get_pin(acessar_usuario(G, pos_logado)));
			scanf("%d%*c", &pin);
			if(get_pin(acessar_usuario(G, pos_logado)) == pin){
				entrou = 1;
			}else printf("Senha Incorreta!\n");
		}else printf("Não existe este usuário!\n");
	}while(!entrou);
	
	easter_egg(username);

	if(existe_convites(G, pos_logado)){
		do{
			printf("Existem convites de amizade para você. Deseja vê-los?[S/N]\n");			
			c = getchar();
			getchar();
			if(c == 's' || c == 'S'){
				verificar_convites(G, pos_logado);
			}
		}while(c != 's' && c != 'n' && c != 'S' && c != 'N');
	}

	do{	
		imprimir_menu_2(username);
		scanf(" %d%*c", &opc);
		switch(opc){
			case 0:
				listar_amigos(G, pos_logado);
				espera();
				break;
			case 1:
				printf("Digite o username de quem você quer adicionar como amigo:");
				scanf("%s%*c", amigo);
				if((pos_amigo = posicao_vertice(G, amigo)) >= 0){			
					if(!existe_aresta_amigo(G, pos_logado, pos_amigo)){
						afinidade = get_afinidade(G, pos_logado, pos_amigo);
						printf("A chance de você ter amizade verdadeira com %s é %.2lf%%.\n", amigo, afinidade);
						do{
							printf("Tem certeza que vai mandar convite de amizade?[S/N]\n");
							c = getchar();
							getchar();
							if(c == 's' || c == 'S'){
								if(!caixa_convites_cheia(G, pos_amigo)){
									adicionar_convite(G, pos_logado, pos_amigo);
									printf("Espere até que %s responda seu convite!\n", amigo);
								}
								else printf("Caixa de convite de %s está lotada\n", amigo);
							}
						}while(c != 's' && c != 'n' && c != 'S' && c != 'N');	
					}
					else printf("%s já é seu amigo!\n", amigo);
				}else printf("o usuário %s não existe\n", amigo);
				espera();
				break;
			case 2:
				listar_sugeridos(G, pos_logado);
				espera();
				break;
			/*case 3:
				break;*/
			default:
				printf("***ERRO***\nDigite uma opção existente.\n");							
		}
	}while(opc != 4);	

}


void espera(){
	printf("Aperte ENTER para prosseguir...\n");
	scanf("%*[^\n]%*c");
}

void easter_egg(char *username){
	if(!strcmp(username, "roney")){
		system("{ mpg321 -g 100 sc.mp3; } 2> /dev/null");
	}
}