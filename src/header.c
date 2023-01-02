#include "header.h"

void defFunct() {
  sscanf(str, "%s %s %s %s %s", s1, s2, s3, s4, s5);
  // printf("Funcao\n");
  printf("%s:\n", s2);
  printf("pushq %s\n", registradores64[6]);
  printf("movq %s, %s\n", registradores64[7], registradores64[6]);

  if (!strcmp(s3, "pa1"))
    printf("%s = %s\n", "ponteiro", registradores64[5]);
  else if (!strcmp(s3, "pi1"))
    printf("%s = %s\n", "parametro", registradores64[5]);

  if (!strcmp(s4, "pa2"))
    printf("%s = %s\n", "ponteiro", registradores64[4]);
  else if (!strcmp(s4, "pi2"))
    printf("%s = %s\n", "parametro", registradores64[4]);

  if (!strcmp(s5, "pa3"))
    printf("%s = %s\n", "ponteiro", registradores64[3]);
  else if (!strcmp(s5, "pi3"))
    printf("%s = %s\n", "parametro", registradores64[3]);

  printf("\n");
  printf("Definição da função\n");
}

void defLocalVar() {
  int cont = 0;
  // Colocar na pilha
  printf("Definição das variáveis\n");
  while (1) {
    scanf("%[^\n]%*c", str);
    sscanf(str, "%s", s1);

    if (!strcmp("var", s1)) { // Se for variável
      sscanf(str, "%s %2s %d", s1, s2, &ax);
      sscanf(str, "%s %s", s1, s2);
      printf(".align 4\n");
      printf("%s%d: .int 0\n", s2, ax);
      cont += 4;
      printf("%s: -%d", s2, cont);
    } else if (!strcmp("vet", s1)) // Se for um vetor
    {
      sscanf(str, "%s %s %s %2s %d", s1, s2, s3, s4, &a1);
      printf(".align 4\n");
      printf("%s: .int ", s2);
      cont += 4 * a1;
      printf("%s: -%d\n", s2, cont);
      for (ax = 0; ax < a1; ax++) {
        printf("0");
        if (ax + 1 != a1)
          printf(",");
      }
    } else if (!strcmp("enddef", s1))
      break;
  }
}

void funcCall() {
  sscanf(str, "%s %s %s %s %s %s %s", s1, s2, s3, s4, s5, s6, s7);
  if (strlen(s5) > 2) // VERIFICA SE HÁ PARAMETROS, CASO CONTRÁRIO ELE NÃO
  // IRÁ PASSAR NADA. A STRING POSSUI 0 DE TAMANHO
  {
    sscanf(s5, "%2s %d", s2, &ax);
    if (!strcmp(s2, "ci")) // INDICA SE É CONSTANTE
      printf("movl $%d, %s\n", ax,
             registradores32[5]); // verificar se o parametro é do tipo
    // inteiro ou quad
    else if (!strcmp(s2, "va")) // INDICA SE É VETOR
      printf("movl $%s, %s\n", s5, registradores64[5]);
    else
      printf("movl %s, %s\n", s5,
             registradores32[5]); // PARAMETRO OU VARIÁVEL
  }
  if (strlen(s6) > 2) {
    sscanf(s6, "%2s %d", s2, &ax);
    if (!strcmp(s2, "ci"))
      printf("movl $%d, %s\n", ax,
             registradores32[4]); // verificar se o parametro é do tipo
    // inteiro ou quad
    else if (!strcmp(s2, "va"))
      printf("movl $%s, %s\n", s6, registradores64[4]);
    else
      printf("movl %s, %s\n", s6, registradores32[4]);
  }
  if (strlen(s7) > 2) {
    sscanf(s7, "%2s %d", s2, &ax);
    if (!strcmp(s2, "ci"))
      printf("movl $%d, %s\n", ax,
             registradores32[3]); // verificar se o parametro é do tipo
    // inteiro ou quad
    else if (!strcmp(s2, "va"))
      printf("movl $%s, %s\n", s7, registradores64[3]);
    else
      printf("movl %s, %s\n", s7, registradores32[3]);
  }
  printf("call %s\n", s4);
  printf("movl %s, %s\n", registradores32[0],
         s1); // FINALIZA A FUNÇÃO MOVENDO %EAX PARA A VARIAVEL DEFINIDA
}

