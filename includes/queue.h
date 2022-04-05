//TRAB1 IA - 2021-2
//GUSTAVO VALENTE NUNES GRR20182557
//BRUNO EDUARDO FARIAS GRR20186715

#ifndef __QUEUE__
#define __QUEUE__

/*
#ifndef NULL
#define NULL ((void *)0)
#endif
*/

#include "../include/includes.h"

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

void queue_print(char *name, queue_t *queue, void print_elem(void *));

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
int fila_correta(queue_state_t *fila);

#endif
