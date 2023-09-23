#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

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
   lexer(buffer);
}