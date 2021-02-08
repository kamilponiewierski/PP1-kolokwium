#include <iostream>
#include <iomanip> // setw()
#include <cstring> // strcmp()

#include "argumentParsing.h"
#include "programmerDetails.h"

using namespace std;


namespace ArgumentParsing
{
    void printPossibleOptions()
    {
        cout << "Possible program options:\n";
        for (unsigned i=0; i<argumensCount; ++i)
        {
            cout << setw(12) << arguments[i][0] << "\t\t" << arguments[i][1] << '\n';
        }
    }

    // I know it can be done better with map and pair, but
    const char* getInformationByName(const char* informationName)
    {
        if (0 == strcmp(informationName, "firstname"))
        {
            return StudentsInfo::FIRSTNAME;
        }
        if (0 == strcmp(informationName, "surname"))
        {
            return StudentsInfo::SURNAME;
        }
        if (0 == strcmp(informationName, "mail"))
        {
            return StudentsInfo::MAIL;
        }
        if (0 == strcmp(informationName, "bookId"))
        {
            return StudentsInfo::BOOK_ID;
        }
        return nullptr;
    }

    void reactToProgramArgumentsPossibilyExit(int argc, char* argv[])
    {
        for(int a=1; a<argc; ++a)
        {
            const char* argument = argv[a];
            const char* information2Print = getInformationByName(argument);
            if (information2Print)
            {
                std::cout << information2Print << std::endl;
                exit(0);
            }
            if (0 == strcmp("--help", argument))
            {
                printPossibleOptions();
                exit(0);
            }
        }
    }
} // namespace ArgumentParsing
