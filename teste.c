// Grafos UFPR - Trab1.
// GUSTAVO VALENTE NUNES GRR20182557
// BRUNO EDUARDO FARIAS GRR20186715

#include "grafo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRING_SIZE 1024

//------------------------------------------------------------------------------

int main(int argc, char const *argv[]) {

  //entrada no estilo ./grafo -i arquivo_entrada -v vertice

  if (argc < 5) {
    fprintf(stderr, "ENTRADA INCORRETA!\n\n\n");
    fprintf(stderr, "USO: ./grafo -i <nome_arquivo_grafo> -v <vertice>\n");
    fprintf(stderr, "Exemplo: ./grafo -i teste1.in -v b\n");
    return -1;
  }

  char *nomeArquivo = malloc(STRING_SIZE * sizeof(char));
  char *v = (char *)malloc(STRING_SIZE * sizeof(char));

  // le de argv o arquivo de entrada e o vértice procurado
  if (strcmp(argv[1], "-i") == 0) {
    strcpy(nomeArquivo, argv[2]);
    strcpy(v, argv[4]);
  } else if (strcmp(argv[1], "-v") == 0) {
    strcpy(nomeArquivo, argv[4]);
    strcpy(v, argv[2]);
  } else {
    fprintf(stderr, "ENTRADA INCORRETA!\n\n\n");
    fprintf(stderr, "USO: ./grafo -i <nome_arquivo_grafo> -v <vertice>\n");
    fprintf(stderr, "Exemplo: ./grafo -i teste1.in -v b\n");
    return -1;
  }

  // printf("nomeArquivo: %s\n", nomeArquivo);
  // printf("vertice: %s\n", v);

  FILE *arquivo = fopen(nomeArquivo, "r");

  // faz a leitura do grafo
  grafo *g = le_grafo(arquivo);

  // printf("\n\nVertice = %s\n", v);

  // calcula o coeficiente de proximidade
  double coef = coeficiente_proximidade(g, v);

  printf("O coeficiente de proximidade é %f\n", coef);

  free(nomeArquivo);
  free(v);

  // libera a memória usada
  int result = destroi_grafo(g);
  if (result == 1)
    return 0;
  return 1;
}
