#ifndef FILE_NUMBERS_H
#define FILE_NUMBERS_H

#ifdef __cplusplus
    #include <cstdint>
    #include <cstddef>  // size_t
#else
    #include <stdint.h>
    #include <stddef.h>  // size_t
#endif

/**
------ Tresc zadania:
1. Funkcja, która wczytuje liczby w pliku (wiele liczb obok siebie, bez żadnego oddzielenia to ta sama liczba),
nastepnie zwraca w postaci instancji struktury Numbers (ponizej),
w taki sposob, ze liczby znajduja sie w polu "numbers", a ich ilosc w polu "numberCount", ale:
    a) Nie-liczby powinny zostac pominiete
    b) Od momentu znalezienia znaku "#" do konca linii tekst powinien zostac pominiety
    c) Funkcja powinna zwrócić liczby posortowane
    d) Powinny być odrzucone duplikaty
    e) W razie gdy podano NULL funkcja powinna wyjsc z programu zwracajac wartosc 1
    f) W razie gdy plik nie istnieje funkcja powinna wyjsc z programu zwracajac wartosc 2
    *g) Opcjonalnie: wykrywanie liczb ujemnych (nie ma na to testow)
    *h) Opcjonalnie: Wykrywanie liczb dziesietnych (nie ma na to testow)
    *i) Opcjonalnie: Liczby wykladnicze np. 10e4 (nie ma na to testow)
    **j) Opcjonalnie: Liczby szestnastkowe np. 0xabcdef (nie ma na to testow)
2. Funkcja powinna zliczac ilosc linii (dwa testy) w polu "linesCount"
Reszta tresci zawarta jest w testach automatycznych

PODPOWIEDZ: Rozbijamy na funkcje, bedzie latwiej wiele drobnych funkcji, niz jeden olbrzym
**/

typedef int64_t T;

#ifdef __cplusplus
extern "C"
{
#endif
    struct Numbers
    {
        T* numbers;
        size_t numberCount;
        size_t linesCount;
    };

    struct Numbers getSortedUniqueNumbersFromFile(const char* filename);
#ifdef __cplusplus
} // extern "C"
#endif

#endif  // FILE_NUMBERS_H
