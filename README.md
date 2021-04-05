
# ![UAlg FCT Logo](readme_images/fct.svg)

# Quadrado Magico

## Guilherme Henriques | a61018

### 2021

# Conteúdo

1. [Resumo](#resumo)

2. [Abstract](#abstract)

3. [Introdução](#introdução)

4. [Enquadramento](#enquadramento)

5. [Estudo de casos](#estudo-de-casos)

6. [Análise de resultados e discussão](#análise-de-resultados-e-discussão)

7. [Comentários finais](#comentários-finais)

8. [Bibliografia](#bibliografia)

# Resumo

Neste trabalho temos como objetivo comparar o desempenho de 1 programa refeito com 5 implementações diferentes:

  1. Sequential
  2. Threaded
  3. OpenMP
  4. MPI
  5. Híbrido OpenMP + MPI

Irei numa primeira fase explicar o problema que deve ser resolvido pelo programa. Também irei dar explicação detalhada sobre a lógica por de trás dos programas. Isto é, explicar como funcionam sem entrar demasiado no código.

O projeto tráz os ficheiros com o código dos programas organizados por pastas.
Tráz também os ficheiros de testes que foram usados pelos programas como forma de comparação entre as implementações.
Neste relatório darei instruções de como compilar e correr as cinco implementações.

Irei mostrar o procedimento de como mensurar o desempenho dos programas compilados. Este projeto tráz as ferramentas de benchmarking utilizadas nestas medições.
Farei também uma breve explicação de como estas ferramentas funcionam internamente.

Por fim, irei analisar os dados obtidos. Fazer as comparações necessárias e explicar os resultados em detalhe.

# Abstract

(WORK IN PROGRESS)

# Introdução

Este projeto tem como objetivo o desenvolvimento de um conjunto de programas na linguagem C com 5 diferentes abordagens, sendo estas sequencial, threaded, OpenMP, MPI e uma abordagem híbrida do OpenMP com MPI.
O propósito destes programas é sempre o mesmo, determinar se os dados contidos num dado ficheiro de texto correspondem a um quadrado mágico e, em caso afirmativo, determinar se é [quadrado mágico](https://pt.wikipedia.org/wiki/Quadrado_m%C3%A1gico) perfeito ou imperfeito.

(Como determinar se é quadrado magico)

Foi nos fornecido uma ferramenta para gerar quadrados mágicos, e depressa começamos a partilhar entre nós, colegas, os ficheiros de teste gerados para utilização de todos.
Os testes são compostos por uma linha única com todos os números inteiros que compõem um quadrado magico separados apenas por um espaço ```' '```. Os ficheiros mais simples são ficheiros com quadrados pequenos 3 por 3. E os mais elaborados são ficheiros de com quadrados de 20001 de lado. Estes últimos, por conterem mais dados, são maiores no espaço que ocupam no disco rígido da maquina. Pode chegar aos 3,6Gb. Por serem maiores irão, logicamente, requerer mais recursos computacionais para resolver o problema.\
Para facilitar a identificação do quadrado que o ficheiro contém foi seguida uma convenção para a nomeação do ficheiro em si, onde quadrados perfeitos começam pela letra ```p```, quadrados imperfeitos começam pela letra ```i``` e quadrados que não são mágicos começam pela letra ```n```. Precedendo a letra identificadora vem um numero inteiro com o tamanho do lado do quadrado. Por fim vem a extensão do ficheiro que será sempre ```.txt```.
Exemplo de nomes de ficheiro de teste:\
```p3.txt```\
```i7.txt```\
```n31.txt```

Como forma de mensurar a performance dos programas desenvolvidos irei utilizar os scripts de benchmark criados por mim e partilhados com os meus colegas.
Estes scripts tem por base a utilização do programa ```time``` presente no kernel. Esta função informa-nos sobre o tempo que um dado programa leva desde que começa a sua execução até que termina.\
O script irá correr o programa 31 vezes onde apenas a primeira não é contabilizada. Os resultados são devolvidos num ficheiro de texto com os tempos das 30 execuções e serão depois usados para calcular a media. Para analisar estes dados e calcular a media de forma mais conveniente criei um programa e em linguagem C ao qual é fornecido o ficheiro com os tempos e ele devolve a media dos tempos no stdout. Este programa foi também partilhado com os meus colegas.

# Enquadramento

## Quadrado magico

(Detalhes importantes referir, não esquecer colocar referencias e bibliografia)

## GCC

(Detalhes importantes referir, não esquecer colocar referencias e bibliografia)

## Script

(Detalhes importantes referir, não esquecer colocar referencias e bibliografia)

## Implementação sequencial

(Detalhes importantes referir, não esquecer colocar referencias e bibliografia)

## Implementação threaded

(Detalhes importantes referir, não esquecer colocar referencias e bibliografia)

## OpenMP

(Detalhes importantes referir, não esquecer colocar referencias e bibliografia)

## MPI

(Detalhes importantes referir, não esquecer colocar referencias e bibliografia)

## Programa ```time```

(Detalhes importantes referir, não esquecer colocar referencias e bibliografia)

# Estudo de casos

- descrição do problema

- alternativas criadas a avaliar

- implementações e recolha de resultados

(Diferenças entre as implementações)

## Instruções (WORK IN PROGRESS)

Apenas estão incluídos alguns ficheiros de teste, não foi possível incluir os restantes devido ao limite de 100Mb do github.
Para o resto dos test files clicar [aqui](https://mega.nz/file/Cc8lnYaS#bikjsB_99M4HY81XMtz3itC8jDUnwN8ruZFvVP2_rxM).\
Extrair o conteúdo do ficheiro comprimido para o diretório ```/tests```

Abrir terminal no diretório do projeto

- Compilar e executar - correr o seguinte commando:

```bash
# Sequential
./sequential/run.sh tests/<test-file>

# Threaded
./threaded/run.sh tests/<test-file> <thread-count>
```

O programa irá compilar e correr com o ficheiro de teste fornecido.

- Compilar apenas:

```bash
# Sequential
./sequential/compile.sh

# Threaded
./threaded/compile.sh
```

- Executar apenas:

```bash
# Sequential
./sequential/a.out tests/<test-file>

# Threaded
./threaded/a.out tests/<test-file> <thread-count>
```

# Análise de resultados e discussão

# Comentários finais

# Bibliografia

[Quadrado mágico - in Wikipedia](https://pt.wikipedia.org/wiki/Quadrado_m%C3%A1gico)
