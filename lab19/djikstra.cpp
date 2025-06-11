#include "graph.hpp"
#include <unordered_map>
#include <queue>
#include <limits>
#include <algorithm>

struct PathCosts {
    int cost;
    std::vector<std::string> path;
};

PathCosts dijkstra(Graph& graph, const std::string& start, const std::string& end) {
    std::unordered_map<std::string, int> distances;
    std::unordered_map<std::string, std::string> parents;
    std::priority_queue<std::pair<int, std::string>, std::vector<std::pair<int, std::string>>, std::greater<std::pair<int, std::string>>> queue;

    // Initialize distances
    auto vertices = graph.getVertices();
    for (const auto& vertex : vertices) {
        distances[vertex] = std::numeric_limits<int>::max();
    }
    distances[start] = 0;
    
    queue.push({0, start});
    
    while (!queue.empty()) {
        auto [dist, current] = queue.top();
        queue.pop();
        
        if (dist > distances[current]) continue;
        
        auto neighbors = graph.neighbours(current);
        for (const auto& neighbor : neighbors) {
            int edgeWeight = graph.getEdgeValue(current, neighbor);
            int newDist = distances[current] + edgeWeight;
            
            if (newDist < distances[neighbor]) {
                distances[neighbor] = newDist;
                parents[neighbor] = current;
                queue.push({newDist, neighbor});
            }
        }
    }
    
    // Reconstruct path
    std::vector<std::string> path;
    std::string current = end;
    
    if (distances[end] == std::numeric_limits<int>::max()) {
        return {-1, {}}; // No path found
    }
    
    while (!current.empty()) {
        path.push_back(current);
        current = parents.count(current) ? parents[current] : "";
    }
    
    std::reverse(path.begin(), path.end());
    
    return {distances[end], path};
}

void buildGraph(Graph& graph) {
    std::vector<std::string> vertices = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J"};

    for (const auto& vertex : vertices) {
        graph.addVertex(vertex);
    }

    std::vector<std::tuple<std::string, std::string, int>> edges = {
        // A ↔ B (bidirectional, weight 3)
        {"A", "B", 3},
        {"B", "A", 3},
        
        // B ↔ C (bidirectional, weight 2)
        {"B", "C", 2},
        {"C", "B", 2},
        
        // C ↔ H (bidirectional, weight 2)
        {"C", "H", 2},
        {"H", "C", 2},
        
        // D ↔ E (bidirectional, weight 1)
        {"D", "E", 1},
        {"E", "D", 1},
        
        // B ↔ D (bidirectional, weight 1)
        {"D", "B", 1},
        {"B", "D", 1},

        // E ↔ F (bidirectional, weight 1)
        {"E", "F", 1},
        {"F", "E", 1},
        
        // F ↔ G (bidirectional, weight 1)
        {"F", "G", 1},
        {"G", "F", 1},
        
        // G ↔ H (bidirectional, weight 1)
        {"G", "H", 1},
        {"H", "G", 1},
        
        // F ↔ H (bidirectional, weight 2)
        {"F", "H", 2},
        {"H", "F", 2},
        
        // H ↔ I (bidirectional, weight 2)
        {"H", "I", 2},
        {"I", "H", 2},
        
        // H ↔ J (bidirectional, weight 1)
        {"H", "J", 1},
        {"J", "H", 1}
    };

    for (const auto& [from, to, cost] : edges) {
        graph.addEdge(from, to);
        graph.setEdgeValue(from, to, cost);
    }
}

int main(int argc, char* argv[]) {
    Graph building;
    buildGraph(building);

    if (argc == 1) {
        std::cout << "Usage options:\n";
        std::cout << "  " << argv[0] << " <start> <end>     - Find path between two vertices\n";
        std::cout << "  " << argv[0] << " all A             - Find paths from all vertices to A\n";
        std::cout << "  " << argv[0] << " I D               - Find path from I to D\n";
        return 1;
    }

    if (argc == 3 && std::string(argv[1]) == "all" && std::string(argv[2]) == "A") {
        std::vector<std::string> vertices = {"B", "C", "D", "E", "F", "G", "H", "I", "J"};
        
        for (const auto& vertex : vertices) {
            PathCosts result = dijkstra(building, vertex, "A");
            
            std::cout << "From " << vertex << " to A:\n";
            if (result.cost == -1) {
                std::cout << "  No path found\n";
            } else {
                std::cout << "  Cost: " << result.cost << "\n";
                std::cout << "  Path: ";
                for (size_t i = 0; i < result.path.size(); ++i) {
                    std::cout << result.path[i];
                    if (i != result.path.size() - 1) std::cout << " -> ";
                }
                std::cout << "\n";
            }
            std::cout << "\n";
        }
        return 0;
    }

    if (argc == 3) {
        std::string start = argv[1];
        std::string end = argv[2];
        
        PathCosts result = dijkstra(building, start, end);

        if (result.cost == -1) {
            std::cout << "No path from " << start << " to " << end << std::endl;
        } else {
            std::cout << "Shortest time: " << result.cost << std::endl;
            std::cout << "Path: ";
            for (size_t i = 0; i < result.path.size(); ++i) {
                std::cout << result.path[i];
                if (i != result.path.size() - 1) std::cout << " -> ";
            }
            std::cout << std::endl;
        }
        return 0;
    }

    std::cerr << "Invalid arguments. Use " << argv[0] << " without arguments for usage help.\n";
    return 1;
}