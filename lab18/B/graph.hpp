#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <unordered_map>

class Graph {
    std::unordered_map<std::string, std::unordered_map<std::string, int>> adj_list;
    std::unordered_map<std::string, int> vertex_values;
public:
    Graph() = default;

    int size();
    bool adjacent(const std::string& x, const std::string& y);
    std::vector<std::string> neighbours(const std::string& x);
    void addVertex(const std::string& x);
    void removeVertex(const std::string& x);
    void addEdge(const std::string& x, const std::string& y);
    void removeEdge(const std::string& x, const std::string& y);
    int getVertexValue(const std::string& x);
    void setVertexValue(const std::string& x, int v);
    int getEdgeValue(const std::string& x, const std::string& y);
    void setEdgeValue(const std::string& x, const std::string& y, int v);
    void generateDotFile(const std::string& filename) const;
    std::vector<std::string> getVertices() const;
};

#endif