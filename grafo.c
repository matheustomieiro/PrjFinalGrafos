#include "grafo.h"

struct noaresta{
	Pessoa *usuario_ligado;
	double afinidade;
	NoAresta *prox;
};

struct novertice{
	int convites[100];
	int nConvites;
	Pessoa *usuario;
	NoAresta *ini_amigos, *fim_amigos;
	int grau_amigos;
	NoAresta *ini_sugeridos, *fim_sugeridos;
	int grau_sugeridos;
};

struct grafo{
	int pos_famoso;
	int pos_legal;
	int numVertices;
	NoVertice adj[MAX_NUM_VERTICES];
};


Grafo *criar_grafo(){
	Grafo *G = (Grafo *) calloc(1, sizeof(Grafo));
	if(G){
		G->numVertices = 0;
		G->pos_famoso = -1;
		G->pos_legal = -1;
		for(int i=0; i<MAX_NUM_VERTICES; i++){
			G->adj[i].ini_amigos = NULL;
			G->adj[i].ini_sugeridos = NULL;
			G->adj[i].fim_amigos = NULL;
			G->adj[i].fim_sugeridos = NULL;
			G->adj[i].usuario = NULL;
		}
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
			afinidade = calcular_afinidade(G, G->numVertices, i);
			//insere aresta de sugerido se afinidade for maior que 100...
			if(afinidade >= 90){
				inserir_aresta_amigo(G, G->numVertices, i);
				inserir_aresta_sugerido(G, G->numVertices, i, afinidade);
			}	
			else if(afinidade >= 70) inserir_aresta_sugerido(G, G->numVertices, i, afinidade);
		}
		if(G->pos_famoso == -1 || (G->adj[G->numVertices].grau_amigos > G->adj[G->pos_famoso].grau_amigos)){
			G->pos_famoso = G->numVertices;
		}
		if(G->pos_legal == -1 || (G->adj[G->numVertices].grau_sugeridos > G->adj[G->pos_legal].grau_sugeridos)){
			G->pos_legal = G->numVertices;
		}		
		G->numVertices++;
	}

}


void recuperar_usuarios_preenchimento(Grafo *G, FILE *arquivo){
	fscanf(arquivo, "%*[^\n]%*c"); //ignora a primeira linha do csv
	char teste;
	//enquanto não chega no fim do arquivo
	while((teste = fgetc(arquivo)) != EOF){
		fseek(arquivo, -1, SEEK_CUR);
		Pessoa *P = criar_pessoa();
		ler_informacoes(P, arquivo);
		G->adj[G->numVertices++].usuario = P;

		busca_largura(G, G->pos_famoso, G->pos_legal, G->numVertices-1);
	}

}

void ordenar_vertices(Grafo *G){
	//ordena array de vértices pelo username de cada vértice/usuário
	merge_sort(G->adj, 0, G->numVertices-1);
	for(int i=0; i<G->numVertices; i++){
		if(G->pos_famoso == -1 || (G->adj[i].grau_amigos > G->adj[G->pos_famoso].grau_amigos)){
			G->pos_famoso = i;
		}
		if(G->pos_legal == -1 || (G->adj[i].grau_sugeridos > G->adj[G->pos_legal].grau_sugeridos)){
			G->pos_legal = i;
		}
	}
}


double calcular_afinidade(Grafo *G, int v1, int v2){
	double afinidade = 0;
	//PROCESSO DE DEFINIÇÃO DA AFINIDADE
	if(nomes_iguais(G->adj[v1].usuario, G->adj[v2].usuario)) afinidade += 15;
	afinidade += faixa_etaria(G->adj[v1].usuario, G->adj[v2].usuario);
	if(cidades_iguais(G->adj[v1].usuario, G->adj[v2].usuario)) afinidade += 50;
	if(filmes_iguais(G->adj[v1].usuario, G->adj[v2].usuario)) afinidade += 25;
	if(times_iguais(G->adj[v1].usuario, G->adj[v2].usuario)) afinidade += 25;
	if(cores_iguais(G->adj[v1].usuario, G->adj[v2].usuario)) afinidade += 15;
	afinidade = (afinidade / 90) * 100;
	//if(afinidade > 100) afinidade = 100;
	return afinidade;
}


