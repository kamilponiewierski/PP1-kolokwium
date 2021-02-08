#include <string>

#include "programmerDetails.h"

namespace StudentsInfo
{
    constexpr inline size_t compileTimeStrlen(const char* text) noexcept
    {
        return (*text ? 1+compileTimeStrlen(text+1) : 0);
    }

    constexpr inline size_t compileTimeCountFirstDigits(const char* text) noexcept
    {
        return (*text && ('0'<=*text && *text<='9') ? 1+compileTimeCountFirstDigits(text+1) : 0);
    }

    constexpr inline bool compileTimeIsDigit(const char* text) noexcept
    {
        return compileTimeStrlen(text) == compileTimeCountFirstDigits(text);
    }

    /// int is return type because of gcc bug: https://stackoverflow.com/questions/29261276/constexpr-void-function-rejected
    constexpr inline int validateFirstname()
    {
        static_assert(compileTimeStrlen(FIRSTNAME) > 2, "You must input your first name!");
        return 1;
    }

    constexpr inline int validateSurname()
    {
        static_assert(compileTimeStrlen(SURNAME) > 2, "You must input your surname!");
        return 2;
    }

    constexpr inline int validateStudentBookId()
    {
        static_assert(compileTimeStrlen(BOOK_ID) > 1, "You must input your student book id!");
        static_assert(compileTimeIsDigit(BOOK_ID), "You student book id should consist only digits, shouldn't it?!");
        return 3;
    }

    constexpr inline int validateMail()
    {
        static_assert(compileTimeStrlen(MAIL) > 3, "You must input your mail (preferred not gmail)!");
        return 4;
    }

    void validateStudentsInfo()
    {
        validateFirstname();
        validateSurname();
        validateStudentBookId();
        validateMail();
    }
} // namespace StudentsInfo
