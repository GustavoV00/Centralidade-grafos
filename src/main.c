// TRAB2 IA - 2021-2
// GUSTAVO VALENTE NUNES GRR20182557
// BRUNO EDUARDO FARIAS GRR20186715

#include "../includes/grafo.h"
#include "../includes/queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRING_SIZE 1024

//------------------------------------------------------------------------------

int main(void) {
  //   vertice_t v;
  double coef;

  //faz a leitura do grafo de stdin
  queue_grafo_t *grafo = le_grafo(stdin);

  char *vertice_procurado = malloc(STRING_SIZE * sizeof(char));
  vertice_procurado = "b";

  char *vert = malloc(STRING_SIZE * sizeof(char));

  strcpy(vert, vertice_procurado);

  printf("\n\nvertice = %s\n", vert);

  //calcula o coeficiente de proximidade
  coef = coeficiente_proximidade(grafo, vertice_procurado);
  //printf("Coeficiente: %f\n", coef);

  printf("O coeficiente de proximidade é %f\n", coef);

  //desaloca a memória usada
  int result = destroi_grafo(grafo);
  if (result == 1)
    return 0;
  return 1;
}
