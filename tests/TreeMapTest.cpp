#include <gtest/gtest.h>
#include "TreeMap.cpp"

class TreeMapTest : public ::testing::Test {
protected:
    TreeMap<int, std::string> map;

    void SetUp() override {
        // Optional setup code if needed
    }
};

TEST_F(TreeMapTest, InsertAndGet) {
    map.insert(1, "One");
    map.insert(2, "Two");

    ASSERT_EQ(map.get(1), "One");
    ASSERT_EQ(map.get(2), "Two");
    ASSERT_EQ(map.get(3), std::nullopt); // Key not found
}

TEST_F(TreeMapTest, Size) {
    ASSERT_EQ(map.size(), 0); // Initially empty

    map.insert(1, "One");
    ASSERT_EQ(map.size(), 1);

    map.insert(2, "Two");
    ASSERT_EQ(map.size(), 2);

    map.insert(1, "Update"); // Inserting with the same key should not increase size
    ASSERT_EQ(map.size(), 2);
}

TEST_F(TreeMapTest, Contains) {
    map.insert(1, "One");

    ASSERT_TRUE(map.contains(1));
    ASSERT_FALSE(map.contains(2)); // Key not found
}

TEST_F(TreeMapTest, ToVector) {
    map.insert(2, "Two");
    map.insert(1, "One");
    

    auto result = map.to_vector();
    ASSERT_EQ(result.size(), 2);
    ASSERT_EQ(result[0].first, 1);
    ASSERT_EQ(result[0].second, "One");
    ASSERT_EQ(result[1].first, 2);
    ASSERT_EQ(result[1].second, "Two");
}

TEST_F(TreeMapTest, IsEmpty) {
    ASSERT_TRUE(map.is_empty());

    map.insert(1, "One");
    ASSERT_FALSE(map.is_empty());

    map.clear();
    ASSERT_TRUE(map.is_empty());
}

TEST_F(TreeMapTest, Clear) {
    map.insert(1, "One");
    map.insert(2, "Two");
    
    ASSERT_EQ(map.size(), 2);
    map.clear();
    ASSERT_EQ(map.size(), 0);
}

TEST_F(TreeMapTest, MultipleInsertionsSameKey) {
    map.insert(1, "One");
    ASSERT_EQ(map.get(1), "One" );
    map.insert(1, "Uno"); // Should overwrite the previous value

    ASSERT_EQ(map.get(1), "Uno"); // Ensure that the value is the new one
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}