void funcExpressoes() {
  sscanf(str, "%s %s %s %s %s", s1, s2, s3, s4, s5);
  // S4 É A OPERAÇÃO
  if (strlen(s5) > 2) // EXPRESSÃO COMPLEXA
  {
    sscanf(s3, "%2s %d", s7, &ax);
    if (!strcmp("vi", s7) || !strcmp("pi", s7))
      printf("movl %s, %s\n", s3, registradores32[2]);
    else
      printf("movl $%d, %s\n", ax, registradores32[2]);
    sscanf(s5, "%2s %d", s7, &ax);
    if (!strcmp("vi", s7) || !strcmp("pi", s7))
      printf("movl %s, %s\n", s5, registradores32[10]);
    else
      printf("movl $%d, %s\n", ax, registradores32[10]);
    if (s4[0] == '*')
      printf("imull %s, %s\n", registradores32[2], registradores32[10]);
    else if (s4[0] == '+')
      printf("addl %s, %s\n", registradores32[2], registradores32[10]);
    else if (s4[0] == '-')
      printf("subl %s, %s\n", registradores32[2], registradores32[10]);
    printf("movl %s, %s\n", registradores32[10], s1);
  } else // EXPRESSÃO SIMPLES
  {
    sscanf(s3, "%2s %d", s7, &ax);
    if (!strcmp("vi", s7) || !strcmp("pi", s7)) {
      printf("movl %s, %s\n", s3, registradores32[2]);
      printf("movl %s, %s\n", registradores32[2], s1);
    } else
      printf("movl $%d, %s\n", ax, s1);
  }
}

void atribuicao() {
  sscanf(str, "%s %s %s", s1, s2, s3);

  if (!strcmp("call", s3)) // VERIFICA SE O QUE ESTÁ SENDO CHAMADO É UMA FUNÇÃo
    funcCall();
  else // CASO NÃO SEJA CHAMADA DE FUNÇÃO, AQUI É DESTINADO À EXPRESSÕES
    funcExpressoes();
  printf("\n");
}

void accessArrayGet() {
  // regisamare 2,3,4  -> usar os registradores r7, r8, r9 para o acesso dos
  // vetores
  printf("Definição do get das variáveis de um vetor\n"); // aqui
  sscanf(str, "%s %s %s %s %s %s", s1, s2, s3, s4, s5, s6);
  printf("movq $%s, %s\n", s2, registradores64[8]);

  sscanf(s4, "%2s %d\n", s7, &ax);
  printf("movq $%d, %s\n", ax, registradores64[9]);
  printf("imulq $4, %s\n", registradores64[9]);
  printf("addq %s, %s\n", registradores64[8],
         registradores64[9]); // até aqui é o mesmo do bloco de cima

  printf("movl (%s), %s\n", registradores64[9], registradores32[10]);
  printf("movl %s, %s\n", registradores32[10],
         s6); // recuperação de uma variável
              // printf("%s\n", s6);
  printf("\n");
}

// Delarar variáveis na pilha

void accessArraySet() {
  // vetores

  printf("Definição do set das variáveis de um vetor\n");
  sscanf(str, "%s %s %s %s %s %s", s1, s2, s3, s4, s5, s6);
  printf("movq $%s, %s\n", s2, registradores64[8]);
  sscanf(s4, "%2s %d", s7, &ax);
  printf("movq $%d, %s\n", ax, registradores64[9]);
  printf("imulq $4, %s\n", registradores64[9]);
  printf("addq %s, %s\n", registradores64[8], registradores64[9]);
  sscanf(s6, "%2s %d\n", s7, &ax);
  // atribuição de constante
  if (!strcmp("ci", s7))
    // printf("%d\n", ax);
    printf("movq $%d, (%s)\n", ax, registradores64[9]);
  else // atribuição através de variável
  {
    printf("movl %s, %s\n", s6, registradores32[10]);
    printf("movslq %s, (%s)\n", registradores32[10], registradores64[9]);
  }
  // printf("%s\n", s6);
}

void condicionalIf() {
  printf("Definição de if\n");
  sscanf(str, "%s %s %s %s", s1, s2, s3, s4);

  printf("cmpl $0, %s\n", s2);
  printf("jne end_if\n");
}

void condicionalEndif() {

  if (!strcmp("endif", s1))
    printf("end_if:\n");
  // ACESSAR ARRAYS E CRIA CONDICIONAIS
}

void retorno() {
  printf("Definição do retorno\n");
  sscanf(str, "%s %s", s1, s2);
  sscanf(s2, "%2s %d", s3, &ax);

  if (!strcmp(s3, "vi") || !strcmp(s3, "pi"))
    printf("movl %s, %s\n", s2, registradores32[0]);

  else
    printf("movl $%d, %s\n", ax, registradores32[0]);
  printf("\n");
}
void leave() { printf("leave\nret\n\n"); }