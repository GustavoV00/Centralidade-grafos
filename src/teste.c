#include "../includes/grafo.h"
#include <stdio.h>

//------------------------------------------------------------------------------

int main(void) {
  grafo g;
  vertice v;
  double coef;

  g = le_grafo(stdin);
  v = le_vertice();

  if (!g)

    return 1;

  coef = coeficiente_proximidade(g, v);

  printf("O coeficiente de proximidade é %f\n", coef);

  return !destroi_grafo(g);
}
