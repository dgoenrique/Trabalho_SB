/*----------------------------------------------------------------
                        Trabalho_SB
                         (header.c)
 -----------------------------------------------------------------
 DESCRIÇÃO:
 ---------
 Bliblioteca que possui os protótipos das funções principais do programa.

 DESENVOLVEDORES:
 ----------------
  Nome: Diego Enrique da Silva Lima

  Nome: Luca Mascarenhas Plaster

  Nome: Marcos Reges Mota

-----------------------------------------------------------------
 REPOSITÓRIO DO PROJETO: https://github.com/dgoenrique/Trabalho_SB.git
-----------------------------------------------------------------
 DATA DA ÚLTIMA ALTERAÇÃO: 24 / 01 / 2023
----------------------------------------------------------------*/

#ifndef __HEADER__
#define __HEADER__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Declaração dos protótipos das funções;
void defFunct(); // Definição das funções;
void defLocalVar(); // Definição das variávies locais;
void atribuicao(); // Atribuições;
void funcCall(); // Chamada de funções;
void funcExpressoes(); // Expressões aritméticas;
void accessArrayGet(); // Acesso ao arrey - get;
void accessArraySet(); // Acesso ao arrey - set;
void condicionalIf();  // Declaração de condicional;
void condicionalEndif(); // Declaração de fim da condicional;
void retorno(); // Retorno da função;
void leave(); // Saída da função.

#endif
