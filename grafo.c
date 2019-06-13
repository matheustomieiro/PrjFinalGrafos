#include "grafo.h"

struct noaresta{
	Pessoa *usuario_ligado;
	double afinidade;
	NoAresta *prox;
};

struct novertice{
	Pessoa *usuario;
	NoAresta *ini_amigos, *fim_amigos;
	int grau_amigos;
	NoAresta *ini_sugeridos, *fim_sugeridos;
	int grau_sugeridos;
};

struct grafo{
	int pos_famoso;
	int numVertices;
	NoVertice adj[MAX_NUM_VERTICES];
};


Grafo *criar_grafo(){
	Grafo *G = (Grafo *) calloc(1, sizeof(Grafo));
	if(G){
		G->numVertices = 0;
		G->pos_famoso = -1;
	}
	return G;
}


/*Função merge(intercala):
 Pega dois vetores previamente ordenados e os intercala formando um só vetor ordenado*/
void merge(NoVertice *vet, int ini, int meio, int fim){
	NoVertice *aux = (NoVertice*)malloc((fim-ini+1) * sizeof(NoVertice));
	int i, j, k;	
    for(i=ini, j=meio+1, k=0; i<=meio && j<=fim; k++){	//Ordena os dois 'blocos'
    	if(strcmp(get_username(vet[i].usuario), get_username(vet[j].usuario)) < 0)
    		aux[k] = vet[i++];
    	else
    		aux[k] = vet[j++];
    }
    while(i <= meio){  //Caso ainda haja elementos na primeira metade
        aux[k++] = vet[i++];
    }
    while(j <= fim){   //Caso ainda haja elementos na segunda metade
        aux[k++] = vet[j++];
    }
    for(k = ini; k <= fim; k++){//Move os elementos de volta para o vetor original
        vet[k] = aux[k-ini];
    }
    free(aux);
}


/* Funcao de ordenacao Mergesort:
	Algoritmo de divisão e conquista onde se ordena, primeiro, pequenos vetores, e depois os junta formando um só vetor ordenado;	
   Parametros:
      int* v - vetor a ser ordenado
      int  ini - posição inicial do vetor
      int fim - posição final do vetor*/
void merge_sort(NoVertice *vet, int ini, int fim){
	if(fim <= ini)	return;
	int meio = (int) (ini+fim)/2;	
	merge_sort(vet, ini, meio);
	merge_sort(vet, meio+1, fim);
	merge(vet, ini, meio, fim);
}


void recuperar_usuarios_base(Grafo *G, FILE *arquivo){
	fscanf(arquivo, "%*[^\n]%*c"); //ignora a primeira linha do csv
	char teste;
	//enquanto não chega no fim do arquivo
	while((teste = fgetc(arquivo)) != EOF){
		fseek(arquivo, -1, SEEK_CUR);
		Pessoa *P = criar_pessoa();
		ler_informacoes(P, arquivo);
		G->adj[G->numVertices].usuario = P;
		double afinidade;
		for(int i=G->numVertices-1; i>=0; i--){
			//PROCESSO DE DEFINIÇÃO DA AFINIDADE
			//precisa de no mínimo 2 caracteristicas iguais para ser recomendado
			//e 3 características já é amigo
			afinidade = verificar_afinidade(G, G->numVertices, i));
			//insere aresta de sugerido se afinidade for maior que 100...
			if(afinidade >= 2) inserir_aresta_sugerido(G, G->numVertices, i, afinidade);
			if(afinidade >= 4) inserir_aresta_amigo(G, G->numVertices, i);
		}
		if(G->pos_famoso == -1 || (G->adj[G->numVertices].grau_amigos > G->adj[G->pos_famoso].grau_amigos)){
			pos_famoso = G->numVertices;
		}	
		G->numVertices++;
	}

	//ordena array de vértices pelo username de cada vértice/usuário
	//merge_sort(G->adj, 0, G->numVertices-1);

	/*for(int i=0; i<G->numVertices; i++){
		imprimir_pessoa(G->adj[i].usuario);
	}*/

}


