#include "header.h"

char ALL_RESERVED_WORDS[TOTAL_RESERVED_WORDS][10] = {
    {"auto"}, {"else"}, {"long"}, {"switch"}, {"break"}, {"enum"}, {"register"}, {"typedef"}, {"case"}, {"extern"}, {"register"}, {"union"}, {"char"}, {"float"}, {"short"}, {"unsigned"}, {"const"}, {"for"}, {"signed"}, {"void"}, {"continue"}, {"goto"}, {"sizeof"}, {"volatil"}, {"default"}, {"if"}, {"static"}, {"while"}, {"do"}, {"int"}, {"struct"}, {"_Packed"}, {"double"}, {"include"}, {"define"}};

PILHA *PILHA_PARENTESES_ABERTO;
PILHA *PILHA_PARENTESES_FECHADO;
PILHA *PILHA_COLCHETES_ABERTO;
PILHA *PILHA_COLCHETES_FECHADO;
PILHA *PILHA_CHAVES_ABERTO;
PILHA *PILHA_CHAVES_FECHADO;

PILHA *criarPilha(int n)
{
  PILHA *tmp = malloc(sizeof(PILHA));
  if (tmp)
  {
    tmp->elementos = malloc(sizeof(DATA *) * n);
    tmp->nextIndex = 0;
    return tmp;
  }
  return NULL;
}
DATA *criarData(unsigned int linha, unsigned char valor)
{
  DATA *tmp = malloc(sizeof(DATA));
  if (tmp)
  {
    tmp->linha = linha;
    tmp->valor = valor;
    return tmp;
  }
  return NULL;
}
DATA *popPilha(PILHA *pilha) { return pilha->elementos[--pilha->nextIndex]; }

int isPilhaEmpty(PILHA *pilha) { return pilha->nextIndex == 0; }

int isLineWithBrackets(char *line)
{
  return (strchr(line, '{') || strchr(line, '}')) ? 1 : 0;
}

int isLineDefine(char *line) { return strstr(line, "#define") ? 1 : 0; }
int isLineInclude(char *line) { return strstr(line, "#include") ? 1 : 0; }
int isCharacterToPush(unsigned char c)
{
  switch (c)
  {
  case '{':
  case '}':
  case '(':
  case ')':
  case '[':
  case ']':
    return 1;
  }
  return 0;
}

int isLastCharOpenBracket(char *linha)
{
  return (linha[strlen(linha)] == '{' || linha[strlen(linha) - 1] == '{' ||
          linha[strlen(linha) - 2] == '{')
             ? 1
             : 0;
}

int isLastCharCloseBracket(char *linha)
{
  return (linha[strlen(linha)] == '}' || linha[strlen(linha) - 1] == '}' ||
          linha[strlen(linha) - 2] == '}')
             ? 1
             : 0;
}

int isLastCharColon(char *line)
{
  return (line[strlen(line)] == ':' || line[strlen(line) - 1] == ':' ||
          line[strlen(line) - 2] == ':')
             ? 1
             : 0;
}

int isLineStruct(char *line) { return strstr(line, "struct") ? 1 : 0; }

int isLineTypedef(char *line) { return strstr(line, "typedef") ? 1 : 0; }

int isControlCharacter(char *line)
{
  for (int i = strlen(line); i > 0; i--)
  {
    if (line[i] < 32)
      return 1;
  }
  return 0;
}

int isLineBlock(char *line)
{
  char str1[400];
  char str2[400];
  char c1, c2;

  sscanf(line, "%[^(]%c%[^{]%c", str1, &c1, str2, &c2);
  if (str1[0] && c1 && str2[0] && c2)
  {
    // printf("\n\n%s %c %s\n\n", str1, c1, str2);
    return 1;
  }
  return 0;
}

int isValidEndLine(char *line)
{
  return /*isLastCharSemicolon(line)*/ testSemicolon(line) ||
         isLastCharOpenBracket(line) || isLastCharColon(line) ||
         !isControlCharacter(line);
  return 0;
}

// com essa função foi para os ;. Mas somente na função acima e não levando em conta a linha 25
int testSemicolon(char *line)
{
  int i = strlen(line);

  for (; i >= strlen(line) + 1 - strlen(line); i--)
  {
    if (line[i] == ';')
      return 1;
  }
  return 0;
}

