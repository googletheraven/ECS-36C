#ifndef GRAPH_CPP
#define GRAPH_CPP

#include "Graph.hpp"
#include "GraphNode.hpp"
#include <queue>

template <typename T>
Graph<T>::Graph(const std::vector<std::pair<T, T>>& edges) {
    for (const auto& edge : edges) {
        addVertex(edge.first);
        addVertex(edge.second);
        addEdge(edge.first, edge.second);
    }
}

template <typename T>
Graph<T>::Graph(const std::map<T, std::set<T>>& adjList) : _adjList(adjList) {
    for (const auto& [vertex, neighbors] : adjList) {
        _vertices[vertex] = GraphNode<T>(vertex);
        for (const auto& neighbor : neighbors) {
            _vertices[neighbor] = GraphNode<T>(neighbor);
        }
    }
}

template <typename T>
int Graph<T>::size() const {
    return _vertices.size();
}

template <typename T>
void Graph<T>::addVertex(T vertex) {
    if (_adjList.find(vertex) == _adjList.end()) {
        _adjList[vertex] = std::set<T>();
        _vertices[vertex] = GraphNode<T>(vertex);
    }
}

template <typename T>
void Graph<T>::addEdge(T from, T to) {
    addVertex(from);
    addVertex(to);
    _adjList[from].insert(to);
}

template <typename T>
bool Graph<T>::hasEdge(T from, T to) const {
    auto it = _adjList.find(from);
    if (it == _adjList.end()) return false;
    return it->second.find(to) != it->second.end();
}

template <typename T>
std::optional<std::set<T>> Graph<T>::getNeighbors(T vertex) const {
    auto it = _adjList.find(vertex);
    if (it == _adjList.end()) return std::nullopt;
    return it->second;
}

template <typename T>
std::vector<T> Graph<T>::BFS(T start) {
    std::vector<T> result;
    
    for (auto& [vertex, node] : _vertices) {
        node.color = White;
        node.distance = -1;
        node.predecessor = std::nullopt;
    }
    
    _vertices[start].color = Gray;
    _vertices[start].distance = 0;
    
    std::queue<T> q;
    q.push(start);
    result.push_back(start);
    
    while (!q.empty()) {
        T u = q.front();
        q.pop();
        
        auto neighbors = getNeighbors(u);
        if (neighbors) {
            for (const T& v : *neighbors) {
                if (_vertices[v].color == White) {
                    _vertices[v].color = Gray;
                    _vertices[v].distance = _vertices[u].distance + 1;
                    _vertices[v].predecessor = u;
                    q.push(v);
                    result.push_back(v);
                }
            }
        }
        
        _vertices[u].color = Black;
    }
    
    return result;
}

template <typename T>
int Graph<T>::shortestPath(T start, T end) {
    BFS(start);
    return _vertices[end].distance;
}

template <typename T>
std::list<T> Graph<T>::DFS() {
    std::list<T> result;
    
    // Initialize all vertices
    for (auto& [vertex, node] : _vertices) {
        node.color = White;
        node.predecessor = std::nullopt;
        node.discovery_time = -1;
        node.finish_time = -1;
    }
    
    int time = 0;
    
    // Get vertices in sorted order to ensure consistent processing
    std::vector<T> vertices;
    for (const auto& [vertex, _] : _vertices) {
        vertices.push_back(vertex);
    }
    std::sort(vertices.begin(), vertices.end());
    
    // Process each unvisited vertex
    for (const T& vertex : vertices) {
        if (_vertices[vertex].color == White) {
            DFS_visit(vertex, time, result);
        }
    }
    
    return result;
}

template <typename T>
void Graph<T>::DFS_visit(const T& u, int& time, std::list<T>& result) {
    time++;
    _vertices[u].discovery_time = time;
    _vertices[u].color = Gray;
    
    // Get and process neighbors in sorted order
    auto neighbors = getNeighbors(u);
    if (neighbors) {
        std::vector<T> sortedNeighbors(neighbors->begin(), neighbors->end());
        std::sort(sortedNeighbors.begin(), sortedNeighbors.end());
        
        for (const T& v : sortedNeighbors) {
            if (_vertices[v].color == White) {
                _vertices[v].predecessor = u;
                DFS_visit(v, time, result);
            }
        }
    }
    
    _vertices[u].color = Black;
    time++;
    _vertices[u].finish_time = time;
    result.push_front(u);
}

#endif // GRAPH_CPP