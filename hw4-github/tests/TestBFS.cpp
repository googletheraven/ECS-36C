
#include <gtest/gtest.h>
#include "Graph.cpp"

using namespace std;

Graph<char> getTextbookGraphBFS() {
    std::map<char, std::set<char>> adjList;
    adjList['w'] = { 'r', 'v', 'x', 'z' };
    adjList['r'] = { 'w', 't', 's' };
    adjList['t'] = { 'r', 'u' };
    adjList['u'] = { 't', 's', 'y' };
    adjList['s'] = { 'r', 'u', 'v' };
    adjList['v'] = { 'w', 's', 'y' };
    adjList['x'] = { 'w', 'y', 'z' };
    adjList['y'] = { 'x', 'u', 'v' };
    adjList['z'] = { 'w', 'x' };

    Graph<char> g(adjList);
    return g;
}

TEST(BFSTest, InstantiateGraphFromEdges)
{
    Graph<int> g({ {1, 2}, {1, 3}, {2, 3} });
    ASSERT_EQ(g.size(), 3);

    std::vector<int> bfs = g.BFS(1);
    std::vector<int> expected{ 1, 2, 3 };

    ASSERT_EQ(bfs.size(), g.size());
    ASSERT_EQ(bfs, expected);
}

TEST(BFSTest, TextbookGraphTraversal) 
{
    Graph<char> g = getTextbookGraphBFS();
    std::vector<char> bfs = g.BFS('s');
    
    // Verify BFS properties instead of exact order:
    // 1. Start vertex should be first
    ASSERT_EQ(bfs[0], 's');
    
    // 2. First level vertices (direct neighbors of 's') should appear before others
    auto level1 = std::set<char>{'r', 'u', 'v'};
    auto found_level1 = std::vector<size_t>();
    for (char v : level1) {
        auto it = std::find(bfs.begin(), bfs.end(), v);
        ASSERT_NE(it, bfs.end()); // vertex should exist in BFS
        found_level1.push_back(it - bfs.begin());
    }
    
    // 3. Second level vertices should appear after first level
    auto level2 = std::set<char>{'w', 't', 'y'};
    auto found_level2 = std::vector<size_t>();
    for (char v : level2) {
        auto it = std::find(bfs.begin(), bfs.end(), v);
        ASSERT_NE(it, bfs.end());
        found_level2.push_back(it - bfs.begin());
    }
    
    // 4. Third level vertices should appear last
    auto level3 = std::set<char>{'x', 'z'};
    auto found_level3 = std::vector<size_t>();
    for (char v : level3) {
        auto it = std::find(bfs.begin(), bfs.end(), v);
        ASSERT_NE(it, bfs.end());
        found_level3.push_back(it - bfs.begin());
    }
    
    // Verify level ordering
    auto max_level1 = *std::max_element(found_level1.begin(), found_level1.end());
    auto min_level2 = *std::min_element(found_level2.begin(), found_level2.end());
    auto max_level2 = *std::max_element(found_level2.begin(), found_level2.end());
    auto min_level3 = *std::min_element(found_level3.begin(), found_level3.end());
    
    ASSERT_GT(min_level2, max_level1); // level 2 comes after level 1
    ASSERT_GT(min_level3, max_level2); // level 3 comes after level 2
    
    // 5. Verify total size
    ASSERT_EQ(bfs.size(), 9);
}

TEST(BFSTest, SingleNodeGraph) 
{
    Graph<int> g;
    g.addVertex(1);
    
    std::vector<int> bfs = g.BFS(1);
    ASSERT_EQ(bfs.size(), 1);
    ASSERT_EQ(bfs[0], 1);
}

TEST(BFSTest, DisconnectedGraph) 
{
    Graph<int> g({{1, 2}, {3, 4}});  // Two disconnected components
    
    std::vector<int> bfs = g.BFS(1);
    // Should only visit vertices reachable from 1
    std::vector<int> expected{1, 2};
    
    ASSERT_EQ(bfs, expected);
}

TEST(BFSTest, CyclicGraph) 
{
    Graph<int> g({{1, 2}, {2, 3}, {3, 1}});  // Cycle: 1->2->3->1
    
    std::vector<int> bfs = g.BFS(1);
    std::vector<int> expected{1, 2, 3};
    
    ASSERT_EQ(bfs, expected);
}

TEST(BFSTest, LinearGraph) 
{
    Graph<int> g({{1, 2}, {2, 3}, {3, 4}, {4, 5}});  // Linear path
    
    std::vector<int> bfs = g.BFS(1);
    std::vector<int> expected{1, 2, 3, 4, 5};
    
    ASSERT_EQ(bfs, expected);
}

TEST(BFSTest, ShortestPathBasic) 
{
    Graph<int> g({{1, 2}, {2, 3}, {1, 3}});
    
    ASSERT_EQ(g.shortestPath(1, 3), 1);  // Direct path from 1 to 3
    ASSERT_EQ(g.shortestPath(1, 2), 1);  // Direct path from 1 to 2
    ASSERT_EQ(g.shortestPath(2, 3), 1);  // Direct path from 2 to 3
}

TEST(BFSTest, ShortestPathTextbookGraph) 
{
    Graph<char> g = getTextbookGraphBFS();
    
    ASSERT_EQ(g.shortestPath('s', 'z'), 3);  // s->w->z or s->v->w->z
    ASSERT_EQ(g.shortestPath('s', 'x'), 3);  // s->w->x or s->v->w->x
    ASSERT_EQ(g.shortestPath('s', 'y'), 2);  // s->v->y or s->u->y
}

TEST(BFSTest, ShortestPathNoPath) 
{
    Graph<int> g({{1, 2}, {3, 4}});  // Disconnected components
    
    ASSERT_EQ(g.shortestPath(1, 4), -1);  // No path exists
    ASSERT_EQ(g.shortestPath(2, 3), -1);  // No path exists
}

TEST(BFSTest, ShortestPathSameVertex) 
{
    Graph<int> g({{1, 2}, {2, 3}});
    
    ASSERT_EQ(g.shortestPath(1, 1), 0);  // Distance to self is 0
    ASSERT_EQ(g.shortestPath(2, 2), 0);  // Distance to self is 0
}

TEST(BFSTest, ShortestPathComplexGraph) 
{
    Graph<int> g({
        {1, 2}, {1, 3}, {2, 4}, 
        {3, 4}, {4, 5}, {3, 5},
        {5, 6}, {4, 6}
    });
    
    ASSERT_EQ(g.shortestPath(1, 6), 3);  // 1->3->5->6 or 1->2->4->6
    ASSERT_EQ(g.shortestPath(1, 5), 2);  // 1->3->5
    ASSERT_EQ(g.shortestPath(2, 6), 2);  // 2->4->6
}