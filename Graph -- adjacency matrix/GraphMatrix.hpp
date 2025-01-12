#ifndef GRAPH_MATRIX_HPP
#define GRAPH_MATRIX_HPP

#include <vector>
#include <map>
#include <set>
#include <queue>
#include <list>
#include <optional>
#include <algorithm>
#include "GraphNode.hpp"

template <typename T>
class GraphMatrix {
private:
    std::vector<std::vector<bool>> _adjMatrix;
    std::map<T, int> _vertexToIndex;
    std::map<int, T> _indexToVertex;
    std::map<T, GraphNode<T>> _vertices;
    int _nextIndex = 0;

    void DFS_visit(const T& u, int& time, std::list<T>& result) {
        time++;
        _vertices[u].discovery_time = time;
        _vertices[u].color = Gray;
        
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

    int getIndex(const T& vertex) const {
        auto it = _vertexToIndex.find(vertex);
        return (it != _vertexToIndex.end()) ? it->second : -1;
    }

    void resizeMatrix() {
        size_t newSize = _vertexToIndex.size();
        _adjMatrix.resize(newSize, std::vector<bool>(newSize, false));
        for (auto& row : _adjMatrix) {
            row.resize(newSize, false);
        }
    }

public:
    GraphMatrix() = default;

    GraphMatrix(const std::vector<std::pair<T, T>>& edges) {
        for (const auto& edge : edges) {
            addVertex(edge.first);
            addVertex(edge.second);
            addEdge(edge.first, edge.second);
        }
    }

    GraphMatrix(const std::map<T, std::set<T>>& adjList) {
        for (const auto& [vertex, neighbors] : adjList) {
            addVertex(vertex);
            for (const auto& neighbor : neighbors) {
                addVertex(neighbor);
                addEdge(vertex, neighbor);
            }
        }
    }

    int size() const {
        return _vertexToIndex.size();
    }

    void addVertex(T vertex) {
        if (_vertexToIndex.find(vertex) == _vertexToIndex.end()) {
            _vertexToIndex[vertex] = _nextIndex;
            _indexToVertex[_nextIndex] = vertex;
            _vertices[vertex] = GraphNode<T>(vertex);
            _nextIndex++;
            resizeMatrix();
        }
    }

    void addEdge(T from, T to) {
        addVertex(from);
        addVertex(to);
        int fromIdx = _vertexToIndex[from];
        int toIdx = _vertexToIndex[to];
        _adjMatrix[fromIdx][toIdx] = true;
    }

    bool hasEdge(T from, T to) const {
        int fromIdx = getIndex(from);
        int toIdx = getIndex(to);
        if (fromIdx == -1 || toIdx == -1) return false;
        return _adjMatrix[fromIdx][toIdx];
    }

    std::optional<std::set<T>> getNeighbors(T vertex) const {
        int idx = getIndex(vertex);
        if (idx == -1) return std::nullopt;

        std::set<T> neighbors;
        for (int i = 0; i < _adjMatrix[idx].size(); i++) {
            if (_adjMatrix[idx][i]) {
                neighbors.insert(_indexToVertex.at(i));
            }
        }
        return neighbors;
    }

    GraphNode<T>& operator[](const T& vertex) {
        return _vertices[vertex];
    }

    const GraphNode<T>& operator[](const T& vertex) const {
        return _vertices.at(vertex);
    }

    std::vector<T> BFS(T start) {
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

    int shortestPath(T start, T end) {
        BFS(start);
        return _vertices[end].distance;
    }

    std::list<T> DFS() {
        std::list<T> result;
        
        for (auto& [vertex, node] : _vertices) {
            node.color = White;
            node.predecessor = std::nullopt;
            node.discovery_time = -1;
            node.finish_time = -1;
        }
        
        int time = 0;
        
        std::vector<T> vertices;
        for (const auto& [vertex, _] : _vertices) {
            vertices.push_back(vertex);
        }
        std::sort(vertices.begin(), vertices.end());
        
        for (const T& vertex : vertices) {
            if (_vertices[vertex].color == White) {
                DFS_visit(vertex, time, result);
            }
        }
        
        return result;
    }
};

#endif // GRAPH_MATRIX_HPP