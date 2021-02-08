#ifdef __cplusplus
#include <cstring>

using namespace std;
#else

#include <string.h>
#include <stdio.h>

#endif

#include "task3TextReverse.h"


// sugeruje taka funkcje rowniez zaimplementowac - dla ulatwienia:
void swap(char *a, char *b)
{
    char tmp = *a;
    *a = *b;
    *b = tmp;
}

void reverseText(char text[])
{
    unsigned int len = strlen(text);

    if (len == 0) return;

    for (int i = 0; i <= len / 2; i++)
    {
        swap(&text[i], &text[len - i - 1]);
    }
}
