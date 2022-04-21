// TRAB2 IA - 2021-2
// GUSTAVO VALENTE NUNES GRR20182557
// BRUNO EDUARDO FARIAS GRR20186715

#include "../includes/queue.h"
#include <stdio.h>

/**
* Removes the first element
*
* @param[in] queue Queue of elements
* @param[in] elem The elem to be removed from the queue
*/

// int retirar_primeiro_elemento_queue(queue_t **queue, queue_t *elem){
//   printf("Retirando primeiro elemento da fila...\n");
//   if (*queue == NULL) {
//     perror("Erro ao remover primeiro elemento da fila: NULL!\n");
//     return -1;
//   }

//   printf("aqui\n");

//   elem = *(queue);
//   //printf("Elem: %s\n", elem->vertice)

//   printf("Chamando queue_remove...\n");
//   return queue_remove(queue, elem);
// }

/**
 * Appends a element to the queue
 *
 * @param[in] queue Queue of elements
 * @param[in] elem The elem to be appended to the queue
 */
int queue_append(queue_t **queue, queue_t *elem) {

  // verify if the element exists
  if (elem != NULL) {
    // verify if the element is in the right queue
    if (elem->next == NULL && elem->prev == NULL) {
      // if there's no elements in the queue -> adds as the first one
      if (*queue == NULL) {

        // queue points to first element
        (*queue) = elem;
        (*queue)->next = elem;
        (*queue)->prev = elem;

      } else {

        // fix pointers
        (*queue)->prev->next = elem;
        elem->next = *queue;
        elem->prev = (*queue)->prev;
        (*queue)->prev = elem;
      }
      return 0;
    } else
      // printf("Erro: Elemento já está inserido ou está na fila incorreta\n");
      perror("Error: element is already on a queue or wrong queue!");
  } else {
    // printf("Erro: Elemento não existe\n");
    perror("Error: element doesn't exists!");
  }

  return -1;
}

/**
 * Prints the elements in the queue
 *
 * @param[in] name Name of the queue
 * @param[in] queue The queue to be printed
 * @param[in] print_elem Function to print a elem
 */
void queue_print(char *name, queue_t *queue, void (*print_elem)(void *)) {
  queue_t *aux = queue;

  printf("%s: [", name);

  // Pega o tamanho da fila
  int tam = queue_size(queue);
  for (int i = 0; i < tam; i++) {
    print_elem(aux);
    aux = aux->next;

    // Formata o output, para ficar igual aos testes
    if (i + 1 != tam)
      printf(" ");
  }

  printf("]\n");

  return;
}

/**
 * Remove the element elem from the queue
 *
 * @param[in] queue Queue of elements
 * @param[in] elem The elem to be removed from the queue
 */
int queue_remove(queue_t **queue, queue_t *elem) {
  queue_t **aux = queue, *first = *queue;

  // verift if the element exists
  if (elem != NULL) {
    // verify that the queue exists
    if (elem->next != NULL && elem->prev != NULL) {

      if (*queue != NULL) {
        if (*aux == elem) {
          switch (queue_size(*queue)) {
          // remove the first (and only) element of the queue
          case 1:
            *queue = NULL;
            break;

          // remove the element when the queue has more than one element
          default:
            (*queue)->next->prev = (*queue)->prev;
            (*queue)->prev->next = (*queue)->next;
            (*queue) = (*queue)->next;
            break;
          }
        }
        // removes the second or the last element
        else {
          // removes the last element
          if ((*aux)->prev == elem)
            *aux = (*aux)->prev;
          else {
            // removes the second element
            while ((*aux = (*aux)->next) != elem) {
              if (*aux == first) {
                // printf("Erro: Elemento não pertence a está fila\n");
                perror("Error: The element doesn't belong to this queue!");
                return -1;
              }
            }
          }

          // Arruma os ponteiros da remoção do ultimo e segundo elemento
          (*aux)->prev->next = (*aux)->next;
          (*aux)->next->prev = (*aux)->prev;
          *queue = first;
        }
        elem->next = NULL;
        elem->prev = NULL;
        return 0;

      } else
        // printf("Erro: Fila não existe\n");
        perror("Error: queue doesn't exists!");
    } else
      // printf("Erro: Elemento não está em nenhuma fila.\n");
      perror("Error: element isn't inside a queue!");
  } else {
    // printf("Erro: Elemento não existe\n");
    perror("Error: element doesn't exists!");
  }

  return -1;
}

/**
 * Returns the size of a queue
 *
 * @param[in] queue Queue of elements
 */
int queue_size(queue_t *queue) {
  queue_t *aux = queue;

  // Tamanho da fila, se ela estiver vazia
  if (aux == NULL)
    return 0;
  else {
    int tamanhoFila = 1;
    while ((aux = aux->next) != queue)
      tamanhoFila += 1;
    //printf("tamanhoFila = %d\n", tamanhoFila);
    return tamanhoFila;
  }
}
