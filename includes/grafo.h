// Grafos UFPR - Trab1.
// GUSTAVO VALENTE NUNES GRR20182557
// BRUNO EDUARDO FARIAS GRR20186715

#ifndef _GRAFO_H
#define _GRAFO_H

#include <stdbool.h>
#include <stdio.h>

//------------------------------------------------------------------------------
// (apontador para) estrutura de dados para representar um grafo
//
// o grafo tem um nome, que é uma "string"

//------------------------------------------------------------------------------
// (apontador para) estrutura de dados para representar um vértice
//
// o vértice tem um nome, que é uma "string"

typedef struct vertice {
  char *id;
} vertice;

typedef struct lista_adj_t {
  struct lista_adj_t *prev;
  struct lista_adj_t *next;
  char *vertice;

} lista_adj_t;

// Em vez de utilizar uma matriz para representar o
// grafo, estou utilizando uma fila. Sendo que cada nodo
// dessa lista, é  eferente a um id. a, b, c, ..., z
typedef struct grafo {
  struct grafo *prev;
  struct grafo *next;
  struct lista_adj_t *lista_adj;
  char *vertice;
  int distancia;
  int estado;
  char *pai;

} grafo;

//------------------------------------------------------------------------------
// estrutura de uma fila genérica, sem conteúdo definido.
// Veja um exemplo de uso desta estrutura em testafila.c

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
// devolve o grafo lido. Caso o arquivo esteja mal formado o
// comportamento da função é indefinido

grafo *le_grafo(FILE *input);

//------------------------------------------------------------------------------
// pede para o usuário entrar com um vértice.

vertice le_vertice(void);

//------------------------------------------------------------------------------
// escreve o grafo g em output, no mesmo formato que o usado por le_grafo()
//
// devolve o grafo escrito,
//         ou
//         NULL, em caso de erro

//------------------------------------------------------------------------------
// devolve o coeficiente de agrupamento de g
// ou seja, o número de tríades fechadas divido pelo
// total de tríades (ou seja, a soma de tríades abertas e fechadas).
//

double coeficiente_proximidade(grafo *g, char *v);

//------------------------------------------------------------------------------
void print_fila_adj(void *ptr);
void print_filas_adjacencia(grafo *g);
grafo *inicia_novo_vertice(char *v);
lista_adj_t *inicia_nova_lista(char *v);
grafo *adicionar_no_grafo_nulo(grafo *g, grafo *novo_vertice,
                               grafo *novo_vertice2,
                               lista_adj_t *nova_lista_adj,
                               lista_adj_t *nova_lista_adj2, char *v1,
                               char *v2);
grafo *adiciona_novo_vertice_grafo(grafo *g, char *v1, char *v2,
                                   grafo *novo_vertice,
                                   lista_adj_t *nova_lista_adj);

grafo *verifica_se_elemento_esta_no_grafo(char *v1, char *v2, grafo *aux,
                                          int *v_esta_grafo);
grafo *inclui_nodo_na_fila(char *v1, char *v2, grafo *g);
void separa_vertices(char *v1, char *v2, char *v);
grafo *busca_vertice_id(grafo *g, char *vertice);
grafo *caminhos_minimos(grafo *g, char *r);
bool fequal(float a, float b);
#endif