void inserir_aresta_sugerido(Grafo *G, int v1, int v2, double afinidade){
	if(G && v1 <= G->numVertices && v2 <= G->numVertices){
		if(!(G->adj[v1].ini_sugeridos)){
			/*Insere no inicio*/
			G->adj[v1].ini_sugeridos = (NoAresta *)malloc(sizeof(NoAresta));
			G->adj[v1].ini_sugeridos->prox = NULL;
			G->adj[v1].grau_sugeridos++;
			G->adj[v1].ini_sugeridos->usuario_ligado = G->adj[v2].usuario;
			G->adj[v1].ini_sugeridos->afinidade = afinidade;
			G->adj[v1].fim_sugeridos = G->adj[v1].ini_sugeridos;	
		}else{
			/*Insere no fim*/
			G->adj[v1].fim_sugeridos->prox = (NoAresta *)malloc(sizeof(NoAresta));
			G->adj[v1].fim_sugeridos->prox->prox = NULL;
			G->adj[v1].grau_sugeridos++;
			G->adj[v1].fim_sugeridos = G->adj[v1].fim_sugeridos->prox;
			G->adj[v1].fim_sugeridos->usuario_ligado = G->adj[v2].usuario;
			G->adj[v1].fim_sugeridos->afinidade = afinidade;
		}	
		if(!(G->adj[v2].ini_sugeridos)){
			/*Insere no inicio*/
			G->adj[v2].ini_sugeridos = (NoAresta *)malloc(sizeof(NoAresta));
			G->adj[v2].ini_sugeridos->prox = NULL;
			G->adj[v2].grau_sugeridos++;
			G->adj[v2].ini_sugeridos->usuario_ligado = G->adj[v1].usuario;
			G->adj[v2].ini_sugeridos->afinidade = afinidade;
			G->adj[v2].fim_sugeridos = G->adj[v2].ini_sugeridos;
		}else{
			/*Insere no fim*/
			G->adj[v2].fim_sugeridos->prox = (NoAresta*)malloc(sizeof(NoAresta));
			G->adj[v2].fim_sugeridos->prox->prox = NULL;
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
			G->adj[v1].ini_amigos->prox = NULL;
			G->adj[v1].grau_amigos++;
			G->adj[v1].ini_amigos->usuario_ligado = G->adj[v2].usuario;
			G->adj[v1].fim_amigos = G->adj[v1].ini_amigos;	
		}else{
			/*Insere no fim*/
			G->adj[v1].fim_amigos->prox = (NoAresta *)malloc(sizeof(NoAresta));
			G->adj[v1].fim_amigos->prox->prox = NULL;
			G->adj[v1].grau_amigos++;
			G->adj[v1].fim_amigos = G->adj[v1].fim_amigos->prox;
			G->adj[v1].fim_amigos->usuario_ligado = G->adj[v2].usuario;
		}	
		if(!(G->adj[v2].ini_amigos)){
			/*Insere no inicio*/
			G->adj[v2].ini_amigos = (NoAresta *)malloc(sizeof(NoAresta));
			G->adj[v2].ini_amigos->prox = NULL;
			G->adj[v2].grau_amigos++;
			G->adj[v2].ini_amigos->usuario_ligado = G->adj[v1].usuario;
			G->adj[v2].fim_amigos = G->adj[v2].ini_amigos;
		}else{
			/*Insere no fim*/
			G->adj[v2].fim_amigos->prox = (NoAresta*)malloc(sizeof(NoAresta));
			G->adj[v2].fim_amigos->prox->prox = NULL;
			G->adj[v2].grau_amigos++;
			G->adj[v2].fim_amigos = G->adj[v2].fim_amigos->prox;
			G->adj[v2].fim_amigos->usuario_ligado = G->adj[v1].usuario;
		}
	}
}


