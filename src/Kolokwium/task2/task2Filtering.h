#ifndef TASK2_FILTERING
#define TASK2_FILTERING

#include "person.h"

/**
Tresc zadania: [rzutowanie, switch, typy, struktury, dynamiczna alokacja]
1. Prosze wpierw wejsc do pliku person.h i dokonac drobnych zmian.
2. Majac nasza strukture prosze o zaimplementowanie funkcji getFilteredPersons()
Przyjmuje ona wskaznik na poczatek oraz od razu za koncem tablicy osob.
Funkcja tworzy kopie elementow na dynamicznej tablicy, ktora sie konczy osoba o id==0.
Kopiowane są osoby, ktorych okreslone pole (ktore wiemy po PersonField) ma wartosc rowna fieldValue.

Dla ulatwienia: mozemy allokowac wieksza tablice niz jest konieczna na wszystkie elementy.

W razie bledu funkcja zwraca NULL
Bledy moga wystapic gdy:
    - podany zakres od > podanego zakresu do
    - jesli ktorys z zakresow wynosi NULL

IMPLEMENTACJA W PLIKU: task2Filtering.h, pliku naglowkowego nie ruszamy!
**/

enum PersonField
{
    PERSON_FIELD_ANY,
    PERSON_FIELD_ID,
    PERSON_FIELD_NAME,
    PERSON_FIELD_PROFESSION,
    PERSON_FIELD_SEX,
    PERSON_FIELD_AGE
};
#ifdef __STDC__
    typedef enum PersonField PersonField;
#endif


#ifdef __cplusplus
extern "C"
{
#endif

    Person* getFilteredPersons(const Person* personsBegin, const Person* personsEnd, PersonField field, const void* fieldValue);

#ifdef __cplusplus
} // extern "C"
#endif


#endif // TASK2_FILTERING
