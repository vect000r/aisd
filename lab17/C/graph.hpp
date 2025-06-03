#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <vector>
#include <fstream>

class Graph {
    std::vector<std::vector<int>> adj_list;
    std::vector<int> vertex_values;
    std::vector<std::vector<int>> edge_values;
public:
    Graph(int n) : adj_list(n),
                vertex_values(n, 0),
                edge_values(n, std::vector<int>(n, 0)) {}

    int size();
    bool adjacent(int x, int y);
    std::vector<int> neighbours(int x);
    void addVertex();
    void removeVertex(int x);
    void addEdge(int x, int y);
    void removeEdge(int x, int y);
    int getVertexValue(int x);
    void setVertexValue(int x, int v);
    int getEdgeValue(int x, int y);
    void setEdgeValue(int x, int y, int v);
    void generateDotFile(const std::string filename) const;
};

#endif