#include "TreeSet.cpp"
#include <gtest/gtest.h>

TEST(TreeSetTest, InstantiateEmptyTree)
{
    TreeSet<int> s{};

    ASSERT_EQ(s.size(), 0);
}

TEST(TreeSetTest, InstantiateTreeWithComparator)
{
    // comparator that returns the opposite of the default comparator
    auto cmp = [](int a, int b) {
        if (a < b)
        {
            return 1;
        }
        else if (a > b)
        {
            return -1;
        }
        else
        {
            return 0;
        }
    };
    TreeSet<int> s(cmp);

    ASSERT_EQ(s.size(), 0);

    s.add(1);
    s.add(2);
    s.add(3);
    s.add(4);
    ASSERT_EQ(s.to_vector(), std::vector<int>({ 4, 3, 2, 1 }));
    ASSERT_EQ(s.min(), 4);
}

TEST(TreeSetTest, UnionTwo)
{
    TreeSet<int> s1({ 1, 2, 3, 4, 5 });
    TreeSet<int> s2({ 3, 4, 5, 6, 7 });
    TreeSet<int> s3 = s1 + s2;

    ASSERT_EQ(s3.size(), 7);
    ASSERT_EQ(s3.to_vector(), std::vector<int>({ 1, 2, 3, 4, 5, 6, 7 }));

    // union should not mutate original sets
    ASSERT_EQ(s1.size(), 5);
    ASSERT_EQ(s1.to_vector(), std::vector<int>({ 1, 2, 3, 4, 5 }));
    ASSERT_EQ(s2.size(), 5);
    ASSERT_EQ(s2.to_vector(), std::vector<int>({ 3, 4, 5, 6, 7 }));
}

TEST(TreeSetTest, Clear)
{
    TreeSet<int> s({ 1, 2, 3, 4, 5 });
    s.clear();

    ASSERT_EQ(s.size(), 0);
    ASSERT_EQ(s.to_vector(), std::vector<int>({}));
}

TEST(TreeSetTest, AddElements)
{
    TreeSet<int> s;
    s.add(3);
    s.add(1);
    s.add(4);
    s.add(2);

    ASSERT_EQ(s.size(), 4);
    ASSERT_EQ(s.to_vector(), std::vector<int>({ 1, 2, 3, 4 })); // Assuming default comparator
}

TEST(TreeSetTest, AddDuplicateElements)
{
    TreeSet<int> s;
    s.add(1);
    s.add(1); // Adding duplicate
    s.add(2);
    s.add(3);

    ASSERT_EQ(s.size(), 3);
    ASSERT_EQ(s.to_vector(), std::vector<int>({ 1, 2, 3 })); // Duplicates should be ignored
}

TEST(TreeSetTest, Contains)
{
    TreeSet<int> s({ 5, 3, 8 });
    ASSERT_TRUE(s.contains(5));
    ASSERT_TRUE(s.contains(3));
    ASSERT_FALSE(s.contains(1));
    ASSERT_FALSE(s.contains(9));
}

TEST(TreeSetTest, MinMax)
{
    TreeSet<int> s({ 10, 20, 5, 15 });

    ASSERT_EQ(s.min(), 5);
    ASSERT_EQ(s.max(), 20);
}

TEST(TreeSetTest, MinMaxWithSingleElement)
{
    TreeSet<int> s({ 42 });

    ASSERT_EQ(s.min(), 42);
    ASSERT_EQ(s.max(), 42);
}

TEST(TreeSetTest, MinMaxWithNegativeAndPositive)
{
    TreeSet<int> s({ -10, -20, 5, 3 });

    ASSERT_EQ(s.min(), -20);
    ASSERT_EQ(s.max(), 5);
}

TEST(TreeSetTest, AddingDuplicateElements)
{
    TreeSet<int> s;

    s.add(1);
    s.add(2);
    s.add(1); // Duplicate
    s.add(3);

    ASSERT_EQ(s.size(), 3);
    ASSERT_EQ(s.to_vector(), std::vector<int>({ 1, 2, 3 }));
}

TEST(TreeSetTest, UnionWithEmptySet)
{
    TreeSet<int> s1({ 1, 2, 3 });
    TreeSet<int> s2;

    TreeSet<int> s3 = s1 + s2;

    ASSERT_EQ(s3.size(), 3);
    ASSERT_EQ(s3.to_vector(), std::vector<int>({ 1, 2, 3 }));
}

