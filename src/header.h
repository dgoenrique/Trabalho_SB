#ifndef __HEADER__
#define __HEADER__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void defFunct();
void defLocalVar();
void atribuicao();
void funcCall();
void expressoes();
void accessArrayGet();
void accessArraySet();
void condicionalIf();
void condicionalEndif();
void retorno();
void leave();

// mudar o nome das variáveis para ficar mais facil de escrever e entender
char str[100], s1[20], s2[20], s3[20], s4[20], s5[20], s6[20], s7[20];
int ax, a1, a2, a3;
char registradores32[16][6] = {
    {"\%eax"},  {"\%ebx"},  {"\%ecx"},  {"\%edx"},  {"\%esi"},  {"\%edi"},
    {"\%ebp"},  {"\%esp"},  {"\%r8d"},  {"\%r9d"},  {"\%r10d"}, {"\%r11d"},
    {"\%r12d"}, {"\%r13d"}, {"\%r14d"}, {"\%r15d"},
};

char registradores64[16][6] = {
    {"\%rax"}, {"\%rbx"}, {"\%rcx"}, {"\%rdx"}, {"\%rsi"}, {"\%rdi"},
    {"\%rbp"}, {"\%rsp"}, {"\%r8"},  {"\%r9"},  {"\%r10"}, {"\%r11"},
    {"\%r12"}, {"\%r13"}, {"\%r14"}, {"\%r15"},
};

#endif