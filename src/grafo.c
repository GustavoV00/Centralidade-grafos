// Grafos UFPR - Trab1.
// GUSTAVO VALENTE NUNES GRR20182557
// BRUNO EDUARDO FARIAS GRR20186715

#include "../includes/grafo.h"
#include <ctype.h>
#include <float.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 30
#define STRING_SIZE 1024

bool fequal(float a, float b) { return fabs(a - b) < FLT_EPSILON; }

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
void queue_print(const char *name, queue_t *queue, void (*print_elem)(void *)) {
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
    // printf("tamanhoFila = %d\n", tamanhoFila);
    return tamanhoFila;
  }
}

/**
 * Imprime as filas de adjacência de cada vértice
 *
 * @param[in] grafo Grafo
 */
void print_filas_adjacencia(grafo *g) {
  grafo *aux = g;
  do {
    printf("%s -> ", aux->vertice);

    lista_adj_t *aux2 = aux->lista_adj;
    if (aux2 != NULL) {
      do {
        printf("%s, ", aux2->vertice);
        aux2 = aux2->next;
      } while (aux2 != NULL && aux2 != aux->lista_adj);
    }

    aux = aux->next;
    printf("\n");
  } while (aux != g);
}

/**
 * Imprime a fila
 *
 * @param[in] ptr Grafo
 */
void print_fila(void *ptr) {

  struct grafo *elem = ptr;
  if (!elem)
    return;

  elem->prev ? printf("%s", elem->prev->vertice) : printf("*");
  printf("<%s>", elem->vertice);

  elem->prev ? printf("%s", elem->next->vertice) : printf("*");
}

/**
 * Imprime a lista de adjacência de um vértice
 *
 * @param[in] ptr Vértice
 */
void print_fila_adj(void *ptr) {

  struct lista_adj_t *elem = ptr;
  if (!elem)
    return;
  printf("%s, ", elem->vertice);
}

/**
 * Desaloca a memória utilizada pelo grafo
 *
 * @param[in] g Grafo
 *
 */
int destroi_grafo(grafo *g) {
  while (g) {
    while (g->lista_adj) {
      queue_remove((queue_t **)&g->lista_adj, (queue_t *)g->lista_adj);
    }
    queue_remove((queue_t **)&g, (queue_t *)g);
  }

  if (g == NULL) {
    return 1;
  }
  return 0;
}

/**
 * Aloca memória para um novo vértice que vai fazer parte da lista que
 * representa o grafo
 *
 * @param[in] v1 Nome do vértice
 */
grafo *inicia_novo_vertice(char *v) {

  grafo *novo_vertice = (grafo *)malloc(sizeof(grafo));
  novo_vertice->vertice = malloc(strlen(v));
  novo_vertice->prev = NULL;
  novo_vertice->next = NULL;

  return novo_vertice;
}

/**
 * Inicia um item da lista de adjacência que cada vértice vai possuir
 *
 * @param[in] v1 Nome do vértice
 */
lista_adj_t *inicia_nova_lista(char *v) {

  lista_adj_t *nova_lista_adj = (lista_adj_t *)malloc(sizeof(lista_adj_t));
  nova_lista_adj->vertice = malloc(strlen(v));
  nova_lista_adj->next = NULL;
  nova_lista_adj->prev = NULL;

  return nova_lista_adj;
}

/**
 * Adiciona primeiro vértice quando a lista que representa o grafo é vazia
 * (nula)
 *
 * @param[in] g Grafo
 * @param[in] novo_vertice Novo vértice a ser adicionado (v1)
 * @param[in] novo_vertice2 Novo vértice a ser adicionado (v2)
 * @param[in] nova_lista_adj  Lista de adj. do vértice v1
 * @param[in] nova_lista_adj2  Lista de adj. do vértice v2
 * @param[in] v1 Nome do primeiro vértice da linha
 * @param[in] v2 Nome do segundo vértice da linha
 */
