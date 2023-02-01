/*----------------------------------------------------------------
                      Trabalho_SB
                         (header.c)
 -----------------------------------------------------------------
 DESCRIÇÃO:
 ---------
 Implementação das funções da biblioteca "header.h", que contêm os protótipos das funções
 e as variaveis globais com os registradores.

 DESENVOLVEDORES:
 ----------------
  Nome: Diego Enrique da Silva Lima

  Nome: Luca Mascarenhas Plaster

  Nome: Marcos Reges Mota

-----------------------------------------------------------------
 REPOSITÓRIO DO PROJETO: https://github.com/dgoenrique/Trabalho_SB.git
-----------------------------------------------------------------
 DATA DA ÚLTIMA ALTERAÇÃO: 31 / 01 / 2023
----------------------------------------------------------------*/

#include "header.h"

// Variáveis globais auxiliares para armazenar as strings
char str[100], s1[20], s2[20], s3[20], s4[20], s5[20], s6[20], s7[20];
// Variáveis globais para armazenar os valores decimais
int ax, a1, a2, a3;

// Matriz com o nome dos registradores de 32 bits.
char registradores32[16][6] = {
    {"\%eax"},
    {"\%ebx"},
    {"\%ecx"},
    {"\%edx"},
    {"\%esi"},
    {"\%edi"},
    {"\%ebp"},
    {"\%esp"},
    {"\%r8d"},
    {"\%r9d"},
    {"\%r10d"},
    {"\%r11d"},
    {"\%r12d"},
    {"\%r13d"},
    {"\%r14d"},
    {"\%r15d"},
};

// Matriz com o nome dos registradores de 64 bits.
char registradores64[16][6] = {
    {"\%rax"},
    {"\%rbx"},
    {"\%rcx"},
    {"\%rdx"},
    {"\%rsi"},
    {"\%rdi"},
    {"\%rbp"},
    {"\%rsp"},
    {"\%r8"},
    {"\%r9"},
    {"\%r10"},
    {"\%r11"},
    {"\%r12"},
    {"\%r13"},
    {"\%r14"},
    {"\%r15"},
};

int qi = 0;        // Quantidade de ifs
short int pos[10]; // Posição dos elementos em uma pilha do vetor
char posparam = 0; // Quantidade de parâmetros de uma função

void defFunct()
{
  sscanf(str, "%s %s %s %s %s", s1, s2, s3, s4, s5);
  printf(".globl %s\n", s2);
  printf("%s:\n", s2);
  printf("pushq %s\n", registradores64[6]);
  printf("movq %s, %s\n", registradores64[7], registradores64[6]);

  if (!strcmp(s3, "pa1") || !strcmp(s3, "pi1"))
    posparam++;
  if (!strcmp(s4, "pa2") || !strcmp(s4, "pi2"))
    posparam++;
  if (!strcmp(s5, "pa3") || !strcmp(s5, "pi3"))
    posparam++;
}

void defLocalVar()
{
  int cont = 0;
  while (1)
  {
    scanf("%[^\n]%*c", str);
    sscanf(str, "%s", s1);
    if (!strcmp("var", s1)) // Se for variável
    {
      sscanf(str, "%s %2s %d", s1, s2, &ax);
      sscanf(str, "%s %s", s1, s2);
      cont += 4;
      pos[ax - 1] = cont;
      printf("    # %s: -%d \n", s2, cont);
    }
    else if (!strcmp("vet", s1)) // Se for um vetor
    {
      sscanf(str, "%s %2s %d %s %2s %d", s1, s2, &ax, s3, s4, &a1);
      cont += 4 * a1;
      pos[ax - 1] = cont;
      printf("    # %s%d: -%d \n", s2, ax, cont);
    }
    else if (!strcmp("enddef", s1)) // Salva os parametros na pilha
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
        aux = 0;
        while (posparam--)
        {
          cont += 8;
          pos[7 + aux] = cont; // Salva o endereço dos parâmetros
          printf("    movq %s, -%d(%s)\n", registradores64[5 - aux], cont, registradores64[6]);
          aux++;
        }
      }
      else
      {
        if (cont % 16)
          cont = cont + 16 - (cont % 16);
        if (cont != 0)
          printf("    subq $%d, %s\n", cont, registradores64[7]);
      }
      break;
    }
  }
}

