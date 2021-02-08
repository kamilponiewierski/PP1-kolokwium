#ifdef __cplusplus
#include <iostream>
#include <cstring>
#include <cctype>

using namespace std;
#else

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#endif

#include "task1TextInput.h"


bool isDigitOrChar(char c);

char *inputAlphanumericTextFromFile(const char *filename)
{
#ifndef _MSC_FULL_VER // if not Visual Studio Compiler
#warning "Funkcja jest do zaimplementowania. Instrukcja w pliku naglowkowym"
#else
#pragma message ("Funkcja jest do zaimplementowania. Instrukcja w pliku naglowkowym")
#endif

    char *buffer = malloc(1000);
    buffer[0] = '\0';


    if (filename == NULL) return NULL;
    FILE *file = fopen(filename, "r");
    if (file == NULL) return NULL;

    int iter = 0;
    int c;

    while ((c = fgetc(file)) != EOF)
    {
        if (isspace(c))
        {
            buffer[iter] = ' ';
            iter++;
        }

        if (isDigitOrChar((char) c))
        {
            buffer[iter] = (char) c;
            iter++;
        }
    }
    buffer[iter] = '\0';


    return buffer;
}

bool isDigitOrChar(char c)
{
    return isdigit(c) || ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z');
}
