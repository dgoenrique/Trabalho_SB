<h1 align="center"> Tabalho de Software Básico </h1>
<p align="center"><img src="ufg.png" alt="Logo UFG" height="170" width="240"></p>

## Integrantes:
<ul>
  <li><i>Diego Enrique da Silva Lima</i></li>
  <li><i>Luca Mascarenhas Plaster</i></li>
  <li><i>Marcos Reges Mota</i> (Regittos)</li>
</ul>

## Tabela de Conteúdo

* [Integrantes](#integrantes)
* [Tabela de conteúdos](#tabela-de-conteúdos)
* [Descrição do Projeto](#descrição-do-Projeto)
* [Como  compilar e rodar](#como-compilar-e-rodar)
* [Descrição da Linguagem](#descricao-da-linguagem)

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

## Descrição da Linguagem

### Definição da função
### Variáveis locais
### Corpo da função
- #### Atribuição
- #### Chamada da função
- #### Acessso ao array
- #### Condicional
## BNF da Linguagem
```
<prog> → <func>
 | <func> <prog>
<func> → <header> <defs> <cmds> <ret> '\n' 'end' '\n'
<header> → 'function' <fname> <params> '\n'
<fname> → 'f'<num>
<params> → ε
 | <param> <params>
<param> → <parint>
 | <pararr>
<parint> → 'pi'<num>
<pararr> → 'pa'<num>
<defs> → 'def' '\n' <vardef> 'enddef' '\n'
<vardef> → 'var' <varint> '\n'
 | 'vet' <vararr> 'size' <const> '\n'
<varint> → 'vi'<num>
<vararr> → 'va'<num>
<const> → 'ci'<snum>
<cmds> → <cmd> '\n'
 | <cmd> '\n' <cmds>
<cmd> → <attr>
 | <arrayget>
 | <arrayset>
 | <if>
<attr> → <varint> '=' <expr>
<expr> → <valint>
 | <oper>
 | <call>
<valint> → <varint>
 | <parint>
 | <const>
<oper> → <valint> <op> <valint>
<op> → '+' | '-' | '*' | '/'
<call> → 'call' <fname> <args>
<args> → ε
 | <arg> <args>
<arg> → <valint>
 | <array>
<array> → <vararr>
 | <pararr>
<arrayget> → 'get' <array> 'index' <const> 'to' <varint>
<arrayset> → 'set' <array> 'index' <const> 'with' <valint>
<if> → 'if' <valint> '\n' <body> '\n' 'endif'
<body> → <attr>
 | <arrayget>
 | <arrayset>
 | <ret>
<ret> → 'return' <valint>
<num> → <digit>
 | <digit> <num>
<snum> → <num>
 | '-'<num>
<digit> → '0' | '1' | '2' | '3' | '4' | '5' | '6' | '7'| '8' | '9'
```