int existe_aresta_amigo(Grafo *G, int v1, int v2){
	if(G != NULL && v1 < G->numVertices && v2 < G->numVertices && G->adj[v1].grau_amigos != 0 && G->adj[v2].grau_amigos != 0){
		for(NoAresta *a=G->adj[v1].ini_amigos; a!=NULL; a=a->prox){
			if(posicao_vertice(G, get_username(a->usuario_ligado)) == v2)
				return 1;
		}
	}	
	return 0;
}


int existe_aresta_amigo_2(Grafo *G, int v1, int v2){
	if(G != NULL && v1 < G->numVertices && v2 < G->numVertices && G->adj[v1].grau_amigos != 0 && G->adj[v2].grau_amigos != 0){
		for(NoAresta *a=G->adj[v1].ini_amigos; a!=NULL; a=a->prox){
			if(a->usuario_ligado == G->adj[v2].usuario)
				return 1;
		}
	}	
	return 0;
}


int existe_aresta_sugerido(Grafo *G, int v1, int v2){
	if(G != NULL && v1 < G->numVertices && v2 < G->numVertices && G->adj[v1].grau_sugeridos != 0 && G->adj[v2].grau_sugeridos != 0){
		for(NoAresta *a=G->adj[v1].ini_sugeridos; a!=NULL; a=a->prox){
			if(posicao_vertice(G, get_username(a->usuario_ligado)) == v2)
				return 1;
		}
	}	
	return 0;
}


int existe_aresta_sugerido_2(Grafo *G, int v1, int v2){
	if(G != NULL && v1 < G->numVertices && v2 < G->numVertices && G->adj[v1].grau_sugeridos != 0 && G->adj[v2].grau_sugeridos != 0){
		for(NoAresta *a=G->adj[v1].ini_sugeridos; a!=NULL; a=a->prox){
			if(a->usuario_ligado == G->adj[v2].usuario)
				return 1;
		}
	}	
	return 0;
}


