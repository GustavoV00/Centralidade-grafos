#include "../includes/grafo.h"
#include "../includes/queue.h"
#include <stdio.h>

//------------------------------------------------------------------------------

int main(void)
{
	vertice_t v;
	double coef;

	queue_grafo_t *grafo = le_grafo(stdin);
	// queue_print("Elementos inseridos:\n", (queue_t *)grafo, print_fila);
	// v = le_vertice();

	char vertice_procurado = 'i';
	

	coef = coeficiente_proximidade(grafo, &vertice_procurado);

	// printf("O coeficiente de proximidade é %f\n", coef);

	// return !destroi_grafo(g);
	return 0;
}