grafo *adicionar_no_grafo_nulo(grafo *g, grafo *novo_vertice,
                               grafo *novo_vertice2,
                               lista_adj_t *nova_lista_adj,
                               lista_adj_t *nova_lista_adj2, char *v1,
                               char *v2) {

  strcpy(novo_vertice->vertice, v1);
  strcpy(nova_lista_adj->vertice, v2);
  queue_append((queue_t **)&g, (queue_t *)novo_vertice);
  queue_append((queue_t **)&novo_vertice->lista_adj, (queue_t *)nova_lista_adj);
  // novo_vertice->lista_adj = nova_lista_adj;

  strcpy(novo_vertice2->vertice, v2);
  strcpy(nova_lista_adj2->vertice, v1);
  queue_append((queue_t **)&g, (queue_t *)novo_vertice2);
  queue_append((queue_t **)&novo_vertice2->lista_adj,
               (queue_t *)nova_lista_adj2);

  // novo_vertice2->lista_adj = nova_lista_adj2;
  // queue_print("Fila: ", (queue_t *)g, print_fila);
  // queue_print("Lista_adj1: ", (queue_t *)nova_lista_adj, print_fila_adj);
  // queue_print("Lista_adj2: ", (queue_t *)nova_lista_adj2, print_fila_adj);

  printf("\n");

  return g;
}

/**
 * Adiciona um novo vértice na lista que representa o grafo.
 *
 * @param[in] g Grafo
 * @param[in] v1 Nome do primeiro vértice da linha
 * @param[in] v2 Nome do segundo vértice da linha
 * @param[in] novo_vertice Novo vértice a ser adicionado
 * @param[in] nova_lista_adj  Lista de adj. do vértice
 */
grafo *adiciona_novo_vertice_grafo(grafo *g, char *v1, char *v2,
                                   grafo *novo_vertice,
                                   lista_adj_t *nova_lista_adj) {

  // printf("Adicionando v = %s no grafo\n", v1);

  strcpy(novo_vertice->vertice, v1);
  queue_append((queue_t **)&g, (queue_t *)novo_vertice);

  if (strlen(v2) > 0) {
    strcpy(nova_lista_adj->vertice, v2);
    queue_append((queue_t **)&novo_vertice->lista_adj,
                 (queue_t *)nova_lista_adj);
  } else {
    novo_vertice->lista_adj = NULL;
  }

  return g;
}

/**
 * Verifica se os vértices v1 e v2 existem na fila e adiciona v1 na lista de adj
 * de v2 e vice-versa (auxiliar).
 *
 * @param[in] v1 Nome do primeiro vértice da linha
 * @param[in] v2 Nome do segundo vértice da linha
 * @param[in] aux Grafo
 * @param[in] v_esta_grafo Retorna se v1 está no grafo
 */
grafo *verifica_se_elemento_esta_no_grafo(char *v1, char *v2, grafo *aux,
                                          int *v_esta_grafo) {
  if (strlen(v1) > 0) {
    if (strcmp(aux->vertice, v1) == 0) {
      *v_esta_grafo = 1;
      // printf("V1 está no grafo!\n");
      // printf("Elemento aux: %s igual ao v1: %s\n", aux->vertice, v1);
      int precisa_adicionar = 1;
      lista_adj_t *aux2 = aux->lista_adj;
      // Verifica se o v2 já existe na lista de adjacência do v1

      if (strlen(v2) > 0) {
        do {
          // printf("Verificando se v2 = %s está na lista de adjacencia de v1 =
          // "
          // "%s\n",
          // v2, v1);
          if (strcmp(aux2->vertice, v2) == 0) {
            // printf("Estou na lista de adjacência\n");
            precisa_adicionar = 0;
            break;
          }
          aux2 = aux2->next;
        } while (aux2 != NULL && aux2 != aux->lista_adj);

        // adiciona v2 na lista de adj de v1
        if (precisa_adicionar) {
          lista_adj_t *nova_lista_aux = inicia_nova_lista(v2);
          // printf("Precisa adicionar v2 = %s na lista de adj de v1 = %s\n",
          // v2, v1);
          strcpy(nova_lista_aux->vertice, v2);
          queue_append((queue_t **)&aux->lista_adj, (queue_t *)nova_lista_aux);
          // printf("Adicionou v2 na lista de adj!\n");
        }
      }
    }
  }
  return aux;
}

