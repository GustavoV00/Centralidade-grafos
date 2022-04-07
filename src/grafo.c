#include "../includes/grafo.h"
#include "../includes/queue.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 30
#define STRING_SIZE 1024

void print_filas_adjacencia(queue_grafo_t *grafo)
{
	// percorre todos os vértices
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
		do
		{
			// Caso esse vértice exista no grafo, verifico se o v2
			// Existe em sua lista de adjacência.
			printf(" aux = %s\n", aux->vertice);
			if (strcmp(aux->vertice, v1) == 0)
			{
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
				} while (aux2 != aux->lista_adj && aux2 != NULL);

				if (precisa_adicionar)
				{
					strcpy(nova_lista_adj->vertice, v2);
					queue_append((queue_t **)&aux->lista_adj, (queue_t *)nova_lista_adj);
				}

				return g;
			}
			aux = aux->next;
		} while (aux != g);
		printf("Sai do aux\n");
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

//------------------------------------------------------------------------------
// lê um vertice

// vertice le_vertice(void) { return (vertice)NULL; }

//------------------------------------------------------------------------------
// devolve o coeficiente de proximidade do vértice v de g
//

double coeficiente_proximidade(queue_grafo_t *g, vertice_t v)
{

	int n = queue_size((queue_t *)g);

	int *distancias = malloc(n * sizeof(int));

	queue_grafo_t *aux;

	return 0.0;
}
