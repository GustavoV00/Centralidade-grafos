#include "../includes/grafo.h"
#include <stdlib.h>

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
    inclui_nodo_na_fila(v1, v2, grafo);
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

// double coeficiente_proximidade(grafo g, vertice v) {

//   v = NULL;
//   g = NULL;

//   return !(v == (vertice)g);
// }
