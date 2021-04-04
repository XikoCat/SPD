# SPD

## Objetivo

Este projeto tem como objetivo a  um programa na linguagem C com 5 diferentes abordagens, sendo estas sequencial, threaded, OpenMP, MPI e uma abordagem híbrida do OpenMP com MPI.
O programa deve aceitar um ficheiro como argumento, e determinar se os dados desse ficheiro correspondem a um [quadrado mágico](https://pt.wikipedia.org/wiki/Quadrado_m%C3%A1gico).
O programa deve identificar se o quadrado é magico perfeito, quadrado magico imperfeito ou se não é quadrado magico.

## Implementações

### Sequencial

Status: Working

TODO:

- [ ] Comentários funções

### Threaded (Current)

Status: Working

TODO:

- [x] Leitura threaded
- [ ] Resolver threaded

### OpenMP

Status: Not started

TODO:

- [ ] Everything

### MPI

Status: Not started

TODO:

- [ ] Everything

### OpenMP + MPI

Status: Not started

TODO:

- [ ] Everything

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
