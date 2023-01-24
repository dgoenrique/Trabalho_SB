/*----------------------------------------------------------------
                        Trabalho_SB
                         (main.c)
 -----------------------------------------------------------------
 DESCRIÇÃO:
 ---------
 O trabalho se baseia na implementação de um tradutor de uma 
 linguagem simples (chamada de BPL – Bruno’s Programming Language)
 para Assembly, utilizando a linguagem C.

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

#include "header.c"

int main() 
{
  // Inserção das seções 
  printf(".section .rodata\n");
  printf(".data\n");
  printf(".text\n\n");
  while (1)
  {
    // Limpeza dos lixos dentro das variaveis auxiliares globais
    memset(str, 0, sizeof(str));
    memset(s1, 0, sizeof(s1));
    memset(s2, 0, sizeof(s2));
    memset(s3, 0, sizeof(s3));
    memset(s4, 0, sizeof(s4));
    memset(s5, 0, sizeof(s5));
    memset(s6, 0, sizeof(s6));
    memset(s7, 0, sizeof(s7));
    
    // Leitura da linhas do arquivo
    if (scanf("%[^\n]%*c", str) == EOF)
      break;
    if (!strlen(str))
      scanf("%*c");

    sscanf(str, "%s", s1);
    if (!strcmp("function", s1)) // Definição das funções
    {
      defFunct();
    }
    else if (!strcmp("def", s1)) // Variáveis Locais
    {
      defLocalVar();
    }
    else if (!strcmp("return", s1)) // Retorno da função 
      retorno();
    else if (!strcmp("end", s1)) // Fim da função
    {
      memset(pos, 0, sizeof(pos));
      posparam = 0;
    }
    else if ('v' == s1[0] && 'i' == s1[1]) // Atribuição
    {
      atribuicao();
    }
    else if (!strcmp("if", s1)) // Condicionais 
    {
      condicionalIf();
    }
    else if (!strcmp("endif", s1)) // Termino das condicionais
      condicionalEndif();
    else if (!strcmp("set", s1)) // Acesso ao Array (set)
    {
      accessArraySet();
    }
    else if (!strcmp("get", s1)) // Acesso ao Array (get)
    {
      accessArrayGet();
    }
    printf("\n");
  }
}
