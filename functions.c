
#include "functions.h"
const char *keywords[39] = {
    "structure",
    "procedure",
    "character",
    "interface",
    "constant",
    "accessor",
    "positive",
    "function",
    "mutator",
    "integer",
    "subtype",
    "natural",
    "elseif",
    "module",
    "return",
    "struct",
    "begin",
    "elsif",
    "array",
    "while",
    "range",
    "other",
    "exit",
    "then",
    "case",
    "loop",
    "type",
    "when",
    "else",
    "null",
    "bool",
    "out",
    "and",
    "end",
    "if",
    "in",
    "or",
    "of",
    "is"};
const char *operators[27] = {":=", "..", "<<", ">>", "<>", "<=", ">=", "**", "!=", "=>", ".", "<", ">", "(", ")", "+", "-", "*", "/", "|", "&", ";", ",", ":", "[", "]", "="};



void lexer(char *s, char *name)
{
  char nameOfFile[256] = "";
  strcat(nameOfFile, name);
  strcat(nameOfFile, ".lexer");
  FILE *out_file = fopen(nameOfFile, "w");
  int sizeofS = strlen(s);
  // int begOfS = 0;
  // char *a;
  // char b = s[0];
  //comments test
  for (int i = 0; i < sizeofS; i++)
  {
    // b = s[i];
    // test for comments
    if (s[i] == '/' && s[i + 1] == '*')
    {
      // begOfS = i;
      fprintf(out_file, "%c", s[i]);
      i++;
      while (s[i] != '/')
      {
        fprintf(out_file, "%c", s[i]);
        i++;
      }
      fprintf(out_file, "%c (comment)\n", s[i]);
      i++;
    }
    // test for string
    if (s[i] == '\"')
    {
      // begOfS = i;
      fprintf(out_file, "%c", s[i]);
      i++;
      while (s[i] != '\"')
      {
        fprintf(out_file, "%c", s[i]);
        i++;
      }
      // i++;
      fprintf(out_file, "%c (string)\n", s[i]);
      i++;
    }
    // keywords
    for (int j = 0; j <39; j++)
    {
      char *a;
      int keyWordLen = strlen(keywords[j]);
      if (keyWordLen < sizeofS - i)
      {
        a = malloc(keyWordLen);
        strncpy(a, s + i, keyWordLen);
        if (!strcmp(a, keywords[j]) && (s[i+keyWordLen] == ' '|| s[i+keyWordLen] == '\n' ||s[i+keyWordLen] == ';' ||s[i+keyWordLen] == ')'))
        {
          fprintf(out_file, "%s (keyword)\n", a);
          i += keyWordLen;
        }
        free(a);
      }
    }
    // character literals
    if (s[i] == '\'' && s[i+2] == '\'')
    {
      // begOfS = i;
      fprintf(out_file, "%c", s[i]);
      i++;
      fprintf(out_file, "%c", s[i]);
      i++;
      fprintf(out_file, "%c (character literal)\n", s[i]);
      //i--;
    }
    // doubleoperators test
    int doubleOperator = 0;
    for (int j = 0; j < 10; j++)
    {
      if(s[i] == operators[j][0] &&s[i+1] == operators[j][1])
      {
          fprintf(out_file, "%c%c (operator)\n",s[i],s[i+1]);
          i +=2;
          doubleOperator = 1;
      }
    }
 // test for comments
    if (s[i] == '/' && s[i + 1] == '*')
    {
      // begOfS = i;
      fprintf(out_file, "%c", s[i]);
      i++;
      while (s[i] != '/')
      {
        fprintf(out_file, "%c", s[i]);
        i++;
      }
      fprintf(out_file, "%c (comment)\n", s[i]);
      i++;
    }
    //singleOperators test
    for(int j = 10; j <27;j++)
    {
       if(s[i] == operators[j][0])
      {
          fprintf(out_file, "%c (operator)\n",s[i]);
          //i++;
      }
    }
    i-=doubleOperator;
    doubleOperator = 0;
    // numeric literal
    if (isdigit(s[i]) != 0 || s[i] == '#')
    {
      fprintf(out_file, "%c", s[i]);
      i++;
      if (s[i] == '.' && isdigit(s[i + 1]) != 0)
      {
        fprintf(out_file, "%c", s[i]);
        i++;
      }
      int continueLoop = 1;
      while (continueLoop == 1)
      {
        if (isdigit(s[i]) != 0 || s[i] == '#')
        {
          fprintf(out_file, "%c", s[i]);
          i++;
        }
        else
          continueLoop = 0;
      }
      fprintf(out_file, " (numeric literal)\n");
      i--;
    }
    // identifier
    if (isalpha(s[i]) != 0)
    {
      fprintf(out_file, "%c", s[i]);
      i++;
      while (isalpha(s[i]) != 0 || isdigit(s[i]) != 0 || s[i] == '_')
      {
        fprintf(out_file, "%c", s[i]);
        i++;
      }
      fprintf(out_file, " (identifier)\n");
      i--;
    }
  }
}



