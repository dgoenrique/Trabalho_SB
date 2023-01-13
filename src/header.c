#include "header.h"

// TODO
// * ATRIBUIÇÃO

int qi = 0;        // Quantidade de ifs
short int pos[10]; // posição dos elementos em uma pilha do vetor
char posparam = 0; // quantidade de parâmetros de uma função
void defFunct()
{
  sscanf(str, "%s %s %s %s %s", s1, s2, s3, s4, s5);
  printf("    ");
  printf("%s:\n", s2);
  printf("pushq %s\n", registradores64[6]);
  printf("movq %s, %s\n", registradores64[7], registradores64[6]);

  if (!strcmp(s3, "pa1") || !strcmp(s3, "pi1")) // verifica se há parâmetros
    posparam++;
  if (!strcmp(s4, "pa2") || !strcmp(s4, "pi2"))
    posparam++;
  if (!strcmp(s5, "pa3") || !strcmp(s5, "pi3"))
    posparam++;

  printf("\n");
  printf("Definição da função\n");
}

void defLocalVar()
{
  int cont = 0;
  // Colocar na pilha
  printf("Definição das variáveis\n");
  while (1)
  {
    scanf("%[^\n]%*c", str);
    sscanf(str, "%s", s1);
    if (!strcmp("var", s1))
    { // Se for variável
      sscanf(str, "%s %2s %d", s1, s2, &ax);
      sscanf(str, "%s %s", s1, s2);
      cont += 4;
      pos[ax - 1] = cont;
      printf("   # %s: -%d \n", s2, cont, registradores64[6]);
    }
    else if (!strcmp("vet", s1)) // Se for um vetor
    {
      sscanf(str, "%s %2s %d %s %2s %d", s1, s2, &ax, s3, s4, &a1);
      cont += 4 * a1;
      pos[ax - 1] = cont;
      printf("  # %s%d: -%d \n", s2, ax, cont, registradores64[6]);
    }
    else if (!strcmp("enddef", s1)) // salva os parametros na pilha
    {
      if (posparam != 0)
      {
        int aux = cont;
        aux = aux + posparam * 8;
        if (aux % 16)

          aux = aux + 16 - (aux % 16);
        printf("    subq $%d, %s\n\n", aux, registradores64[7]);
        if (cont % 8)
          cont = cont + 8 - (cont % 8);
        aux = posparam;
        while (posparam--)
        {
          cont += 8;
          pos[7 + (3 - aux)] = cont; // Salva o endereço dos parâmetros
          printf("    movq %s, -%d(%s)\n", registradores64[2 + (aux)], cont, registradores64[6]);
          aux--;
        }
      }
      else
      {
        if (cont % 16)
          cont = cont + 16 - (cont % 16);
        printf("    subq $%d, %s\n\n", cont, registradores64[7]);
      }
      break;
    }
  }
}
void funcCall()
{

  sscanf(str, "%s %s %s %s %s %s %s", s1, s2, s3, s4, s5, s6, s7);
  if (strlen(s5) > 2) // VERIFICA SE HÁ PARAMETROS, CASO CONTRÁRIO ELE NÃO
  // IRÁ PASSAR NADA. A STRING POSSUI 0 DE TAMANHO
  {
    sscanf(s5, "%2s %d", s2, &ax);
    if (!strcmp(s2, "ci"))                                  // INDICA SE É CONSTANTE
      printf("    movl $%d, %s\n", ax, registradores32[5]); // verificar se o parametro é do tipo
    // inteiro ou quad
    else if (!strcmp(s2, "va")) // INDICA SE É VETOR
      printf("    movl $%s, %s\n", s5, registradores64[5]);
    else
      printf("    movl %s, %s\n", s5, registradores32[5]); // PARAMETRO OU VARIÁVEL
  }
  if (strlen(s6) > 2)
  {
    sscanf(s6, "%2s %d", s2, &ax);
    if (!strcmp(s2, "ci"))
      printf("    movl $%d, %s\n", ax, registradores32[4]); // verificar se o parametro é do tipo
    // inteiro ou quad
    else if (!strcmp(s2, "va"))
      printf("    movl $%s, %s\n", s6, registradores64[4]);
    else
      printf("    movl %s, %s\n", s6, registradores32[4]);
  }
  if (strlen(s7) > 2)
  {
    sscanf(s7, "%2s %d", s2, &ax);
    if (!strcmp(s2, "ci"))
      printf("    movl $%d, %s\n", ax, registradores32[3]); // verificar se o parametro é do tipo
    // inteiro ou quad
    else if (!strcmp(s2, "va"))
      printf("    movl $%s, %s\n", s7, registradores64[3]);
    else
      printf("    movl %s, %s\n", s7, registradores32[3]);
  }
  printf("    call %s\n", s4);
  printf("    movl %s, %s\n", registradores32[0],
         s1); // FINALIZA A FUNÇÃO MOVENDO %EAX PARA A VARIAVEL DEFINIDA
}

