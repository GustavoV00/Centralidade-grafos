Bruno Eduardo Farias - GRR
Gustavo Valente Nunes - GRR 20182557


# Introdução
Neste trabalho implementaremos um algoritmo que calcula uma medida de centralidade que
pode ser associada à um vértice de um grafo. Esta medida é bastante conhecida na área de estudos
de redes sociais, sendo chamada de coeficiente de proximidade [1,2].
Dado um vértice v de um grafo G = (V(G), E(G)) com n vértices, o coeficiente de proximidade
de v, denotado C(v), é definido como a distância média de todos os grafos até um grafo em especifíco.

Note que C(v) é a distância média de v a um vértice qualquer de G. O objetivo do trabalho é, a
partir de um grafo de entrada, calcular o seu coeficiente de proximidade de um vértice qualquer
requisitado pelo usuário.


# Estrutura do projeto
  src: Local onde fica os arquivos do tipo *.c
    grafo.c: Nucleo de todo o projeto, está implementado todas as funções e leitura de dados.
    main.c: Está localizado a main do código.
    queue.c: Arquivo onde está implementado a API da fila.
     
  includes: Local onde fiica os arquivos do tipo *.h
    grafo.h: Arquivo de .h para o grafo.c
    queue.h: Estrutura utilizada para fazer a implementação da lista encadeada dos grafos.

  testes: Diretório que contém os arquivos de testes.

# Como utilizar o algoritmo
  para compilar:
    make ou make all

  para testar o código:
    ./grafo -i arquivo_entrada -v vertice
                    ou
    ./grafo -v vertice -i arquivo_entrada

    O "arquivo_entrada" é um arquivo que deve conter todos os vértices de entrada, igual ao 
    que já existe no diretorio de testes/

    O "vertice" seria uma string, com um tamanho máximo de 1024 bytes.

# Referências
[1] Networks: An Introduction, Newman, M.E.J. Oxford University Press, 2010.
[2] https://en.wikipedia.org/wiki/Closeness centrality
