/**
 * @file functions.h
 * @author Michael J Habermann
 * @brief The header file for the lexer program
 * @date 2023-09-24
 *
 *
 */
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
// function prototypes
void lexer(char *s, char *name);
int testComments(FILE *fileName, char *s, int counter);
int testString(FILE *fileName, char *s, int counter);
int testKeywords(FILE *fileName, char *s, int counter);
int testCharacters(FILE *fileName, char *s, int counter);
int operatorTest(FILE *fileName, char *s, int counter);
int testNumeric(FILE *fileName, char *s, int counter);
int testIdentifier(FILE *fileName, char *s, int counter);