#include "graph.hpp"

int Graph::size() {
    return adj_list.size();
}

bool Graph::adjacent(const std::string& x, const std::string& y) {
    return adj_list.count(x) && adj_list[x].count(y);
}

std::vector<std::string> Graph::neighbours(const std::string& x) {
    std::vector<std::string> result;
    if (adj_list.count(x)) {
        for (const auto& pair : adj_list[x]) {
            result.push_back(pair.first);
        }
    }
    return result;
}

void Graph::addVertex(const std::string& x) {
    if (!adj_list.count(x)) {
        adj_list[x] = std::unordered_map<std::string, int>();
        vertex_values[x] = 0;
    }
}

void Graph::removeVertex(const std::string& x) {
    adj_list.erase(x);
    vertex_values.erase(x);
    
    // Remove edges pointing to this vertex
    for (auto& vertex : adj_list) {
        vertex.second.erase(x);
    }
}

void Graph::addEdge(const std::string& x, const std::string& y) {
    addVertex(x);
    addVertex(y);
    adj_list[x][y] = 1;
}

void Graph::removeEdge(const std::string& x, const std::string& y) {
    if (adj_list.count(x)) {
        adj_list[x].erase(y);
    }
}

int Graph::getVertexValue(const std::string& x) {
    return vertex_values.count(x) ? vertex_values[x] : 0;
}

void Graph::setVertexValue(const std::string& x, int v) {
    addVertex(x);
    vertex_values[x] = v;
}

int Graph::getEdgeValue(const std::string& x, const std::string& y) {
    return (adj_list.count(x) && adj_list[x].count(y)) ? adj_list[x][y] : 0;
}

void Graph::setEdgeValue(const std::string& x, const std::string& y, int v) {
    addVertex(x);
    addVertex(y);
    adj_list[x][y] = v;
}

void Graph::generateDotFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + filename);
    }
    
    file << "graph G {\n";
    
    for (const auto& vertex : adj_list) {
        for (const auto& edge : vertex.second) {
            if (edge.second != 0) {
                file << "    \"" << vertex.first << "\" -- \"" << edge.first << "\";\n";
            }
        }
    }
    
    file << "}\n";
    file.close();
}

std::vector<std::string> Graph::getVertices() const {
    std::vector<std::string> result;
    for (const auto& pair : adj_list) {
        result.push_back(pair.first);
    }
    return result;
}
