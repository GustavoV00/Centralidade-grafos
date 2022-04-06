#ifndef _GRAFO_H
#define _GRAFO_H

#include <stdio.h>

//------------------------------------------------------------------------------
// (apontador para) estrutura de dados para representar um grafo
//
// o grafo tem um nome, que é uma "string"

//------------------------------------------------------------------------------
// (apontador para) estrutura de dados para representar um vértice
//
// o vértice tem um nome, que é uma "string"

typedef struct vertice_t {
  char *id;
  int indice;

} vertice_t;

// typedef struct grafo_t {
//   struct vertice_t *lista_adj;

// } grafo_t;

// Em vez de utilizar uma matriz para representar o
// grafo, estou utilizando uma fila. Sendo que cada nodo
// dessa lista, é  eferente a um id. a, b, c, ..., z
typedef struct queue_grafo_t {
  struct queue_grafo_t *prev;
  struct queue_grafo_t *next;
  struct vertice_t vertice;

  // Lista que contem os vértices, que o nodo x fazem parte
  struct vertice_t *lista_adj;

} queue_grafo_t;

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

int destroi_grafo(queue_grafo_t g);

//------------------------------------------------------------------------------
// lê um grafo de input.
// um grafo é um arquivo onde cada linha tem zero, uma ou duas
// strings (sequência de caracteres sem "whitespace").
//
// devolve o grafo lido. Caso o arquivo esteja mal formado o
// comportamento da função é indefinido

queue_grafo_t *le_grafo(FILE *input);

//------------------------------------------------------------------------------
// pede para o usuário entrar com um vértice.

vertice_t le_vertice(void);

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

double coeficiente_proximidade(queue_grafo_t *g, vertice_t v);

//------------------------------------------------------------------------------
#endif