void funcExpressoes()
{
  sscanf(str, "%s %s %s %s %s", s1, s2, s3, s4, s5);
  // S4 É A OPERAÇÃO
  if (strlen(s5) > 2) // EXPRESSÃO COMPLEXA
  {
    sscanf(s3, "%2s %d", s7, &ax);
    if (!strcmp("vi", s7) || !strcmp("pi", s7))
      printf("    movl %s, %s\n", s3, registradores32[2]);
    else
      printf("    movl $%d, %s\n", ax, registradores32[2]);
    sscanf(s5, "%2s %d", s7, &ax);
    if (!strcmp("vi", s7) || !strcmp("pi", s7))
      printf("    movl %s, %s\n", s5, registradores32[10]);
    else
      printf("    movl $%d, %s\n", ax, registradores32[10]);
    if (s4[0] == '*')
      printf("    imull %s, %s\n", registradores32[2], registradores32[10]);
    else if (s4[0] == '+')
      printf("    addl %s, %s\n", registradores32[2], registradores32[10]);
    else if (s4[0] == '-')
      printf("    subl %s, %s\n", registradores32[2], registradores32[10]);
    printf("    movl %s, %s\n", registradores32[10], s1);
  }
  else // EXPRESSÃO SIMPLES
  {
    sscanf(s1, "%2s %d", s2, &a1);
    sscanf(s3, "%2s %d", s7, &ax);
    if (!strcmp("vi", s7))
    {
      printf("    movl -%d(%s), %s\n", pos[ax - 1], registradores64[6], registradores32[2]);
      printf("    movl %s, -%d(%s)\n", registradores32[2], pos[a1 - 1], registradores64[6]);
    }
    else if (!strcmp("pi", s7))
    {
      printf("    movl -%d(%s), %s\n", pos[7 + (3 - ax)], registradores64[6], registradores32[2]);
      printf("    movl %s, -%d(%s)\n", registradores32[2], pos[a1 - 1], registradores64[6]);
    }
    else
      printf("    movl $%d, -%d(%s)\n", ax, pos[a1 - 1], registradores64[6]);
  }
}

void atribuicao()
{
  sscanf(str, "%s %s %s", s1, s2, s3);

  if (!strcmp("call", s3)) 
    funcCall();
  else 
    funcExpressoes();
  printf("\n");
}

void accessArrayGet()
{
  printf("Definição do get das variáveis de um vetor\n"); // aqui
  sscanf(str, "%s %2s %d %s %2s %d %s %2s %d", s1, s2, &ax, s3, s4, &a1, s5, s6, &a2);

  printf("    movq $%d, %s\n", a1, registradores64[8]);

  printf("    imulq $4, %s\n", registradores64[8]);

  if (!strcmp(s2, "va"))
    printf("    leaq -%d(%s), %s\n", pos[ax - 1], registradores64[6], registradores64[9]);
  else
    printf("    leaq -%d(%s), %s\n", pos[6 + ax], registradores64[6], registradores64[9]);

  printf("    addq %s, %s\n", registradores64[9], registradores64[8]);

  printf("    movl (%s), %s\n", registradores64[8], registradores32[9]);

  printf("    movl %s, -%d(%s)\n", registradores32[9], pos[a2 - 1], registradores64[6]);

  printf("\n");
}

void accessArraySet()
{
  printf("Definição do set das variáveis de um vetor\n");
  sscanf(str, "%s %2s %d %s %2s %d %s %2s %d", s1, s2, &ax, s3, s4, &a1, s5, s6, &a2);

  printf("    movq $%d, %s\n", a1, registradores64[8]);

  printf("    imulq $4, %s\n", registradores64[8]);

  if (!strcmp(s2, "va"))
    printf("    leaq -%d(%s), %s\n", pos[ax - 1], registradores64[6], registradores64[9]);
  else
    printf("    leaq -%d(%s), %s\n", pos[6 + ax], registradores64[6], registradores64[9]);

  printf("    addq %s, %s\n", registradores64[9], registradores64[8]);
  if (!strcmp("ci", s6))
    printf("    movl $%d, (%s)", a2, registradores64[8]);
  else
  {
    printf("    movl -%d(%s), %s\n", pos[a2 - 1], registradores64[6], registradores32[9]);

    printf("    movl %s, (%s)\n", registradores32[9], registradores64[8]);
  }
  printf("\n");
}

void condicionalIf()
{
  printf("Definição de if\n");
  sscanf(str, "%s %s %s %s", s1, s2, s3, s4);
  qi++;
  printf("    cmpl $0, %s\n", s2);
  printf("    jne end_if%d\n", qi);
}

void condicionalEndif()
{

  if (!strcmp("endif", s1))
    printf("end_if%d:\n", qi);
}

void retorno()
{
  printf("Definição do retorno\n");
  sscanf(str, "%s %s", s1, s2);
  sscanf(s2, "%2s %d", s3, &ax);

  if (!strcmp(s3, "vi") || !strcmp(s3, "pi"))
    printf("    movl %s, %s\n", s2, registradores32[0]);

  else
    printf("    movl $%d, %s\n", ax, registradores32[0]);
  printf("\n");
}
void leave()
{
  memset(pos, 0, sizeof(pos));
  printf("leave\nret\n\n");
}
