#ifndef GRAFO_H
#define GRAFO_H

#include "pessoa.h"
#include "fila.h"

#define MAX_NUM_VERTICES 10000

typedef struct grafo Grafo;
typedef struct novertice NoVertice;
typedef struct noaresta NoAresta;

/* criar_grafo:
	Cria um grafo;
@Retorno:
	O grafo criado;
*/
Grafo *criar_grafo();

/* recuperar_usuarios_base:
	Recupera de um arquivo csv os dados dos usuários base da rede;
@Argumentos:
	Ponteiro para grafo;
	Ponteiro para o arquivo csv;
*/
void recuperar_usuarios_base(Grafo *G, FILE *arquivo);

/* recuperar_usuarios_preenchimento:
	Recupera de um arquivo csv os dados dos usuários de preenchimento da rede;
@Argumentos:
	Ponteiro para grafo;
	Ponteiro para o arquivo csv;
*/
void recuperar_usuarios_preenchimento(Grafo *G, FILE *arquivo);

/* ordenar_vertices:
	Ordena os vértices de um grafo pelo username;
@Argumentos:
	Ponteiro para grafo;
	Ponteiro para o arquivo csv;
*/
void ordenar_vertices(Grafo *G);

/* calcular_afinidade
	calcula a afinidade entre dois usuários;
@Argumentos:
	Ponteiro para grafo;
	Posição de cada vértice;
@Retorno:
	Afinidade entre os usuário em porcentagem;
*/
double calcular_afinidade(Grafo *G, int v1, int v2);

/* inserir_aresta_sugerido:
	Insere uma aresta de sugestão no grafo;
@Argumentos:
	Ponteiro para grafo;
	Posição de cada vértice;
*/
void inserir_aresta_sugerido(Grafo *G, int v1, int v2, double afinidade);

/* inserir_aresta_amigo:
	Insere uma aresta de amizade no grafo;
@Argumentos:
	Ponteiro para grafo;
	Posição de cada vértice;
*/
void inserir_aresta_amigo(Grafo *G, int v1, int v2);

/* existe_aresta_amigo:
	Verifica se existe uma aresta de amizade no grafo;
@Argumentos:
	Ponteiro para grafo;
	Posição de cada vértice;
@Retorno:
	Inteiro com 1 se existe ou 0 caso contrário;	
*/
int existe_aresta_amigo(Grafo *G, int v1, int v2);

/* existe_aresta_amigo_2:
	Verifica se existe uma aresta de amizade no grafo alternativo;
@Argumentos:
	Ponteiro para grafo;
	Posição de cada vértice;
@Retorno:
	Inteiro com 1 se existe ou 0 caso contrário;	
*/
int existe_aresta_amigo_2(Grafo *G, int v1, int v2);

/* existe_aresta_sugerido:
	Verifica se existe uma aresta de sugestão no grafo;
@Argumentos:
	Ponteiro para grafo;
	Posição de cada vértice;
@Retorno:
	Inteiro com 1 se existe ou 0 caso contrário;	
*/
int existe_aresta_sugerido(Grafo *G, int v1, int v2);

/* existe_aresta_sugerido_2:
	Verifica se existe uma aresta de sugestão no grafo alternativo;
@Argumentos:
	Ponteiro para grafo;
	Posição de cada vértice;
@Retorno:
	Inteiro com 1 se existe ou 0 caso contrário;	
*/
int existe_aresta_sugerido_2(Grafo *G, int v1, int v2);

/* busca_largura:
	Faz um percurso no grafo por busca em largura começando dos vértices de usuário mais legal e mais famoso
	tentando encontrar usuário com afinidade ao novo usuário adicionado do grafo;
@Argumentos:
	Ponteiro para grafo;
	Posição do usuário mais famoso;
	Posição do usuário mais legal(maior grau de sugeridos);
	Posição do usuário ao qual se deve encontrar outros com afinidade;
*/
void busca_largura(Grafo *G, int pos_famoso, int pos_legal, int pos_novo);

/* listaAmigoVazia:
	Verifica se a lista de adjacência de amigos de um vértice é vazia;
@Argumentos:
	Ponteiro para grafo;
	Posição do vértice;
@Retorno:
	Inteiro com 1 se está vazio ou 0 caso contrário;	
*/
int listaAmigoVazia(Grafo *G, int v);

/* primeiroVerticeAmigo:
	Encontra a posição do primeiro vértice da lista de adjacência de amizades de um vértice;
@Argumentos:
	Ponteiro para grafo;
	Posição do vértice;
@Retorno:
	Inteiro com a posição do primeiro vértice adjacente;	
*/
int primeiroVerticeAmigo(Grafo *G, int v);

/* proximoVerticeAmigo:
	Encontra a posição do próximo vértice da lista de adjacência de amizades de um vértice;
@Argumentos:
	Ponteiro para grafo;
	Posição do vértice;
	Posição do vértice atual na adjacência;
@Retorno:
	Inteiro com a posição do próximo vértice adjacente;	
*/
int proximoVerticeAmigo(Grafo *G, int v, int atual);

/* listaSugeridoVazia:
	Verifica se a lista de adjacência de sugeridos de um vértice é vazia;
@Argumentos:
	Ponteiro para grafo;
	Posição do vértice;
@Retorno:
	Inteiro com 1 se está vazio ou 0 caso contrário;	
*/
int listaSugeridoVazia(Grafo *G, int v);