/**
 * Verifica se os vértices v1 e v2 existem na fila e adiciona v1 na lista de adj
 * de v2 e vice-versa.
 *
 * @param[in] v1 Nome do primeiro vértice da linha
 * @param[in] v2 Nome do segundo vértice da linha
 * @param[in] g Grafo
 */
grafo *inclui_nodo_na_fila(char *v1, char *v2, grafo *g) {

  // aloca structs dos vértices
  grafo *novo_vertice = inicia_novo_vertice(v1);
  grafo *novo_vertice2 = inicia_novo_vertice(v2);
  lista_adj_t *nova_lista_adj = inicia_nova_lista(v1);
  lista_adj_t *nova_lista_adj2 = inicia_nova_lista(v2);

  if (g != NULL) { // se já tiver vértice na lista (foi inicializada)
    grafo *aux = g;
    int v1_esta_grafo = 0;
    int v2_esta_grafo = 0;

    // verifica se v1 e v2 existem no grafo
    // printf("Verificando se v1 = %s está no grafo...\n", v1);
    do {
      // Caso esse vértice v1 exista no grafo, verifico se o v2
      // Existe em sua lista de adjacência.
      aux = verifica_se_elemento_esta_no_grafo(v1, v2, aux, &v1_esta_grafo);

      // Caso o vértice v2 já exista no grafo, verifica se o v1 existe em sua
      // lista de adj
      if (strlen(v2) > 0) {
        aux = verifica_se_elemento_esta_no_grafo(v2, v1, aux, &v2_esta_grafo);
      }

      aux = aux->next;
    } while (aux != g);

    // se v1 não estiver no grafo -> adiciona
    if (v1_esta_grafo == 0) {
      // printf("v1 = %s não está no grafo!\n", v1);
      g = adiciona_novo_vertice_grafo(g, v1, v2, novo_vertice, nova_lista_adj);
    }

    // se v2 não estiver no grafo -> adiciona
    if (strlen(v2) > 0 && v2_esta_grafo == 0) {
      // printf("v2 = %s não está no grafo!\n", v2);
      g = adiciona_novo_vertice_grafo(g, v2, v1, novo_vertice2,
                                      nova_lista_adj2);
    }

    return g;
  }

  // caso em que seja o primeiro elemento da lista
  g = adicionar_no_grafo_nulo(g, novo_vertice, novo_vertice2, nova_lista_adj,
                              nova_lista_adj2, v1, v2);

  return g;
}

/**
 * Pega a linha que contém os dois vértices e separa em v1 e v2.
 *
 * @param[in] v1 Nome do primeiro vértice da linha
 * @param[in] v2 Nome do segundo vértice da linha
 * @param[in] v Linha com os dois vértices
 */
void separa_vertices(char *v1, char *v2, char *v) {

  int i = 0;
  int j = 0;
  int flag = 0;
  while (v[i] != 0) {
    int espaco = isspace(v[i]);
    if (espaco != 0) {
      flag = 1;
      j = 0;
      i++;
      continue;
    }
    if (flag == 0)
      v1[j] = v[i];
    else
      v2[j] = v[i];

    i += 1;
    j += 1;
  }
}

/**
 * Lê o grafo de stdin e coloca numa fila
 *
 * @param[in] input stdin
 */
