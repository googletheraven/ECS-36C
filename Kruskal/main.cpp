/* Simple Kruskal's Implementation
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <cassert>

class UnionFind {
private:
    std::unordered_map<int, int> parent;
    std::unordered_map<int, int> rank;

public:
    UnionFind(const std::vector<int>& vertices) {
        for (int v : vertices) {
            parent[v] = v;
            rank[v] = 0;
        }
    }
    
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    
    void union_sets(int x, int y) {
        int root_x = find(x);
        int root_y = find(y);
        
        if (root_x != root_y) {
            if (rank[root_x] < rank[root_y]) {
                std::swap(root_x, root_y);
            }
            parent[root_y] = root_x;
            if (rank[root_x] == rank[root_y]) {
                rank[root_x]++;
            }
        }
    }
};

struct Edge {
    int src, dest, weight;
    
    Edge(int s, int d, int w) : src(s), dest(d), weight(w) {}
    
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

std::vector<Edge> kruskalMST(std::vector<int>& vertices, std::vector<Edge>& edges, int& total_weight) {
    std::sort(edges.begin(), edges.end());
    
    UnionFind uf(vertices);
    std::vector<Edge> mst;
    total_weight = 0;
    
    for (const Edge& edge : edges) {
        if (uf.find(edge.src) != uf.find(edge.dest)) {
            uf.union_sets(edge.src, edge.dest);
            mst.push_back(edge);
            total_weight += edge.weight;
        }
    }
    
    return mst;
}

void printMST(const std::vector<Edge>& mst, int total_weight) {
    std::cout << "Edges in the Minimum Spanning Tree:" << std::endl;
    for (const Edge& edge : mst) {
        std::cout << edge.src << " -- " << edge.dest 
                 << " with weight " << edge.weight << std::endl;
    }
    std::cout << "Total MST weight: " << total_weight << std::endl;
    std::cout << "------------------------" << std::endl;
}

void runTestCase(const std::string& test_name, 
                std::vector<int>& vertices, 
                std::vector<Edge>& edges,
                int expected_weight) {
    std::cout << "Running Test Case: " << test_name << std::endl;
    int total_weight;
    std::vector<Edge> mst = kruskalMST(vertices, edges, total_weight);
    printMST(mst, total_weight);
    
    assert(total_weight == expected_weight && 
           "MST weight doesn't match expected weight!");
    std::cout << "Test passed! Expected weight: " << expected_weight 
              << ", Got: " << total_weight << std::endl << std::endl;
}

int main() {
    // Test Case 1: Basic graph (Original test case)
    {
        std::vector<int> vertices = {0, 1, 2, 3};
        std::vector<Edge> edges = {
            Edge(0, 1, 10),
            Edge(0, 2, 6),
            Edge(0, 3, 5),
            Edge(1, 3, 15),
            Edge(2, 3, 4)
        };
        runTestCase("Basic Graph", vertices, edges, 19);
    }

    // Test Case 2: Complete graph with 5 vertices
    {
        std::vector<int> vertices = {0, 1, 2, 3, 4};
        std::vector<Edge> edges = {
            Edge(0, 1, 2), Edge(0, 2, 3), Edge(0, 3, 6), Edge(0, 4, 5),
            Edge(1, 2, 4), Edge(1, 3, 7), Edge(1, 4, 1),
            Edge(2, 3, 5), Edge(2, 4, 8),
            Edge(3, 4, 9)
        };
        runTestCase("Complete Graph", vertices, edges, 11);
    }

    // Test Case 3: Linear graph (path)
    {
        std::vector<int> vertices = {0, 1, 2, 3};
        std::vector<Edge> edges = {
            Edge(0, 1, 1),
            Edge(1, 2, 2),
            Edge(2, 3, 3)
        };
        runTestCase("Linear Graph", vertices, edges, 6);
    }

    // Test Case 4: Graph with parallel edges (multiple edges between same vertices)
    {
        std::vector<int> vertices = {0, 1, 2};
        std::vector<Edge> edges = {
            Edge(0, 1, 5),
            Edge(0, 1, 2),  // Parallel edge with different weight
            Edge(1, 2, 3),
            Edge(1, 2, 1)   // Parallel edge with different weight
        };
        runTestCase("Graph with Parallel Edges", vertices, edges, 3);
    }

    // Test Case 5: Star-shaped graph
    {
        std::vector<int> vertices = {0, 1, 2, 3, 4};
        std::vector<Edge> edges = {
            Edge(0, 1, 1),
            Edge(0, 2, 2),
            Edge(0, 3, 3),
            Edge(0, 4, 4)
        };
        runTestCase("Star-shaped Graph", vertices, edges, 10);
    }

    return 0;
}
*/