void recuperar_usuarios_preenchimento(Grafo *G, FILE *arquivo){
	fscanf(arquivo, "%*[^\n]%*c"); //ignora a primeira linha do csv
	char teste;
	//enquanto não chega no fim do arquivo
	while((teste = fgetc(arquivo)) != EOF){
		fseek(arquivo, -1, SEEK_CUR);
		Pessoa *P = criar_pessoa();
		ler_informacoes(P, arquivo);
		G->adj[G->numVertices].usuario = P;

		busca_largura(G, G->pos_famoso, G->numVertices);

		G->numVertices++;
	}

	//ordena array de vértices pelo username de cada vértice/usuário
	merge_sort(G->adj, 0, G->numVertices-1);

	/*for(int i=0; i<G->numVertices; i++){
		imprimir_pessoa(G->adj[i].usuario);
	}*/

}


int verificar_afinidade(Grafo *G, int v1, int v2){
	int afinidade = 0;
	//PROCESSO DE DEFINIÇÃO DA AFINIDADE
	//precisa de no mínimo 2 caracteristicas iguais para ser recomendado
	//e 3 características já é amigo
	if(nomes_iguais(G->adj[v1].usuario, G->adj[v2].usuario)) afinidade ++;
	if(idades_iguais(G->adj[v1].usuario, G->adj[v2].usuario)) afinidade++;
	if(cidades_iguais(G->adj[v1].usuario, G->adj[v2].usuario)) afinidade ++;
	if(filmes_iguais(G->adj[v1].usuario, G->adj[v2].usuario)) afinidade ++;
	if(times_iguais(G->adj[v1].usuario, G->adj[v2].usuario)) afinidade ++;
	if(cores_iguais(G->adj[v1].usuario, G->adj[v2].usuario)) afinidade ++;
	return afinidade;
}


void inserir_aresta_sugerido(Grafo *G, int v1, int v2, double afinidade){
	if(G && v1 <= G->numVertices && v2 <= G->numVertices){
		if(!(G->adj[v1].ini_sugeridos)){
			/*Insere no inicio*/
			G->adj[v1].ini_sugeridos = (NoAresta *)malloc(sizeof(NoAresta));
			G->adj[v1].grau_sugeridos++;
			G->adj[v1].ini_sugeridos->usuario_ligado = G->adj[v2].usuario;
			G->adj[v1].ini_sugeridos->afinidade = afinidade;
			G->adj[v1].fim_sugeridos = G->adj[v1].ini_sugeridos;	
		}else{
			/*Insere no fim*/
			G->adj[v1].fim_sugeridos->prox = (NoAresta *)malloc(sizeof(NoAresta));
			G->adj[v1].grau_sugeridos++;
			G->adj[v1].fim_sugeridos = G->adj[v1].fim_sugeridos->prox;
			G->adj[v1].fim_sugeridos->usuario_ligado = G->adj[v2].usuario;
			G->adj[v1].fim_sugeridos->afinidade = afinidade;
		}	
		if(!(G->adj[v2].ini_sugeridos)){
			/*Insere no inicio*/
			G->adj[v2].ini_sugeridos = (NoAresta *)malloc(sizeof(NoAresta));
			G->adj[v2].grau_sugeridos++;
			G->adj[v2].ini_sugeridos->usuario_ligado = G->adj[v1].usuario;
			G->adj[v2].ini_sugeridos->afinidade = afinidade;
			G->adj[v2].fim_sugeridos = G->adj[v2].ini_sugeridos;
		}else{
			/*Insere no fim*/
			G->adj[v2].fim_sugeridos->prox = (NoAresta*)malloc(sizeof(NoAresta));
			G->adj[v2].grau_sugeridos++;
			G->adj[v2].fim_sugeridos = G->adj[v2].fim_sugeridos->prox;
			G->adj[v2].fim_sugeridos->usuario_ligado = G->adj[v1].usuario;
			G->adj[v2].fim_sugeridos->afinidade = afinidade;
		}
	}
}