grafo *le_grafo(FILE *input) {
  grafo *g = NULL;
  FILE *f = input;
  char *v = malloc(2050 * sizeof(char));
  // int i = 0;

  // le todas as linhas
  while (fgets(v, 2050, f) != NULL) {
    if (v[0] != '\n') {
      char *v1 = malloc(STRING_SIZE * sizeof(char));
      char *v2 = malloc(STRING_SIZE * sizeof(char));

      // separa o vertice v1 e v2 na linha
      separa_vertices(v1, v2, v);
      // printf("%s e %s\n", v1, v2);

      // printf(
      // "**************************************************************\n");

      // se ñ tem v1 na fila -> adiciona
      // se ñ tem v2 na fila -> adiciona

      // se ñ tem v2 na fila de adj de v1 -> adiciona
      // se ñ tem v1 na fila de adj de v2 -> adiciona
      g = inclui_nodo_na_fila(v1, v2, g);

      // imprime para acompanhamento
      // queue_print("Fila ", (queue_t *)g, print_fila);
      // print_filas_adjacencia(g);

      // printf(
      // "**************************************************************\n");
    }
    // i += 1;
  }

  // queue_print("\n\n Grafo ao final da leitura ", (queue_t *)g, print_fila);
  // print_filas_adjacencia(g);

  free(v);
  fclose(f);
  return g;
}

/**
 * Procura um vértice na lista que representa o grafo utilizando seu "nome"
 *
 * @param[in] g Grafo
 * @param[in] r Nome do vértice que está sendo procurado
 */
grafo *busca_vertice_id(grafo *g, char *v) {
  grafo *aux = g;
  do {
    if (strcmp(aux->vertice, v) == 0) {
      return aux;
    }
    aux = aux->next;
  } while (aux != g);

  fprintf(stderr, "Falha ao encontrar vertice %s!\n", v);
  exit(-1);
  return NULL;
}

/**
 * Roda o algoritmo de caminhos mínimos utilizando busca em largura (conforme
 * visto em sala)
 *
 * @param[in] g Grafo
 * @param[in] r Vértice
 */
