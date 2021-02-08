#ifdef __cplusplus
#include <iostream>
#include <cstring>

using namespace std;
#else

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#endif

#include "task2Filtering.h"

//    /// pomocna moze okazac sie zaimplementowanie rowniez funkcji:
bool isPersonAsIWant(const Person *person, PersonField field, const void *fieldValue)
{
    switch (field)
    {
        case PERSON_FIELD_ANY:
            return isPersonAsIWant(person, PERSON_FIELD_ID, fieldValue) ||
                   isPersonAsIWant(person, PERSON_FIELD_NAME, fieldValue) ||
                   isPersonAsIWant(person, PERSON_FIELD_PROFESSION, fieldValue) ||
                   isPersonAsIWant(person, PERSON_FIELD_SEX, fieldValue) ||
                   isPersonAsIWant(person, PERSON_FIELD_AGE, fieldValue);
        case PERSON_FIELD_ID:
            return person->id == *((PersonId_t *) fieldValue);
        case PERSON_FIELD_NAME:
            return strcmp(person->name, fieldValue) == 0;
        case PERSON_FIELD_PROFESSION:
            return strcmp(person->profession, fieldValue) == 0;
        case PERSON_FIELD_SEX:
            return person->sex == *((Sex *) fieldValue);
        case PERSON_FIELD_AGE:
            return person->ageInYears == *((PersonAge_t *) fieldValue);
        default:
            return false;
    }
    return false;
}

Person *
getFilteredPersons(const Person *personsBegin, const Person *personsEnd, PersonField field, const void *fieldValue)
{
#ifndef _MSC_FULL_VER // if not Visual Studio Compiler
#warning "Funkcja jest do zaimplementowania. Instrukcja w pliku naglowkowym"
#else
#pragma message ("Funkcja jest do zaimplementowania. Instrukcja w pliku naglowkowym")
#endif

    Person *person = malloc(sizeof(Person) * 1000);

    if (personsEnd < personsBegin)
        return NULL;

    int iter = 0;
    if (personsBegin != NULL && personsEnd != NULL)
    {
        Person *personIter = (Person *) personsBegin;
        while (personIter < personsEnd)
        {
            if (isPersonAsIWant(personIter, field, fieldValue))
            {
                person[iter] = *personIter;
                iter++;
            }

            personIter++;
        }

        iter++;
    }
    else
        return NULL;

    person[iter].id = 0;
    return person;
}