void inserir_aresta_amigo(Grafo *G, int v1, int v2){
	if(G && v1 <= G->numVertices && v2 <= G->numVertices){
		if(!(G->adj[v1].ini_amigos)){
			/*Insere no inicio*/
			G->adj[v1].ini_amigos = (NoAresta *)malloc(sizeof(NoAresta));
			G->adj[v1].grau_amigos++;
			G->adj[v1].ini_amigos->usuario_ligado = G->adj[v2].usuario;
			G->adj[v1].fim_amigos = G->adj[v1].ini_amigos;	
		}else{
			/*Insere no fim*/
			G->adj[v1].fim_amigos->prox = (NoAresta *)malloc(sizeof(NoAresta));
			G->adj[v1].grau_amigos++;
			G->adj[v1].fim_amigos = G->adj[v1].fim_amigos->prox;
			G->adj[v1].fim_amigos->usuario_ligado = G->adj[v2].usuario;
		}	
		if(!(G->adj[v2].ini_amigos)){
			/*Insere no inicio*/
			G->adj[v2].ini_amigos = (NoAresta *)malloc(sizeof(NoAresta));
			G->adj[v2].grau_amigos++;
			G->adj[v2].ini_amigos->usuario_ligado = G->adj[v1].usuario;
			G->adj[v2].fim_amigos = G->adj[v2].ini_amigos;
		}else{
			/*Insere no fim*/
			G->adj[v2].fim_amigos->prox = (NoAresta*)malloc(sizeof(NoAresta));
			G->adj[v2].grau_amigos++;
			G->adj[v2].fim_amigos = G->adj[v2].fim_amigos->prox;
			G->adj[v2].fim_amigos->usuario_ligado = G->adj[v1].usuario;
		}
	}
}


void visita_bfs_sugeridos(Grafo *G, int v, int cor[], int pos_novo, int *qtd_sugeridos){
	int fimListaAdj, peso, adj, aux, afinidade;
	fila *F;
	F = fila_criar();
	cor[v] = 1;
	fila_inserir(F, v);
	while(!fila_vazia(F)){
		v = fila_retirar(F);
		if((afinidade = verificar_afinidade(G, v, pos_novo)) >= 2){
			(*qtd_sugeridos)++;
			inserir_aresta_sugerido(G, v, pos_novo, afinidade);
			if(*qtd_sugeridos >= 10) return;
		}			
		if(!listaSugeridoVazia(G, v)){
			aux = primeiroVerticeSugerido(G, v);
			fimListaAdj = 0;
			while(!fimListaAdj){
				adj = proximoVerticeSugerido(G, v, aux);
				fimListaAdj = (adj < 0);
				aux = adj;
				if(cor[adj] == 0){
					cor[adj] = 1;
					fila_inserir(F, adj);
				}
			}
		}
		cor[v] = 2;
	}	
}

void visita_bfs_amigos(Grafo *G, int v, int cor[], int pos_novo, int *qtd_sugeridos){
	int fimListaAdj, peso, adj, aux, afinidade;
	fila *F;
	F = fila_criar();
	cor[v] = 1;
	fila_inserir(F, v);
	while(!fila_vazia(F)){
		v = fila_retirar(F);
		if((afinidade = verificar_afinidade(G, v, pos_novo)) >= 2){
			(*qtd_sugeridos)++;
			inserir_aresta_sugerido(G, v, pos_novo, afinidade);
			if(*qtd_sugeridos >= 10) return;
		}			
		if(!listaAmigoVazia(G, v)){
			aux = primeiroVerticeAmigo(G, v);
			fimListaAdj = 0;
			while(!fimListaAdj){
				adj = proximoVerticeAmigo(G, v, aux);
				fimListaAdj = (adj < 0);
				aux = adj;
				if(cor[adj] == 0){
					cor[adj] = 1;
					fila_inserir(F, adj);
				}
			}
		}
		cor[v] = 2;
	}	
}


void busca_largura(Grafo *G, int pos_inicial, int pos_novo){
	int qtd_sugeridos = 0;
	int v, cor[G->numVertices];
	for(v=0; v<G->numVertices; v++){
		cor[v] = 0;
	}
	int v = pos_inicial;
	visita_bfs_sugeridos(G, v, distancia, cor, antecessor, pos_novo, &qtd_sugeridos);
	if(qtd_sugeridos < 10)
		visita_bfs_amigos(G, v, distancia, cor, antecessor, pos_novo, &qtd_sugeridos);
	
	if(qtd_sugeridos == 0){
		//sugere o mais famoso da rede
		inserir_aresta_sugerido(G, pos_novo, G->pos_famoso, 0);
	}
}


