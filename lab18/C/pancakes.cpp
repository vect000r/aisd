#include "graph.hpp"
#include <unordered_map>
#include <algorithm>

void dfs(const std::string& node, Graph& graph, std::unordered_map<std::string, bool>& visited, std::vector<std::string>& order) {
    visited[node] = true;
    
    for (const auto& neighbor : graph.neighbours(node)) {
        if (!visited[neighbor]) {
            dfs(neighbor, graph, visited, order);
        }
    }
    
    order.push_back(node);
}

std::vector<std::string> topologicalDfs(Graph& graph) {
    std::vector<std::string> vertices = { "3/4 cup milk", "1 egg", "1 Tbl oil", "1 cup mix", "heat syrup", "heat griddle", "pour 1/4 cup", "turn when bubbly", "eat" };
    std::unordered_map<std::string, bool> visited;
    std::vector<std::string> order;

    for (const auto& vertex : vertices) {
        if (!visited[vertex]) {
            dfs(vertex, graph, visited, order);
        }
    }

    std::reverse(order.begin(), order.end());
    
    return order;
}

int main() {
    Graph recipe;

    std::vector<std::string> nodes = { "3/4 cup milk", "1 egg", "1 Tbl oil", "1 cup mix", "heat syrup", "heat griddle", "pour 1/4 cup", "turn when bubbly", "eat" };

    for (const auto& node : nodes) {
        recipe.addVertex(node);
    }

    recipe.addEdge("3/4 cup milk", "1 cup mix");
    recipe.addEdge("1 egg", "1 cup mix");
    recipe.addEdge("1 Tbl oil", "1 cup mix");
    recipe.addEdge("1 cup mix", "heat syrup");
    recipe.addEdge("1 cup mix", "pour 1/4 cup");
    recipe.addEdge("heat griddle", "pour 1/4 cup");
    recipe.addEdge("pour 1/4 cup", "turn when bubbly");
    recipe.addEdge("turn when bubbly", "eat");
    recipe.addEdge("heat syrup", "eat");

    std::vector<std::string> stepsOrder = topologicalDfs(recipe);

    std::cout << "Order:\n";
    for (const auto& step : stepsOrder) {
        std::cout << "-> " << step << "\n";
    }

    return 0;
}