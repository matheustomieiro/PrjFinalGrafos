/*
	Trabalho de Grafos - Rede Social de Amizade Verdadeira
	Professor: Tiago A. S. Pardo
	Monitor PAE: Roney Lira de Sales Santos
	
	Alunos:
	Mateus Prado Santos (10851707)
	Matheus Lopez Rigato (10260462)
	Matheus Tomieiro de Oliveira (10734630)

	Este programa simula uma rede social com recomendações de amizade verdadeira.

	A documentação está nos arquivos headers(.h);

*/


#include "grafo.h"

void imprimir_menu_1();
void imprimir_menu_2();
void login(Grafo *G);
void cadastrar(Grafo *G);
void espera();
void easter_egg(char *username);
void remover(Grafo *G);

int main(){

	//Processo de criação do grafo:
	Grafo *G = criar_grafo();
	FILE *arquivo_base = fopen("inicial.csv", "r");
	FILE *arquivo_preenchimento = fopen("adicao.csv", "r");
	recuperar_usuarios_base(G, arquivo_base);
	recuperar_usuarios_preenchimento(G, arquivo_preenchimento);
	ordenar_vertices(G);

	//Menu inicial:
	int opc;
	
	do{	
		imprimir_menu_1();
		scanf(" %d%*c", &opc);
		switch(opc){
			case 1:
				login(G);
				break;
			case 2:
				cadastrar(G);
				break;
			case 3:
				remover(G);
				break;			
		}
		if(opc < 0 || opc > 3){
			printf("***ERRO***\nDigite uma opção existente.\n");
		}
	}while(opc != 0);
	
	//liberação de memória e ponteiros para arquivos
	fclose(arquivo_base);
	fclose(arquivo_preenchimento);
	limpar_grafo(G);

	return 0;
}


void imprimir_menu_1(){
	printf("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
	printf("\t\tFriendbook\n");
	printf("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
	printf("Escolha uma das opções a seguir:\n");
	printf("#Opção (0): Sair do Programa.\n");
	printf("#Opção (1): Fazer Login.\n");
	printf("#Opção (2): Cadastrar-se.\n");
	printf("#Opção (3): Remover Conta.\n");
	printf("Digite o número correspondente:");
}

void imprimir_menu_2(char *username){
	printf("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
	printf("\tFriendbook - %s\n", username);
	printf("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
	printf("Escolha uma das opções a seguir:\n");
	printf("#Opção (0): Sair da Conta.\n");
	printf("#Opção (1): Listar Amigos.\n");
	printf("#Opção (2): Adicionar Amigo.\n");
	printf("#Opção (3): Remover Amigo.\n");
	printf("#Opção (4): Recomendações de Amizade VERDADEIRA.\n");
	printf("#Opção (5): Listar Amigos 'Maçãs Podres'.\n");
	printf("#Opção (6): Cupido.\n");
	printf("#Opção (7): Meu Perfil\n");
	printf("#Opção (8): Buscar Perfil.\n");
	printf("Digite o número correspondente:");
}

void login(Grafo *G){

	char username[256], amigo[256], c;
	int pin, entrou = 0, pos_logado, pos_amigo, opc;
	double afinidade;

	//Processo de login
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

	//Verifica se há convites de amizade
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

	//Menu de usuário.
	do{	
		imprimir_menu_2(username);
		scanf(" %d%*c", &opc);
		switch(opc){
			//listar amigos
			case 1:
				listar_amigos(G, pos_logado);
				espera();
				break;
			//adicionar amigos	
			case 2:
				printf("Digite o username de quem você quer adicionar como amigo:");
				scanf("%s%*c", amigo);
				if((pos_amigo = posicao_vertice(G, amigo)) >= 0){			
					if(!existe_aresta_amigo(G, pos_logado, pos_amigo)){
						afinidade = get_afinidade(G, pos_logado, pos_amigo);
						if(afinidade > 100) afinidade = 100;
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
			//remover amigos	
			case 3:
				printf("Digite o username do amigo que você quer remover:");
				scanf("%s%*c", amigo);
				if((pos_amigo = posicao_vertice(G, amigo)) >= 0){
					if(existe_aresta_amigo(G, pos_logado, pos_amigo)) remover_aresta_amigo(G, pos_logado, pos_amigo);
					else printf("o usuário %s não é seu amigo\n", amigo);
				}else printf("o usuário %s não existe\n", amigo);
				espera();
				break;
			//listar sugeridos	
			case 4:
				listar_sugeridos(G, pos_logado);
				espera();
				break;
			//listar amigos maças podres	
			case 5:
				listar_amigos_nao_sugeridos(G, pos_logado);
				espera();
				break;
			//mostrar suposto interesse romantico	
			case 6:
				indicar_interesse_romantico(G, pos_logado);
				espera();
				break;
			//imprimir dados do usuário logado	
			case 7:
				imprimir_pessoa(acessar_usuario(G, pos_logado));
				espera();
				break;	
			//imprimir dados de um usuário qualquer da rede
			case 8:
				printf("Digite o username do perfil que você quer ver:");
				scanf("%s%*c", amigo);
				if((pos_amigo = posicao_vertice(G, amigo)) >= 0){
					imprimir_pessoa(acessar_usuario(G, pos_amigo));
				}else printf("o usuário %s não existe\n", amigo);
				espera();
				break;
		}

		if(opc < 0 || opc > 8){
			printf("***ERRO***\nDigite uma opção existente.\n");							
		}

	}while(opc != 0);	

}

void cadastrar(Grafo *G){
	int valido = 0;
	Pessoa *P;
	do{
		//Registra os dados de uma pessoa verificando se são válidos
		P = registrar_pessoa();
		valido = registro_valido(G, P);
		if(!valido){
			printf("***ERRO***\nUsername digitado já existe.\n");
		}
	}while(!valido);
	//insere na rede	
	inserir_vertice(G, P);
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


void remover(Grafo *G){
	char username[256];
	int pos;
	//procura usuário na rede
	do{
		printf("Username:");
		scanf("%s%*c", username);
		pos = (posicao_vertice(G, username));
		if(pos < 0){
			printf("***ERRO***\nUsuário não existe.\n");
		}
	}while(pos < 0);
	//remove o usuário da rede
	remover_vertice(G, pos);

}