int listaAmigoVazia(Grafo *G, int v){
	if((G != NULL && v <= MAX_NUM_VERTICES) || G->adj[v].ini_amigos == NULL){
		return 1;
	}
	return 0;
}

int primeiroVerticeAmigo(Grafo *G, int v){
	if(G != NULL && v <= MAX_NUM_VERTICES){
		if(G->adj[v].ini_amigos != NULL) return posicao_vertice(G, get_username(G->adj[v].ini_amigos->usuario_ligado));
	}
	return -1;	
}

int proximoVerticeAmigo(Grafo *G, int v, int atual){
	if(G != NULL && v <= MAX_NUM_VERTICES && atual <= MAX_NUM_VERTICES){
		NoAresta *aux = G->adj[v].ini_amigos;
		while(posicao_vertice(G, get_username(aux->usuario_ligado)) != atual) aux = aux->prox;
		aux = aux->prox;
		if(aux != NULL){
			return posicao_vertice(G, get_username(aux->usuario_ligado));
		}
	}	
	return -1;		
}


int listaSugeridoVazia(Grafo *G, int v){
	if((G != NULL && v <= MAX_NUM_VERTICES) || G->adj[v].ini_sugeridos == NULL){
		return 1;
	}
	return 0;
}

int primeiroVerticeSugerido(Grafo *G, int v){
	if(G != NULL && v <= MAX_NUM_VERTICES){
		if(G->adj[v].ini_sugeridos != NULL) return posicao_vertice(G, get_username(G->adj[v].ini_sugeridos->usuario_ligado));
	}
	return -1;	
}

int proximoVerticeSugerido(Grafo *G, int v, int atual){
	if(G != NULL && v <= MAX_NUM_VERTICES && atual <= MAX_NUM_VERTICES){
		NoAresta *aux = G->adj[v].ini_sugeridos;
		while(posicao_vertice(G, get_username(aux->usuario_ligado)) != atual) aux = aux->prox;
		aux = aux->prox;
		if(aux != NULL){
			return posicao_vertice(G, get_username(aux->usuario_ligado));
		}
	}	
	return -1;		
}


int busca_binaria(NoVertice *vet, char *chave, int comeco, int fim){
	int centro = (comeco+fim)/2;
	if(comeco > fim) return -1;
	if(strcmp(get_username(vet[centro].usuario), chave) == 0) return centro;
	else{
		if(strcmp(get_username(vet[centro].usuario), chave) > 0)
			return busca_binaria(vet, chave, comeco, centro-1);
		else
			return busca_binaria(vet, chave, centro+1, fim);
	}
}

int posicao_vertice(Grafo *G, char *username){
	return (busca_binaria(G->adj, username, 0, G->numVertices-1));
}

Pessoa *acessar_usuario(Grafo *G, int pos){
	return G->adj[pos].usuario;
}

void listar_amigos(Grafo *G, int pos){
	if(G->adj[pos].grau_amigos == 0){
		system("mpg321 -g 5 /home/mateusp_8877/Desktop/naruto.mp3");
		printf("Sem amigos... tururuuu\n");
	}else{
		printf("amigos(%d): ", G->adj[pos].grau_amigos);
		for(NoAresta *i=G->adj[pos].ini_amigos; i!=NULL; i=i->prox){
			printf(" %s,", get_username(i->usuario_ligado));
		}
		printf("\n");
	}

	getchar();//esperar o usuário clicar para prosseguir

}


void listar_sugeridos(Grafo *G, int pos){
	
	printf("sugeridos(%d): ", G->adj[pos].grau_sugeridos);
	for(NoAresta *i=G->adj[pos].ini_sugeridos; i!=NULL; i=i->prox){
		printf(" %s,", get_username(i->usuario_ligado));
	}
	printf("\n");

	getchar();//esperar o usuário clicar para prosseguir

}