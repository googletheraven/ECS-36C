#include <gtest/gtest.h>
#include "msort.cpp"

TEST(MergeSortTest, SortEmpty)
{
    std::vector<int> v;
    merge_sort(v.begin(), v.end(), std::less<int>());
    std::vector<int> expected;
    ASSERT_EQ(v, expected);
}

TEST(MergeSortTest, SortVectorWithOneElement)
{
    std::vector<int> v{1};
    merge_sort(v.begin(), v.end(), std::less<int>());
    std::vector<int> expected{1};
    ASSERT_EQ(v, expected);
}

TEST(MergeSortTest, SortVectorWithMultipleElements)
{
    std::vector<int> v{3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    merge_sort(v.begin(), v.end(), std::less<int>());
    std::vector<int> expected{1, 1, 2, 3, 3, 4, 5, 5, 5, 6, 9};
    ASSERT_EQ(v, expected);
}

TEST(MergeSortTest, SortVectorWithReverseOrder)
{
    std::vector<int> v{9, 8, 7, 6, 5, 4, 3, 2, 1};
    merge_sort(v.begin(), v.end(), std::less<int>());
    std::vector<int> expected{1, 2, 3, 4, 5, 6, 7, 8, 9};
    ASSERT_EQ(v, expected);
}

TEST(MergeSortTest, SortVectorWithIdenticalElements)
{
    std::vector<int> v{5, 5, 5, 5, 5};
    merge_sort(v.begin(), v.end(), std::less<int>());
    std::vector<int> expected{5, 5, 5, 5, 5};
    ASSERT_EQ(v, expected);
}

TEST(MergeSortTest, SortVectorWithNegativeNumbers)
{
    std::vector<int> v{-3, -1, -7, 5, 2, -6};
    merge_sort(v.begin(), v.end(), std::less<int>());
    std::vector<int> expected{-7, -6, -3, -1, 2, 5};
    ASSERT_EQ(v, expected);
}

TEST(MergeSortTest, SortVectorWithDuplicates)
{
    std::vector<int> v{4, 1, 4, 2, 2, 4, 3};
    merge_sort(v.begin(), v.end(), std::less<int>());
    std::vector<int> expected{1, 2, 2, 3, 4, 4, 4};
    ASSERT_EQ(v, expected);
}

TEST(MergeSortTest, SortVectorWithLargeNumbers)
{
    std::vector<int> v{1000000, 500000, 99999, 1234567};
    merge_sort(v.begin(), v.end(), std::less<int>());
    std::vector<int> expected{99999, 500000, 1000000, 1234567};
    ASSERT_EQ(v, expected);
}

TEST(MergeSortTest, SortVectorWithDescendingComparator)
{
    std::vector<int> v{1, 2, 3, 4, 5};
    merge_sort(v.begin(), v.end(), std::greater<int>());
    std::vector<int> expected{5, 4, 3, 2, 1};
    ASSERT_EQ(v, expected);
}