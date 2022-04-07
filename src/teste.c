#include "../includes/grafo.h"
#include "../includes/queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRING_SIZE 1024

//------------------------------------------------------------------------------

int main(void) {
  vertice_t v;
  double coef;

  queue_grafo_t *grafo = le_grafo(stdin);
  // queue_print("Elementos inseridos:\n", (queue_t *)grafo, print_fila);
  // v = le_vertice();

  char *vertice_procurado = malloc(STRING_SIZE * sizeof(char));
  vertice_procurado = "b";

  char *vert = malloc(STRING_SIZE * sizeof(char));

  strcpy(vert, vertice_procurado);

  printf("vertice = %s\n", vert);

  coef = coeficiente_proximidade(grafo, vertice_procurado);
  printf("Coeficiente: %f\n", coef);

  //   printf("O coeficiente de proximidade é %f\n", coef);

  // return !destroi_grafo(g);
  return 0;
}
