#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
    char str[100], s1[20], s2[20], s3[20], s4[20], s5[20], s6[20], s7[20];
    int ax, a1, a2, a3;
    char regisverdes[5][6] = {{"\%ebx"}, {"\%r12d"}, {"\%r13d"}, {"\%r14d"}, {"\%r15d"}};
    char regisamare[9][5] = {
        {"\%eax"},
        {"\%ecx"},
        {"\%r7d"},
        {"\%r8d"},
        {"\%r9d"},
        {"\%r10d"},
        {"\%r11d"},
        {"\%rbp"},
        {"\%rsp"}};
    char regispilha[3][5] = {{"\%edi"}, {"\%esi"}, {"\%edx"}};
    char regispilha2[3][5] = {{"\%rdi"}, {"\%rsi"}, {"\%rdx"}};
    // FOI UTILIZADO VETORES DE CHAR PARA ARMAZENAR OS REGISTRADORES PARA QUE FICASSE MAIS FACIL A SUA MANIPULAÇÃO

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
        }


        else if (!strcmp("def", s1)) /// AQUI SÃO DEFINIDAS AS VARIÁVEIS LOCAIS
        {
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

                else if (!strcmp("vet", s1))
                {
                    sscanf(str, "%s %2s %d %*c %s %2s %d", s1, s2, &ax, s3, s4, &a1);
                    printf("Vetor %d de tamanho %d\n", ax, a1);
                }

                else if (!strcmp("enddef", s1))
                    break;
            }
            printf("\n");
        }
        else if (!strcmp("return", s1)) // AQUI É DEFINIDA O RETORNO DA FUNÇÃO
        {
            sscanf(str, "%s %s", s1, s2);
            sscanf(s2, "%2s %d", s3, &ax);

            if (!strcmp(s3, "vi") || !strcmp(s3, "pi"))
                printf("movl %s, %s\n", s2, regisamare[0]);

            else
                printf("movl $%d, %s\n", ax, regisamare[0]);
            printf("\n");
        }
        else if (!strcmp("end", s1)) // AQUI SE LOCALIZA O FIM DA FUNÇÃO
        {

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
                    if (!strcmp(s2, "ci"))                           // INDICA SE É CONSTANTE
                        printf("movl $%d, %s\n", ax, regispilha[0]); // verificar se o parametro é do tipo inteiro ou quad
                    else if (!strcmp(s2, "va"))                      // INDICA SE É VETOR
                        printf("movl $%s, %s\n", s5, regispilha2[0]);
                    else
                        printf("movl %s, %s\n", s5, regispilha[0]); // PARAMETRO OU VARIÁVEL
                }


                if (strlen(s6) > 2)
                {
                    sscanf(s6, "%2s %d", s2, &ax);
                    if (!strcmp(s2, "ci"))
                        printf("movl $%d, %s\n", ax, regispilha[1]); // verificar se o parametro é do tipo inteiro ou quad
                    else if (!strcmp(s2, "va"))
                        printf("movl $%s, %s\n", s6, regispilha2[1]);
                    else
                        printf("movl %s, %s\n", s6, regispilha[1]);
                }
                

                if (strlen(s7) > 2)
                {
                    sscanf(s7, "%2s %d", s2, &ax);
                    if (!strcmp(s2, "ci"))
                        printf("movl $%d, %s\n", ax, regispilha[2]); // verificar se o parametro é do tipo inteiro ou quad
                    else if (!strcmp(s2, "va"))
                        printf("movl $%s, %s\n", s7, regispilha2[2]);
                    else
                        printf("movl %s, %s\n", s7, regispilha[2]);
                }

                printf("call %s\n", s4);
                printf("movl %s, %s\n", regisamare[0], s1); // FINALIZA A FUNÇÃO MOVENDO %EAX PARA A VARIAVEL DEFINIDA
            }
            else // CASO NÃO SEJA CHAMADA DE FUNÇÃO, AQUI É DESTINADO À EXPRESSÕES
            {
                sscanf(str, "%s %s %s %s %s", s1, s2, s3, s4, s5);
                // S4 É A OPERAÇÃO
                if (strlen(s5) > 2) // EXPRESSÃO COMPLEXA
                {
                    sscanf(s3, "%2s %d", s7, &ax);
                    if (!strcmp("vi", s7) || !strcmp("pi", s7))
                        printf("movl %s, %s\n", s3, regisamare[1]);
                    else
                        printf("movl $%d, %s\n", ax, regisamare[1]);


                    sscanf(s5, "%2s %d", s7, &ax);
                    if (!strcmp("vi", s7) || !strcmp("pi", s7))
                        printf("movl %s, %s\n", s5, regisamare[2]);
                    else
                        printf("movl $%d, %s\n", ax, regisamare[2]);


                    if (s4[0] == '*')
                        printf("imull %s, %s\n", regisamare[1], regisamare[2]);
                    else if (s4[0] == '+')
                        printf("addl %s, %s\n", regisamare[1], regisamare[2]);
                    else if (s4[0] == '-')
                        printf("subl %s, %s\n", regisamare[1], regisamare[2]);
                    printf("movl %s, %s\n", regisamare[2], s1);
                }
                else // EXPRESSÃO SIMPLES
                {
                    sscanf(s3, "%2s %d", s7, &ax);
                    if (!strcmp("vi", s7) || !strcmp("pi", s7))
                    {
                        printf("movl %s, %s\n", s3, regisamare[1]);
                        printf("movl %s, %s\n", regisamare[1], s1);
                    }
                    else
                        printf("movl $%d, %s\n", ax, s1);
                }
            }
            printf("\n");
        }
        // ACESSAR ARRAYS E CRIAR CONDICIONAIS
    }
}
