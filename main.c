#include <stdio.h>
#include <stdlib.h>
#include "getTokens.h"
const char *keywords[37] = {"accessor", "and", "array", "begin", "bool", "case", "character", "constant", "else", "elsif", "end", "exit", "function",
                            "if", "in", "integer", "interface", "is", "loop", "module", "mutator", "natural", "null", "of", "or", "other", "out",
                            "positive", "procedure", "range", "return", "struct", "subtype", "then", "type", "when", "while"};
const char *operators[27] = {".", "<", ">", "(", ")", "+", "-", "*", "/", "|", "&", ";", ",", ":", "[", "]", "=", ":=", "..",
                             "<<", ">>", "<>", "<=", ">=", "**", "!=", "=>"};
const char *comments[2] = {"/*","*/"};
int main(void)
{
    FILE *fp1;
    char *buffer = 0;
    long length;
    fp1 = fopen("./files/complex.cci", "rb");
    if (fp1)
    {

        fseek(fp1, 0, SEEK_END);
        length = ftell(fp1);
        fseek(fp1, 0, SEEK_SET);
        buffer = malloc(length);
        if (buffer)
        {
            fread(buffer, 1, length, fp1);
        }
        fclose(fp1);
        //printf("%s\n", buffer);
    }
    int counter = 0;
    char **arrayOfTokens = NULL;
    counter = getTokens(buffer, &arrayOfTokens);
    for (int i = 0; i < counter; i++)
    {
        if(!strcmp(arrayOfTokens[i],comments[0]))
        {
            printf("%s\n", arrayOfTokens[i]);
            i++;
            while(strcmp(arrayOfTokens[i],comments[1]))
            {
                printf("%s ", arrayOfTokens[i]);
                i++;
            }
            printf("\n%s (comment)\n",arrayOfTokens[i]);
        }
        for (int j = 0; j < 37; j++)
        {
            if (!strcmp(arrayOfTokens[i],keywords[j]))
            {
                printf("%s (keyword)\n", arrayOfTokens[i]);
            }
            //else{printf("%s (keyword)\n", arrayOfTokens[i]);}
        }
        for (int j = 0; j < 27; j++)
        {
            if (!strcmp(arrayOfTokens[i],operators[j]))
                printf("%s (operator)\n", arrayOfTokens[i]);
        }
        
    }
    //    int c = getc(fp1);
    /* while(c != EOF)
       {
           fscanf(fp1,"",name);
           printf("%s\n",name);
           putchar(c);
           c = getc(fp1);

       }*/

    return 0;
}