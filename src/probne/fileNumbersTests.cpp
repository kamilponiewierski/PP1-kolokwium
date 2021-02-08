#include <iostream>
#include <fstream>
#include <algorithm> // count
#include <vector>
#include <cmath>
#include <gtest/gtest.h>

#include "fileNumbers.h"


namespace
{
using namespace std;
using namespace ::testing;
} // namespace


class FileNumbersTester : public ::testing::Test
{
protected:
    void TearDown() override
    {
        for (const auto& filename : files2Remove)
        {
            remove(filename.c_str());
        }

        free(numbers.numbers);
    }

    string saveText2FileReturningItsName(const char* text)
    {
        char filename[L_tmpnam];
        tmpnam(filename);

        ofstream file(filename);
        file << text << flush;

        files2Remove.push_back(filename);

        return filename;
    }

    string numbers2Text(const Numbers& numbers)
    {
        string numbersAsText = "Numbers[" + to_string(numbers.numberCount) + "]={";
        for (size_t i=0; i < numbers.numberCount; ++i)
        {
            numbersAsText += to_string(numbers.numbers[i]) + ",";
        }
        return numbersAsText + "}";
    }

    vector<string> files2Remove;
    Numbers numbers = {};
};

TEST_F(FileNumbersTester, readingFewOneDigitNumbersInMultipleLine)
{
    constexpr const char* text =
            "1\n"
            "2\n"
            "3\n";
    auto filename = saveText2FileReturningItsName(text);

    constexpr T expectedNumbers[] = {1, 2, 3};
    constexpr size_t expectedNumbersCount = sizeof(expectedNumbers) / sizeof(expectedNumbers[0]);

    numbers = getSortedUniqueNumbersFromFile(filename.c_str());
    ASSERT_EQ(expectedNumbersCount, numbers.numberCount);
    for (size_t i=0; i < expectedNumbersCount; ++i)
    {
        EXPECT_EQ(expectedNumbers[i], numbers.numbers[i]) << numbers2Text(numbers);
    }
}

TEST_F(FileNumbersTester, readingSingleOneDigitNumbers)
{
    constexpr const char* text = "1";
    auto filename = saveText2FileReturningItsName(text);

    constexpr T expectedNumbers[] = {1};
    constexpr size_t expectedNumbersCount = sizeof(expectedNumbers) / sizeof(expectedNumbers[0]);

    numbers = getSortedUniqueNumbersFromFile(filename.c_str());
    ASSERT_EQ(expectedNumbersCount, numbers.numberCount);
    for (size_t i=0; i < expectedNumbersCount; ++i)
    {
        EXPECT_EQ(expectedNumbers[i], numbers.numbers[i]) << numbers2Text(numbers);
    }
}

TEST_F(FileNumbersTester, readingFewOneDigitNumbersInMultipleLineSeparatedWithEmptyLines)
{
    constexpr const char* text =
            "\n"
            "1\n"
            "\n"
            "3\n"
            "\n"
            "5\n"
            "\n";
    auto filename = saveText2FileReturningItsName(text);

    constexpr T expectedNumbers[] = {1, 3, 5};
    constexpr size_t expectedNumbersCount = sizeof(expectedNumbers) / sizeof(expectedNumbers[0]);

    numbers = getSortedUniqueNumbersFromFile(filename.c_str());
    ASSERT_EQ(expectedNumbersCount, numbers.numberCount);
    for (size_t i=0; i < expectedNumbersCount; ++i)
    {
        EXPECT_EQ(expectedNumbers[i], numbers.numbers[i]) << numbers2Text(numbers);
    }
}

TEST_F(FileNumbersTester, emptyFile_expectedNumberCountAsZero)
{
    constexpr const char* text = "";
    auto filename = saveText2FileReturningItsName(text);

    constexpr size_t expectedNumbersCount = 0;

    numbers = getSortedUniqueNumbersFromFile(filename.c_str());
    ASSERT_EQ(expectedNumbersCount, numbers.numberCount);
}