void visita_bfs_sugeridos(Grafo *G, int v, int cor[], int pos_novo, int *qtd_sugeridos){
	int fimListaAdj, peso, adj, aux, afinidade;
	fila *F;
	F = fila_criar();
	cor[v] = 1;
	fila_inserir(F, v);
	while(!fila_vazia(F)){
		v = fila_retirar(F);
		if(v != pos_novo && (afinidade = calcular_afinidade(G, v, pos_novo)) >= 70 && (!existe_aresta_sugerido_2(G, pos_novo, v))){
			(*qtd_sugeridos)++;
			inserir_aresta_sugerido(G, v, pos_novo, afinidade);
			if(G->adj[v].grau_sugeridos > G->adj[G->pos_legal].grau_sugeridos) G->pos_legal = v;
			if(*qtd_sugeridos >= 3) return;
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
	fila_apagar(F);	
}

void visita_bfs_amigos(Grafo *G, int v, int cor[], int pos_novo, int *qtd_sugeridos){
	int fimListaAdj, peso, adj, aux, afinidade;
	fila *F;
	F = fila_criar();
	cor[v] = 1;
	fila_inserir(F, v);
	while(!fila_vazia(F)){
		v = fila_retirar(F);
		if(v != pos_novo && (afinidade = calcular_afinidade(G, v, pos_novo)) >= 70 && (!existe_aresta_sugerido_2(G, pos_novo, v))){
			(*qtd_sugeridos)++;
			inserir_aresta_sugerido(G, v, pos_novo, afinidade);
			if(G->adj[v].grau_sugeridos > G->adj[G->pos_legal].grau_sugeridos) G->pos_legal = v;
			if(*qtd_sugeridos >= 3) return;
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
	fila_apagar(F);	
}


void busca_largura(Grafo *G, int pos_famoso, int pos_legal, int pos_novo){
	int qtd_sugeridos = 0;
	int v, cor[G->numVertices];
	for(v=0; v<G->numVertices; v++){
		cor[v] = 0;
	}
	visita_bfs_sugeridos(G, pos_legal, cor, pos_novo, &qtd_sugeridos);
	if(qtd_sugeridos < 3)
		visita_bfs_amigos(G, pos_famoso, cor, pos_novo, &qtd_sugeridos);
	if(qtd_sugeridos == 0){
		//sugere o mais famoso da rede e o mais legal
		inserir_aresta_sugerido(G, pos_novo, pos_famoso, 70);
		if(!existe_aresta_sugerido_2(G, pos_novo, pos_legal)) inserir_aresta_sugerido(G, pos_novo, pos_legal, 70);
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
		printf("Sem amigos... tururuuu\n");
		system("{ mpg321 -g 100 forever_alone.mp3; } 2> /dev/null");
	}else{
		printf("---------------------------------------------\n");
		printf("Amigos(%d): ", G->adj[pos].grau_amigos);
		for(NoAresta *i=G->adj[pos].ini_amigos; i!=NULL; i=i->prox){
			printf(" %s,", get_username(i->usuario_ligado));
		}
		printf("\n---------------------------------------------\n");
	}

}


void listar_amigos_nao_sugeridos(Grafo *G, int pos){
	if(G->adj[pos].grau_amigos == 0){
		printf("Sem amigos... tururuuu\n");
		system("{ mpg321 -g 100 forever_alone.mp3; } 2> /dev/null");
	}else{
		printf("---------------------------------------------\n");
		printf("Amigos maçãs podres: ");
		for(NoAresta *i=G->adj[pos].ini_amigos; i!=NULL; i=i->prox){
			if(!existe_aresta_sugerido(G, pos, posicao_vertice(G, get_username(i->usuario_ligado))))
				printf(" %s,", get_username(i->usuario_ligado));
		}
		printf("\n---------------------------------------------\n");
	}

}


void listar_sugeridos(Grafo *G, int pos){
	printf("---------------------------------------------\n");
	printf("Sugeridos: ");
	for(NoAresta *i=G->adj[pos].ini_sugeridos; i!=NULL; i=i->prox){
		if(!existe_aresta_amigo(G, pos, posicao_vertice(G, get_username(i->usuario_ligado))))
			printf(" %s,", get_username(i->usuario_ligado));
	}
	printf("\n---------------------------------------------\n");

}

void indicar_interesse_romantico(Grafo *G, int pos){
	int pos_paixao = -1, pos_atual;
	double maior_afinidade = 0, afinidade_atual;
	for(NoAresta *i=G->adj[pos].ini_sugeridos; i!=NULL; i=i->prox){
		pos_atual = posicao_vertice(G, get_username(i->usuario_ligado));
		afinidade_atual = get_afinidade(G, pos, pos_atual);
		if((pos_paixao == -1) || (afinidade_atual > maior_afinidade)){
			pos_paixao = pos_atual;
			maior_afinidade = afinidade_atual;	
		}
	}
	if(maior_afinidade > 100) maior_afinidade = 100;
	printf("---------------------------------------------\n");
	if(pos_paixao != -1){
		printf("ATENÇÃO, sua alma gêmea é...\n");
		printf(" ♥♥♥♥♥   ♥♥♥♥♥\n");
		printf("♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥♥\n");
		printf("%s - %.2lf%%\n", get_username(acessar_usuario(G, pos_paixao)), maior_afinidade);
		printf(" ♥♥♥♥♥♥♥♥♥♥♥♥♥♥\n");
		printf("    ♥♥♥♥♥♥♥♥\n");
		printf("      ♥♥♥♥\n");
		printf("       ♥♥\n");	
	}
	else{
		printf("Infelizmente, tu nasceu pra viver sozinho...\n");	
		system("{ mpg321 -g 150 forever_alone.mp3; } 2> /dev/null");
	}
	printf("---------------------------------------------\n");	
}

void verificar_convites(Grafo *G, int v){
	char c;
	double afinidade;
	for(int i=0; i<G->adj[v].nConvites; i++){
		int pos_amigo = G->adj[v].convites[i];
		do{
			afinidade = get_afinidade(G, pos_amigo, v);
			if(afinidade > 100) afinidade = 100;
			printf("%s quer ser seu amigo e a chance da amizade ser verdadeira é de %.2lf%%.\nVocê aceita o convite?[S/N]\n", get_username(G->adj[pos_amigo].usuario), afinidade);
			c = getchar();
			getchar();
			if(c == 's' || c == 'S'){
				inserir_aresta_amigo(G, v, pos_amigo);
				printf("%s agora é seu amigo!\n", get_username(G->adj[pos_amigo].usuario));		
			}
		}while(c != 's' && c != 'n' && c != 'S' && c != 'N');
		G->adj[v].convites[i] = 0;
	}
	G->adj[v].nConvites = 0;
}


int existe_convites(Grafo *G, int v){
	return (G->adj[v].nConvites > 0); 
}


double get_afinidade(Grafo *G, int v1, int v2){
	if(G != NULL && v1 <= G->numVertices && v2 <= G->numVertices){
		NoAresta *atual = G->adj[v1].ini_sugeridos;
		while(atual != NULL && posicao_vertice(G, get_username(atual->usuario_ligado)) != v2){
			atual = atual->prox;
		}
		if(atual != NULL){
			return atual->afinidade;
		}
	}
	return 0;
}

int caixa_convites_cheia(Grafo *G, int v){
	return (G->adj[v].nConvites >= 100);
}


void adicionar_convite(Grafo *G, int v1, int v2){
	G->adj[v2].convites[G->adj[v2].nConvites++] = v1;
}


int registro_valido(Grafo *G, Pessoa *usuario){
	if(posicao_vertice(G, get_username(usuario)) >= 0){
		return 0;
	}
	return 1;
}

void inserir_vertice(Grafo *G, Pessoa *usuario){

	G->adj[G->numVertices].usuario = usuario;

	int i = G->numVertices;
	NoVertice aux;
	//shift
	while((i>0) && (strcmp(get_username(G->adj[i-1].usuario), get_username(G->adj[i].usuario)) > 0)){
		aux = G->adj[i-1];
		G->adj[i-1] = G->adj[i];
		G->adj[i] = aux;
		if((i-1) == G->pos_famoso) G->pos_famoso++;
		if((i-1) == G->pos_legal) G->pos_legal++;
		i--;
	}

	G->numVertices++;

	busca_largura(G, G->pos_famoso, G->pos_legal, i);

	
}

void remover_aresta_amigo(Grafo *G, int v1, int v2){
	if(G != NULL && v1 < G->numVertices && v2 < G->numVertices){		
		NoAresta *ant = G->adj[v1].ini_amigos;
		if(posicao_vertice(G, get_username(ant->usuario_ligado)) == v2){
			/*Está no início*/
			G->adj[v1].ini_amigos = G->adj[v1].ini_amigos->prox;
			free(ant);
		}else{
			NoAresta *atual = ant->prox;
			while(atual != NULL && posicao_vertice(G, get_username(atual->usuario_ligado)) != v2){
				ant = ant->prox;
				atual = atual->prox;
			}
			if(atual){
				if(atual == G->adj[v1].fim_amigos){
					/*Achou no fim*/	
					G->adj[v1].fim_amigos = ant;
				}
				else{
					/*Achou no meio*/		
					ant->prox = atual->prox;
				}
				free(atual);
				atual = NULL;
			}	
		}
		ant = G->adj[v2].ini_amigos;
		if(posicao_vertice(G, get_username(ant->usuario_ligado)) == v1){
			/*Está no início*/
			G->adj[v2].ini_amigos = G->adj[v2].ini_amigos->prox;
			free(ant);
		}else{
			NoAresta *atual = ant->prox;
			while(posicao_vertice(G, get_username(atual->usuario_ligado)) != v1){
				ant = ant->prox;
				atual = atual->prox;
			}	
			if(atual == G->adj[v2].fim_amigos){
				/*Achou no fim_amigos*/	
				G->adj[v2].fim_amigos = ant;
			}
			else{
				/*Achou no meio*/	
				ant->prox = atual->prox;
			}
			free(atual);
			atual = NULL;
		}	
	}	
}


void remover_aresta_sugerido(Grafo *G, int v1, int v2){
	if(G != NULL && v1 < G->numVertices && v2 < G->numVertices){		
		NoAresta *ant = G->adj[v1].ini_sugeridos;
		if(posicao_vertice(G, get_username(ant->usuario_ligado)) == v2){
			/*Está no início*/
			G->adj[v1].ini_sugeridos = G->adj[v1].ini_sugeridos->prox;
			free(ant);
		}else{
			NoAresta *atual = ant->prox;
			while(atual != NULL && posicao_vertice(G, get_username(atual->usuario_ligado)) != v2){
				ant = ant->prox;
				atual = atual->prox;
			}
			if(atual){
				if(atual == G->adj[v1].fim_sugeridos){
					/*Achou no fim*/	
					G->adj[v1].fim_sugeridos = ant;
				}
				else{
					/*Achou no meio*/		
					ant->prox = atual->prox;
				}
				free(atual);
				atual = NULL;
			}	
		}
		ant = G->adj[v2].ini_sugeridos;
		if(posicao_vertice(G, get_username(ant->usuario_ligado)) == v1){
			/*Está no início*/
			G->adj[v2].ini_sugeridos = G->adj[v2].ini_sugeridos->prox;
			free(ant);
		}else{
			NoAresta *atual = ant->prox;
			while(posicao_vertice(G, get_username(atual->usuario_ligado)) != v1){
				ant = ant->prox;
				atual = atual->prox;
			}	
			if(atual == G->adj[v2].fim_sugeridos){
				/*Achou no fim_sugeridos*/	
				G->adj[v2].fim_sugeridos = ant;
			}
			else{
				/*Achou no meio*/	
				ant->prox = atual->prox;
			}
			free(atual);
			atual = NULL;
		}	
	}	
}


void remover_vertice(Grafo *G, int pos){
	int reajuste_famoso, reajuste_legal;
	reajuste_famoso = (pos == G->pos_famoso);
	reajuste_legal = (pos == G->pos_legal);
	//shift
	NoVertice aux;
	for(int i=pos; i<G->numVertices-1; i++){
		aux = G->adj[i];
		G->adj[i] = G->adj[i+1];
		G->adj[i+1] = aux;
		if((i+1) == G->pos_famoso) G->pos_famoso--;
		if((i+1) == G->pos_legal) G->pos_legal--;
	}

	//remove as arestas
	for(NoAresta *a=G->adj[pos].ini_sugeridos; a!=NULL; a=a->prox){
		remover_aresta_sugerido(G, G->numVertices-1, posicao_vertice(G, get_username(a->usuario_ligado)));
	}

	for(NoAresta *a=G->adj[pos].ini_amigos; a!=NULL; a=a->prox){
		remover_aresta_amigo(G, G->numVertices-1, posicao_vertice(G, get_username(a->usuario_ligado)));
	}

	//remove o vértice
	remover_pessoa(G->adj[G->numVertices-1].usuario);
	G->numVertices--;

	if(reajuste_famoso){
		for(int i=0; i<G->numVertices; i++){
			if(G->pos_famoso == -1 || (G->adj[i].grau_amigos > G->adj[G->pos_famoso].grau_amigos)){
				G->pos_famoso = i;
			}
		}
	}
	if(reajuste_legal){
		for(int i=0; i<G->numVertices; i++){
			if(G->pos_legal == -1 || (G->adj[i].grau_sugeridos > G->adj[G->pos_legal].grau_sugeridos)){
				G->pos_legal = i;
			}
		}
	}

}


void limpar_grafo(Grafo *G){
	if(G != NULL){
		for(int i=0; i<G->numVertices; i++){
			NoAresta *rem = G->adj[i].ini_amigos, *prox;
			if(rem) prox = rem->prox; 
			while(rem){
				free(rem);
				rem = prox;
				if(prox) prox = prox->prox;
			}
			rem = G->adj[i].ini_sugeridos;
			if(rem) prox = rem->prox;
			while(rem){
				free(rem);
				rem = prox;
				if(prox) prox = prox->prox;
			}
			remover_pessoa(G->adj[i].usuario);
		}
		free(G);
	}	
}