int isLastCharSemicolon(char *line)
{
  char testFormat[400] = {0};
  char c;

  sscanf(line, "%[^;]%c", testFormat, &c);
  if (c == ';' || line[strlen(line) - 1] == ';' ||
      line[strlen(line) - 2] == ';' || line[strlen(line)] == ';')
  {
    // aqui dá para ver que temos um erro >> printf("%s%c\n", testFormat,c);
    return 1;
  }
  return 0;
}

int isLineOptionalSemicolon(char *line)
{
  // Não há a necessidade de colocar ';'
  char reservedWords[5][7] = {
      {"if"}, {"else"}, {"while"}, {"for"}, {"else if"}};
  for (int i = 0; i < 5; i++)
  {
    if (strstr(line, reservedWords[i]) != NULL)
    {
      return 1;
    }
  }
  return 0;
}

int isOnlyCloseBracket(char *line)
{
  for (int i = 0; i < strlen(line); i++)
  {
    if (line[i] > 32 && line[i] != '}')
    {
      return 0;
    }
  }
  return 1;
}

int processLineComment(char *linha, int *isLineIgnored)
{
  for (int i = 0; i < strlen(linha); i++)
  {
    if (i + 1 < strlen(linha))
    {

      if (linha[i] == '/' && linha[i + 1] == '/')
      {
        *isLineIgnored = 0;
        return 1;
      }
      else if (linha[i] == '/' && linha[i + 1] == '*')
      {
        *isLineIgnored = 1;
        return 1;
      }
      else if (linha[i] == '*' && linha[i + 1] == '/')
      {
        *isLineIgnored = 0;
        return 0;
      }
    }
  }
  return 0;
}
void printAllReservedWord(char *linha)
{

  for (int i = 0; i < TOTAL_RESERVED_WORDS; i++)
  {
    if (strstr(linha, ALL_RESERVED_WORDS[i]))
      printf(" '%s' ", ALL_RESERVED_WORDS[i]);
  }
}
int isReserverdWord(char *linha)
{

  for (int i = 0; i < TOTAL_RESERVED_WORDS; i++)
  {
    if (strstr(linha, ALL_RESERVED_WORDS[i]))
      return i;
  }
  return 0;
}

void pushPilha(PILHA *pilha, DATA *elemento)
{
  pilha->elementos[pilha->nextIndex++] = elemento;
}
void popPilhaWithFree(PILHA *pilha)
{
  free(pilha->elementos[--pilha->nextIndex]);
}
void processLineDefine(char *line, int linha)
{
  //#define  -- erro, nenhum nome macro declarado
  //#define      macro -- valido, se macro não for utilizado
  //#def -- não passa no isLineDefine
  //#define macro; -- válido se o usuário quiser, mas somente se não usar o
  // #define macro val; -- válido se o usuário quiser

  unsigned int lineLen = strlen(line);
  if (lineLen == 8)
  {
    showErrorDefine(linha, 1);
  }
}
void processLineInclude(char *line, int linha)
{
  unsigned int countQuotes = 0;
  unsigned int countLess = 0;
  unsigned int countGreat = 0;

  for (int i = 0; i < strlen(line); i++)
  {
    if (line[i] == '"')
      countQuotes++;
    else if (line[i] == '<')
      countLess++;
    else if (line[i] == '>')
      countGreat++;
  }

  if (countQuotes > 2)
  {
    showErrorInclude(linha, 2);
  }
  else if (countQuotes == 1)
  {
    showErrorInclude(linha, 2);
  }
  else if (countGreat + countLess > 2 || (countLess ^ countGreat))
  {
    showErrorInclude(linha, 1);
  }
  else if (!countQuotes && !countLess && !countGreat)
  {
    showErrorInclude(linha, 0);
  }
}
void processQueueRestElements(PILHA *pilha)
{
  if (!isPilhaEmpty(pilha))
  {
    for (int i = 0; i < pilha->nextIndex; i++)
    {
      DATA *element = pilha->elementos[i];
      switch (element->valor)
      {
      case '}':
        showErrorCrulybrk(element->linha, 2);
        break;
      case '{':
        showErrorCrulybrk(element->linha, 1);
        break;
      case '(':
        showErrorParenthesis(element->linha, 1);
        break;
      case ')':
        showErrorParenthesis(element->linha, 2);
        break;
      case '[':
        showErrorSqtbrk(element->linha, 1);
        break;
      case ']':
        showErrorSqtbrk(element->linha, 2);
        break;
      }
    }
  }
}

