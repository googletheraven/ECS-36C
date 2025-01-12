#include <vector>
#include <iostream>

class Graph {
private:
    std::vector<std::vector<int>> adj_matrix;
    int V; // number of vertices

public:
    Graph(int vertices) : V(vertices) {
        // Initialize V x V adjacency matrix with zeros
        adj_matrix = std::vector<std::vector<int>>(V, std::vector<int>(V, 0));
    }

    void addEdge(int from, int to) {
        if (from < V && to < V) {
            adj_matrix[from][to] = 1;
        }
    }

    std::pair<std::vector<int>, bool> topologicalSort() {
        std::vector<int> sorted_nodes;
        std::vector<int> in_degree(V, 0);
        
        // Calculate in-degree for each vertex - O(V²)
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (adj_matrix[i][j] == 1) {
                    in_degree[j]++;
                }
            }
        }

        // Process vertices V times - O(V)
        for (int count = 0; count < V; count++) {
            // Find a vertex with in-degree 0 - O(V)
            int current = -1;
            for (int i = 0; i < V; i++) {
                if (in_degree[i] == 0) {
                    current = i;
                    in_degree[i] = -1;  // Mark as processed
                    break;
                }
            }

            // If no vertex with in-degree 0 found but not all vertices processed,
            // there must be a cycle
            if (current == -1) {
                return {std::vector<int>(), true};
            }

            sorted_nodes.push_back(current);

            // Reduce in-degree of adjacent vertices - O(V)
            for (int i = 0; i < V; i++) {
                if (adj_matrix[current][i] == 1) {
                    in_degree[i]--;
                }
            }
        }

        return {sorted_nodes, false};
    }
};

void testTopologicalSort() {
    // Test case 1: Simple DAG
    Graph g1(6);  // vertices 0 through 5
    g1.addEdge(5, 2);
    g1.addEdge(5, 0);
    g1.addEdge(4, 0);
    g1.addEdge(4, 1);
    g1.addEdge(2, 3);
    g1.addEdge(3, 1);

    auto [sorted_nodes1, has_cycle1] = g1.topologicalSort();
    std::cout << "Test 1 (DAG):\n";
    std::cout << "Has cycle: " << (has_cycle1 ? "true" : "false") << "\n";
    std::cout << "Topological order: ";
    for (int node : sorted_nodes1) {
        std::cout << node << " ";
    }
    std::cout << "\n\n";

    // Test case 2: Graph with cycle
    Graph g2(3);  // vertices 0 through 2
    g2.addEdge(0, 1);
    g2.addEdge(1, 2);
    g2.addEdge(2, 0);

    auto [sorted_nodes2, has_cycle2] = g2.topologicalSort();
    std::cout << "Test 2 (Cycle):\n";
    std::cout << "Has cycle: " << (has_cycle2 ? "true" : "false") << "\n";
    std::cout << "Topological order: ";
    for (int node : sorted_nodes2) {
        std::cout << node << " ";
    }
    std::cout << "\n";
}

int main() {
    testTopologicalSort();
    return 0;
}