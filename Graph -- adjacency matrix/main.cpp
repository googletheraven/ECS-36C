#include <iostream>
#include "GraphMatrix.hpp"
#include <cassert>

// Helper function to print test results
void printTestResult(const std::string& testName, bool passed) {
    std::cout << testName << ": " << (passed ? "PASSED" : "FAILED") << std::endl;
}

// Helper function to get textbook BFS graph
GraphMatrix<char> getTextbookGraphBFS() {
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
    
    return GraphMatrix<char>(adjList);
}

// Helper function to get textbook DFS graph
GraphMatrix<char> getTextbookGraphDFS() {
    std::map<char, std::set<char>> adjList;
    adjList['u'] = { 'v', 'x' };
    adjList['v'] = { 'y' };
    adjList['x'] = { 'v' };
    adjList['y'] = { 'x' };
    adjList['w'] = { 'y', 'z' };
    adjList['z'] = { 'z' };
    
    return GraphMatrix<char>(adjList);
}

void testBasicOperations() {
    std::cout << "\nTesting Basic Operations:" << std::endl;
    
    // Test empty graph
    GraphMatrix<int> g1;
    printTestResult("Empty Graph", g1.size() == 0);
    
    // Test vertex addition
    g1.addVertex(1);
    printTestResult("Add Vertex", g1.size() == 1);
    
    // Test edge addition and verification
    g1.addEdge(1, 2);  // Should automatically add vertex 2
    printTestResult("Add Edge", g1.size() == 2 && g1.hasEdge(1, 2));
    printTestResult("Directed Edge", !g1.hasEdge(2, 1));
    
    // Test neighbor retrieval
    auto neighbors = g1.getNeighbors(1);
    printTestResult("Get Neighbors", neighbors && neighbors->size() == 1 && 
                   neighbors->find(2) != neighbors->end());
}

void testGraphConstruction() {
    std::cout << "\nTesting Graph Construction:" << std::endl;
    
    // Test construction from edges
    std::vector<std::pair<int, int>> edges = {{1, 2}, {1, 3}, {2, 3}};
    GraphMatrix<int> g1(edges);
    printTestResult("Construction from Edges", 
                   g1.size() == 3 && g1.hasEdge(1, 2) && g1.hasEdge(1, 3) && g1.hasEdge(2, 3));
    
    // Test construction from adjacency list
    std::map<int, std::set<int>> adjList = {
        {1, {2, 3}},
        {2, {3}},
        {3, {}}
    };
    GraphMatrix<int> g2(adjList);
    printTestResult("Construction from Adj List", 
                   g2.size() == 3 && g2.hasEdge(1, 2) && g2.hasEdge(1, 3) && g2.hasEdge(2, 3));
}

void testBFSTraversal() {
    std::cout << "\nTesting BFS Traversal:" << std::endl;
    
    // Test BFS on simple graph
    GraphMatrix<int> g1({{1, 2}, {1, 3}, {2, 3}});
    auto bfs1 = g1.BFS(1);
    printTestResult("Simple BFS", 
                   bfs1.size() == 3 && bfs1[0] == 1 && 
                   (bfs1[1] == 2 || bfs1[1] == 3));
    
    // Test BFS on disconnected graph
    GraphMatrix<int> g2({{1, 2}, {3, 4}});
    auto bfs2 = g2.BFS(1);
    printTestResult("Disconnected BFS", bfs2.size() == 2);
    
    // Test BFS on textbook graph
    auto g3 = getTextbookGraphBFS();
    auto bfs3 = g3.BFS('s');
    printTestResult("Textbook BFS", bfs3.size() == 9 && bfs3[0] == 's');
}

void testShortestPath() {
    std::cout << "\nTesting Shortest Path:" << std::endl;
    
    // Test basic shortest path
    GraphMatrix<int> g1({{1, 2}, {2, 3}, {1, 3}});
    printTestResult("Direct Path", g1.shortestPath(1, 3) == 1);
    
    // Test no path
    GraphMatrix<int> g2({{1, 2}, {3, 4}});
    printTestResult("No Path", g2.shortestPath(1, 4) == -1);
    
    // Test complex path
    GraphMatrix<int> g3({{1, 2}, {2, 3}, {3, 4}, {1, 4}});
    printTestResult("Complex Path", g3.shortestPath(1, 3) == 2);
}

void testDFSTraversal() {
    std::cout << "\nTesting DFS:" << std::endl;
    
    auto g = getTextbookGraphDFS();
    auto dfs = g.DFS();
    
    // Convert list to vector for easier comparison
    std::vector<char> dfsVec(dfs.begin(), dfs.end());
    
    // Check size
    printTestResult("DFS Size", dfsVec.size() == 6);
    
    // Check if 'w' comes before 'z' (as per textbook example)
    auto wPos = std::find(dfsVec.begin(), dfsVec.end(), 'w');
    auto zPos = std::find(dfsVec.begin(), dfsVec.end(), 'z');
    printTestResult("DFS Order", 
                   wPos != dfsVec.end() && zPos != dfsVec.end() && 
                   wPos < zPos);
}

int main() {
    testBasicOperations();
    testGraphConstruction();
    testBFSTraversal();
    testShortestPath();
    testDFSTraversal();
    
    return 0;
}