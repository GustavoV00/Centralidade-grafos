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

int main(int argc, char const *argv[]) {
  if(argc < 5){
    fprintf(stderr, "ENTRADA INCORRETA!\n\n\n");
    fprintf(stderr, "USO: ./grafo -i <nome_arquivo_grafo> -v <vertice>\n");
    fprintf(stderr, "Exemplo: ./grafo -i teste1.in -v b\n");
    return -1;
  }

  char *nomeArquivo = malloc(STRING_SIZE * sizeof(char));
  char *vertice = malloc(STRING_SIZE * sizeof(char)); 

  //le de argv o arquivo de entrada e o vértice procurado
  if(strcmp(argv[1], "-i") == 0){
    strcpy(nomeArquivo, argv[2]);
    strcpy(vertice, argv[4]);
  } else if(strcmp(argv[1], "-v") == 0){
    strcpy(nomeArquivo, argv[4]);
    strcpy(vertice, argv[2]);
  } else {
    fprintf(stderr, "ENTRADA INCORRETA!\n\n\n");
    fprintf(stderr, "USO: ./grafo -i <nome_arquivo_grafo> -v <vertice>\n");
    fprintf(stderr, "Exemplo: ./grafo -i teste1.in -v b\n");
    return -1;
  }

  printf("nomeArquivo: %s\n", nomeArquivo);
  printf("vertice: %s\n", vertice);

  FILE *arquivo = fopen(nomeArquivo, "r");

  //faz a leitura do grafo de stdin
  queue_grafo_t *grafo = le_grafo(arquivo);

  printf("\n\nVertice = %s\n", vertice);

  //calcula o coeficiente de proximidade
  double coef = coeficiente_proximidade(grafo, vertice);

  printf("O coeficiente de proximidade é %f\n", coef);

  free(nomeArquivo);
  free(vertice);

  //desaloca a memória usada
  int result = destroi_grafo(grafo);
  if (result == 1)
    return 0;
  return 1;
}