void funcCall()
{
  sscanf(str, "%s %s %s %s %s %s %s", s1, s2, s3, s4, s5, s6, s7);
  if (strlen(s5) > 1)
  {
    sscanf(s5, "%2s %d", s2, &ax);
    if (!strcmp(s2, "ci")) // Para constantes inteiras
      printf("    movl $%d, %s\n", ax, registradores32[5]);
    else if (s2[1] == 'a') // Para va (variáveis arrays) ou pa (parâmetros arrays)
    {
      if (!strcmp(s2, "va")) // Variável array
        printf("    leaq -%d(%s), %s\n", pos[ax - 1], registradores64[6], registradores64[5]);
      else
        printf("    movq -%d(%s), %s\n", pos[6 + ax], registradores64[6], registradores64[5]); // Parâmetro array
    }
    else if (s2[1] == 'i') // Para vi (variável inteira) ou pi (parâmetro inteiro)
    {
      if (!strcmp(s2, "vi")) // Variável inteira
        printf("    movl -%d(%s), %s\n", pos[ax - 1], registradores64[6], registradores32[5]);
      else
        printf("    movl -%d(%s), %s\n", pos[6 + ax], registradores64[6], registradores32[5]); // Parâmetro inteiro
    }
  }
  if (strlen(s6) > 1)
  {
    sscanf(s6, "%2s %d", s2, &ax);
    if (!strcmp(s2, "ci")) // Para constantes inteiras
      printf("    movl $%d, %s\n", ax, registradores32[4]);
    else if (s2[1] == 'a') // Para va (variáveis arrays) ou pa (parâmetros arrays)
    {
      if (!strcmp(s2, "va")) // Variável array
        printf("    leaq -%d(%s), %s\n", pos[ax - 1], registradores64[6], registradores64[4]);
      else
        printf("    leaq -%d(%s), %s\n", pos[6 + ax], registradores64[6], registradores64[4]); // Parâmetro array
    }
    else if (s2[1] == 'i') // Para vi (variável inteira) ou pi (parâmetro inteiro)
    {
      if (!strcmp(s2, "vi")) // Variável inteira
        printf("    movl -%d(%s), %s\n", pos[ax - 1], registradores64[6], registradores32[4]);
      else
        printf("    movl -%d(%s), %s\n", pos[6 + ax], registradores64[6], registradores32[4]); // Parâmetro inteiro
    }
  }
  if (strlen(s7) > 1)
  {
    sscanf(s7, "%2s %d", s2, &ax);
    if (!strcmp(s2, "ci")) // Para constantes inteiras
      printf("    movl $%d, %s\n", ax, registradores32[3]);
    else if (s2[1] == 'a') // Para va (variáveis arrays) ou pa (parâmetros arrays)
    {
      if (!strcmp(s2, "va")) // Variável array
        printf("    leaq -%d(%s), %s\n", pos[ax - 1], registradores64[6], registradores64[3]);
      else
        printf("    leaq -%d(%s), %s\n", pos[6 + ax], registradores64[6], registradores64[3]); // Parâmetro array
    }
    else if (s2[1] == 'i') // Para vi (variáveis inteiras) e pi (parâmetros inteiros)
    {
      if (!strcmp(s2, "vi")) // Variáveis inteiras
        printf("    movl -%d(%s), %s\n", pos[ax - 1], registradores64[6], registradores32[3]);
      else
        printf("    movl -%d(%s), %s\n", pos[6 + ax], registradores64[6], registradores32[3]); // Parâmetro inteiro
    }
  }
  printf("    call %s\n", s4); // Chamada da função
  sscanf(s1, "%2s %d", s2, &ax);
  printf("    movl %s, -%d(%s)\n", registradores32[0], pos[ax - 1], registradores64[6]); // %eax para pilha
}