/* Kruskal's with cycle
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <cassert>
#include <iomanip>
#include <queue>
#include <set>

// Edge class to represent graph edges
class Edge {
public:
    int src, dest, weight;
    
    Edge(int s, int d, int w) : src(s), dest(d), weight(w) {}
    
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

// UnionFind class for cycle detection
class UnionFind {
private:
    std::unordered_map<int, int> parent;
    std::unordered_map<int, int> rank;

public:
    UnionFind(const std::vector<int>& vertices) {
        for (int v : vertices) {
            parent[v] = v;
            rank[v] = 0;
        }
    }
    
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    
    void union_sets(int x, int y) {
        int root_x = find(x);
        int root_y = find(y);
        
        if (root_x != root_y) {
            if (rank[root_x] < rank[root_y]) {
                std::swap(root_x, root_y);
            }
            parent[root_y] = root_x;
            if (rank[root_x] == rank[root_y]) {
                rank[root_x]++;
            }
        }
    }
};

// Function to validate MST properties
bool validateMST(const std::vector<Edge>& mst, int num_vertices) {
    // Check if we have correct number of edges (V-1)
    if (mst.size() != num_vertices - 1) {
        std::cout << "Invalid number of edges in MST!" << std::endl;
        return false;
    }

    // Check connectivity using BFS
    std::vector<std::vector<int>> adj(num_vertices);
    for (const Edge& edge : mst) {
        adj[edge.src].push_back(edge.dest);
        adj[edge.dest].push_back(edge.src);
    }

    std::vector<bool> visited(num_vertices, false);
    std::queue<int> q;
    q.push(0);
    visited[0] = true;
    int visited_count = 1;

    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int u : adj[v]) {
            if (!visited[u]) {
                visited[u] = true;
                visited_count++;
                q.push(u);
            }
        }
    }

    if (visited_count != num_vertices) {
        std::cout << "MST is not connected!" << std::endl;
        return false;
    }

    return true;
}

// Kruskal's Algorithm implementation
std::vector<Edge> kruskalMST(std::vector<int>& vertices, std::vector<Edge>& edges, int& total_weight) {
    // Sort edges by weight
    std::sort(edges.begin(), edges.end());
    
    UnionFind uf(vertices);
    std::vector<Edge> mst;
    total_weight = 0;
    
    for (const Edge& edge : edges) {
        if (uf.find(edge.src) != uf.find(edge.dest)) {
            uf.union_sets(edge.src, edge.dest);
            mst.push_back(edge);
            total_weight += edge.weight;
        }
    }
    
    // Validate the MST
    bool is_valid = validateMST(mst, vertices.size());
    if (!is_valid) {
        std::cout << "Warning: Generated MST is invalid!" << std::endl;
    }
    
    return mst;
}

// Pretty printing function for MST
void printMST(const std::vector<Edge>& mst, int total_weight, int vertices_count) {
    std::cout << "\nEdges in the Minimum Spanning Tree (" << vertices_count << " vertices):" << std::endl;
    std::cout << std::string(50, '-') << std::endl;
    std::cout << std::setw(4) << "From" << " | " 
              << std::setw(4) << "To" << " | " 
              << std::setw(6) << "Weight" << std::endl;
    std::cout << std::string(50, '-') << std::endl;
    
    for (const Edge& edge : mst) {
        std::cout << std::setw(4) << edge.src << " | " 
                 << std::setw(4) << edge.dest << " | " 
                 << std::setw(6) << edge.weight << std::endl;
    }
    std::cout << std::string(50, '-') << std::endl;
    std::cout << "Total MST weight: " << total_weight << std::endl;
    std::cout << std::string(50, '-') << std::endl;
}

// Test case runner
void runTestCase(const std::string& test_name, 
                std::vector<int>& vertices, 
                std::vector<Edge>& edges,
                int expected_weight) {
    std::cout << "\nRunning Test Case: " << test_name << std::endl;
    std::cout << "Number of vertices: " << vertices.size() << std::endl;
    std::cout << "Number of edges: " << edges.size() << std::endl;
    
    int total_weight;
    std::vector<Edge> mst = kruskalMST(vertices, edges, total_weight);
    printMST(mst, total_weight, vertices.size());
    
    assert(total_weight == expected_weight && 
           "MST weight doesn't match expected weight!");
    std::cout << "Test passed! Expected weight: " << expected_weight 
              << ", Got: " << total_weight << std::endl;
}

int main() {
    // Test Case 1: Complex Cycle Graph
    {
        std::vector<int> vertices = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        std::vector<Edge> edges = {
            // Outer cycle
            Edge(0, 1, 4), Edge(1, 2, 8), Edge(2, 3, 7), Edge(3, 4, 9),
            Edge(4, 5, 10), Edge(5, 6, 2), Edge(6, 7, 1), Edge(7, 8, 7),
            Edge(8, 9, 8), Edge(9, 0, 4),
            // Cross edges
            Edge(0, 5, 8), Edge(1, 6, 11), Edge(2, 7, 2),
            Edge(3, 8, 6), Edge(4, 9, 3)
        };
        runTestCase("Complex Cycle Graph", vertices, edges, 37);
    }

    // Test Case 2: Dense Graph
    {
        std::vector<int> vertices = {0, 1, 2, 3, 4, 5, 6, 7};
        std::vector<Edge> edges = {
            Edge(0, 1, 4), Edge(0, 2, 3), Edge(0, 3, 6), Edge(0, 4, 8),
            Edge(1, 2, 2), Edge(1, 3, 5), Edge(1, 5, 7), Edge(1, 6, 9),
            Edge(2, 3, 1), Edge(2, 4, 4), Edge(2, 5, 6), Edge(2, 7, 8),
            Edge(3, 4, 2), Edge(3, 6, 5), Edge(3, 7, 7),
            Edge(4, 5, 3), Edge(4, 6, 6), Edge(4, 7, 9),
            Edge(5, 6, 1), Edge(5, 7, 4),
            Edge(6, 7, 2)
        };
        runTestCase("Dense Graph", vertices, edges, 14);
    }

    // Test Case 3: Grid Graph (3x3)
    {
        std::vector<int> vertices = {0, 1, 2, 3, 4, 5, 6, 7, 8};
        std::vector<Edge> edges = {
            // Horizontal edges
            Edge(0, 1, 2), Edge(1, 2, 3),    // Top row
            Edge(3, 4, 1), Edge(4, 5, 4),    // Middle row
            Edge(6, 7, 5), Edge(7, 8, 2),    // Bottom row
            
            // Vertical edges
            Edge(0, 3, 3), Edge(3, 6, 6),    // Left column
            Edge(1, 4, 2), Edge(4, 7, 4),    // Middle column
            Edge(2, 5, 1), Edge(5, 8, 3),    // Right column
            
            // Diagonal edges
            Edge(0, 4, 4), Edge(1, 5, 5),
            Edge(3, 7, 2), Edge(4, 8, 6)
        };
        runTestCase("Grid Graph (3x3)", vertices, edges, 18);
    }

    // Test Case 4: Large Cyclic Graph
    {
        
        std::vector<int> vertices;
        std::vector<Edge> edges;
        
        // Create vertices 0-14
        for(int i = 0; i < 15; i++) {
            vertices.push_back(i);
        }
        
        // Create main cycle
        for(int i = 0; i < 14; i++) {
            edges.push_back(Edge(i, i+1, i+1));
        }
        edges.push_back(Edge(14, 0, 15));  // Complete the cycle
        
        // Add cross edges
        edges.push_back(Edge(0, 7, 4));
        edges.push_back(Edge(1, 8, 6));
        edges.push_back(Edge(2, 9, 3));
        edges.push_back(Edge(3, 10, 5));
        edges.push_back(Edge(4, 11, 7));
        edges.push_back(Edge(5, 12, 2));
        edges.push_back(Edge(6, 13, 8));
        edges.push_back(Edge(7, 14, 1));
        
        runTestCase("Large Cyclic Graph", vertices, edges, 57); 
    }

    return 0;
} */

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <cassert>
#include <iomanip>
#include <queue>
#include <set>
#include <limits>

