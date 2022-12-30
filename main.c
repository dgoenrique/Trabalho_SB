#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main() // Código em C
{
    char str[100], s1[20], s2[20], s3[20], s4[20], s5[20], s6[20], s7[20];
    int ax, a1, a2, a3;
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

     // FOI UTILIZADO VETORES DE CHAR PARA ARMAZENAR OS REGISTRADORES PARA QUE FICASSE MAIS FACIL A SUA MANIPULAÇÃO
    printf(".section .rodata\n");
    printf(".data\n");
    printf(".text\n\n");
    while (1)
    {
        memset(str, 0, sizeof(str));
        memset(s1, 0, sizeof(s1));
        memset(s2, 0, sizeof(s2)); // O VETOR INTEIRO É ZERADO PARA EVITAR O RECEBIMENTO DE INFORMAÇÕES ERRADAS
        memset(s3, 0, sizeof(s3));
        memset(s4, 0, sizeof(s4));
        memset(s5, 0, sizeof(s5));
        memset(s6, 0, sizeof(s6));
        scanf("%[^\n]%*c", str);

        // printf("%s\n", sr);
        //  sscanf(str, "%s %s %s %s %s %s", s1, s2, s3, s4, s5, s6);
        sscanf(str, "%s", s1);
        if (!strcmp("function", s1)) // definição da função
        {
            sscanf(str, "%s %s %s %s %s", s1, s2, s3, s4, s5);

            // printf("Funcao\n");
            printf("%s:\n", s2);
            printf("pushq %s\n", registradores64[6]);
            printf("movq %s, %s\n", registradores64[7], registradores64[6]);
            if (!strcmp(s3, "pa1"))
            {
                printf("%s = %rdi\n", "ponteiro");
            }
            else if (!strcmp(s3, "pi1"))
            {
                printf("%s = %rdi\n", "parametro");
            }

            if (!strcmp(s4, "pa2"))
            {
                printf("%s = %rsi\n", "ponteiro");
            }
            else if (!strcmp(s4, "pi2"))
            {
                printf("%s = %rsi\n", "parametro");
            }

            if (!strcmp(s5, "pa3"))
            {
                printf("%s = %rdx\n", "ponteiro");
            }
            else if (!strcmp(s5, "pi3"))
            {
                printf("%s = %rdx\n", "parametro");
            }
            printf("\n");
            printf("Definição da função\n");
        }

        else if (!strcmp("def", s1)) /// AQUI SÃO DEFINIDAS AS VARIÁVEIS LOCAIS
        {
            printf("Definição das variáveis\n");
            while (1)
            {
                scanf("%[^\n]%*c", str);
                sscanf(str, "%s", s1);

                if (!strcmp("var", s1))
                {
                    sscanf(str, "%s %2s %d", s1, s2, &ax);
                    printf(".align 4\n");
                    printf("%s%d: .int 0\n", s2, ax);
                }

                else if (!strcmp("vet", s1)) // definição de um vetor
                {
                    sscanf(str, "%s %s %s %2s %d", s1, s2, s3, s4, &a1);
                    printf(".align 4\n");
                    printf("%s: .int ", s2);
                    for (ax = 0; ax < a1; ax++)
                    {
                        printf("0");
                        if (ax + 1 != a1)
                            printf(",");
                    }
                }

                else if (!strcmp("enddef", s1))
                    break;
            }
            printf("\n");
        }
        else if (!strcmp("return", s1)) // AQUI É DEFINIDA O RETORNO DA FUNÇÃO
        {
            printf("Definição do retorno\n");
            sscanf(str, "%s %s", s1, s2);
            sscanf(s2, "%2s %d", s3, &ax);

            if (!strcmp(s3, "vi") || !strcmp(s3, "pi"))
                printf("movl %s, %s\n", s2, registradores32[0]);

            else
                printf("movl $%d, %s\n", ax, registradores32[0]);
            printf("\n");
        }
        else if (!strcmp("end", s1)) // AQUI SE LOCALIZA O FIM DA FUNÇÃO
        {
            printf("Definição do fim\n");
            printf("leave\nret\n\n");
            return 0;
        }
        else if ('v' == s1[0] && 'i' == s1[1]) // SEÇÃO DE ATRIBUIÇÃO DE VARIÁVEIS
        {
            sscanf(str, "%s %s %s", s1, s2, s3);
            if (!strcmp("call", s3)) // VERIFICA SE O QUE ESTÁ SENDO CHAMADO É UMA FUNÇÃO
            {
                sscanf(str, "%s %s %s %s %s %s %s", s1, s2, s3, s4, s5, s6, s7);

                if (strlen(s5) > 2) // VERIFICA SE HÁ PARAMETROS, CASO CONTRÁRIO ELE NÃO IRÁ PASSAR NADA. A STRING POSSUI 0 DE TAMANHO
                {
                    sscanf(s5, "%2s %d", s2, &ax);
                    if (!strcmp(s2, "ci"))                                // INDICA SE É CONSTANTE
                        printf("movl $%d, %s\n", ax, registradores32[5]); // verificar se o parametro é do tipo inteiro ou quad
                    else if (!strcmp(s2, "va"))                           // INDICA SE É VETOR
                        printf("movl $%s, %s\n", s5, registradores64[5]);
                    else
                        printf("movl %s, %s\n", s5, registradores32[5]); // PARAMETRO OU VARIÁVEL
                }

                if (strlen(s6) > 2)
                {
                    sscanf(s6, "%2s %d", s2, &ax);
                    if (!strcmp(s2, "ci"))
                        printf("movl $%d, %s\n", ax, registradores32[4]); // verificar se o parametro é do tipo inteiro ou quad
                    else if (!strcmp(s2, "va"))
                        printf("movl $%s, %s\n", s6, registradores64[4]);
                    else
                        printf("movl %s, %s\n", s6, registradores32[4]);
                }

                if (strlen(s7) > 2)
                {
                    sscanf(s7, "%2s %d", s2, &ax);
                    if (!strcmp(s2, "ci"))
                        printf("movl $%d, %s\n", ax, registradores32[3]); // verificar se o parametro é do tipo inteiro ou quad
                    else if (!strcmp(s2, "va"))
                        printf("movl $%s, %s\n", s7, registradores64[3]);
                    else
                        printf("movl %s, %s\n", s7, registradores32[3]);
                }

                printf("call %s\n", s4);
                printf("movl %s, %s\n", registradores32[0], s1); // FINALIZA A FUNÇÃO MOVENDO %EAX PARA A VARIAVEL DEFINIDA
            }
            else // CASO NÃO SEJA CHAMADA DE FUNÇÃO, AQUI É DESTINADO À EXPRESSÕES
            {
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
                }
                else // EXPRESSÃO SIMPLES
                {
                    sscanf(s3, "%2s %d", s7, &ax);
                    if (!strcmp("vi", s7) || !strcmp("pi", s7))
                    {
                        printf("movl %s, %s\n", s3, registradores32[2]);
                        printf("movl %s, %s\n", registradores32[2], s1);
                    }
                    else
                        printf("movl $%d, %s\n", ax, s1);
                }
            }
            printf("\n");
        }
        else if (!strcmp("if", s1)) // Definição do IF
        {
            printf("Definição de if\n");
            sscanf(str, "%s %s %s %s", s1, s2, s3, s4);

            printf("cmpl $0, %s\n", s2);
            printf("jne end_if\n");
        }
        else if (!strcmp("endif", s1))
            printf("end_if:\n");
        // ACESSAR ARRAYS E CRIAR CONDICIONAIS

        else if (!strcmp("set", s1))
        {
            // regisamare 2,3,4 -> usar os registradores r7, r8, r9 para o acesso dos vetores

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

        else if (!strcmp("get", s1))
        {
            // regisamare 2,3,4  -> usar os registradores r7, r8, r9 para o acesso dos vetores
            printf("Definição do get das variáveis de um vetor\n"); // aqui
            sscanf(str, "%s %s %s %s %s %s", s1, s2, s3, s4, s5, s6);
            printf("movq $%s, %s\n", s2, registradores64[8]);

            sscanf(s4, "%2s %d\n", s7, &ax);
            printf("movq $%d, %s\n", ax, registradores64[9]);
            printf("imulq $4, %s\n", registradores64[9]);
            printf("addq %s, %s\n", registradores64[8], registradores64[9]); // até aqui é o mesmo do bloco de cima

            printf("movl (%s), %s\n", registradores64[9], registradores32[10]);
            printf("movl %s, %s\n", registradores32[10], s6); // recuperação de uma variável
            // printf("%s\n", s6);
        }
        printf("\n");
    }
    // Delarar variáveis na pilha
}
