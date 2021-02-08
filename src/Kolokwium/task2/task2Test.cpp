#include <iostream>
#include <type_traits>

#include <gtest/gtest.h>

#include "task2Filtering.h"


namespace
{
    using namespace ::testing;

    /// commented name and proffession are because of: https://stackoverflow.com/questions/19178124/static-initialisation-of-a-char-array-in-a-constant-struct-from-c-to-c
    const Person persons[] =
    {
        { /// http://www.filmweb.pl/film/Poranek+kojota-2001-8790
            /*.id =*/ 1,
            /*.name =*/ "Krzysiu Jarzyna ze Szczecina", /// http://www.filmweb.pl/person/Edward+Linde+Lubaszenko-4734
            /*.profession =*/ "szef wszystkich szefow",
            /*.sex =*/ SEX_MAN,
            /*.ageInYears =*/ 74.5
        },
        { /// http://www.filmweb.pl/film/Planeta+singli-2016-751987
            /*.id =*/ 2,
            /*.name =*/ "Ania Kwiatkowska", /// http://www.filmweb.pl/person/Kasia.Smutniak
            /*.profession =*/ "dziewczyna glownego bohatera",
            /*.sex =*/ SEX_WOMAN,
            /*.ageInYears =*/ 31
        },
        { /// http://www.filmweb.pl/film/Obywatel-2014-699039
            /*.id =*/ 3,
            /*.name =*/ "Jan Bratek", /// http://www.filmweb.pl/person/Jerzy.Stuhr
            /*.profession =*/ "obywatel",
            /*.sex =*/ SEX_MAN,
            /*.ageInYears =*/ 70
        },
        { /// http://www.filmweb.pl/Kariera.Nikosia.Dyzmy
            /*.id =*/ 4,
            /*.name =*/ "Nikoś Dyzma", /// http://www.filmweb.pl/person/Cezary.Pazura
            /*.profession =*/ "czołowy polski polityk",
            /*.sex =*/ SEX_MAN,
            /*.ageInYears =*/ 55
        },
        { /// http://www.filmweb.pl/serial/%C5%9Awiat+wed%C5%82ug+Kiepskich-1999-87947
            /*.id =*/ 5,
            /*.name =*/ "Halinka Kiepska", /// http://www.filmweb.pl/person/Marzena+Kipiel+Sztuka-100459
            /*.profession =*/ "pielegniarka",
            /*.sex =*/ SEX_WOMAN,
            /*.ageInYears =*/ 52
        },
        { /// http://www.filmweb.pl/Haker
            /*.id =*/ 6,
            /*.name =*/ "Laura", /// http://www.filmweb.pl/person/Kasia.Smutniak
            /*.profession =*/ "dziewczyna glownego bohatera",
            /*.sex =*/ SEX_WOMAN,
            /*.ageInYears =*/ 38
        }
    };

    const size_t numberOfPersons = sizeof(persons) / sizeof(persons[0]);


    inline bool isTextEqual(const decltype(Person::name)& lhs, const decltype(Person::name)& rhs)
    {
        return 0 == strcmp(lhs, rhs);
    }

    bool isTheSamePerson(const Person& lhs, const Person& rhs)
    {
        if (lhs.id != rhs.id || lhs.sex != rhs.sex || lhs.ageInYears != rhs.ageInYears)
        {
            return false;
        }
        if (!isTextEqual(lhs.name, rhs.name) || !isTextEqual(lhs.profession, rhs.profession))
        {
            return false;
        }
        return true;
    }
} // namespace

static bool operator==(const Person& lhs, const Person& rhs)
{
    return isTheSamePerson(lhs, rhs);
}

std::ostream& operator<<(std::ostream& os, const Person& p)
{
    return os << "Person(" << p.id << ", " << (p.sex == SEX_MAN ? "M,, " : "W ") << p.ageInYears << ", " << p.name << ", " << p.profession << ") ";
}


struct Task2PersonReturningFilterTester : public ::testing::Test
{
};


TEST_F(Task2PersonReturningFilterTester, typeOfPersonId)
{
    ASSERT_LE(sizeof(short), sizeof(PersonId_t));
    ASSERT_LE(sizeof(PersonId_t), sizeof(long long));
}

TEST_F(Task2PersonReturningFilterTester, typeOfPersonAge)
{
    ASSERT_EQ(sizeof(double), sizeof(PersonAge_t));
}


TEST_F(Task2PersonReturningFilterTester, returnFirstPerson)
{
    const decltype(Person::id) id = 1;
    Person* person = getFilteredPersons(persons, persons+numberOfPersons, PERSON_FIELD_ID, &id);

    ASSERT_EQ(persons[0], person[0]) << persons[0] << person[0];

    free(person);
}

TEST_F(Task2PersonReturningFilterTester, returnNotFirstPersonById)
{
    const decltype(Person::id) id = 2;
    Person* person = getFilteredPersons(persons, persons+numberOfPersons, PERSON_FIELD_ID, &id);

    ASSERT_EQ(persons[1], person[0]) << persons[1] << person[0];

    free(person);
}

