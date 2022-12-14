#include "header.h"
extern PILHA *PILHA_PARENTESES_ABERTO;
extern PILHA *PILHA_PARENTESES_FECHADO;
extern PILHA *PILHA_COLCHETES_ABERTO;
extern PILHA *PILHA_COLCHETES_FECHADO;
extern PILHA *PILHA_CHAVES_ABERTO;
extern PILHA *PILHA_CHAVES_FECHADO;

int main(int argc, char *argv[]) {

  unsigned int counterLine = 1;
  char str[200];
  int isLineIgnoring = 0;
  int isOnlyReserved = 0;
  int isIdeMode = 0;
  if (argc == 1) {
    fprintf(stderr, "\nSintáxe inválida.\n\nSintaxe:\n./parser <nome do arquivo> --only-reserved\n./parser <nome do arquivo>\n./parser --ide-mode\n\n");
    exit(1);
  }
  if (strcmp(argv[1], "--ide-mode") == 0) {
    int c;
    char test[57][40] = {{"auto"},
                         {"else"},
                         {"long"},
                         {"long long"},
                         {"signed char"},
                         {"unsigned char"},
                         {"short int"},
                         {"signed short"},
                         {"signed short int"},
                         {"unsigned short"},
                         {"unsigned short int"},
                         {"signed int"},
                         {"unsigned int"},
                         {"long int"},
                         {"signed long"},
                         {"signed long int"},
                         {"unsigned long"},
                         {"unsigned long int"},
                         {"long long"},
                         {"long long int"},
                         {"signed long long"},
                         {"signed long long int"},
                         {"unsigned long long"},
                         {"unsigned long long int"},
                         {"long double"},
                         {"switch"},
                         {"break"},
                         {"enum"},
                         {"register"},
                         {"typedef"},
                         {"case"},
                         {"extern"},
                         {"register"},
                         {"union"},
                         {"char"},
                         {"float"},
                         {"short"},
                         {"unsigned"},
                         {"const"},
                         {"for"},
                         {"signed"},
                         {"void"},
                         {"continue"},
                         {"goto"},
                         {"sizeof"},
                         {"volatil"},
                         {"default"},
                         {"if"},
                         {"static"},
                         {"while"},
                         {"do"},
                         {"int"},
                         {"struct"},
                         {"_Packed"},
                         {"double"},
                         {"include"},
                         {"define"}};

    int array[57] = {};
    char word[200];
    printf("Digite a palavra e aperte enter, para sair digite ^\n");

    while (1) {
      char *ig = fgets(word, 200, stdin);
      if ((strlen(word) > 0) && (word[strlen(word) - 1] == '\n'))
        word[strlen(word) - 1] = '\0';
      if (strcmp(word, "^") == 0) {
        break;
      }
      printf("\nSugestões:\n");

      for (int i = 0; i < 57; i++) {
        if (containSubs(word, test[i])) {
          array[i] = 1;
        }
      }
      for (int i = 0; i < 57; i++) {
        if (array[i]) {
          printf("%s\n", test[i]);
        }
      }

      memset(array, 0, sizeof(array));
      memset(word, 0, sizeof(word));
      printf("\n");
    }
  } else {
    FILE *arq = fopen(argv[1], "r");
    if (!arq) {
      fprintf(stderr, "Arquivo não encontrado.\n\nSintaxe:./parser "
                      "nomeDoArquivo.c [--only-reserved]\n./parser --ide-mode\n");
      exit(1);
    }
    fseek(arq, 0L, SEEK_END);
    long int totalBytes = ftell(arq);
    fseek(arq, 0L, SEEK_SET);

    PILHA_PARENTESES_ABERTO = criarPilha(100);
    PILHA_PARENTESES_FECHADO = criarPilha(100);
    PILHA_COLCHETES_ABERTO = criarPilha(100);
    PILHA_COLCHETES_FECHADO = criarPilha(100);
    PILHA_CHAVES_ABERTO = criarPilha(100);
    PILHA_CHAVES_FECHADO = criarPilha(100);
    if (argc >= 3) {
      if (strcmp(argv[2], "--only-reserved") == 0)
        isOnlyReserved = 1;
    }
    while (fgets(str, 200, arq) != NULL) {
      if (isOnlyReserved) {
        if (isReserverdWord(str)) {
          printf("Palavra chave encontrada");
          printAllReservedWord(str);
          printf(" linha %d\n", counterLine);
        }
        counterLine++;
        continue;
      }

      if (isLineIgnoring) {
        processLineComment(str, &isLineIgnoring);
        counterLine++;
        continue;
      }
      if (isLineInclude(str)) {
        processLineInclude(str, counterLine);
      } else if (isLineDefine(str)) {
        processLineDefine(str, counterLine);
      } else if (processLineComment(str, &isLineIgnoring)) {
        counterLine++;
        continue;
      } else if (isLineStruct(str)) {
        if (!isLastCharOpenBracket(str)) {
          showErrorSemicolon(counterLine, 2);
        }
      } else if (isLineTypedef(str)) {
        if (!isLastCharSemicolon(str)) {
          showErrorSemicolon(counterLine, 1);
        }
      } else if (isLineOptionalSemicolon(str)) {
        // montar depois
      } else if (isLineBlock(str)) {
        if (!isLastCharSemicolon(str) && !isLastCharOpenBracket(str)) {
          showErrorBlock(counterLine);
        }
      } else {
        if (!testSemicolon(str) && !isValidEndLine(str))
          if (totalBytes != ftell(arq))
            if (!isOnlyCloseBracket(str))
              showErrorSemicolon(counterLine, 1);
      }
      for (int i = 0; i < strlen(str); i++) {
        if (isCharacterToPush(str[i]))
          pushCharToQueue(str[i], counterLine);
      }
      counterLine++;
    }

    processQueueRestElements(PILHA_PARENTESES_ABERTO);
    processQueueRestElements(PILHA_PARENTESES_FECHADO);
    processQueueRestElements(PILHA_COLCHETES_ABERTO);
    processQueueRestElements(PILHA_COLCHETES_FECHADO);
    processQueueRestElements(PILHA_CHAVES_ABERTO);
    processQueueRestElements(PILHA_CHAVES_FECHADO);
    freePilha(PILHA_PARENTESES_ABERTO);
    freePilha(PILHA_PARENTESES_FECHADO);
    freePilha(PILHA_COLCHETES_ABERTO);
    freePilha(PILHA_COLCHETES_FECHADO);
    freePilha(PILHA_CHAVES_ABERTO);
    freePilha(PILHA_CHAVES_FECHADO);
    fclose(arq);
    fflush(stdin);
    fflush(stdout);
    fflush(stderr);
  }
}
