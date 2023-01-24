/*----------------------------------------------------------------
                        Trabalho_SB
                         (main.c)
 -----------------------------------------------------------------
 DESCRIÇÃO:
 ---------
 O trabalho se baseia na implementação de um tradutor de uma 
 linguagem simples (chamada de BPL – Bruno’s Programming Language) para Assembly.

 DESENVOLVEDORES:
 ----------------
  Nome: Diego Enrique da Silva Lima
  E-mail: diegoenrique@discente.ufg.br

  Nome: Luca Mascarenhas Plaster
  E-mail: 

  Nome: Marcos Reges Mota
  E-mail: 

-----------------------------------------------------------------
 REPOSITÓRIO DO PROJETO: https://github.com/dgoenrique/Trabalho_SB.git
-----------------------------------------------------------------
 DATA DA ÚLTIMA ALTERAÇÃO: 23 / 01 / 2023
----------------------------------------------------------------*/

#include "header.c"

int main() // Código em C
{
  printf(".section .rodata\n");
  printf(".data\n");
  printf(".text\n\n");
  while (1)
  {
    // Limpeza dos lixos dentro das variaveis
    memset(str, 0, sizeof(str));
    memset(s1, 0, sizeof(s1));
    memset(s2, 0, sizeof(s2));
    memset(s3, 0, sizeof(s3));
    memset(s4, 0, sizeof(s4));
    memset(s5, 0, sizeof(s5));
    memset(s6, 0, sizeof(s6));
    memset(s7, 0, sizeof(s7));

    if (scanf("%[^\n]%*c", str) == EOF)
      break;
    if (!strlen(str))
      scanf("%*c");

    sscanf(str, "%s", s1);
    //
    if (!strcmp("function", s1))
    {
      defFunct();
    }
    else if (!strcmp("def", s1))
    {
      defLocalVar();
    }
    else if (!strcmp("return", s1)) // AQUI É DEFINIDA O RETORNO DA FUNÇÃO
      retorno();
    else if (!strcmp("end", s1)) // AQUI SE LOCALIZA O FIM DA FUNÇÃO
    {
      memset(pos, 0, sizeof(pos));
      posparam = 0;
    }
    else if ('v' == s1[0] && 'i' == s1[1]) // SEÇÃO DE ATRIBUIÇÃO DE VARIÁVEIS
    {
      atribuicao();
    }
    else if (!strcmp("if", s1)) // Definição do IF
    {
      condicionalIf();
    }
    else if (!strcmp("endif", s1))
      condicionalEndif();
    else if (!strcmp("set", s1))
    {
      accessArraySet();
    }
    else if (!strcmp("get", s1))
    {
      accessArrayGet();
    }
    printf("\n");
  }
}
