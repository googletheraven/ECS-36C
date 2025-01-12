#include <gtest/gtest.h>
#include "Graph.cpp"

TEST(GraphTest, InstantiateEmptyGraph)
{
    Graph<int> g;
    ASSERT_EQ(g.size(), 0);
}

TEST(GraphTest, InstantiateFromVector)
{
    std::vector<std::pair<int, int>> edges({ {1, 2}, {1, 3}, {2, 3} });
    Graph<int> g(edges);
    ASSERT_EQ(g.size(), 3);
    ASSERT_TRUE(g.hasEdge(1, 2));
}

TEST(GraphTest, AddVertex)
{
    Graph<char> g;
    g.addVertex('a');

    ASSERT_EQ(g.size(), 1);
    ASSERT_FALSE(g.hasEdge('a', 'b'));
    ASSERT_EQ(g.getNeighbors('a').value().size(), 0);
}

TEST(GraphTest, AddVertex2)
{
    Graph<char> g;
    g.addVertex('a');

    ASSERT_EQ(g.size(), 1);
    ASSERT_FALSE(g.hasEdge('a', 'b'));
    ASSERT_EQ(g.getNeighbors('a').value().size(), 0);
}

TEST(GraphTest, InstantiateFromAdjList) 
{
    std::map<int, std::set<int>> adjList = {
        {1, {2, 3}},
        {2, {3}},
        {3, {}}
    };
    Graph<int> g(adjList);
    
    ASSERT_EQ(g.size(), 3);
    ASSERT_TRUE(g.hasEdge(1, 2));
    ASSERT_TRUE(g.hasEdge(1, 3));
    ASSERT_TRUE(g.hasEdge(2, 3));
    ASSERT_FALSE(g.hasEdge(3, 1));
}

TEST(GraphTest, AddAndVerifyEdges) 
{
    Graph<int> g;
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(1, 3);
    
    ASSERT_TRUE(g.hasEdge(1, 2));
    ASSERT_TRUE(g.hasEdge(2, 3));
    ASSERT_TRUE(g.hasEdge(1, 3));
    ASSERT_FALSE(g.hasEdge(3, 1));  // Verify directed nature
    ASSERT_FALSE(g.hasEdge(2, 1));  // Verify directed nature
    
    auto neighbors = g.getNeighbors(1);
    ASSERT_TRUE(neighbors.has_value());
    ASSERT_EQ(neighbors->size(), 2);
}

TEST(GraphTest, NonexistentVertexOperations) 
{
    Graph<char> g;
    g.addVertex('a');
    
    // Test getting neighbors of nonexistent vertex
    auto neighbors = g.getNeighbors('b');
    ASSERT_FALSE(neighbors.has_value());
    
    // Test edge with nonexistent vertices
    ASSERT_FALSE(g.hasEdge('b', 'c'));
}

TEST(GraphTest, MultipleOperations) 
{
    Graph<std::string> g;
    
    // Add vertices and edges incrementally
    g.addVertex("A");
    g.addVertex("B");
    g.addEdge("A", "B");
    g.addEdge("B", "C");  // Should automatically add C
    
    ASSERT_EQ(g.size(), 3);
    ASSERT_TRUE(g.hasEdge("A", "B"));
    ASSERT_TRUE(g.hasEdge("B", "C"));
    
    // Verify neighbors
    auto neighborsA = g.getNeighbors("A");
    ASSERT_TRUE(neighborsA.has_value());
    ASSERT_EQ(neighborsA->size(), 1);
    ASSERT_TRUE(neighborsA->find("B") != neighborsA->end());
    
    auto neighborsB = g.getNeighbors("B");
    ASSERT_TRUE(neighborsB.has_value());
    ASSERT_EQ(neighborsB->size(), 1);
    ASSERT_TRUE(neighborsB->find("C") != neighborsB->end());
}

TEST(GraphTest, DuplicateOperations) 
{
    Graph<int> g;
    
    // Add same vertex multiple times
    g.addVertex(1);
    g.addVertex(1);
    ASSERT_EQ(g.size(), 1);
    
    // Add same edge multiple times
    g.addEdge(1, 2);
    g.addEdge(1, 2);
    
    auto neighbors = g.getNeighbors(1);
    ASSERT_TRUE(neighbors.has_value());
    ASSERT_EQ(neighbors->size(), 1);  // Should only store unique edges
}

TEST(GraphTest, ComplexDataType) 
{
    // Test with a pair as vertex type
    Graph<std::pair<int, int>> g;
    g.addEdge({1, 1}, {2, 2});
    g.addEdge({2, 2}, {3, 3});
    
    ASSERT_EQ(g.size(), 3);
    ASSERT_TRUE(g.hasEdge({1, 1}, {2, 2}));
    ASSERT_TRUE(g.hasEdge({2, 2}, {3, 3}));
    ASSERT_FALSE(g.hasEdge({1, 1}, {3, 3}));
}