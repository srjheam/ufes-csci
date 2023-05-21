<div align="center">
  <h3 align="center">csci</h3>
</div>

## Sobre

Csci foi o primeiro trabalho desenvolvido ao longo da disciplina de Estrutura de Dados, ministrada pelo professor Filipe Mutz ([@filipemtz](https://github.com/filipemtz)).

## Começando

### Pré-requisitos

- Linux (sem suporte pro windows, sra. microsoft)
- [GNU Compiler Collection](https://gcc.gnu.org/)
- [GNU Make](https://www.gnu.org/software/make/)

### Instalando

1. Clone o repositório

   ```sh
   git clone https://github.com/srjheam/ufes-csci.git
   ```

2. Dirija-se ao seu diretório

   ```sh
   cd ufes-csci/
   ```

## Testando

1. Dirija-se ao diretório de testes

   ```sh
   cd csci/tests/
   ```
2. Execute o script de testes

Há dois scripts de testes, um para testar todos os testes e outro para testar um teste específico.

```sh
sh test-all.sh -m 0
```

Onde,

- `-m` é a flag para executar o teste com o Valgrind

```sh
sh run-test.sh -e convolution_test -m 0
```

Onde,

- `-e` é a flag para executar um teste específico
- `-m` é a flag para executar o teste com o Valgrind

## Contribuindo

Este projeto está configurado e integrado com o Visual Studio Code.

Abra a main do teste que deseja executar e inicie o debugador.

### Valgrind

Os scripts de teste recebem a flag `-m` para executar o teste com o Valgrind.

```sh
sh test-all.sh -m 1
```

O log do Valgrind é salvo no arquivo `valgrind-out.txt`.

Caso um leak seja detectado, o teste falha e seus resultados são reportados na saída.

## Suporte

Esse programa não funciona em ambientes não-POSIX e pode até mesmo não funcionar em sistemas não-Linux.

Isso se deve ao fato de usar APIs que são extenções do POSIX e não fazem parte do padrão C.

## License

Licensed under [Unlicense](./LICENSE).