TEST_F(FileNumbersTester, fileContainsOnlyAlphabetCharacters_expectedNumberCountAsZero)
{
    /// Author of quote: "Sw. Antoni Pustelnik"
    constexpr const char* text =
            "Przyjda takie czasy, \n"
            "ze ludzie beda szaleni i gdy zobacza kogos przy zdrowych zmyslach, \n"
            "powstana przeciw niemu mowiac: \n"
            "Jestes szalony bo nie jestes do nas podobny.";
    auto filename = saveText2FileReturningItsName(text);

    constexpr size_t expectedNumbersCount = 0;

    numbers = getSortedUniqueNumbersFromFile(filename.c_str());
    ASSERT_EQ(expectedNumbersCount, numbers.numberCount);
}

TEST_F(FileNumbersTester, fileContainsOnlyComments_expectedNumberCountAsZero)
{
    constexpr const char* text =
            "#\n"
            "#\n"
            "#\n";
    auto filename = saveText2FileReturningItsName(text);

    constexpr size_t expectedNumbersCount = 0;

    numbers = getSortedUniqueNumbersFromFile(filename.c_str());
    ASSERT_EQ(expectedNumbersCount, numbers.numberCount);
}

TEST_F(FileNumbersTester, fileContainsNumbersAfterComments_expectedNumberCountAsZero)
{
    constexpr const char* text =
            "#2\n"
            "#4\n"
            "#8\n";
    auto filename = saveText2FileReturningItsName(text);

    constexpr size_t expectedNumbersCount = 0;

    numbers = getSortedUniqueNumbersFromFile(filename.c_str());
    ASSERT_EQ(expectedNumbersCount, numbers.numberCount);
}

TEST_F(FileNumbersTester, fileContainsNumbersBeforeAndAfterComments_expectedCommentedTextIgnored)
{
    constexpr const char* text =
            "1#2\n"
            "3#4\n"
            "5#6\n";
    auto filename = saveText2FileReturningItsName(text);

    constexpr T expectedNumbers[] = {1, 3, 5};
    constexpr size_t expectedNumbersCount = sizeof(expectedNumbers) / sizeof(expectedNumbers[0]);

    numbers = getSortedUniqueNumbersFromFile(filename.c_str());
    ASSERT_EQ(expectedNumbersCount, numbers.numberCount);
    for (size_t i=0; i < expectedNumbersCount; ++i)
    {
        EXPECT_EQ(expectedNumbers[i], numbers.numbers[i]) << numbers2Text(numbers);
    }
}

TEST_F(FileNumbersTester, fileContainsMultipleDigitsNumbers)
{
    constexpr const char* text =
            "34\n"
            "123\n"
            "5600\n"
            "10005001009\n";
    auto filename = saveText2FileReturningItsName(text);

    constexpr T expectedNumbers[] = {34, 123, 5600, 10005001009};
    constexpr size_t expectedNumbersCount = sizeof(expectedNumbers) / sizeof(expectedNumbers[0]);

    numbers = getSortedUniqueNumbersFromFile(filename.c_str());
    ASSERT_EQ(expectedNumbersCount, numbers.numberCount);
    for (size_t i=0; i < expectedNumbersCount; ++i)
    {
        EXPECT_EQ(expectedNumbers[i], numbers.numbers[i]) << numbers2Text(numbers);
    }
}

TEST_F(FileNumbersTester, fileContainsEverythingAbove)
{
    constexpr const char* text =
            R"---(
A teraz numer 1 to najpilniejszy czlowiek #:) 2 tez
W klasie jest 26 uczniow, w szkole 520 # chociaz tych 20 nie chodzi

Lubie moja szkole, mimo iz jest 1200-tna w malopolsce # oraz 7420-sieczna w Polsce)---";
    auto filename = saveText2FileReturningItsName(text);

    constexpr T expectedNumbers[] = {1, 26, 520, 1200};
    constexpr size_t expectedNumbersCount = sizeof(expectedNumbers) / sizeof(expectedNumbers[0]);

    numbers = getSortedUniqueNumbersFromFile(filename.c_str());
    ASSERT_EQ(expectedNumbersCount, numbers.numberCount);
    for (size_t i=0; i < expectedNumbersCount; ++i)
    {
        EXPECT_EQ(expectedNumbers[i], numbers.numbers[i]) << numbers2Text(numbers);
    }
}

