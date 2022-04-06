#include "../includes/grafo.h"
#include "../includes/queue.h"
#include <stdlib.h>

#define SIZE 27

void print_fila(void *ptr) {
  struct queue_grafo_t *elem = ptr;

  if (!elem)
    return;

  // elem->prev ? printf("%c", elem->prev->vertice.id) : printf("*");
  printf("%c = ", elem->vertice.id);
  printf("[ ");
  for (int i = 0; i < elem->vertice.indice; i++) {
    printf("%c ", elem->lista_adj[i].id);
  }
  printf("]\n");
  // elem->prev ? printf("%c", elem->next->vertice.id) : printf("*");
}

//------------------------------------------------------------------------------
// (apontador para) estrutura de dados para representar um grafo
//
// o grafo tem um nome, que é uma "string"

typedef struct grafo *grafo;

//------------------------------------------------------------------------------
// (apontador para) estrutura de dados para representar um vértice
//
// o vértice tem um nome, que é uma "string"

typedef struct vertice *vertice;

//------------------------------------------------------------------------------
// desaloca toda a memória usada em *g
//
// devolve 1 em caso de sucesso,
//         ou
//         0, caso contrário

// int destroi_grafo(queue_grafo_t g) { return g == NULL; }

queue_grafo_t *inclui_nodo_na_fila(char v1, char v2, queue_grafo_t *g) {
  queue_grafo_t *novo_vertice = (queue_grafo_t *)malloc(sizeof(queue_grafo_t));
  novo_vertice->prev = NULL;
  novo_vertice->next = NULL;
  if (g != NULL) {
    queue_grafo_t *aux = g;
    do {
      if (aux->vertice.id == v1) {
        int tam = aux->vertice.indice;
        aux->lista_adj[tam].id = v2;
        aux->lista_adj[tam].indice = tam;
        aux->vertice.indice += 1;
        return g;
      }
      aux = aux->next;
    } while (aux != g);
  }
  int tam = novo_vertice->vertice.indice = 0;
  novo_vertice->vertice.id = v1;
  novo_vertice->lista_adj = malloc(SIZE * sizeof(vertice_t));
  novo_vertice->lista_adj[tam].id = v2;
  novo_vertice->lista_adj[tam].indice = tam;
  queue_append((queue_t **)&g, (queue_t *)novo_vertice);
  novo_vertice->vertice.indice += 1;

  return g;
}

//------------------------------------------------------------------------------
// lê um grafo
//
// devolve o grafo lido,
//         ou
//         NULL, em caso de erro

queue_grafo_t *le_grafo(FILE *input) {
  queue_grafo_t *grafo = NULL;

  FILE *f = input;

  char v1, v2;
  while (!feof(f)) {
    fscanf(f, "%c %c ", &v1, &v2);
    if (v1 != v2)
      grafo = inclui_nodo_na_fila(v1, v2, grafo);
    printf("%c e %c\n", v1, v2);
  }

  fclose(f);

  return grafo;
}

//------------------------------------------------------------------------------
// lê um vertice 

// vertice le_vertice(void) { return (vertice)NULL; }

//------------------------------------------------------------------------------
// devolve o coeficiente de proximidade do vértice v de g
//

double coeficiente_proximidade(queue_grafo_t *g, vertice_t v) {
  int n = queue_size((queue_t *)g);
  int *distancias = malloc(n * sizeof(int));
  queue_grafo_t *aux;

  // while (n > 0) {
  //   aux = g;
  //   int possiveis_starters = aux->vertice.indice;
  //   do {

  //   }while(aux->)
  // }

  return 0.0;
}
