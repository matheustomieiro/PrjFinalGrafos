#ifndef GRAFO_H
#define GRAFO_H

#include "pessoa.h"

#define MAX_NUM_VERTICES 10000

typedef struct grafo Grafo;
typedef struct novertice NoVertice;
typedef struct noaresta NoAresta;

Grafo *criar_grafo();
void recuperar_usuarios_base(Grafo *G, FILE *arquivo);
void inserir_aresta_sugerido(Grafo *G, int v1, int v2, double afinidade);
void inserir_aresta_amigo(Grafo *G, int v1, int v2);
int posicao_vertice(Grafo *G, char *username);
Pessoa *acessar_usuario(Grafo *G, int pos);
void listar_amigos(Grafo *G, int pos);


#endif