TEST_F(Task2PersonReturningFilterTester, returnLastPersonById)
{
    const decltype(Person::id) id = 6;
    Person* person = getFilteredPersons(persons, persons+numberOfPersons, PERSON_FIELD_ID, &id);

    ASSERT_EQ(persons[numberOfPersons-1], person[0]) << persons[numberOfPersons-1] << person[0];
    ASSERT_EQ(0, person[1].id);

    free(person);
}

TEST_F(Task2PersonReturningFilterTester, returnAllMen)
{
    const decltype(Person::sex) sex = SEX_MAN;
    Person* person = getFilteredPersons(persons, persons+numberOfPersons, PERSON_FIELD_SEX, &sex);

    for(unsigned personIndex=0, i=0; i<numberOfPersons; ++i)
    {
        if (sex == persons[i].sex)
        {
            if (0 == person[personIndex].id)
            {
                ADD_FAILURE() << "Not all men detected but only " << personIndex << " iteration: " << i;
            }
            ASSERT_EQ(persons[i], person[personIndex]) << persons[i] << person[personIndex];
            ++personIndex;
        }
    }

    free(person);
}

TEST_F(Task2PersonReturningFilterTester, returnAllWomen)
{
    const decltype(Person::sex) sex = SEX_WOMAN;
    Person* person = getFilteredPersons(persons, persons+numberOfPersons, PERSON_FIELD_SEX, &sex);

    for(unsigned personIndex=0, i=0; i<numberOfPersons; ++i)
    {
        if (sex == persons[i].sex)
        {
            if (0 == person[personIndex].id)
            {
                ADD_FAILURE() << "Not all women detected but only " << personIndex << " iteration: " << i;
            }
            ASSERT_EQ(persons[i], person[personIndex]) << persons[i] << person[personIndex];
            ++personIndex;
        }
    }

    free(person);
}

TEST_F(Task2PersonReturningFilterTester, returnSinglePersonByName)
{
    const decltype(Person::name) name = "Laura";
    Person* person = getFilteredPersons(persons, persons+numberOfPersons, PERSON_FIELD_NAME, &name);

    ASSERT_EQ(persons[numberOfPersons-1], person[0]) << persons[numberOfPersons-1] << person[0];
    ASSERT_EQ(0, person[1].id);

    free(person);
}

TEST_F(Task2PersonReturningFilterTester, returnTwoPersonsByProfession)
{
    const decltype(Person::profession) profession = "dziewczyna glownego bohatera";
    Person* person = getFilteredPersons(persons, persons+numberOfPersons, PERSON_FIELD_PROFESSION, &profession);

    unsigned personIndex=0;
    for(unsigned i=0; i<numberOfPersons; ++i)
    {
        if (isTextEqual(profession, persons[i].profession))
        {
            if (0 == person[personIndex].id)
            {
                ADD_FAILURE() << "Not all women detected but only " << personIndex << " iteration: " << i;
            }
            ASSERT_EQ(persons[i], person[personIndex]) << persons[i] << person[personIndex];
            ++personIndex;
        }
    }
    ASSERT_EQ(0, person[personIndex].id);

    free(person);
}

TEST_F(Task2PersonReturningFilterTester, try2returnPersonWithNotExistingId)
{
    const decltype(Person::id) id = 99;
    Person* person = getFilteredPersons(persons, persons+numberOfPersons, PERSON_FIELD_ID, &id);

    ASSERT_EQ(0, person[0].id);

    free(person);
}

TEST_F(Task2PersonReturningFilterTester, tryEmptyRange)
{
    const decltype(Person::id) id = 1;
    Person* person = getFilteredPersons(persons, persons, PERSON_FIELD_ID, &id);

    ASSERT_TRUE(nullptr != person);
    ASSERT_EQ(0, person[0].id);

    free(person);
}

TEST_F(Task2PersonReturningFilterTester, tryRangeWhenRangeToIsLessThanRangeFromExpectedNullReturned)
{
    const decltype(Person::id) id = 1;
    Person* person = getFilteredPersons(persons+1, persons, PERSON_FIELD_ID, &id);

    ASSERT_TRUE(nullptr == person);

    free(person);
}

TEST_F(Task2PersonReturningFilterTester, tryNullptrAsRangeFromArgumentExpectedNullReturned)
{
    const decltype(Person::id) id = 1;

    ASSERT_TRUE(nullptr == getFilteredPersons(nullptr, persons, PERSON_FIELD_ID, &id));
}

TEST_F(Task2PersonReturningFilterTester, tryNullptrAsRangeToArgumentExpectedNullReturned)
{
    const decltype(Person::id) id = 1;

    ASSERT_TRUE(nullptr == getFilteredPersons(persons, nullptr, PERSON_FIELD_ID, &id));
}
