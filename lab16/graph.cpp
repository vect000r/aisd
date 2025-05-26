#include "graph.hpp"

int Graph::size() {
    return adj_matrix.size();
}


bool Graph::adjacent(int x, int y) {
    return (adj_matrix[x][y] == 1) ? true : false;
}

std::vector<int> Graph::neighbours(int x) {
    std::vector<int> result;
    for (int i = 0; i < adj_matrix[x].size(); ++i) {
        if (adj_matrix[x][i] == 1) {
            result.push_back(i);
        }
    }
    return result;
}

void Graph::addVertex(int x) {
    int n = adj_matrix.size();
    adj_matrix.push_back(std::vector<int>(n + 1, 0));
    for (int i = 0; i < n; ++i) {
        adj_matrix[i].push_back(0);
    }
    
    // update the value vectors
    vertex_values.push_back(x);
    edge_values.push_back(std::vector<int>(n + 1, 0));
    for (int i = 0; i < n; ++i) {
        edge_values[i].push_back(0);
    }
}

void Graph::removeVertex(int x) {
    if (x < 0 || x >= adj_matrix.size()) return;
    adj_matrix.erase(adj_matrix.begin() + x);
    for (auto& row : adj_matrix) {
        row.erase(row.begin() + x);
    }
    
    // update the vectors
    vertex_values.erase(vertex_values.begin() + x);
    edge_values.erase(edge_values.begin() + x);
    for (auto& row : edge_values) {
        row.erase(row.begin() + x);
    }
}

void Graph::addEdge(int x, int y) {
    adj_matrix[x][y] = 1;
}

void Graph::removeEdge(int x, int y) {
    adj_matrix[x][y] = 0;
}

int Graph::getVertexValue(int x) {
    return vertex_values[x];
}

void Graph::setVertexValue(int x, int v) {
    vertex_values[x] = v;
}

int Graph::getEdgeValue(int x, int y) {
    return edge_values[x][y];
}

void Graph::setEdgeValue(int x, int y, int v) {
    edge_values[x][y] = v;
}