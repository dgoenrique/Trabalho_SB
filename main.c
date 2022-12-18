#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
    char str[100], st1[20], st2[20], st3[20], st4[20], st5[20], st6[20], st7[20];
    int ax, a1, a2, a3;
    char regisverdes[5][6] = {{"\%ebx"}, {"\%r12d"}, {"\%r13d"}, {"\%r14d"}, {"\%r15d"}};
    char regisamare[1][5] = {{"\%eax"}};
    char regispilha[3][5] = {{"\%edi"}, {"\%esi"}, {"\%edx"}};
    char regispilha2[3][5] = {{"\%rdi"}, {"\%rsi"}, {"\%rdx"}};

    while (1)
    {
        memset(str, 0, sizeof(str));

        memset(st1, 0, sizeof(st1));
        memset(st2, 0, sizeof(st2));
        memset(st3, 0, sizeof(st3));
        memset(st4, 0, sizeof(st4));
        memset(st5, 0, sizeof(st5));
        memset(st6, 0, sizeof(st6));
        scanf("%[^\n]%*c", str);

        // printf("%s\n", str);
        //  sscanf(str, "%s %s %s %s %s %s", st1, st2, st3, st4, st5, st6);
        sscanf(str, "%s", st1);
        if (!strcmp("function", st1)) // definição da função
        {
            sscanf(str, "%s %s %s %s %s", st1, st2, st3, st4, st5);

            // printf("Funcao\n");
            printf("%s:\n", st2);
            if (!strcmp(st3, "pa1"))
            {
                printf("%s = %rdi\n", "ponteiro");
            }
            else if (!strcmp(st3, "pi1"))
            {
                printf("%s = %rdi\n", "parametro");
            }

            if (!strcmp(st4, "pa2"))
            {
                printf("%s = %rsi\n", "ponteiro");
            }
            else if (!strcmp(st4, "pi2"))
            {
                printf("%s = %rsi\n", "parametro");
            }

            if (!strcmp(st5, "pa3"))
            {
                printf("%s = %rdx\n", "ponteiro");
            }
            else if (!strcmp(st5, "pi3"))
            {
                printf("%s = %rdx\n", "parametro");
            }
        }
        else if (!strcmp("def", st1)) /// variáveis locais
        {
            while (1)
            {
                scanf("%[^\n]%*c", str);
                sscanf(str, "%s", st1);
                if (!strcmp("var", st1))
                {
                    sscanf(str, "%s %2s %d", st1, st2, &ax);
                    printf(".align 4\n");
                    printf("%s%d: .int 0\n", st2, ax);
                    // printf("movl $%d, %s\n", ax, regisverdes[ax - 1]);
                    //  printf("Variável %d\n", ax);
                }
                else if (!strcmp("vet", st1))
                {
                    sscanf(str, "%s %2s %d %*c %s %2s %d", st1, st2, &ax, st3, st4, &a1);
                    printf("Vetor %d de tamanho %d\n", ax, a1);
                }
                else if (!strcmp("enddef", st1))
                    break;
            }
        }
        else if (!strcmp("return", st1))
        {
            sscanf(str, "%s %2s %d", st1, st2, &ax);
            // printf("return %d\n", ax);
            printf("movl $%d, %s\n", ax, regisamare[0]);
        }
        else if (!strcmp("end", st1))
        {
            // printf("fim da funcao\n");
            printf("leave\nret\n");
            return 0;
        }
        else if ('v' == st1[0] && 'i' == st1[1])
        {
            sscanf(str, "%s %s %s", st1, st2, st3);
            if (!strcmp("call", st3))
            {
                sscanf(str, "%s %s %s %s %s %s %s", st1, st2, st3, st4, st5, st6, st7);
               // printf("%s %s %s %s %s %s %s\n", st1, st2, st3, st4, st5, st6, st7);
                if (strlen(st5) > 2)
                {
                    sscanf(st5, "%2s %d", st2, &ax);
                    if (!strcmp(st2, "ci"))
                        printf("movl $%d, %s\n", ax, regispilha[0]); // verificar se o parametro é do tipo inteiro ou quad
                    else if (!strcmp(st2, "va"))
                        printf("movl $%s, %s\n", st5, regispilha2[0]);
                    else
                        printf("movl $%s, %s\n", st5, regispilha[0]);
                }

                if (strlen(st6) > 2)
                {
                    sscanf(st6, "%2s %d", st2, &ax);
                    if (!strcmp(st2, "ci"))
                        printf("movl $%d, %s\n", ax, regispilha[1]); // verificar se o parametro é do tipo inteiro ou quad
                    else if (!strcmp(st2, "va"))
                        printf("movl $%s, %s\n", st6, regispilha2[1]);
                    else
                        printf("movl $%s, %s\n", st6, regispilha[1]);
                }

                if (strlen(st7) > 2)
                {
                    sscanf(st7, "%2s %d", st2, &ax);
                    if (!strcmp(st2, "ci"))
                        printf("movl $%d, %s\n", ax, regispilha[2]); // verificar se o parametro é do tipo inteiro ou quad
                    else if (!strcmp(st2, "va"))
                        printf("movl $%s, %s\n", st7, regispilha2[2]);
                    else
                        printf("movl $%s, %s\n", st7, regispilha[2]);
                }

                printf("call %s\n", st4);
                printf("movl %s, %s\n\n", regisamare[0], st1);
            }

            else
            {
                sscanf(str, "%s %s %2s %d", st1, st2, st3, &ax);
                printf("movl $%d, %s\n", ax, st1);
            }
        }

        // printf("%s %s %s %s %s %s", st1, st2, st3, st4, st5, st6);
    }
}