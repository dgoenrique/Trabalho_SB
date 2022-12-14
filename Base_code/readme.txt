DESENVOLVEDORES:
- Iaan Mesquita de Souza (201904219);
- Diego Enrique da Silva Lima (202003556).

COMPILAÇÃO:
gcc header.c main.c -o parser

EXECUÇÃO:
./parser <nome do arquivo> --only-reserved (Apresenta todas as palavras reservadas no arquivo);
./parser <nome do arquivo> (Faz uma verificação sintática no arquivo);
./parser --ide-mode (Executa um "modo IDE" para sugestão de palavras reservadas).

FUNCIONALIDADES:
- Verificação de '{', '}', '[', ']', '(', ')', ';', '"', '<', '>';
- Os ';' são verificados apenas nos finais de sentenças;
- Verificação de abertura e fechamento de blocos;
- Verificação de comentários de linha e de bloco ("//" e "/* */"), sendo as linhas ignoradas;
- Lidamos com "while", "do while", "if", "else", "switch case";
- Verificação de "#define";
- Verificação de "#include";
- Verificação de palavras reservadas, bastando passar a flag "--only-reserved-words" 
para mostrar todas as palavras reservadas encontradas no arquivo;
- Desenvolvimento de um modo "autocomplete" (--ide-mode), que irá informar sugestões de palavras reservadas.