class Edge {
public:
    int src, dest, weight;
    Edge(int s, int d, int w) : src(s), dest(d), weight(w) {}
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

class UnionFind {
private:
    std::unordered_map<int, int> parent;
    std::unordered_map<int, int> rank;

public:
    UnionFind(const std::vector<int>& vertices) {
        for (int v : vertices) {
            parent[v] = v;
            rank[v] = 0;
        }
    }
    
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    
    void union_sets(int x, int y) {
        int root_x = find(x);
        int root_y = find(y);
        
        if (root_x != root_y) {
            if (rank[root_x] < rank[root_y]) {
                std::swap(root_x, root_y);
            }
            parent[root_y] = root_x;
            if (rank[root_x] == rank[root_y]) {
                rank[root_x]++;
            }
        }
    }
};

// New: Edge Validation Functions
class GraphValidator {
public:
    static bool validateEdges(const std::vector<Edge>& edges, int numVertices) {
        // Check for self-loops
        for (const Edge& edge : edges) {
            if (edge.src == edge.dest) {
                std::cout << "Error: Self-loop detected at vertex " << edge.src << std::endl;
                return false;
            }
        }

        // Check for negative weights
        for (const Edge& edge : edges) {
            if (edge.weight < 0) {
                std::cout << "Error: Negative weight detected in edge " << edge.src 
                         << " -> " << edge.dest << std::endl;
                return false;
            }
        }

        // Check for vertex bounds
        for (const Edge& edge : edges) {
            if (edge.src < 0 || edge.src >= numVertices || 
                edge.dest < 0 || edge.dest >= numVertices) {
                std::cout << "Error: Vertex out of bounds in edge " << edge.src 
                         << " -> " << edge.dest << std::endl;
                return false;
            }
        }

        return true;
    }