void freePilha(PILHA *pilha)
{
  if (!isPilhaEmpty(pilha))
  {
    int oldIndex = pilha->nextIndex;
    for (int i = 0; i < oldIndex; i++)
    {
      popPilhaWithFree(pilha);
    }
  }
  free(pilha->elementos);
  free(pilha);
}

void pushCharToQueue(unsigned char c, unsigned int linha)
{
  DATA *el = criarData(linha, c);
  if (c == '{')
  {
    pushPilha(PILHA_CHAVES_ABERTO, el);
  }
  else if (c == '}')
  {
    if (isPilhaEmpty(PILHA_CHAVES_ABERTO))
    {
      pushPilha(PILHA_CHAVES_FECHADO, el);
    }
    else
    {
      popPilhaWithFree(PILHA_CHAVES_ABERTO);
      free(el);
    }
  }
  else if (c == '(')
  {
    pushPilha(PILHA_PARENTESES_ABERTO, el);
  }
  else if (c == ')')
  {
    if (isPilhaEmpty(PILHA_PARENTESES_ABERTO))
    {
      pushPilha(PILHA_PARENTESES_FECHADO, el);
    }
    else
    {
      popPilhaWithFree(PILHA_PARENTESES_ABERTO);
      free(el);
    }
  }
  else if (c == '[')
  {
    pushPilha(PILHA_COLCHETES_ABERTO, el);
  }
  else if (c == ']')
  {
    if (isPilhaEmpty(PILHA_COLCHETES_ABERTO))
    {
      pushPilha(PILHA_COLCHETES_FECHADO, el);
    }
    else
    {
      popPilhaWithFree(PILHA_COLCHETES_ABERTO);
      free(el);
    }
  }
}
void showErrorInclude(int line, int tipo)
{
  if (tipo == 1)
  { // <>
    fprintf(stderr,
            "Erro na linha %d: Include não possui less (<) ou greater (>)\n",
            line);
  }
  else if (tipo == 2)
  { // ""
    fprintf(stderr,
            "Erro na linha %d: Include não possui double quotes (\") \n", line);
  }
  else
  { // Invalid Include
    fprintf(stderr, "Erro na linha %d: Include inválido\n", line);
  }
}
void showErrorDefine(int line, int tipo)
{
  if (tipo == 1)
  {
    fprintf(stderr,
            "Erro na linha %d: Nenhum nome macro oferecido para "
            "diretiva #define\n",
            line);
  }
}

void showErrorSemicolon(int line, int tipo)
{
  if (tipo == 1)
  {
    fprintf(stderr, "Erro na linha %d: É esperado um ';'.\n", line);
  }
  else if (tipo == 2)
  {
    fprintf(stderr, "Erro na linha %d: Não é esperado um ';'.\n", line);
  }
}
void showErrorParenthesis(int line, int tipo)
{
  if (tipo == 1)
  { // Parenthesis error )
    fprintf(stderr, "Erro na linha %d: É esperado um ')'.\n", line);
  }
  else if (tipo == 2)
  { // parenthesis error (
    fprintf(stderr, "Erro na linha %d: É esperado um '('.\n", line);
  }
}

void showErrorSqtbrk(int line, int tipo)
{
  if (tipo == 1)
  { // Square brackets error ]
    fprintf(stderr, "Erro na linha %d: É esperado um ']'.\n", line);
  }
  else if (tipo == 2)
  { // Square Brackerts error [
    fprintf(stderr, "Erro na linha %d: É esperado um '['.\n", line);
  }
}

void showErrorCrulybrk(int line, int tipo)
{
  if (tipo == 1)
  { // Curly brackets error }
    fprintf(stderr, "Erro na linha %d: É esperado um '}'.\n", line);
  }
  if (tipo == 2)
  { // Curly brackets error {
    fprintf(stderr, "Erro na linha %d: É esperado um '{'.\n", line);
  }
}
void showErrorBlock(int line)
{
  fprintf(stderr, "Erro na linha %d: É esperado um ';' ou um '{'\n", line);
}

int containSubs(char *substr, char *str)
{

  int startsWith = 0;
  for (int i = 0; substr[i] != '\0'; i++)
  {
    if (str[i] != substr[i])
    {
      startsWith = 0;
      break;
    }
    startsWith = 1;
  }

  return startsWith;
}
