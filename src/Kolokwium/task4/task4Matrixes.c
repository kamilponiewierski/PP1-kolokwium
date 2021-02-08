#ifdef __cplusplus
#include <cstdio>

using namespace std;
#else

#include <stdio.h>

#endif

#include "task4Matrixes.h"


bool multiplyMatrixes(int *m1[], int m1Rows, int m1Columns,
                      int *m2[], int m2Rows, int m2Columns,
                      int *result[], int *resultRows, int *resultColumns)
{
#ifndef _MSC_FULL_VER // if not Visual Studio Compiler
#warning "Funkcja jest do zaimplementowania. Instrukcja w pliku naglowkowym"
#else
#pragma message ("Funkcja jest do zaimplementowania. Instrukcja w pliku naglowkowym")
#endif
    if (m2Rows != m1Columns)
        return false;

    *resultRows = m1Rows;
    *resultColumns = m2Columns;

    for (int i = 0; i < *resultRows; i++)
    {
        for (int j = 0; j < *resultColumns; j++)
        {
            int sum = 0;
            for (int r = 0; r < m1Columns; r++)
            {
                sum += m1[i][r] * m2[r][j];
            }
            result[i][j] = sum;
        }
    }

    return true;
}
