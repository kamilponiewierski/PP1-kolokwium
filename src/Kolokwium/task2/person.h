#ifndef PERSON_H
#define PERSON_H


/** Treść:
 *  Prosze o dokonanie zmian w ponizszych aliasach typow, aby odpowiadaly ponizszym opisom:
        - PersonId_t - liczba naturalna powyzej 1 bajta
        - PersonAge_t - jest to liczba zmiennoprzecinkowa podwojnej precyzji **/

typedef unsigned int PersonId_t;
typedef double PersonAge_t;

enum Sex
{
    SEX_MAN,
    SEX_WOMAN
};

#ifdef __STDC__
    typedef enum Sex Sex;
#endif

struct Person
{
    PersonId_t id;

    char name[50];
    char profession[50];

    Sex sex;
    PersonAge_t ageInYears;
};

#ifdef __STDC__
    typedef struct Person Person;
#endif

#endif // PERSON_H
