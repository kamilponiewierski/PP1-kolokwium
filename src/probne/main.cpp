#include <iostream>
#include <gtest/gtest.h>
using namespace ::testing;

#include "utils/programmerDetails.h"
#include "utils/argumentParsing.h"

#include "probne/fileNumbers.h"

/** Tresc zadan dla Panstwa:

Zadanie 0: absolutnie obowiazkowe, chociaz bez punktow
1) Pierwsza rzecza jest poprawa bledow kompilacji,
   czyli wpisanie poprawnych Panstwa danych w pliku: programmerDetails.h
2) Oddanne kolokwium musi sie bezwzglednie kompilowac,
   jesli sie nie skompiluje to jest to 0 punktow za kolokwium!
   Oczywiscie w razie problemow z kompilacja prosze pisać.
   Dobrze, jesli nie byloby warningow kompilacji, ale za to nie obnizam punktow.
   Aby się upewnić, że się kompiluje można skorzystać z narzędzia: http://administrare.kis.agh.edu.pl:12345
3) Oddane kolokwium nie powinno crashować na żadnym teście,
   jeśli crashuje proszę zrobic implementacje -fake, ktora bedzie zwracac zawsze te same wartosci
   -test bedzie failowal, ale za to testy nie beda sie crashowaly.
   W przypadku crasha biorę pod uwagę tylko tyle testów, ile przejdzie do czasu crasha!
5) Mam program antyplagiatowy, dlatego prosze pracowac samodzielnie!
   Osoby ktore udostepniaja swoje rozwiazania rowniez beda mialy kare!

Zadanie implementacyjne - patrz plik fileNumbers.h
**/

int main(int argc, char* argv[])
{
    StudentsInfo::validateStudentsInfo();

    ArgumentParsing::reactToProgramArgumentsPossibilyExit(argc, argv);

    ::testing::InitGoogleTest(&argc, argv);
    GTEST_FLAG(print_time) = false;
    return RUN_ALL_TESTS();
}
