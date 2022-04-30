Bruno Eduardo Farias - GRR 20186715
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

  grafo.c: Nucleo de todo o projeto, está implementado a leitura de dados e todas as funções de tratamento do grafo.

  teste.c: Está localizado a main do código.

     
  grafo.h: Arquivo de .h para o grafo.c

  /testes: Diretório que contém os arquivos de testes.

# Como utilizar o algoritmo
  para compilar:
    make ou make all

  para testar o código:
    ./teste -i arquivo_entrada -v vertice
                    ou
    ./teste -v vertice -i arquivo_entrada

    O "arquivo_entrada" é um arquivo que deve conter todos os vértices de entrada, igual ao 
    que já existe no diretorio de testes/

    O "vertice" seria uma string, com um tamanho máximo de 1024 bytes.

# Funcionamento
  Ao executar o programa como mostrado acima, um grafo é construído utilizando as listas de adjacências. Após esta construção, é executado o algoritmo de caminhos mínimos para encontrar todos os caminhos mínimos a partir do vértice passado na linha de comando. Então, calculamos o coeficiente de proximidade como definido na especificação: quantidade de vértices dividido pela soma das distâncias do vértice escolhido até todos os outros vértices.

# Referências
[1] Networks: An Introduction, Newman, M.E.J. Oxford University Press, 2010.
[2] https://en.wikipedia.org/wiki/Closeness centrality
