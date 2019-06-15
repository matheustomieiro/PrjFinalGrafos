#ifndef GRAFO_H
#define GRAFO_H

#include "pessoa.h"
#include "fila.h"

#define MAX_NUM_VERTICES 10000

typedef struct grafo Grafo;
typedef struct novertice NoVertice;
typedef struct noaresta NoAresta;

Grafo *criar_grafo();
void recuperar_usuarios_base(Grafo *G, FILE *arquivo);
void recuperar_usuarios_preenchimento(Grafo *G, FILE *arquivo);
void ordenar_vertices(Grafo *G);
double calcular_afinidade(Grafo *G, int v1, int v2);
void inserir_aresta_sugerido(Grafo *G, int v1, int v2, double afinidade);
void inserir_aresta_amigo(Grafo *G, int v1, int v2);
int existe_aresta_amigo(Grafo *G, int v1, int v2);
int existe_aresta_amigo_2(Grafo *G, int v1, int v2);
int existe_aresta_sugerido(Grafo *G, int v1, int v2);
int existe_aresta_sugerido_2(Grafo *G, int v1, int v2);
void busca_largura(Grafo *G, int pos_famoso, int pos_legal, int pos_novo);
int listaAmigoVazia(Grafo *G, int v);
int primeiroVerticeAmigo(Grafo *G, int v);
int proximoVerticeAmigo(Grafo *G, int v, int atual);
int listaSugeridoVazia(Grafo *G, int v);
int primeiroVerticeSugerido(Grafo *G, int v);
int proximoVerticeSugerido(Grafo *G, int v, int atual);
int posicao_vertice(Grafo *G, char *username);
Pessoa *acessar_usuario(Grafo *G, int pos);
void listar_amigos(Grafo *G, int pos);
void listar_amigos_nao_sugeridos(Grafo *G, int pos);
void listar_sugeridos(Grafo *G, int pos);
void indicar_interesse_romantico(Grafo *G, int pos);
void verificar_convites(Grafo *G, int v);
int existe_convites(Grafo *G, int v);
double get_afinidade(Grafo *G, int v1, int v2);
int caixa_convites_cheia(Grafo *G, int v);
void adicionar_convite(Grafo *G, int v1, int v2);
int registro_valido(Grafo *G, Pessoa *usuario);
void inserir_vertice(Grafo *G, Pessoa *usuario);
void remover_aresta_amigo(Grafo *G, int v1, int v2);
void remover_aresta_sugerido(Grafo *G, int v1, int v2);
void remover_vertice(Grafo *G, int pos);
void limpar_grafo(Grafo *G);

#endif