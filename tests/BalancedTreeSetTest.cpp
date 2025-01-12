
#include "TreeSet.cpp"
#include <gtest/gtest.h>

class BalancedTreeSetTest : public ::testing::Test {
protected:
    TreeSet<int> tree;

    void SetUp() override {
        // This will be called before each test
        tree = TreeSet<int>();
    }
};

TEST_F(BalancedTreeSetTest, InstantiateEmptyTree) {
    ASSERT_TRUE(tree.is_balanced());
}

TEST_F(BalancedTreeSetTest, SingleNodeTree) {
    tree.add(1);
    ASSERT_TRUE(tree.is_balanced());
}

TEST_F(BalancedTreeSetTest, TwoNodeTree) {
    tree.add(1);
    tree.add(2);
    ASSERT_TRUE(tree.is_balanced());
}

TEST_F(BalancedTreeSetTest, ThreeNodeTree) {
    tree.add(2);
    tree.add(1);
    tree.add(3);
    ASSERT_TRUE(tree.is_balanced());
}

TEST_F(BalancedTreeSetTest, LargerBalancedTree) {
    std::vector<int> values = {5, 2, 7, 1, 3, 6, 8};
    for (int value : values) {
        tree.add(value);
    }
    ASSERT_TRUE(tree.is_balanced());
}

TEST_F(BalancedTreeSetTest, InsertInAscendingOrder) {
    for (int i = 1; i <= 10; ++i) {
        tree.add(i);
        ASSERT_TRUE(tree.is_balanced()) << "Tree became unbalanced after inserting " << i;
    }
}

TEST_F(BalancedTreeSetTest, InsertInDescendingOrder) {
    for (int i = 10; i >= 1; --i) {
        tree.add(i);
        ASSERT_TRUE(tree.is_balanced()) << "Tree became unbalanced after inserting " << i;
    }
}

TEST_F(BalancedTreeSetTest, RandomInsertions) {
    std::vector<int> values = {8, 3, 10, 1, 6, 14, 4, 7, 13};
    for (int value : values) {
        tree.add(value);
        ASSERT_TRUE(tree.is_balanced()) << "Tree became unbalanced after inserting " << value;
    }
}

TEST_F(BalancedTreeSetTest, DuplicateInsertions) {
    std::vector<int> values = {5, 2, 7, 2, 5, 7, 1, 8};
    for (int value : values) {
        tree.add(value);
        ASSERT_TRUE(tree.is_balanced()) << "Tree became unbalanced after inserting " << value;
    }
}

TEST_F(BalancedTreeSetTest, LargeNumberOfInsertions) {
    for (int i = 0; i < 1000; ++i) {
        tree.add(rand() % 10000);
        if (i % 100 == 0) {  // Check balance every 100 insertions to save time
            ASSERT_TRUE(tree.is_balanced()) << "Tree became unbalanced after " << i + 1 << " insertions";
        }
    }
    ASSERT_TRUE(tree.is_balanced());
}