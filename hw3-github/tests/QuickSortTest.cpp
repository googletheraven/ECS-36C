#include <gtest/gtest.h>
#include "qsort.cpp"

TEST(QuickSortTest, SortEmpty)
{
    std::vector<int> v;
    quick_sort(v.begin(), v.end(), std::less<int>());
    std::vector<int> expected;
    ASSERT_EQ(v, expected);
}

TEST(QuickSortTest, SortVectorWithOneElement)
{
    std::vector<int> v{1};
    quick_sort(v.begin(), v.end(), std::less<int>());
    std::vector<int> expected{1};
    ASSERT_EQ(v, expected);
}

// TODO: Add more tests here

TEST(QuickSortTest, SortVectorWithMultipleElements)
{
    std::vector<int> v{3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    quick_sort(v.begin(), v.end(), std::less<int>());
    std::vector<int> expected{1, 1, 2, 3, 3, 4, 5, 5, 5, 6, 9};
    ASSERT_EQ(v, expected);
}

TEST(QuickSortTest, SortVectorWithReverseOrder)
{
    std::vector<int> v{9, 8, 7, 6, 5, 4, 3, 2, 1};
    quick_sort(v.begin(), v.end(), std::less<int>());
    std::vector<int> expected{1, 2, 3, 4, 5, 6, 7, 8, 9};
    ASSERT_EQ(v, expected);
}

TEST(QuickSortTest, SortVectorWithIdenticalElements)
{
    std::vector<int> v{5, 5, 5, 5, 5};
    quick_sort(v.begin(), v.end(), std::less<int>());
    std::vector<int> expected{5, 5, 5, 5, 5};
    ASSERT_EQ(v, expected);
}

TEST(QuickSortTest, SortVectorWithNegativeNumbers)
{
    std::vector<int> v{-3, -1, -7, 5, 2, -6};
    quick_sort(v.begin(), v.end(), std::less<int>());
    std::vector<int> expected{-7, -6, -3, -1, 2, 5};
    ASSERT_EQ(v, expected);
}

TEST(QuickSortTest, SortVectorWithDuplicates)
{
    std::vector<int> v{4, 1, 4, 2, 2, 4, 3};
    quick_sort(v.begin(), v.end(), std::less<int>());
    std::vector<int> expected{1, 2, 2, 3, 4, 4, 4};
    ASSERT_EQ(v, expected);
}

TEST(QuickSortTest, SortVectorWithLargeNumbers)
{
    std::vector<int> v{1000000, 500000, 99999, 1234567};
    quick_sort(v.begin(), v.end(), std::less<int>());
    std::vector<int> expected{99999, 500000, 1000000, 1234567};
    ASSERT_EQ(v, expected);
}

TEST(QuickSortTest, SortVectorWithDescendingComparator)
{
    std::vector<int> v{1, 2, 3, 4, 5};
    quick_sort(v.begin(), v.end(), std::greater<int>());
    std::vector<int> expected{5, 4, 3, 2, 1};
    ASSERT_EQ(v, expected);
}