TEST_F(FileNumbersTester, fileContainsNotSortedNumbers_expectedSorting)
{
    constexpr const char* text =
            "6\n"
            "444\n"
            "2\n"
            "999\n";
    auto filename = saveText2FileReturningItsName(text);

    constexpr T expectedNumbers[] = {2, 6, 444, 999};
    constexpr size_t expectedNumbersCount = sizeof(expectedNumbers) / sizeof(expectedNumbers[0]);

    numbers = getSortedUniqueNumbersFromFile(filename.c_str());
    ASSERT_EQ(expectedNumbersCount, numbers.numberCount);
    for (size_t i=0; i < expectedNumbersCount; ++i)
    {
        EXPECT_EQ(expectedNumbers[i], numbers.numbers[i]) << numbers2Text(numbers);
    }
}

TEST_F(FileNumbersTester, fileContainsSortedNumbersWithDuplications_expectedRemovingDuplicatedNumbers)
{
    constexpr const char* text =
            "11\n"
            "11\n"
            "11\n"
            "11\n"
            "13\n"
            "17\n"
            "17\n"
            "19\n"
            "21\n"
            "21\n"
            "21\n";
    auto filename = saveText2FileReturningItsName(text);

    constexpr T expectedNumbers[] = {11, 13, 17, 19, 21};
    constexpr size_t expectedNumbersCount = sizeof(expectedNumbers) / sizeof(expectedNumbers[0]);

    numbers = getSortedUniqueNumbersFromFile(filename.c_str());
    ASSERT_EQ(expectedNumbersCount, numbers.numberCount);
    for (size_t i=0; i < expectedNumbersCount; ++i)
    {
        EXPECT_EQ(expectedNumbers[i], numbers.numbers[i]) << numbers2Text(numbers);
    }
}


TEST_F(FileNumbersTester, filenameIsNull_expectedExit)
{
    ASSERT_EXIT(getSortedUniqueNumbersFromFile(nullptr), ::testing::ExitedWithCode(1), "");
}

TEST_F(FileNumbersTester, fileDoesNotExist_expectedExit)
{
    constexpr const char* filename = "nie istniejemy.txt";
    ASSERT_EXIT(getSortedUniqueNumbersFromFile(filename), ::testing::ExitedWithCode(2), "");
}


TEST_F(FileNumbersTester, countingLinesWhenFewNotEmptyLinesAndFileEndingWithEmptyLine)
{
    const char* text =
            "P\n"
            "o\n"
            "w\n"
            "o\n"
            "d\n"
            "z\n"
            "e\n"
            "n\n"
            "i\n"
            "a\n"
            "!!!\n";
    auto filename = saveText2FileReturningItsName(text);

    const size_t expectedLinesCount = count(text, text+strlen(text), '\n');

    numbers = getSortedUniqueNumbersFromFile(filename.c_str());
    ASSERT_EQ(expectedLinesCount, numbers.linesCount);
}

TEST_F(FileNumbersTester, countingLinesWhenFewNotEmptyLinesAndFileNotEndingWithEmptyLine)
{
    const char* text =
            "W\n"
            "s\n"
            "z\n"
            "y\n"
            "s\n"
            "t\n"
            "k\n"
            "i\n"
            "m\n"
            "!!!\n";
    auto filename = saveText2FileReturningItsName(text);

    const size_t expectedLinesCount = count(text, text+strlen(text), '\n');

    numbers = getSortedUniqueNumbersFromFile(filename.c_str());
    ASSERT_EQ(expectedLinesCount, numbers.linesCount);
}
