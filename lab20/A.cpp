#include "graph.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>

const int INF = std::numeric_limits<int>::max();


Graph buildGraphFromFile(const std::string& filename) {
    Graph graph;
    std::ifstream file(filename);
    std::string line;
    
    if (!file.is_open()) {
        std::cerr << "Nie można otworzyć pliku: " << filename << std::endl;
        return graph;
    }
    
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string city1, city2;
        int distance;
        
        if (iss >> city1 >> city2 >> distance) {
            graph.addVertex(city1);
            graph.addVertex(city2);
            graph.setEdgeValue(city1, city2, distance);
            graph.setEdgeValue(city2, city1, distance);
        }
    }
    
    file.close();
    return graph;
}

std::vector<std::vector<int>> floydWarshall(Graph& graph) {
    std::vector<std::vector<int>> distances;

    // Initialize distance matrix
    distances.resize(graph.size(), std::vector<int>(graph.size(), INF));
    
    auto vertices = graph.getVertices();
    
    // Fill initial distances
    for (size_t i = 0; i < vertices.size(); ++i) {
        for (size_t j = 0; j < vertices.size(); ++j) {
            if (i == j) {
                distances[i][j] = 0;
            } else {
                int edgeWeight = graph.getEdgeValue(vertices[i], vertices[j]);
                if (edgeWeight > 0) { // Check for positive edge weight (valid edge)
                    distances[i][j] = edgeWeight;
                }
            }
        }
    }
    
    // Floyd-Warshall algorithm
    for (size_t k = 0; k < vertices.size(); ++k) {
        for (size_t i = 0; i < vertices.size(); ++i) {
            for (size_t j = 0; j < vertices.size(); ++j) {
                if (distances[i][k] != INF && distances[k][j] != INF) {
                    distances[i][j] = std::min(distances[i][j], distances[i][k] + distances[k][j]);
                }
            }
        }
    }
    
    return distances;

}

int main() {
    Graph cityGraph = buildGraphFromFile("czasy");
    
    auto vertices = cityGraph.getVertices();
    std::cout << "Read " << vertices.size() << " cities:" << std::endl;
    
    for (const auto& city : vertices) {
        std::cout << "- " << city << std::endl;
    }
    
    std::cout << "\nExample: Distance between Warszawa and Białystok:\n" 
              << cityGraph.getEdgeValue("Warszawa", "Białystok") << " km" << std::endl;
    
    std::vector<std::vector<int>> result = floydWarshall(cityGraph);

    std::cout << "\nShortest distances between all pairs of cities:\n";
    for (size_t i = 0; i < vertices.size(); ++i) {
        for (size_t j = 0; j < vertices.size(); ++j) {
            if (result[i][j] == INF) {
                std::cout << vertices[i] << " -> " << vertices[j] << ": No path\n";
            } else {
                std::cout << vertices[i] << " -> " << vertices[j] << ": " << result[i][j] << " km\n";
            }
        }
    }

    return 0;
}