    static bool validateMST(const std::vector<Edge>& mst, int numVertices) {
        // Check number of edges
        if (mst.size() != numVertices - 1) {
            std::cout << "Error: MST should have exactly " << numVertices - 1 
                     << " edges, but has " << mst.size() << std::endl;
            return false;
        }

        // Check connectivity using BFS
        std::vector<std::vector<int>> adj(numVertices);
        for (const Edge& edge : mst) {
            adj[edge.src].push_back(edge.dest);
            adj[edge.dest].push_back(edge.src);
        }

        std::vector<bool> visited(numVertices, false);
        std::queue<int> q;
        q.push(0);
        visited[0] = true;
        int visitedCount = 1;

        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int u : adj[v]) {
                if (!visited[u]) {
                    visited[u] = true;
                    visitedCount++;
                    q.push(u);
                }
            }
        }

        if (visitedCount != numVertices) {
            std::cout << "Error: MST is not fully connected. Only " << visitedCount 
                     << " of " << numVertices << " vertices are reachable." << std::endl;
            return false;
        }

        return true;
    }

    // New: Verify if the MST is truly minimal
    static bool verifyMinimality(const std::vector<Edge>& mst, const std::vector<Edge>& allEdges, 
                               int numVertices, int mstWeight) {
        // Try all possible edge combinations
        std::vector<bool> used(allEdges.size(), false);
        return !existsBetterSpanningTree(used, 0, 0, 0, mstWeight, allEdges, numVertices);
    }

private:
    static bool existsBetterSpanningTree(std::vector<bool>& used, int idx, int edgeCount, 
                                       int currentWeight, int bestWeight, 
                                       const std::vector<Edge>& edges, int numVertices) {
        if (currentWeight >= bestWeight) return false;
        if (edgeCount == numVertices - 1) {
            // Create a vector of vertices from 0 to numVertices-1
            std::vector<int> vertices;
            for (int i = 0; i < numVertices; i++) {
                vertices.push_back(i);
            }
            UnionFind uf(vertices);  // Fixed: Properly initialize UnionFind
            int components = numVertices;
            
            for (size_t i = 0; i < edges.size(); i++) {
                if (used[i]) {
                    if (uf.find(edges[i].src) != uf.find(edges[i].dest)) {
                        uf.union_sets(edges[i].src, edges[i].dest);
                        components--;
                    }
                }
            }
            return components == 1;
        }
        if (idx >= edges.size()) return false;

        // Don't use current edge
        bool result = existsBetterSpanningTree(used, idx + 1, edgeCount, 
                                             currentWeight, bestWeight, edges, numVertices);
        if (result) return true;

        // Use current edge
        used[idx] = true;
        result = existsBetterSpanningTree(used, idx + 1, edgeCount + 1, 
                                        currentWeight + edges[idx].weight, 
                                        bestWeight, edges, numVertices);
        used[idx] = false;
        
        return result;
    }

};

