#include "../includes/grafo.h"
#include "../includes/queue.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 30
#define STRING_SIZE 1024

void print_filas_adjacencia(queue_grafo_t *grafo)
{

  queue_grafo_t *aux = grafo ; 
	do {
    printf("%s -> ", aux->vertice);

    lista_adj_t *aux2 = aux->lista_adj;

    do {
      printf("%s, ", aux2->vertice);
      aux2 = aux2->next;
    } while(aux2 != aux->lista_adj);
    aux = aux->next;
    printf("\n");
  } while (aux != grafo);
}

void print_fila(void *ptr)
{

	struct queue_grafo_t *elem = ptr;
	if (!elem)
		return;

	elem->prev ? printf("%s", elem->prev->vertice) : printf("*");
	printf("<%s>", elem->vertice);
	// printf("[ ");
	// for (int i = 0; i < elem->vertice.indice; i++) {
	//   printf("%s ", elem->lista_adj);
	// }
	// printf("]\n");

	elem->prev ? printf("%s", elem->next->vertice) : printf("*");
}

void print_fila_adj(void *ptr)
{

	struct lista_adj_t *elem = ptr;
	if (!elem)
		return;
	// elem->prev ? printf("%s", elem->prev->vertice) : printf("*");
	printf("%s, ", elem->vertice);
	// printf("[ ");
	// for (int i = 0; i < elem->vertice.indice; i++) {
	//   printf("%s ", elem->lista_adj);
	// }
	// printf("]\n");
	// elem->prev ? printf("%s", elem->next->vertice) : printf("*");
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

queue_grafo_t *inicia_novo_vertice(char *v)
{

	queue_grafo_t *novo_vertice = (queue_grafo_t *)malloc(sizeof(queue_grafo_t));
	novo_vertice->vertice = malloc(strlen(v));
	novo_vertice->prev = NULL;
	novo_vertice->next = NULL;

	return novo_vertice;
}

lista_adj_t *inicia_nova_lista(char *v)
{

	lista_adj_t *nova_lista_adj = (lista_adj_t *)malloc(sizeof(lista_adj_t));
	nova_lista_adj->vertice = malloc(strlen(v));
	nova_lista_adj->next = NULL;
	nova_lista_adj->prev = NULL;

	return nova_lista_adj;
}

queue_grafo_t *inclui_nodo_na_fila(char *v1, char *v2, queue_grafo_t *g)
{

	queue_grafo_t *novo_vertice = inicia_novo_vertice(v1);
	queue_grafo_t *novo_vertice2 = inicia_novo_vertice(v2);
	lista_adj_t *nova_lista_adj = inicia_nova_lista(v1);
	lista_adj_t *nova_lista_adj2 = inicia_nova_lista(v2);

	if (g != NULL)
	{
		queue_grafo_t *aux = g;
		// Verifica se o indice v1 já não existe no grafo.
    int v1_esta_grafo = 0;
    int v2_esta_grafo = 0;
		do
		{
			// Caso esse vértice exista no grafo, verifico se o v2
			// Existe em sua lista de adjacência.
			printf(" aux = %s\n", aux->vertice);
      printf("Verificando se v1 = %s está no grafo...\n", v1);
			if (strcmp(aux->vertice, v1) == 0)
			{
        v1_esta_grafo = 1;
        printf("V1 está no grafo!\n");
				printf("Elemento aux: %s igual ao v1: %s\n", aux->vertice, v1);
				int precisa_adicionar = 1;
				lista_adj_t *aux2 = aux->lista_adj;
				// Verifica se o v2 já existe na lista de adjacência do v1

				do
				{
					printf("Verificando se v2 = %s está na lista de adjacencia de v1 = %s\n", v2, v1);
					if (strcmp(aux2->vertice, v2) == 0)
					{
						printf("Estou na lista de adjacência\n");
						precisa_adicionar = 0;
						break;
					}
					aux2 = aux2->next;
				} while (aux2 != NULL && aux2 != aux->lista_adj);

				if (precisa_adicionar)
				{
          lista_adj_t *nova_lista_aux = inicia_nova_lista(v2);
          printf("Precisa adicionar v2 = %s na lista de adj de v1 = %s\n", v2, v1);
          strcpy(nova_lista_aux->vertice, v2);
					queue_append((queue_t **)&aux->lista_adj, (queue_t *)nova_lista_aux);
          printf("Adicionou v2 na lista de adj!\n");
				}

				//return g;
			}

      //verifica se v2 está no grafo
      if(strlen(v2) > 0){
        printf("Verificando se v2 = %s está no grafo...\n", v2);

        if (strcmp(aux->vertice, v2) == 0)
        {
          v2_esta_grafo = 1;
          printf("V2 está no grafo!\n");

          printf("Elemento aux: %s igual ao v2: %s\n", aux->vertice, v2);

          int precisa_adicionar = 1;
          lista_adj_t *aux2 = aux->lista_adj;

          // Verifica se o v1 já existe na lista de adjacência do v2
          do
          {
            printf("Verificando se v1 = %s está na lista de adjacencia de v2 = %s\n", v1, v2);
            if (strcmp(aux2->vertice, v1) == 0)
            {
              printf("Estou na lista de adjacência\n");
              precisa_adicionar = 0;
              break;
            }
            aux2 = aux2->next;
          } while (aux2 != NULL && aux2 != aux->lista_adj);

          if (precisa_adicionar)
          {
            lista_adj_t *nova_lista_aux = inicia_nova_lista(v1);
            printf("Precisa adicionar v1 = %s na lista de adj de v2 = %s\n", v1, v2);
            strcpy(nova_lista_aux->vertice, v1);
            queue_append((queue_t **)&aux->lista_adj, (queue_t *)nova_lista_aux);
            printf("Adicionou v1 na lista de adj!\n");
          }

        }
      }
			aux = aux->next;
		} while (aux != g);

    printf("Saiu da procura do V1!\n");

    //se v1 não estiver no grafo -> adiciona
    if(v1_esta_grafo == 0){
      printf("Adicionando v1 = %s no grafo\n", v1);

      strcpy(novo_vertice->vertice, v1);
      strcpy(nova_lista_adj->vertice, v2);
      queue_append((queue_t **)&g, (queue_t *)novo_vertice);
      queue_append((queue_t **)&novo_vertice->lista_adj, (queue_t *)nova_lista_adj);
    }

    //se v2 não estiver no grafo -> adiciona
    if(v2_esta_grafo == 0){
      printf("Adicionando v2 = %s no grafo\n", v2);

      strcpy(novo_vertice2->vertice, v2);
      strcpy(nova_lista_adj2->vertice, v1);
      queue_append((queue_t **)&g, (queue_t *)novo_vertice2);
      queue_append((queue_t **)&novo_vertice2->lista_adj, (queue_t *)nova_lista_adj2);
    }
		printf("Sai do aux\n");

    return g;
	}

	printf("Estou aqui: %s e %s\n", v1, v2);
	strcpy(novo_vertice->vertice, v1);
	strcpy(nova_lista_adj->vertice, v2);
	queue_append((queue_t **)&g, (queue_t *)novo_vertice);
	queue_append((queue_t **)&novo_vertice->lista_adj, (queue_t *)nova_lista_adj);
	// novo_vertice->lista_adj = nova_lista_adj;

	strcpy(novo_vertice2->vertice, v2);
	strcpy(nova_lista_adj2->vertice, v1);
	queue_append((queue_t **)&g, (queue_t *)novo_vertice2);
	queue_append((queue_t **)&novo_vertice2->lista_adj, (queue_t *)nova_lista_adj2);

	// novo_vertice2->lista_adj = nova_lista_adj2;
	queue_print("Fila: \n", (queue_t *)g, print_fila);
	queue_print("Lista_adj1: ", (queue_t *)nova_lista_adj, print_fila_adj);
	queue_print("Lista_adj2: ", (queue_t *)nova_lista_adj2, print_fila_adj);

	printf("\n");

	return g;
}

void separa_vertices(char *v1, char *v2, char *v)
{

	int i = 0;
	int j = 0;
	int flag = 0;
	while (v[i] != 0)
	{
		int espaco = isspace(v[i]);
		if (espaco != 0)
		{
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

//------------------------------------------------------------------------------
// lê um grafo
//
// devolve o grafo lido,
//         ou
//         NULL, em caso de erro

queue_grafo_t *le_grafo(FILE *input)
{
	queue_grafo_t *grafo = NULL;
	FILE *f = input;
	char *v = malloc(2050 * sizeof(char));
	int i = 0;
	while (fgets(v, 2050, f) != NULL)
	{
		if (v[0] != '\n')
		{
			char *v1 = malloc(STRING_SIZE * sizeof(char));
			char *v2 = malloc(STRING_SIZE * sizeof(char));
			separa_vertices(v1, v2, v);
			printf("%s e %s\n", v1, v2);

			printf("**************************************************************\n");
			printf("Passo: %d\n", i);
			// printf("len v1 = %lu len v2 = %lu\n", strlen(v1), strlen(v2));
			// printf("\n");
			// se tem v1 e v2 -> verificar se já existe vértice v1 e v2 e
			// criar uma aresta entre v1 e v2 (na vizinhança dos dois)
			// se tem apenas v1 = vértice isolado

			grafo = inclui_nodo_na_fila(v1, v2, grafo);
			queue_print("Elementos inseridos: ", (queue_t *)grafo, print_fila);
			print_filas_adjacencia(grafo);

			printf("**************************************************************\n");
		}
		i += 1;
	}

	// queue_print("Elementos inseridos: ", (queue_t *)grafo, print_fila);

	// printf("\n");

	free(v);
	fclose(f);
	return grafo;
}

queue_grafo_t *busca_vertice_id(queue_grafo_t *g, char *vertice){
  printf("Procurando vertice %s...\n", vertice);
  queue_grafo_t *aux = g; 
  do {
    if(strcmp(aux->vertice, vertice) == 0){
      return aux;
    }
    aux = aux->next;
  } while (aux != g);

  fprintf(stderr, "Falha ao encontrar vertice %s!\n", vertice);
  return NULL;
}

queue_grafo_t *caminhos_minimos(queue_grafo_t *g, char *r){

  //verificar algoritmo de caminhos mínimos

  //V <- fila vazia
  queue_grafo_t *V = NULL;

  printf("Fila vazia iniciada!\n");

  //procura o vértice r no grafo
  queue_grafo_t *aux = busca_vertice_id(g, r);
  if(aux == NULL){
    perror("Falha o encontrar vértice raiz no grafo!");
    return g;
  }

  printf("Encontrou raiz no grafo! aux = %s\n", aux->vertice);
  
  aux->pai = NULL;

  //enfileirar r em V
  queue_grafo_t *novo_vertice = inicia_novo_vertice(r);
  strcpy(novo_vertice->vertice, r);
  printf("Enfileirando r = %s em V...\n", novo_vertice->vertice);
  queue_append((queue_t **)&V, (queue_t *)novo_vertice);
  printf("Enfileirou a raiz em V!\n");

  queue_print("Fila: ", (queue_t *)V, print_fila);

  aux->estado = 1;
  aux->distancia = 0;

  //enquanto V não estiver vazia
  while(queue_size((queue_t *) V) > 0){
    printf("##########################################################\n");
    //retirar um vertice v da fila
    queue_grafo_t *v = V;
        
    //queue_remove estava dando problema
    //remove sempre o primeiro elemento
    if(queue_size((queue_t *) V) == 1){
      V = NULL;
    } else {
      queue_grafo_t *aux1 = V->next;
      queue_grafo_t *aux2 = V->prev;

      //prev->next = v->next
      V->prev->next = aux1;

      //next->prev = v->prev
      V->next->prev = aux2;

      V = aux1;
    }
      
    printf("Removeu vértice %s da fila!\n", v->vertice);
    queue_print("Fila: ", (queue_t *)V, print_fila);

    printf("Procurando vértice %s no grafo...\n", v->vertice);
    v = busca_vertice_id(g, v->vertice);
    if(v == NULL){
      perror("Falha na busca de vértice pelo id no grafo");
      return g;
    }

    //para cada w da fronteira de v (lista de adjacencia de v)
    lista_adj_t *w = v->lista_adj;

    if(w == NULL){
      printf("w é NULL -> %s é vértice isolado!\n", v->vertice);
      continue;
    }

    //percorre todos os vizinhos
    printf("Vai percorrer todos os vizinhos de %s\n", v->vertice);
    do {
      printf("======================\n");
      printf("w = %s\n", w->vertice);
          
      //procura esse w (vizinho de v) no grafo
      queue_grafo_t *auxx = busca_vertice_id(g, w->vertice);
      if(auxx == NULL){
        perror("Falha na busca de vértice pelo id no grafo");
        return g;
      }

      printf("Encontrou w = %s no grafo!\n", auxx->vertice);

      if(auxx->estado == 0){
        printf("w = %s está no estado 0!\n", auxx->vertice);
        
        //w->pai = v->vertice;
        auxx->pai = malloc(strlen(v->vertice) * sizeof(char));
        strcpy(auxx->pai, v->vertice);
        printf("Setou o pai de %s como %s\n", auxx->vertice, v->vertice);

        auxx->distancia = v->distancia+1;
        printf("distancia de %s é %d\n", auxx->vertice, auxx->distancia);

        //enfileirar w em V
        queue_grafo_t *novo_vertice2 = inicia_novo_vertice(auxx->vertice);
        strcpy(novo_vertice2->vertice, auxx->vertice);
        queue_append((queue_t **)&V, (queue_t *)novo_vertice2);
        printf("Enfileirou w = %s na fila!\n", auxx->vertice);

        queue_print("Fila: ", (queue_t *)V, print_fila);

        auxx->estado = 1;
        printf("Setou o estado de w = %s para 1\n", auxx->vertice);
      } else {
        printf("w = %s está no estado %d -> NÃO FAZ NADA!\n", auxx->vertice, auxx->estado);
      }
         
      w = w->next;
    } while(w != v->lista_adj);

    v->estado = 2;

    printf("Setou o estado de %s para 2!\n", v->vertice);
    queue_print("Fila: ", (queue_t *)V, print_fila);
  }
  
  return g;
}

/*
queue_grafo_t *busca_em_largura(queue_grafo_t *g, , char *v){
  //percorre todos os vértices e seta o estado como 0
  queue_grafo_t *aux = grafo ; 
  do {
    aux->estado = 0;
  } while (aux != grafo);

  busca_em_largura_vertice(g, v);
}
*/


//------------------------------------------------------------------------------
// lê um vertice

// vertice le_vertice(void) { return (vertice)NULL; }

//------------------------------------------------------------------------------
// devolve o coeficiente de proximidade do vértice v de g
//

double coeficiente_proximidade(queue_grafo_t *g, char *v)
{
  printf("\n\n\n\n\nProcurando coeficiente_proximidade do vértice %s\n", v);

  g = caminhos_minimos(g, v);


  printf("\n\n\n\nÁrvore de caminhos mínimos:\n");
  //percorre o grafo imprimindo
  queue_grafo_t *aux = g ; 
  do {
    printf("####\n");
    printf("vertice: %s\n", aux->vertice);
    printf("estado: %d\n", aux->estado);
    printf("distancia: %d\n", aux->distancia);
    aux = aux->next;
  } while (aux != g);

	//int n = queue_size((queue_t *)g);

	//int *distancias = malloc(n * sizeof(int));

	//queue_grafo_t *aux;

  //

	return 0.0;
}