TEST(TreeSetTest, IntersectionWithEmptySet)
{
    TreeSet<int> s1({ 1, 2, 3 });
    TreeSet<int> s2;

    TreeSet<int> s3 = s1 & s2;

    ASSERT_EQ(s3.size(), 0);
    ASSERT_EQ(s3.to_vector(), std::vector<int>({}));
}

TEST(TreeSetTest, IntersectionWithNoCommonElements)
{
    TreeSet<int> s1({ 1, 2, 3 });
    TreeSet<int> s2({ 4, 5, 6 });

    TreeSet<int> s3 = s1 & s2;

    ASSERT_EQ(s3.size(), 0);
    ASSERT_EQ(s3.to_vector(), std::vector<int>({}));
}

TEST(TreeSetTest, UnionWithCommonElements)
{
    TreeSet<int> s1({ 1, 2, 3 });
    TreeSet<int> s2({ 3, 4, 5 });

    TreeSet<int> s3 = s1 + s2;

    ASSERT_EQ(s3.size(), 5);
    ASSERT_EQ(s3.to_vector(), std::vector<int>({ 1, 2, 3, 4, 5 }));
}

TEST(TreeSetTest, ClearMethodAfterAdditions)
{
    TreeSet<int> s({ 1, 2, 3 });

    s.clear();

    ASSERT_EQ(s.size(), 0);
    ASSERT_TRUE(s.is_empty());
}

TEST(TreeSetTest, SizeAfterClear)
{
    TreeSet<int> s({ 10, 20, 30 });

    s.clear();
    s.add(40); // Adding after clear

    ASSERT_EQ(s.size(), 1);
    ASSERT_EQ(s.to_vector(), std::vector<int>({ 40 }));
}

TEST(TreeSetTest, UnionOfEmptySets)
{
    TreeSet<int> s1;
    TreeSet<int> s2;
    TreeSet<int> s3 = s1 + s2;

    ASSERT_EQ(s3.size(), 0);
    ASSERT_EQ(s3.to_vector(), std::vector<int>({}));
}

TEST(TreeSetTest, Intersection)
{
    TreeSet<int> s1({ 1, 2, 3, 4, 5 });
    TreeSet<int> s2({ 4, 5, 6, 7 });
    TreeSet<int> s3 = s1 & s2;

    ASSERT_EQ(s3.size(), 2);
    ASSERT_EQ(s3.to_vector(), std::vector<int>({ 4, 5 }));
}

TEST(TreeSetTest, NotEqual)
{
    TreeSet<int> s1({ 1, 2, 3 });
    TreeSet<int> s2({ 1, 2, 3, 4 });

    ASSERT_TRUE(s1 != s2);
    ASSERT_FALSE(s1 != s1); // Should be equal to itself
}

TEST(TreeSetTest, Equal)
{
    TreeSet<int> s1({ 1, 2, 3 });
    TreeSet<int> s2({ 3, 2, 1 });

    ASSERT_TRUE(s1 == s2);
    ASSERT_FALSE(s1 == TreeSet<int>({ 1, 2 })); // Different sets
}

TEST(TreeSetTest, IsEmpty)
{
    TreeSet<int> s;
    ASSERT_TRUE(s.is_empty());
    
    s.add(1);
    ASSERT_FALSE(s.is_empty());
    
    s.clear();
    ASSERT_TRUE(s.is_empty());
}

TEST(TreeSetTest, MinOnEmptyTree)
{
    TreeSet<int> s;
    ASSERT_EQ(s.min(), std::nullopt); // Ensure min on empty returns std::nullopt
}

TEST(TreeSetTest, MaxOnEmptyTree)
{
    TreeSet<int> s;
    ASSERT_EQ(s.max(), std::nullopt); // Ensure max on empty returns std::nullopt
}

TEST(TreeSetTest, AddAfterClear)
{
    TreeSet<int> s({ 1, 2, 3 });
    s.clear();
    s.add(4);
    
    ASSERT_EQ(s.size(), 1);
    ASSERT_EQ(s.to_vector(), std::vector<int>({ 4 }));
}

TEST(TreeSetTest, AddingNegativeNumbers)
{
    TreeSet<int> s;
    s.add(-1);
    s.add(-2);
    s.add(-3);

    ASSERT_EQ(s.size(), 3);
    ASSERT_EQ(s.to_vector(), std::vector<int>({ -3, -2, -1 }));
}
