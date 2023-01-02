#include "header.c"

int main() // Código em C
{
  printf(".section .rodata\n");
  printf(".data\n");
  printf(".text\n\n");

  while (1) {
    // Limpeza dos lixos dentro das variaveis
    memset(str, 0, sizeof(str));
    memset(s1, 0, sizeof(s1));
    memset(s2, 0, sizeof(s2));
    memset(s3, 0, sizeof(s3));
    memset(s4, 0, sizeof(s4));
    memset(s5, 0, sizeof(s5));
    memset(s6, 0, sizeof(s6));
    memset(s7, 0, sizeof(s7));
    scanf("%[^\n]%*c", str);

    // printf("%s\n", sr);
    //  sscanf(str, "%s %s %s %s %s %s", s1, s2, s3, s4, s5, s6);
    sscanf(str, "%s", s1);
    //
    if (!strcmp("function", s1)) {
      defFunct();
    } else if (!strcmp("def", s1)) {
      defLocalVar();
    } else if (!strcmp("return", s1)) // AQUI É DEFINIDA O RETORNO DA FUNÇÃO
      retorno();
    else if (!strcmp("end", s1)) // AQUI SE LOCALIZA O FIM DA FUNÇÃO
    {
      leave();
      return 0;
    } else if ('v' == s1[0] && 'i' == s1[1]) // SEÇÃO DE ATRIBUIÇÃO DE VARIÁVEIS
    {
      atribuicao();
    } else if (!strcmp("if", s1)) // Definição do IF
    {
      condicionalIf();
    } else if (!strcmp("endif", s1))
      condicionalEndif();
    // ACESSAR ARRAYS E CRIAR CONDICIONAIS

    else if (!strcmp("set", s1)) {
      accessArrayGet();
    }

    else if (!strcmp("get", s1)) {
      accessArraySet();
    }
    printf("\n");
  }
  // Delarar variáveis na pilha
}
