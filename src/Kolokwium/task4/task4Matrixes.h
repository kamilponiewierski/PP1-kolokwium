#ifndef TASK4_MATRIXES_H
#define TASK4_MATRIXES_H


/**
Tresc zadania:
Prosze w pliku naglowkowym task4Matrixes.c dokonac implementacji mnozenia macierzy, wg podanych argumentow

Obsługa błędów:
    - w razie gdy warunek dla mnozenia macierzy nie bedzie spelniony (m2Rows != m1Columns) nalezy zwrocic false,
      w przeciwnym razie zawsze true
**/


#ifdef __cplusplus
extern "C"
{
#else
#include "stdbool.h"
#endif

bool multiplyMatrixes(int *m1[], int m1Rows, int m1Columns,
                      int *m2[], int m2Rows, int m2Columns,
                      int* result[], int* resultRows, int* resultColumns);

#ifdef __cplusplus
} // extern "C"
#endif //__cplusplus

#endif // TASK4_MATRIXES_H
