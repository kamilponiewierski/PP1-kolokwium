
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <inttypes.h>
#include "fileNumbers.h"

void ignoreRestOfLine(FILE* file, struct Numbers* numbers)
{
    while (1)
    {
        int c = getc(file);
        if (EOF == c)
        {
            return;
        }
        if (c == '\n')
        {
            numbers->linesCount++;
            return;
        }
    }
}

void readUntilNumber(FILE* file, struct Numbers* numbers)
{
    while (1)
    {
        int c = getc(file);
        if (EOF == c)
        {
            return;
        }

        if (isdigit(c))
        {
            ungetc(c, file);
            return;
        }

        if ('#' == c)
        {
            ignoreRestOfLine(file, numbers);
        }

        if ('\n' == c)
        {
            numbers->linesCount++;
        }
    }
}

void addNumber(struct Numbers* numbers, T number)
{
    if (numbers->numberCount == 0)
    {
        numbers->numbers = (T*)malloc(sizeof(T));
    }
    else
    {
        numbers->numbers = realloc(numbers->numbers, sizeof(T) * (numbers->numberCount+1));
    }
    numbers->numbers[numbers->numberCount] = number;
    numbers->numberCount++;
}


int compare_ints(const void* a, const void* b)
{
    T arg1 = *(const T*)a;
    T arg2 = *(const T*)b;

    return arg1 - arg2;
}

void sortNumbers(struct Numbers* numbers)
{
    if (numbers->numbers)
    {
        qsort(numbers->numbers, numbers->numberCount, sizeof(T), compare_ints);
    }
}

void removeDuplicatedNumbers(struct Numbers* numbers)
{
    if (0 == numbers->numberCount)
    {
        return;
    }

    size_t uniqueCounter = 0;
    for (size_t i=0; i<numbers->numberCount; ++i)
    {
        if (numbers->numbers[uniqueCounter] != numbers->numbers[i])
        {
            ++uniqueCounter;
        }
        numbers->numbers[uniqueCounter] = numbers->numbers[i];
    }
    numbers->numberCount = uniqueCounter + 1;
}


struct Numbers getSortedUniqueNumbersFromFile(const char* filename)
{
    if (NULL == filename)
    {
        exit(1);
    }

    FILE* file = fopen(filename, "r");
    if (file == NULL)
    {
        exit(2);
    }

    struct Numbers numbers = {0, 0, 0};

    while (1)
    {
        readUntilNumber(file, &numbers);
        if (feof(file))
        {
            break;
        }
        
        T tmp;
        fscanf(file, "%" SCNd64, &tmp);
        addNumber(&numbers, tmp);
    }

    sortNumbers(&numbers);
    removeDuplicatedNumbers(&numbers);

    return numbers;
}
