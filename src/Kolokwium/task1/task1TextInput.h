#ifndef TASK1_TEXT_EXTRACTION
#define TASK1_TEXT_EXTRACTION

/**
Tresc zadania: [operacje na plikach tekstowych, dynamiczna alokacja, operacje na tekście, klasyfikacja tekstu]:
Napisanie funkcji, która wczyta cały tekst z pliku:
char* inputAlphanumericTextFromFile(const char* filename);
    - zwrócony tekst musi się kończyć znakiem końca tekstu
    - wszystkie białe znaki mają być zastąpione spacjami (można użyć: https://en.cppreference.com/w/c/string/byte/isspace)
    - znaki nie będące tekstem ani liczbami mają być pominięte (bialych nie pomijamy)

Obsługa błędów:
    - w razie gdy plik nie istnieje należy zwrócić NULL
    - w razie, gdy filename jest NULL funkcja musi zwrócić NULL


IMPLEMENTACJA W PLIKU: task1textInput.c, pliku naglowkowego nie ruszamy!

Mozna uzyc funkcji klasyfikujacych tekst:
http://www.cplusplus.com/reference/cstdio/
**/


#ifdef __cplusplus
    extern "C" {
#endif
    char* inputAlphanumericTextFromFile(const char* filename);
#ifdef __cplusplus
    } // extern "C"
#endif


#endif // TASK1_TEXT_EXTRACTION