std::vector<Edge> kruskalMST(std::vector<int>& vertices, std::vector<Edge>& edges, int& total_weight) {
    if (!GraphValidator::validateEdges(edges, vertices.size())) {
        throw std::runtime_error("Invalid edge configuration");
    }

    std::sort(edges.begin(), edges.end());
    UnionFind uf(vertices);
    std::vector<Edge> mst;
    total_weight = 0;
    
    for (const Edge& edge : edges) {
        if (uf.find(edge.src) != uf.find(edge.dest)) {
            uf.union_sets(edge.src, edge.dest);
            mst.push_back(edge);
            total_weight += edge.weight;
        }
    }

    if (!GraphValidator::validateMST(mst, vertices.size())) {
        throw std::runtime_error("Invalid MST generated");
    }

    // Verify minimality for small graphs (optional, as it's exponential time)
    if (vertices.size() <= 10) {  // Only for small graphs due to complexity
        if (!GraphValidator::verifyMinimality(mst, edges, vertices.size(), total_weight)) {
            std::cout << "Warning: A better spanning tree might exist!" << std::endl;
        }
    }
    
    return mst;
}

void runTestCase(const std::string& test_name, 
                std::vector<int>& vertices, 
                std::vector<Edge>& edges,
                int expected_weight) {
    try {
        std::cout << "\nRunning Test Case: " << test_name << std::endl;
        std::cout << "Vertices: " << vertices.size() << ", Edges: " << edges.size() << std::endl;
        
        int total_weight;
        std::vector<Edge> mst = kruskalMST(vertices, edges, total_weight);
        
        std::cout << "\nMinimum Spanning Tree Edges:" << std::endl;
        std::cout << std::string(50, '-') << std::endl;
        std::cout << std::setw(4) << "From" << " | " 
                 << std::setw(4) << "To" << " | " 
                 << std::setw(6) << "Weight" << std::endl;
        std::cout << std::string(50, '-') << std::endl;
        
        for (const Edge& edge : mst) {
            std::cout << std::setw(4) << edge.src << " | " 
                     << std::setw(4) << edge.dest << " | " 
                     << std::setw(6) << edge.weight << std::endl;
        }
        
        std::cout << std::string(50, '-') << std::endl;
        std::cout << "Total MST weight: " << total_weight << std::endl;
        
        assert(total_weight == expected_weight && 
               "MST weight doesn't match expected weight!");
        std::cout << "Test passed! Expected weight: " << expected_weight 
                 << ", Got: " << total_weight << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "Test failed with error: " << e.what() << std::endl;
    }
}

int main() {
    // Previous test cases remain...

    // New Test Case: Binary Tree Structure
    {
       std::vector<int> vertices = {0, 1, 2, 3, 4, 5, 6};
        std::vector<Edge> edges = {
            Edge(0, 1, 2), Edge(0, 2, 3),  // Level 1
            Edge(1, 3, 4), Edge(1, 4, 1),  // Level 2 left
            Edge(2, 5, 5), Edge(2, 6, 2),  // Level 2 right
            // Additional cross edges
            Edge(3, 4, 6), Edge(5, 6, 4),
            Edge(1, 5, 7), Edge(2, 4, 3)
        };
        runTestCase("Binary Tree Structure", vertices, edges, 16); 
    }

    // New Test Case: Ring Structure
    {
        std::vector<int> vertices = {0, 1, 2, 3, 4};
        std::vector<Edge> edges = {
            Edge(0, 1, 1), Edge(1, 2, 2),
            Edge(2, 3, 3), Edge(3, 4, 4),
            Edge(4, 0, 5),
            // Diagonals
            Edge(0, 2, 6), Edge(1, 3, 7),
            Edge(2, 4, 8)
        };
        runTestCase("Ring Structure", vertices, edges, 10);
    }

    // New Test Case: Butterfly Structure
    {
        std::vector<int> vertices = {0, 1, 2, 3, 4, 5};
        std::vector<Edge> edges = {
            // Center connections
            Edge(2, 3, 1),
            // Left wing
            Edge(0, 2, 2), Edge(1, 2, 3),
            // Right wing
            Edge(3, 4, 2), Edge(3, 5, 3),
            // Cross connections
            Edge(0, 1, 4), Edge(4, 5, 4),
            Edge(0, 3, 5), Edge(1, 3, 5),
            Edge(2, 4, 6), Edge(2, 5, 6)
        };
        runTestCase("Butterfly Structure", vertices, edges, 11);
    }

    return 0;
}