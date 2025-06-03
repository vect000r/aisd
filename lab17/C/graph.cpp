#include "graph.hpp"
#include <algorithm>

int Graph::size() {
    return adj_list.size();
}

bool Graph::adjacent(int x, int y) {
    if (x < 0 || x >= adj_list.size() || y < 0 || y >= adj_list.size()) {
        return false;
    }
    return std::find(adj_list[x].begin(), adj_list[x].end(), y) != adj_list[x].end();
}

std::vector<int> Graph::neighbours(int x) {
    if (x < 0 || x >= adj_list.size()) {
        return std::vector<int>();
    }
    return adj_list[x];
}

void Graph::addVertex() {
    int new_size = adj_list.size() + 1;
    
    adj_list.push_back(std::vector<int>());
    vertex_values.push_back(0);
    
    edge_values.push_back(std::vector<int>(new_size, 0));
    for (int i = 0; i < new_size - 1; ++i) {
        edge_values[i].push_back(0);
    }
}

void Graph::removeVertex(int x) {
    if (x < 0 || x >= adj_list.size()) {
        return;
    }
    
    for (int i = 0; i < adj_list.size(); ++i) {
        adj_list[i].erase(std::remove(adj_list[i].begin(), adj_list[i].end(), x), adj_list[i].end());
    }
    
    adj_list[x].clear();
    vertex_values[x] = 0;
    
    for (int i = 0; i < edge_values.size(); ++i) {
        edge_values[x][i] = 0;
        edge_values[i][x] = 0;
    }
}

void Graph::addEdge(int x, int y) {
    if (x < 0 || x >= adj_list.size() || y < 0 || y >= adj_list.size()) {
        return;
    }
    
    if (std::find(adj_list[x].begin(), adj_list[x].end(), y) == adj_list[x].end()) {
        adj_list[x].push_back(y);
    }
}

void Graph::removeEdge(int x, int y) {
    if (x < 0 || x >= adj_list.size() || y < 0 || y >= adj_list.size()) {
        return;
    }
    
    adj_list[x].erase(std::remove(adj_list[x].begin(), adj_list[x].end(), y), adj_list[x].end());
}

int Graph::getVertexValue(int x) {
    if (x < 0 || x >= vertex_values.size()) {
        return 0;
    }
    return vertex_values[x];
}

void Graph::setVertexValue(int x, int v) {
    if (x < 0 || x >= vertex_values.size()) {
        return;
    }
    vertex_values[x] = v;
}

int Graph::getEdgeValue(int x, int y) {
    if (x < 0 || x >= edge_values.size() || y < 0 || y >= edge_values.size()) {
        return 0;
    }
    return edge_values[x][y];
}

void Graph::setEdgeValue(int x, int y, int v) {
    if (x < 0 || x >= edge_values.size() || y < 0 || y >= edge_values.size()) {
        return;
    }
    edge_values[x][y] = v;
}