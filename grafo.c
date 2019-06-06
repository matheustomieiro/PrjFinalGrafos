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
	int numVertices;
	NoVertice adj[MAX_NUM_VERTICES];
};


Grafo *criar_grafo(){
	Grafo *G = (Grafo *) calloc(1, sizeof(Grafo));
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


void recuperar_usuarios(Grafo *G, FILE *arquivo){
	fscanf(arquivo, "%*[^\n]%*c"); //ignora a primeira linha do csv
	char teste;
	//enquanto não chega no fim do arquivo
	while((teste = fgetc(arquivo)) != EOF){
		fseek(arquivo, -1, SEEK_CUR);
		Pessoa *P = criar_pessoa();
		ler_informacoes(P, arquivo);
		G->adj[G->numVertices].usuario = P;
		/*for(int i=G->numVertices-1; i>=0; i--){
			//PROCESSO DE DEFINIÇÃO DA AFINIDADE


			//inserir_aresta_sugerido(G, G->adj[->numVertices], i, afin);
		}*/	
		G->numVertices++;
	}

	//ordena array de vértices pelo username de cada vértice/usuário
	merge_sort(G->adj, 0, G->numVertices-1);

	/*for(int i=0; i<G->numVertices; i++){
		imprimir_pessoa(G->adj[i].usuario);
	}*/

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