grafo *caminhos_minimos(grafo *g, char *r) {
  // V <- fila vazia
  grafo *V = NULL;

  // procura o vértice r na lista que representa o grafo
  grafo *aux = busca_vertice_id(g, r);
  if (aux == NULL) {
    perror("Falha o encontrar vértice raiz no grafo!");
    return g;
  }

  // printf("Encontrou raiz no grafo! aux = %s\n", aux->vertice);

  aux->pai = NULL;

  // enfileirar r em V
  grafo *novo_vertice = inicia_novo_vertice(r);
  strcpy(novo_vertice->vertice, r);
  // printf("Enfileirando r = %s em V...\n", novo_vertice->vertice);
  queue_append((queue_t **)&V, (queue_t *)novo_vertice);
  // printf("Enfileirou a raiz em V!\n");

  // queue_print("V: ", (queue_t *)V, print_fila);

  aux->estado = 1;
  aux->distancia = 0;

  // enquanto V não estiver vazia
  while (queue_size((queue_t *)V) > 0) {
    // printf("##########################################################\n");
    // retirar um vertice v da fila
    grafo *v = V;

    // remove sempre o primeiro elemento
    if (queue_size((queue_t *)V) == 1) {
      V = NULL;
    } else {
      grafo *aux1 = V->next;
      grafo *aux2 = V->prev;

      // prev->next = v->next
      V->prev->next = aux1;

      // next->prev = v->prev
      V->next->prev = aux2;

      V = aux1;
    }

    // printf("Removeu vértice %s da fila!\n", v->vertice);
    // queue_print("V: ", (queue_t *)V, print_fila);

    // printf("Procurando vértice %s no grafo...\n", v->vertice);
    v = busca_vertice_id(g, v->vertice);
    if (v == NULL) {
      perror("Falha na busca de vértice pelo id no grafo");
      return g;
    }

    // para cada w da fronteira de v (lista de adjacencia de v)
    lista_adj_t *w = v->lista_adj;

    if (w == NULL) {
      // printf("w é NULL -> %s é vértice isolado!\n", v->vertice);
      continue;
    }

    // percorre todos os vizinhos
    // printf("Vai percorrer todos os vizinhos de %s\n", v->vertice);
    do {
      // printf("======================\n");
      // printf("w = %s\n", w->vertice);

      // procura esse w (vizinho de v) no grafo
      grafo *auxx = busca_vertice_id(g, w->vertice);
      if (auxx == NULL) {
        perror("Falha na busca de vértice pelo id no grafo");
        return g;
      }

      // printf("Encontrou w = %s no grafo!\n", auxx->vertice);

      if (auxx->estado == 0) {
        // printf("w = %s está no estado 0!\n", auxx->vertice);

        // w->pai = v->vertice;
        auxx->pai = malloc(strlen(v->vertice) * sizeof(char));
        strcpy(auxx->pai, v->vertice);
        // printf("Setou o pai de %s como %s\n", auxx->vertice, v->vertice);

        auxx->distancia = v->distancia + 1;
        // printf("distancia de %s é %d\n", auxx->vertice, auxx->distancia);

        // enfileirar w em V
        grafo *novo_vertice2 = inicia_novo_vertice(auxx->vertice);
        strcpy(novo_vertice2->vertice, auxx->vertice);
        queue_append((queue_t **)&V, (queue_t *)novo_vertice2);
        // printf("-> Enfileirou w = %s na fila!\n", auxx->vertice);

        // queue_print("V ", (queue_t *)V, print_fila);

        auxx->estado = 1;
        // printf("Setou o estado de w = %s para 1\n", auxx->vertice);
      } else {
        // printf("w = %s está no estado %d -> NÃO FAZ NADA!\n", auxx->vertice,
        // auxx->estado);
      }

      w = w->next;
    } while (w != v->lista_adj);

    v->estado = 2;

    // printf("Setou o estado de %s para 2!\n", v->vertice);
    // queue_print("V: ", (queue_t *)V, print_fila);
  }

  // printf("Fila V vazia! Fim do algoritmo de caminhos mínimos!\n");

  return g;
}

//------------------------------------------------------------------------------
// lê um vertice

vertice le_vertice(void) {
  // printf("Escolha um vértice: \n");

  // fflush(stdin);
  vertice *vertice_t = (vertice *)malloc(sizeof(vertice));
  // fscanf(stdin, "%s", vertice_t->id);
  fflush(stdin);
  // scanf("%s", vertice_t->id);
  fgets(vertice_t->id, STRING_SIZE, stdin);

  // printf("Vértice lido: %s\n", vertice_t->id);

  return *vertice_t;
  // return (vertice)NULL;
}

/**
 * Percorre a árvore de caminhos mínimos e calcula o coeficiente de proximidade
 * baseado no vértice v
 *
 * @param[in] g Grafo
 * @param[in] r Nome do vértice base
 */
double coeficiente_proximidade(grafo *g, char *v) {
  // printf("\n\n\n\n\nProcurando coeficiente_proximidade do vértice %s\n", v);

  g = caminhos_minimos(g, v);

  // printf("\n\n\n\nÁrvore de caminhos mínimos:\n");
  // percorre o grafo
  grafo *aux = g;
  double i = 0;
  float sum = 0;
  float zero = 0;
  do {
    printf("#########################\n");
    printf("vertice: %s\n", aux->vertice);
    printf("estado: %d\n", aux->estado);
    printf("distancia de %s até %s: %d\n", aux->vertice, v, aux->distancia);

    // somatório das distâncias
    sum += (float)aux->distancia;

    // somatório de n
    i += 1;

    aux = aux->next;
  } while (aux != g);

  printf("#########################\n\n\n");
  printf("n = %f somatório = %f\n", i, sum);

  if (fequal(sum, zero)) {
    perror("A distância é 0, não é possível calcular!");
    return 0;
  }

  // n / somatório das distâncias
  double result = i / sum;

  return result;
}
