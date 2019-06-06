#ifndef GRAFO_H
#define GRAFO_H

#include "pessoa.h"
#include <string.h>

#define MAX_NUM_VERTICES 10000

typedef struct grafo Grafo;
typedef struct novertice NoVertice;
typedef struct noaresta NoAresta;

Grafo *criar_grafo();
void recuperar_usuarios(Grafo *G, FILE *arquivo);
void inserir_aresta_sugerido(Grafo *G, int v1, int v2, double afinidade);


#endif