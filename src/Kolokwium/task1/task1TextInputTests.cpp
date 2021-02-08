#include <cstring> // strlen()
#include <iostream>
#include <gtest/gtest.h>

#include "task1TextInput.h"


namespace
{
using namespace std;
using namespace ::testing;
} // namespace


struct TemporaryFile
{
    constexpr static const char* fileName = "tmp.txt";
    
    TemporaryFile(const char* text2save)
    {
        FILE* file = fopen(fileName, "w+");
        if(!file)
        {
            cerr << "File not opened!\n";
            exit(1);
        }
        
        fputs(text2save, file);
        
        fflush(file);
        
        fclose(file);
    }
    
    ~TemporaryFile()
    {
        remove(fileName);
    }
};
    

struct Task1TextInputTester : public ::testing::Test
{    
};

TEST_F(Task1TextInputTester, singleShortWord)
{
    const char word[] = "Powodzenia";
   
    TemporaryFile temporaryFile(word);

    char* readText = inputAlphanumericTextFromFile(temporaryFile.fileName);

    ASSERT_STREQ(word, readText) << word;

    free(readText);
}

TEST_F(Task1TextInputTester, oneLineSentence)
{
    // source: https://pl.wikiquote.org/wiki/Stanis%C5%82aw_Michalkiewicz#O
    const char quote[]          = "Oczywiscie te podwyzki podatkow to dla naszego dobra, bo pieniadze, jak wiadomo, psuja charakter. Im wiecej pieniedzy rzad nam skonfiskuje, tym lepiej dla nas. Tak w kazdym razie mysla politycy, ktorzy wprawdzie nieustannie pragna naszego dobra, ale nam niestety juz coraz mniej go zostalo.";
    const char expectedResult[] = "Oczywiscie te podwyzki podatkow to dla naszego dobra bo pieniadze jak wiadomo psuja charakter Im wiecej pieniedzy rzad nam skonfiskuje tym lepiej dla nas Tak w kazdym razie mysla politycy ktorzy wprawdzie nieustannie pragna naszego dobra ale nam niestety juz coraz mniej go zostalo";

    TemporaryFile temporaryFile(quote);
    
    char* readText = inputAlphanumericTextFromFile(temporaryFile.fileName);

    ASSERT_STREQ(expectedResult, readText) << quote;

    free(readText);
}

TEST_F(Task1TextInputTester, multiLineSentence)
{
    // source: https://www.cytaty.info/autor/terrypratchett-3.htm
    const char quote[] =   "Uniwersytety sa skarbnicami wiedzy: studenci przychodza ze szkol przekonani, \n"
                           "ze wiedza juz prawie wszystko; po latach odchodza pewni, ze nie wiedza praktycznie niczego. \n"
                           "Gdzie sie podziewa ta wiedza? Zostaje na uniwersytecie, gdzie jest starannie suszona \n"
                           "i skladana w magazynach. \n";
    char expectedQuote[] = "Uniwersytety sa skarbnicami wiedzy studenci przychodza ze szkol przekonani  "
                           "ze wiedza juz prawie wszystko po latach odchodza pewni ze nie wiedza praktycznie niczego  "
                           "Gdzie sie podziewa ta wiedza Zostaje na uniwersytecie gdzie jest starannie suszona  "
                           "i skladana w magazynach  ";

    TemporaryFile temporaryFile(quote);

    char* readText = inputAlphanumericTextFromFile(temporaryFile.fileName);

    ASSERT_STREQ(expectedQuote, readText) << quote;

    free(readText);
}

TEST_F(Task1TextInputTester, emptyText)
{
    char text[] = "";

    TemporaryFile temporaryFile(text);

    char* readText = inputAlphanumericTextFromFile(temporaryFile.fileName);

    ASSERT_STREQ(text, readText) << text;

    free(readText);
}

TEST_F(Task1TextInputTester, nullasInputProvided)
{
    char* readText = inputAlphanumericTextFromFile(NULL);

    ASSERT_STREQ(NULL, readText);

    free(readText);
}

TEST_F(Task1TextInputTester, DISABLED_notExistingFileProvided)
{
    const char* notExistingFilename = "i_believe_i_do_not_live.txt";
    char* readText = inputAlphanumericTextFromFile(notExistingFilename);

    ASSERT_STREQ(NULL, readText);

    free(readText);
}
