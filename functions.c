/**
 * @file functions.c
 * @author Michael J Habermann
 * @brief These are the functions for the lexer program
 * @date 2023-09-24
 *
 *
 */

#include "functions.h"
const char *keywords[37] = {
    "procedure", "interface", "character", "accessor", "positive", "constant", "function",
    "mutator", "natural", "subtype", "integer", "return", "struct", "module",
    "other", "while", "array", "begin", "elsif", "range", "bool", "case", "null", 
    "loop", "then", "else", "type", "when", "exit", "and", "end", "out", "is", "of", "or", "if", "in"};
const char *operators[27] = {":=", "..", "<<", ">>", "<>", "<=", ">=", "**", "!=", "=>", ".", "<", ">", "(", ")", "+", "-", "*", "/", "|", "&", ";", ",", ":", "[", "]", "="};
/**
 * @brief Tests for comments by analyzing if there are '/'s
 *
 * @param fileName The name of the file we are outputting to
 * @param s The string we are analyzing
 * @param counter The counter of where we are at in the string
 * @return int returns counter
 */
int testComments(FILE *fileName, char *s, int counter)
{
  if (s[counter] == '/' && s[counter + 1] == '*')
  {
    // begOfS = i;
    fprintf(fileName, "%c", s[counter]);
    counter++;
    while (s[counter] != '/')
    {
      fprintf(fileName, "%c", s[counter]);
      counter++;
    }
    fprintf(fileName, "%c (comment)\n", s[counter]);
    counter++;
  }
  return counter;
}
/**
 * @brief Tests if there are strings in s
 *
 * @param fileName The name of the file we are outputting to
 * @param s The string we are analyzing
 * @param counter The counter of where we are at in the string
 * @return int returns counter
 */
int testString(FILE *fileName, char *s, int counter)
{
  if (s[counter] == '\"')
  {
    // begOfS = i;
    fprintf(fileName, "%c", s[counter]);
    counter++;
    while (s[counter] != '\"')
    {
      fprintf(fileName, "%c", s[counter]);
      counter++;
    }
    // i++;
    fprintf(fileName, "%c (string)\n", s[counter]);
    counter++;
  }
  return counter;
}
/**
 * @brief Tests for keywords in the string s
 *
 * @param fileName The name of the file we are outputting to
 * @param s The string we are analyzing
 * @param counter The counter of where we are at in the string
 * @return int returns counter
 */
int testKeywords(FILE *fileName, char *s, int counter)
{
  int sizeofS = strlen(s);
  for (int j = 0; j < 37; j++)
  {
    char *a;
    int keyWordLen = strlen(keywords[j]);
    if (keyWordLen < sizeofS - counter)
    {
      a = malloc(keyWordLen);
      strncpy(a, s + counter, keyWordLen);
      if (!strcmp(a, keywords[j]) && (s[counter + keyWordLen] == ' ' || s[counter + keyWordLen] == '\n' || s[counter + keyWordLen] == ';' || s[counter + keyWordLen] == ')'))
      {
        fprintf(fileName, "%s (keyword)\n", a);
        counter += keyWordLen;
      }
      free(a);
    }
  }
  return counter;
}
/**
 * @brief Tests for possible single characters in the string s
 *
 * @param fileName The name of the file we are outputting to
 * @param s The string we are analyzing
 * @param counter The counter of where we are at in the string
 * @return int returns counter
 */
int testCharacters(FILE *fileName, char *s, int counter)
{
  if (s[counter] == '\'' && s[counter + 2] == '\'')
  {
    // begOfS = i;
    fprintf(fileName, "%c", s[counter]);
    counter++;
    fprintf(fileName, "%c", s[counter]);
    counter++;
    fprintf(fileName, "%c (character literal)\n", s[counter]);
  }
  return counter;
}
/**
 * @brief Tests 27 operators for if the string s has them
 *
 * @param fileName The name of the file we are outputting to
 * @param s The string we are analyzing
 * @param counter The counter of where we are at in the string
 * @return int returns counter
 */
int operatorTest(FILE *fileName, char *s, int counter)
{
  int doubleOperator = 0;
  // double operator test
  for (int j = 0; j < 10; j++)
  {
    if (s[counter] == operators[j][0] && s[counter + 1] == operators[j][1])
    {
      fprintf(fileName, "%c%c (operator)\n", s[counter], s[counter + 1]);
      counter += 2;
      doubleOperator = 1;
    }
  }
  // test for comments
  counter = testComments(fileName, s, counter);
  // singleOperators test
  for (int j = 10; j < 27; j++)
  {
    if (s[counter] == operators[j][0])
    {
      fprintf(fileName, "%c (operator)\n", s[counter]);
      // i++;
    }
  }
  counter -= doubleOperator;
  return counter;
}
/**
 * @brief Tests if there are numbers in the function
 *
 * @param fileName The name of the file we are outputting to
 * @param s The string we are analyzing
 * @param counter The counter of where we are at in the string
 * @return int returns counter
 */
int testNumeric(FILE *fileName, char *s, int counter)
{
  if (isdigit(s[counter]) != 0 || s[counter] == '#')
  {
    fprintf(fileName, "%c", s[counter]);
    counter++;
    if (s[counter] == '.' && isdigit(s[counter + 1]) != 0)
    {
      fprintf(fileName, "%c", s[counter]);
      counter++;
    }
    int continueLoop = 1;
    while (continueLoop == 1)
    {
      if (isdigit(s[counter]) != 0 || s[counter] == '#')
      {
        fprintf(fileName, "%c", s[counter]);
        counter++;
      }
      else
        continueLoop = 0;
    }
    fprintf(fileName, " (numeric literal)\n");
    counter--;
  }
  return counter;
}
/**
 * @brief Tests for if there are identifiers in the string s
 *
 * @param fileName The name of the file we are outputting to
 * @param s The string we are analyzing
 * @param counter The counter of where we are at in the string
 * @return int returns counter
 */
int testIdentifier(FILE *fileName, char *s, int counter)
{
  if (isalpha(s[counter]) != 0)
  {
    fprintf(fileName, "%c", s[counter]);
    counter++;
    while (isalpha(s[counter]) != 0 || isdigit(s[counter]) != 0 || s[counter] == '_')
    {
      fprintf(fileName, "%c", s[counter]);
      counter++;
    }
    fprintf(fileName, " (identifier)\n");
    counter--;
  }
  return counter;
}
/**
 * @brief This is the lexer, it pulls from all of the other functions to sort through a string and classify the information
 *
 * @param s The information it is searching through
 * @param name The name of the file the user orginally gave
 */
void lexer(char *s, char *name)
{
  char nameOfFile[256] = "";
  strcat(nameOfFile, name);
  strcat(nameOfFile, ".lexer");
  FILE *out_file = fopen(nameOfFile, "w");
  int sizeofS = strlen(s);
  for (int i = 0; i < sizeofS; i++)
  {
    // test for comments
    i = testComments(out_file, s, i);
    // test for string
    i = testString(out_file, s, i);
    // keywords
    i = testKeywords(out_file, s, i);
    // character literals
    i = testCharacters(out_file, s, i);
    // doubleoperators test
    i = operatorTest(out_file, s, i);
    // numeric literal
    i = testNumeric(out_file, s, i);
    // identifier
    i = testIdentifier(out_file, s, i);
  }
}