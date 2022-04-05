#ifndef _GRAFO_H
#define _GRAFO_H

#include <stdio.h>

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

int destroi_grafo(grafo g);

//------------------------------------------------------------------------------
// lê um grafo de input.
// um grafo é um arquivo onde cada linha tem zero, uma ou duas
// strings (sequência de caracteres sem "whitespace").
// 
// devolve o grafo lido. Caso o arquivo esteja mal formado o
// comportamento da função é indefinido

grafo le_grafo(FILE *input);  



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

double coeficiente_proximidade(grafo g, vertice v);

//------------------------------------------------------------------------------
#endif
