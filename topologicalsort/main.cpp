#include <vector>
#include <unordered_map>
#include <iostream>

enum class NodeState {
    UNVISITED,
    VISITING,
    VISITED
};

class Graph {
private:
    // Adjacency list representation using unordered_map for O(1) lookups
    std::unordered_map<int, std::vector<int>> adj_list;
    
    // Helper function for DFS
    bool dfs(int node, std::unordered_map<int, NodeState>& states, 
             std::vector<int>& sorted_nodes) {
        // Mark node as being processed in current path
        states[node] = NodeState::VISITING;
        
        // Process all neighbors
        for (int neighbor : adj_list[node]) {
            if (states[neighbor] == NodeState::UNVISITED) {
                // If DFS on neighbor detects cycle, propagate the cycle detection
                if (dfs(neighbor, states, sorted_nodes)) {
                    return true;
                }
            }
            else if (states[neighbor] == NodeState::VISITING) {
                // Found a back edge - cycle detected
                return true;
            }
            // If neighbor is VISITED, we can skip it
        }
        
        // Mark node as fully processed and add to result
        states[node] = NodeState::VISITED;
        sorted_nodes.push_back(node);
        return false;
    }

public:
    void addEdge(int from_node, int to_node) {
        adj_list[from_node].push_back(to_node);
        // Ensure both nodes are in the graph even if they have no outgoing edges
        if (adj_list.find(to_node) == adj_list.end()) {
            adj_list[to_node] = std::vector<int>();
        }
    }
    
    // Returns pair of (sorted nodes, has cycle)
    std::pair<std::vector<int>, bool> topologicalSort() {
        std::unordered_map<int, NodeState> states;
        std::vector<int> sorted_nodes;
        bool has_cycle = false;
        
        // Initialize all nodes as unvisited
        for (const auto& pair : adj_list) {
            states[pair.first] = NodeState::UNVISITED;
        }
        
        // Process all nodes to handle disconnected components
        for (const auto& pair : adj_list) {
            int node = pair.first;
            if (states[node] == NodeState::UNVISITED) {
                if (dfs(node, states, sorted_nodes)) {
                    has_cycle = true;
                    break;
                }
            }
        }
        
        // If cycle was detected, return empty vector and true
        if (has_cycle) {
            return {std::vector<int>(), true};
        }
        
        // Reverse the vector to get correct topological order
        std::reverse(sorted_nodes.begin(), sorted_nodes.end());
        return {sorted_nodes, false};
    }
};

// Test function
void testTopologicalSort() {
    // Test case 1: Simple DAG
    Graph g1;
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
    Graph g2;
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