void funcExpressoes()
{
  sscanf(str, "%s %s %s %s %s", s1, s2, s3, s4, s5);
  if (strlen(s5) > 2) // Expressões complexas
  {
    sscanf(s3, "%2s %d", s7, &ax);
    if (!strcmp("vi", s7))
      printf("    movl -%d(%s), %s\n", pos[ax - 1], registradores64[6], registradores32[8]);
    else if (!strcmp("pi", s7))
      printf("    movl -%d(%s), %s\n", pos[6 + ax], registradores64[6], registradores32[8]);
    else
      printf("    movl $%d, %s\n", ax, registradores32[8]);

    sscanf(s5, "%2s %d", s7, &ax);
    if (!strcmp("vi", s7))
      printf("    movl -%d(%s), %s\n", pos[ax - 1], registradores64[6], registradores32[9]);
    else if (!strcmp("pi", s7))
      printf("    movl -%d(%s), %s\n", pos[6 + ax], registradores64[6], registradores32[9]);
    else
      printf("    movl $%d, %s\n", ax, registradores32[9]);

    if (s4[0] == '*') // Multiplicação
      printf("    imull %s, %s\n", registradores32[8], registradores32[9]);
    else if (s4[0] == '+') // Soma
      printf("    addl %s, %s\n", registradores32[8], registradores32[9]);
    else if (s4[0] == '-') // Subtração
      printf("    subl %s, %s\n", registradores32[8], registradores32[9]);
    else if (s4[0] == '/') // Divisão
    {
      // Com base no gabarito do exercício 1 do laboratório de mecanismos de controle
      printf("    movl %s, %s\n", registradores32[8], registradores32[0]);
      printf("    cltd \n");
      printf("    movl %s, %s\n", registradores32[9], registradores32[2]);
      printf("    idivl %s \n", registradores32[2]);  
      printf("    movl %s, %s \n", registradores32[0], registradores32[9]);
    }
    sscanf(s1, "%2s %d", s7, &ax);
    if (!strcmp("pi", s7))
      printf("    movl %s, -%d(%s)\n", registradores32[9], pos[6 + ax], registradores64[6]);
    else
      printf("    movl %s, -%d(%s)\n", registradores32[9], pos[ax - 1], registradores64[6]);
  }
  else // Expressões simples
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
      printf("    movl -%d(%s), %s\n", pos[6 + ax], registradores64[6], registradores32[2]);
      printf("    movl %s, -%d(%s)\n", registradores32[2], pos[a1 - 1], registradores64[6]);
    }
    else
      printf("    movl $%d, -%d(%s)\n", ax, pos[a1 - 1], registradores64[6]);
  }
}

void atribuicao()
{
  sscanf(str, "%s %s %s", s1, s2, s3);

  if (!strcmp("call", s3)) // Chamada de função
    funcCall();
  else
    funcExpressoes(); // Expressões aritméticas e atribuições
  printf("\n");
}

void accessArrayGet()
{
  sscanf(str, "%s %2s %d %s %2s %d %s %2s %d", s1, s2, &ax, s3, s4, &a1, s5, s6, &a2);

  printf("    movabs $%d, %s\n", a1, registradores64[8]);

  printf("    imulq $4, %s\n", registradores64[8]);

  if (!strcmp(s2, "va"))
    printf("    leaq -%d(%s), %s\n", pos[ax - 1], registradores64[6], registradores64[9]);
  else
    printf("    movq -%d(%s), %s\n", pos[6 + ax], registradores64[6], registradores64[9]);

  printf("    addq %s, %s\n", registradores64[9], registradores64[8]);

  printf("    movl (%s), %s\n", registradores64[8], registradores32[9]);

  printf("    movl %s, -%d(%s)\n", registradores32[9], pos[a2 - 1], registradores64[6]);

  printf("\n");
}

void accessArraySet()
{
  sscanf(str, "%s %2s %d %s %2s %d %s %2s %d", s1, s2, &ax, s3, s4, &a1, s5, s6, &a2);

  printf("    movabs $%d, %s\n", a1, registradores64[8]);

  printf("    imulq $4, %s\n", registradores64[8]);

  if (!strcmp(s2, "va"))
    printf("    leaq -%d(%s), %s\n", pos[ax - 1], registradores64[6], registradores64[9]);
  else
    printf("    movq -%d(%s), %s\n", pos[6 + ax], registradores64[6], registradores64[9]);

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
  sscanf(str, "%s %s %s %s", s1, s2, s3, s4);
  qi++;
  sscanf(s2, "%2s %d", s1, &ax);
  if (!strcmp("vi", s1))
    printf("    cmpl $0, -%d(%s)\n", pos[ax - 1], registradores64[6]);
  else if (!strcmp("pi", s1))
    printf("    cmpl $0, -%d(%s)\n", pos[6 + ax], registradores64[6]);
  printf("    je end_if%d\n", qi);
}

void condicionalEndif()
{

  if (!strcmp("endif", s1))
    printf("end_if%d:\n", qi);
}

void leave()
{
  printf("leave\nret\n\n");
}

void retorno()
{
  sscanf(str, "%s %s", s1, s2);
  sscanf(s2, "%2s %d", s3, &ax);

  if (!strcmp(s3, "vi"))
    printf("    movl -%d(%s), %s\n", pos[ax - 1], registradores64[6], registradores32[0]);
  else if (!strcmp(s3, "pi"))
    printf("    movl -%d(%s), %s\n", pos[6 + ax], registradores64[6], registradores32[0]);
  else if (!strcmp(s3, "va"))
    printf("    leaq -%d(%s), %s\n", pos[ax - 1], registradores64[6], registradores64[0]);
  else if (!strcmp(s3, "pa"))
    printf("    movq -%d(%s), %s\n", pos[6 + ax], registradores64[6], registradores64[0]);
  else
    printf("    movl $%d, %s\n", ax, registradores32[0]);

  printf("\n");
  leave();
}
