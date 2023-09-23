
#include "functions.h"
const char *keywords[36] = {
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
    "boolean",
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
    "else",
    "null",
    "out",
    "and",
    "if",
    "in",
    "or",
    "of",
};
const char *operators[27] = {".", "<", ">", "(", ")", "+", "-", "*", "/", "|", "&", ";", ",", ":", "[", "]", "=", ":=", "..",
                             "<<", ">>", "<>", "<=", ">=", "**", "!=", "=>"};
void lexer(char *s)
{
  int sizeofS = strlen(s);
  // int begOfS = 0;
  // char *a;
  // char b = s[0];
  for (int i = 0; i < sizeofS; i++)
  {
    // b = s[i];
    // test for comments
    if (s[i] == '/' && s[i + 1] == '*')
    {
      // begOfS = i;
      printf("%c", s[i]);
      i++;
      while (s[i] != '/')
      {
        printf("%c", s[i]);
        i++;
      }
      printf("%c (comment)\n", s[i]);
      i++;
    }
    // test for string
    if (s[i] == '\"')
    {
      // begOfS = i;
      printf("%c", s[i]);
      i++;
      while (s[i] != '\"')
      {
        printf("%c", s[i]);
        i++;
      }
      // i++;
      printf("%c (string)\n", s[i]);
      i++;
    }
    // keywords
    for (int j = 0; j < 36; j++)
    {
      char *a;
      int keyWordLen = strlen(keywords[j]);
      if (keyWordLen < sizeofS - i)
      {
        a = malloc(keyWordLen);
        strncpy(a, s + i, keyWordLen);
        if (!strcmp(a, keywords[j]))
        {
          printf("%s (keyword)\n", a);
          i += keyWordLen;
        }
        free(a);
      }
    }
    // character literals
    if (s[i] == '\'')
    {
      // begOfS = i;
      printf("%c", s[i]);
      i++;
      while (s[i] != '\'')
      {
        printf("%c", s[i]);
        i++;
      }
      // i++;
      printf("%c (char literal)\n", s[i]);
    }
    //operators
    for (int j = 0; j < 26; j++)
    {
      char *a;
      int operatorsLen = strlen(operators[j]);
      if (operatorsLen < sizeofS - i)
      {
        a = malloc(operatorsLen);
        strncpy(a, s + i, operatorsLen);
        if (!strcmp(a, operators[j]))
        {
          printf("%s (operator)\n", a);
          i += operatorsLen;
        }
        free(a);
      }
    }
    //numeric literal
    if(isdigit(s[i]) != 0|| s[i] == '#')
    {
      printf("%c", s[i]);
      i++;
      if(s[i] == '.')
      {
      printf("%c", s[i]);
      i++; 
      }
      int continueLoop = 0;
      while(continueLoop == 1)
      {
        if(isdigit(s[i]) != 0|| s[i] == '#')
        {
        printf("%c", s[i]);
        i++; 
        }
        else 
        continueLoop = 0;
      }
      printf(" (numeric literal)\n");
      }
      //identifier
      if(isalpha(s[i]) != 0)
      {
        printf("%c", s[i]);
        i++;
        while(isalpha(s[i]) != 0 ||isdigit(s[i]) != 0 ||s[i] == '_' )
        {
            printf("%c", s[i]);
            i++;
        }
        printf(" (identifier)\n");
        i--;
      }
    }
  }
