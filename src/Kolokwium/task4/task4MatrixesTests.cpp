//#include <cstring> // strlen()

#include <iostream>
#include <algorithm>

#include <gtest/gtest.h>
#include "task4Matrixes.h"


namespace
{
using namespace std;
using namespace ::testing;
} // namespace


struct DynamicMatrix
{
    template<size_t Rows, size_t Columns>
    DynamicMatrix(const int (&matrix)[Rows][Columns]): DynamicMatrix(Rows, Columns)
    {
        for (size_t r = 0; r < Rows; ++r)
        {
            for (size_t c=0; c < Columns; ++c)
            {
                m[r][c] = matrix[r][c];
            }
        }
    }
    DynamicMatrix(size_t Rows, size_t Columns): rows(Rows), columns(Columns)
    {
        m = new int*[rows];
        for (size_t r = 0; r < Rows; ++r)
        {
            m[r] = new int[columns]{};
        }
    }
    ~DynamicMatrix()
    {
        for (size_t r = 0; r < rows; ++r)
        {
            delete [] m[r];
        }
        delete [] m;
    }

    const size_t rows, columns;
    int **m;
};


struct Task4MatricesTester : public ::testing::Test
{
};

TEST_F(Task4MatricesTester, matrices2x2)
{
    constexpr size_t rowsColumns = 2;

    constexpr int a[][rowsColumns] =
    {
        {2, 5},
        {1, -2}
    };
    constexpr int b[][rowsColumns] =
    {
        {3, -1},
        {7,  4}
    };
    /// source of result: https://www.naukowiec.org/zadania/matematyka/mnozenie-macierzy-zadanie-1_1342.html
    constexpr const int expectedResult[][rowsColumns] =
    {
        { 41, 18},
        {-11, -9}
    };

    /// jest to po to aby uwtorzyc tablice dynamiczna ze statycznej:
    auto aa = DynamicMatrix{a};
    auto bb = DynamicMatrix{b};
    auto rresult = DynamicMatrix{rowsColumns, rowsColumns};

    int resultRows, resultColumns;

    ASSERT_TRUE(multiplyMatrixes(aa.m, rowsColumns, rowsColumns,
                                 bb.m, rowsColumns, rowsColumns,
                                 rresult.m, &resultRows, &resultColumns));
    ASSERT_EQ(rowsColumns, resultRows);
    ASSERT_EQ(rowsColumns, resultColumns);

    for (size_t r = 0; r < rowsColumns; ++r)
    {
        for (size_t c=0; c < rowsColumns; ++c)
        {
            EXPECT_EQ(expectedResult[r][c], rresult.m[r][c]) << "r=" << r << ", c=" << c;
        }
    }
}

TEST_F(Task4MatricesTester, matrices1x1)
{
    constexpr size_t rowsColumns = 1;

    constexpr int a[][rowsColumns] =
    {
        {2}
    };
    constexpr int b[][rowsColumns] =
    {
        {3}
    };
    constexpr const int expectedResult[][rowsColumns] =
    {
        {6}
    };

    /// jest to po to aby uwtorzyc tablice dynamiczna ze statycznej:
    auto aa = DynamicMatrix{a};
    auto bb = DynamicMatrix{b};
    auto rresult = DynamicMatrix{rowsColumns, rowsColumns};

    int resultRows, resultColumns;

    ASSERT_TRUE(multiplyMatrixes(aa.m, rowsColumns, rowsColumns,
                                 bb.m, rowsColumns, rowsColumns,
                                 rresult.m, &resultRows, &resultColumns));
    ASSERT_EQ(rowsColumns, resultRows);
    ASSERT_EQ(rowsColumns, resultColumns);

    EXPECT_EQ(expectedResult[0][0], rresult.m[0][0]);
}

TEST_F(Task4MatricesTester, matrix4x3And3x3)
{
    constexpr size_t  m1Rows = 4, columns = 3;

    constexpr int a[m1Rows][columns] =
    {
        {5,  -1, 0},
        {4,   9, 4},
        {-10, 0, 7},
        {1,   2, 3}
    };
    constexpr int b[columns][columns] =
    {
        {1, -5, 5},
        {6, -2, 1},
        {2, 13, -3}
    };
    /// source of result: https://www.naukowiec.org/zadania/matematyka/mnozenie-macierzy-zadanie-3_1344.html
    constexpr const int expectedResult[m1Rows][columns] =
    {
        {-1, -23, 24},
        {66, 14, 17},
        {4,  141, -71},
        {19, 30, -2}
    };

    /// jest to po to aby uwtorzyc tablice dynamiczna ze statycznej:
    auto aa = DynamicMatrix{a};
    auto bb = DynamicMatrix{b};
    auto rresult = DynamicMatrix{m1Rows, columns};

    int resultRows, resultColumns;

    ASSERT_TRUE(multiplyMatrixes(aa.m, m1Rows, columns,
                                 bb.m, columns, columns,
                                 rresult.m, &resultRows, &resultColumns));
    ASSERT_EQ(m1Rows, resultRows);
    ASSERT_EQ(columns, resultColumns);

    for (size_t r = 0; r < m1Rows; ++r)
    {
        for (size_t c=0; c < columns; ++c)
        {
            EXPECT_EQ(expectedResult[r][c], rresult.m[r][c]);
        }
    }
}

// TODO:
//TEST_F(Task4MatricesTester, matrices3x3)
//TEST_F(Task4MatricesTester, matricesWhichCan't be multiplied)
