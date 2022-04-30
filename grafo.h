// Grafos UFPR - Trab1.
// GUSTAVO VALENTE NUNES GRR20182557
// BRUNO EDUARDO FARIAS GRR20186715

#ifndef _GRAFO_H
#define _GRAFO_H

#include <stdbool.h>
#include <stdio.h>

typedef struct vertice {
  char *id;
} vertice;

typedef struct lista_adj_t {
  struct lista_adj_t *prev;
  struct lista_adj_t *next;
  char *vertice;

} lista_adj_t;

// Em vez de utilizar uma matriz para representar o
// grafo, estamos utilizando uma fila. Sendo que cada nodo
// dessa lista, é referente a um id. a, b, c, ..., z
typedef struct grafo {
  struct grafo *prev;
  struct grafo *next;
  struct lista_adj_t *lista_adj;
  char *vertice;
  int distancia;
  int estado;
  char *pai;

} grafo;

//fila genérica
typedef struct queue_t {
  struct queue_t *prev; // aponta para o elemento anterior na fila
  struct queue_t *next; // aponta para o elemento seguinte na fila
} queue_t;

//------------------------------------------------------------------------------
// Conta o numero de elementos na fila
// Retorno: numero de elementos na fila

int queue_size(queue_t *queue);

//------------------------------------------------------------------------------
// Percorre a fila e imprime na tela seu conteúdo. A impressão de cada
// elemento é feita por uma função externa, definida pelo programa que
// usa a biblioteca. Essa função deve ter o seguinte protótipo:
//
// void print_elem (void *ptr) ; // ptr aponta para o elemento a imprimir

void queue_print(const char *name, queue_t *queue, void print_elem(void *));

//------------------------------------------------------------------------------
// Insere um elemento no final da fila.
// Condicoes a verificar, gerando msgs de erro:
// - a fila deve existir
// - o elemento deve existir
// - o elemento nao deve estar em outra fila
// Retorno: 0 se sucesso, <0 se ocorreu algum erro

int queue_append(queue_t **queue, queue_t *elem);

//------------------------------------------------------------------------------
// Remove o elemento indicado da fila, sem o destruir.
// Condicoes a verificar, gerando msgs de erro:
// - a fila deve existir
// - a fila nao deve estar vazia
// - o elemento deve existir
// - o elemento deve pertencer a fila indicada
// Retorno: 0 se sucesso, <0 se ocorreu algum erro

int queue_remove(queue_t **queue, queue_t *elem);

//------------------------------------------------------------------------------
// Imprime a fila de nodos, e suas respectivas listas de adjacências.

//
void print_fila(void *ptr);

//------------------------------------------------------------------------------
// desaloca toda a memória usada em *g
//
// devolve 1 em caso de sucesso,
//         ou
//         0, caso contrário

int destroi_grafo(grafo *g);

//------------------------------------------------------------------------------
// lê um grafo de input.
// um grafo é um arquivo onde cada linha tem zero, uma ou duas
// strings (sequência de caracteres sem "whitespace").
//
// devolve o grafo lido.

grafo *le_grafo(FILE *input);

//------------------------------------------------------------------------------
// pede para o usuário entrar com um vértice.

vertice le_vertice(void);

//------------------------------------------------------------------------------
// devolve o coeficiente de agrupamento de g
// ou seja, o número de tríades fechadas divido pelo
// total de tríades (ou seja, a soma de tríades abertas e fechadas).
//

double coeficiente_proximidade(grafo *g, char *v);

//------------------------------------------------------------------------------
//Imprime a lista de adjacência de um vértice
void print_fila_adj(void *ptr);
void print_filas_adjacencia(grafo *g);

//Aloca memória para um novo vértice que vai fazer parte da lista que 
//representa o grafo
grafo *inicia_novo_vertice(char *v);

//Inicia um item da lista de adjacência que cada vértice vai possuir
lista_adj_t *inicia_nova_lista(char *v);

//Adiciona primeiro vértice quando a lista que representa o grafo é vazia (nula)
grafo *adicionar_no_grafo_nulo(grafo *g, grafo *novo_vertice,
                               grafo *novo_vertice2,
                               lista_adj_t *nova_lista_adj,
                               lista_adj_t *nova_lista_adj2, char *v1,
                               char *v2);

//Adiciona um novo vértice na lista que representa o grafo.
grafo *adiciona_novo_vertice_grafo(grafo *g, char *v1, char *v2,
                                   grafo *novo_vertice,
                                   lista_adj_t *nova_lista_adj);

//Verifica se os vértices v1 e v2 existem na fila e adiciona v1 na lista de adj
//de v2 e vice-versa (auxiliar).
grafo *verifica_se_elemento_esta_no_grafo(char *v1, char *v2, grafo *aux,
                                          int *v_esta_grafo);

//Verifica se os vértices v1 e v2 existem na fila e adiciona v1 na lista de adj
//* de v2 e vice-versa.
grafo *inclui_nodo_na_fila(char *v1, char *v2, grafo *g);

//Pega a linha que contém os dois vértices e separa em v1 e v2.
void separa_vertices(char *v1, char *v2, char *v);

//Procura um vértice na lista que representa o grafo utilizando seu "nome"
grafo *busca_vertice_id(grafo *g, char *vertice);

//Roda o algoritmo de caminhos mínimos utilizando busca em largura (conforme
// * visto em sala)
grafo *caminhos_minimos(grafo *g, char *r);

//Compara floats
bool fequal(float a, float b);
#endif
