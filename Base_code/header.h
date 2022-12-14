#ifndef __HEADER__IDE__
#define __HEADER__IDE__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TOTAL_RESERVED_WORDS 35
typedef struct data {
  unsigned int linha;
  unsigned char valor;
} DATA;

typedef struct pilha {
  unsigned int nextIndex;
  DATA **elementos;
} PILHA;

PILHA *criarPilha(int n);
DATA *popPilha(PILHA *pilha);

int containSubs(char *substr, char *str);
void printAllReservedWord(char *line);
int isCharacterToPush(unsigned char c);
int isLineDefine(char *line);
int isLineInclude(char *line);
int isLineWithBrackets(char *line);
int isLineDefine(char *line);
int isLineInclude(char *line);
int isValidInclude(char *line);
int isOnlyCloseBracket(char *line);
int isLineStruct(char *line);
int isLineTypedef(char *line);
int isLastCharSemicolon(char *line);
int processLineComment(char *line, int *isLineIgnoring);
int isCharacterToPush(unsigned char c);
int isReserverdWord(char *linha);
int isPilhaEmpty(PILHA *pilha);
int isLastCharOpenBracket(char *linhha);
int isLineBlock(char *line);
int isLineOptionalSemicolon(char *line);
int isLastLineFileSemicolon(char *line);

/// As alterações que fiz mas ainda tem problemas
// pelo que parece com a nossa isLasCharSemicolon
int isControlCharacter(char *line);
int isLastCharCloseBracket(char *linha);
int isLastCharColon(char *line);
int isValidEndLine(char *line);

int testSemicolon(char *line);
////
void freePilha(PILHA *pilha);
void popPilhaWithFree(PILHA *pilha);
void pushPilha(PILHA *pilha, DATA *elemento);
void processLineInclude(char *line, int linha);
void processLineDefine(char *line, int linha);
void processQueueRestElements(PILHA *pilha);
void showErrorInclude(int line, int tipo);
void showErrorDefine(int line, int tipo);
void pushCharToQueue(unsigned char c, unsigned int linha);
void showErrorParenthesis(int line, int tipo);
void showErrorSqtbrk(int line, int tipo);
void showErrorCrulybrk(int line, int tipo);
void showErrorSemicolon(int line, int tipo);
void showErrorBlock(int line);

#endif
