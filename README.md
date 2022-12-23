# Trabalho de Software Básico
<p align="center"><img src="ufg.png" alt="Logo UFG" height="170" width="240"></p>

## Integrantes:
<ul>
  <li><i>Diego Enrique da Silva Lima</i></li>
  <li><i>Luca Mascarenhas Plaster</i></li>
  <li><i>Marcos Reges Mota</i> (Regittos)</li>
</ul>

### Tabela de Conteúdo

* [Integrantes](#integrantes)
* [Tabela de conteúdos](#tabela-de-conteúdos)
* [Descrição do Projeto](#descrição-do-Projeto)
* [Como  compilar e rodar](#como-compilar-e-rodar)

## Descrição do Projeto

O trabalho se baseia na implementação de um tradutor de uma linguagem simples (chamada de BPL – Bruno’s Programming Language) para Assembly.

### Como compilar e rodar

- O tradutor deve ser escrito na linguagem C e será compilado e testado no ambiente Linux 
- O tradutor deve ler um arquivo em BPL da entrada padrão (e.g., usando o *scanf*) e imprimir
a tradução desse programa em Assembly na saída padrão (e.g., usando o *printf*). Pode-se
criar um arquivo com a linguagem e utilizar o redirecionamento para testar:
```
 $ ./tradutor < prog.blp
```
- O tradutor deve imprimir as posições dos elementos na pilha em forma de comentários,
antes da alocação da pilha. Isso inclui variáveis locais ou qualquer posição de salvamento de
registradores (como se fosse o desenho da pilha). Por exemplo
```
# vi1: -4
# va2: -16
# vi3: -32
# rbx: -36
subq $48, %rsp
```





<p> execute gcc -o main main.c <p>
  <p> ./main <test.txt > out.txt <p>