/* primeiroVerticeSugerido:
	Encontra a posição do primeiro vértice da lista de adjacência de sugeridos de um vértice;
@Argumentos:
	Ponteiro para grafo;
	Posição do vértice;
@Retorno:
	Inteiro com a posição do primeiro vértice adjacente;	
*/
int primeiroVerticeSugerido(Grafo *G, int v);

/* proximoVerticeSugerido:
	Encontra a posição do próximo vértice da lista de adjacência de sugestões de um vértice;
@Argumentos:
	Ponteiro para grafo;
	Posição do vértice;
	Posição do vértice atual na adjacência;
@Retorno:
	Inteiro com a posição do próximo vértice adjacente;	
*/
int proximoVerticeSugerido(Grafo *G, int v, int atual);

/* posicao_vertice:
	Encontra a posição do usuário no grafo de acordo com seu username;
@Argumentos:
	Ponteiro para grafo;
	String com o username;
@Retorno:
	Inteiro com a posição do vértice;	
*/
int posicao_vertice(Grafo *G, char *username);

/* acessar_usuario:
	Acessa o usuário do vértice;
@Argumentos:
	Ponteiro para grafo;
	Inteiro com posição do vértice no grafo;
@Retorno:
	Ponteiro para a pessoa;	
*/
Pessoa *acessar_usuario(Grafo *G, int pos);

/* listar_amigos:
	Lista todos os amigos de um usuário no grafo;
@Argumentos:
	Ponteiro para grafo;
	Inteiro com a posição do usuário;	
*/
void listar_amigos(Grafo *G, int pos);

/* listar_amigos_nao_sugeridos:
	Lista todos os amigos que não são sugeridos de um usuário no grafo;
@Argumentos:
	Ponteiro para grafo;
	Inteiro com a posição do usuário;	
*/
void listar_amigos_nao_sugeridos(Grafo *G, int pos);

/* listar_sugeridos:
	Lista todos os sugeridos de um usuário no grafo;
@Argumentos:
	Ponteiro para grafo;
	Inteiro com a posição do usuário;	
*/
void listar_sugeridos(Grafo *G, int pos);

/* indicar_interesse_romantico:
	Indica o sugerido de um usuário com mais afinidade;
@Argumentos:
	Ponteiro para grafo;
	Inteiro com a posição do usuário;	
*/
void indicar_interesse_romantico(Grafo *G, int pos);

/* verificar_convites:
	Faz uma verificação dos convites de um usuário dando opção de aceitar ou não;
@Argumentos:
	Ponteiro para grafo;
	Inteiro com a posição do usuário;	
*/
void verificar_convites(Grafo *G, int v);

/* existe_convites:
	Verifica se existe convites para o usuário;
@Argumentos:
	Ponteiro para grafo;
	Inteiro com a posição do usuário;	
*/
int existe_convites(Grafo *G, int v);

/* get_afinidade:
	retorna a afinidade entre dois usuários;
@Argumentos:
	Ponteiro para grafo;
	Inteiro para a posição de cada usuário;	
@Retorno:
	Double com a afinidade entre os usuários;
*/
double get_afinidade(Grafo *G, int v1, int v2);

/* caixa_convites_cheia:
	Verifica se a caixa de convits de um usuário está cheia;
@Argumentos:
	Ponteiro para o grafo;
	Inteiro com a posição do vértice;
@Retorno:
	Inteiro com 1 se a caixa está cheia ou 0 caso contrário		
*/
int caixa_convites_cheia(Grafo *G, int v);

/* adicionar_convite:
	Adiciona um convite de amizade de um usuário a outro;
@Argumentos:
	Ponteiro para o grafo;
	Inteiro com a posição de cada vértice;
*/
void adicionar_convite(Grafo *G, int v1, int v2);

/* registro_valido:
	Verifica se um registro de usuário é válido;
@Argumentos:
	Ponteiro para o grafo;
	Ponteiro para o usuário;
@Retorno:
	Inteiro com 1 se o registro é válido ou 0 caso contrário		
*/
int registro_valido(Grafo *G, Pessoa *usuario);

/* inserir_vertice:
	Adiciona um vértice no grafo;
@Argumentos:
	Ponteiro para o grafo;
	Ponteiro para o novo usuário;
*/
void inserir_vertice(Grafo *G, Pessoa *usuario);

/* remover_aresta_amigo:
	Remove um amigo de um usuário;
@Argumentos:
	Ponteiro para o grafo;
	Inteiro com a posição de cada vértice;
*/
void remover_aresta_amigo(Grafo *G, int v1, int v2);

/* remover_aresta_sugerido:
	Remove um sugerido de um usuário;
@Argumentos:
	Ponteiro para o grafo;
	Inteiro com a posição de cada vértice;
*/
void remover_aresta_sugerido(Grafo *G, int v1, int v2);

/* remover_vertice:
	Remove um usuário da rede;
@Argumentos:
	Ponteiro para o grafo;
	Inteiro com a posição do vértice com o usuário;
*/
void remover_vertice(Grafo *G, int pos);

/* limpar_grafo:
	Libera toda a memória alocada dinamicamente por um grafo;
@Argumentos:
	Ponteiro para o grafo;
*/
void limpar_grafo(Grafo *G);

#endif