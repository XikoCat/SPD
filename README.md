
# ![UAlg FCT Logo](readme_images/fct.svg)

# Estudo do desempenho das diferentes implementações na resolução de um problema

Guilherme Henriques | aluno nº 61018
2021

## 2021

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

Este trabalho foi desenvolvido no âmbito da cadeira sistemas paralelos e distribuídos. Neste relatório serão apresentados os objetivos principais do trabalho que nos foi proposto, a metodologia seguida, as implementações feitas e os seus resultados e por fim o comentários finais.

# Abstract

This work was developed in the scope of the parallel and distributed systems course. This report will present the main objectives of the work that was proposed to us, the methodology followed, the implementations made and their results, and finally the final comments.

# Introdução

Este projeto tem como objetivo o estudo do desempenho de um conjunto de programas na linguagem C com 5 diferentes abordagens, sendo estas sequencial, threaded, OpenMP, MPI e uma abordagem híbrida do OpenMP com MPI\
A metodologia usada foi o estudo da preformance das varias implementações implementações.\
O propósito destes programas é sempre o mesmo, determinar se os dados contidos num dado ficheiro de texto correspondem a um [quadrado mágico](#quadrado-magico) e, em caso afirmativo, determinar se é quadrado mágico perfeito ou imperfeito.

Neste relatório pode encontrar:

- [Enquadramento](#enquadramento) Os conceitos fundamentais à compreensão deste relatório
- [Estudo de casos](#estudo-de-casos) A descrição do problema, alternativas criadas, implementações e recolha de dados
- [Análise de resultados e discussão](#análise-de-resultados-e-discussão) A analise critica dos resultados
- [Comentários finais](#comentários-finais) Opinião em relação aos metodos, resultados e outras notas pertinentes
- [Bibliografia](#bibliografia) Bibliografia usada no trabalho

# Enquadramento

## Thread

Uma thread é como um agente, responsavel pela execução de operações a ele atribuidas. Enquanto agente, apenas consegue fazer uma operação de cada vez.

## Implementação sequencial

A implementação sequencial é uma implementação também chamada de codigo corrído. Onde apenas uma Thread é responsável pela execução completa do código de forma sequencial.

## Implementação threaded

A implementação threaded é uma implementação cujo trabalho é dividido por várias threads que trabalham em simultãneo.

## OpenMP

O OpenMp é uma biblioteca com implementação de multithreaded para sistemas computacionais de memória partilhada. Permite ao programador selecionar as partes do codigo que são partilhadas na execução entre as varias threads.

## MPI

MPI é um modelo de programação que permite a divisão da execução do programa por várias máquinas. Permitindo a cada computador executar a parte do código que lhe for atribuida.

## Quadrado magico

Quadrado Mágico é uma tabela quadrada, com números, em que a soma de cada coluna, de cada linha e das duas diagonais são iguais.
Pode ser classificado como:

### Perfeito

Um quadrado que obedece às regras de um quadrado mágico. A soma das linhas, colunas e diagonais é igual

Exemplo:

|**8**|**1**|**6**|
|:---:|:---:|:---:|
|**3**|**5**|**7**|
|**4**|**9**|**2**|

A soma de qualquer linha, coluna ou diagonal é 15.

### Imperfeito/defeituoso

Um quadrado que obedece quase todas regras de um quadrado mágico. A soma das linhas, colunas é igual, porém pelo menos uma das diagonais difere

Exemplo:

|**1**|**2**|**3**|
|:---:|:---:|:---:|
|**2**|**3**|**1**|
|**3**|**1**|**2**|

A soma de qualquer linha ou coluna e uma das diagonais é 6 a outra diagonal é 9.

Existem mais tipos de quadrados mágicos para além dos mencionados, porém não são relevantes para este trabalho.

[Ver fonte](https://pt.wikipedia.org/wiki/Quadrado_m%C3%A1gico)

# Estudo de casos

O programa a desenvolver com as cinco implementações deve ser capaz de identificar o tipo de quadrado, que lhe é fornecido.
Os dados dos quadrados devem estar guardados em ficheiros.

Foi nos fornecido uma ferramenta para gerar quadrados mágicos, e depressa começamos a partilhar entre nós, colegas, os ficheiros de teste gerados para utilização de todos.
Os testes são compostos por uma linha única com todos os números inteiros que compõem um quadrado magico separados apenas por um espaço ```' '```. Os ficheiros mais simples são ficheiros com quadrados pequenos 3 por 3. E os mais elaborados são ficheiros de com quadrados de 20001 de lado. Estes últimos, por conterem mais dados, são maiores no espaço que ocupam no disco rígido da maquina. Pode chegar aos 3,6Gb. Por serem maiores irão, logicamente, requerer mais recursos computacionais para resolver o problema.\
Para facilitar a identificação do quadrado que o ficheiro contém foi seguida uma convenção para a nomeação do ficheiro em si, onde quadrados perfeitos começam pela letra ```p```, quadrados imperfeitos começam pela letra ```i``` e quadrados que não são mágicos começam pela letra ```n```. Precedendo a letra identificadora vem um numero inteiro com o tamanho do lado do quadrado. Por fim vem a extensão do ficheiro que será sempre ```.txt```.
Exemplo de nomes de ficheiro de teste:\
```p3.txt```\
```i7.txt```\
```n31.txt```

## Implementações

### A implementação Sequencial

A implementação sequencial foi implementada de maneira a efectuar os calculos e verificações à medida que vai lendo os dados do ficheiro.
Sempre que um numero é lido é somado ao total da linha e ao total da coluna a que pertence e, no caso de pertencer a alguma diagonal, é somado aos totais coorespondentes. Se durante este procedimento, algum total final das linhas ou colunas for diferente, o quadrado não é mágico. Se as linhas e colunas forem iguais mas alguma das diagonais diferir, o quadrado é magico imperfeito. Se todos os totais forem iguais o quadrado é mágico.

### A implementação Threaded

Na implementação threaded decidi dividir a tarefa mais demorada da sequencial, a leitura. A determinação do tipo de quadrado passou a ser executada após a leitura dos dados todos para uma lista. Dividir o trabalho de leitura por varias partes não é uma tarefa trivial. Primeiro é necessario saber quantos caracteres existem no ficheiro. Sabendo este valor podemos fazer a divisão aproximada da leitura. Ao dividirmos pelo numero de characteres podemos acidentalmente dividir os characteres de um número inteiro. Cada thread irá procurar o inicio no numero mais próximo e ler todos os numeros até que o inicio do seguinte ultrapasse o limite final.
Todos os numeros são guardados em varias listas que depois serão unidas.

### A implementação OpenMP

A implementação é apenas uma adaptação da implementação threaded, com apenas algumas diferenças notáveis. Nesta implementação todas as threads são responsáveis pela leitura, ao passo que na threaded apenas as secundárias são. Visto que a primeira é responsável pela criação e divisão dos dados pelas threads secundárias e das próprias threads.

### A implementação MPI

Esta implementação é semelhante às anteriores. Porém foi necessário a implementação de funções especificas para serem usadas pelo computador satéite para que este leia usando as funções da biblioteca MPI. Para correr a leitura é necessário que o mesmo ficheiro esteja presente nos 2 computadores.

### A implementação OpenMPI

Esta implementação é semelhante à anterior. Apenas foi dividido o trabalho de cada maquina por 2 threads, usando a biblioteca OpenMPI.

## Instruções

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

# OpenMP
./openMP/run.sh tests/<test-file>

# MPI
./MPI/run.sh tests/<test-file>

# OpenMPI
./openMPI/run.sh tests/<test-file>
```

O programa irá compilar e correr com o ficheiro de teste fornecido.

- Compilar apenas:

```bash
# Sequential
./sequential/compile.sh

# Threaded
./threaded/compile.sh

# OpenMP
./openMP/compile.sh

# MPI
./MPI/compile.sh

# OpenMPI
./openMPI/compile.sh
```

- Executar apenas:

```bash
# Sequential
./sequential/a.out tests/<test-file>

# Threaded
./threaded/a.out tests/<test-file> <thread-count>

# OpenMP
./openMP/a.out tests/<test-file>

# MPI
./MPI/mpirun -np 2 ./a.out tests/<test-file>

# OpenMPI
./openMPI/mpirun -np 2 ./a.out tests/<test-file>
```

## Recolha de resultados

Como forma de mensurar a performance dos programas desenvolvidos irei utilizar os scripts de benchmark criados por mim e partilhados com os meus colegas.
Estes scripts tem por base a utilização do programa ```time``` presente no kernel. Esta função informa-nos sobre o tempo que um dado programa leva desde que começa a sua execução até que termina.\
O script irá correr o programa 31 vezes onde apenas a primeira não é contabilizada. Os resultados são devolvidos num ficheiro de texto com os tempos das 30 execuções e serão depois usados para calcular a media. Para analisar estes dados e calcular a media de forma mais conveniente criei um programa e em linguagem C ao qual é fornecido o ficheiro com os tempos e ele devolve a media dos tempos no stdout. Este programa foi também partilhado com os meus colegas.

## Análise de resultados e discussão

Op

## Comentários finais

# Bibliografia

- [Quadrado mágico - in Wikipedia](https://pt.wikipedia.org/wiki/Quadrado_m%C3%A1gico)

- [https://hpc.llnl.gov/openmp-tutorial](https://hpc.llnl.gov/openmp-tutorial)

- [www.bowdoin.edu in OpenMP](http://www.bowdoin.edu/~ltoma/teaching/cs3225-GIS/fall17/Lectures/openmp.html)
