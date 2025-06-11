#include "graph.hpp"
#include <map>
#include <algorithm>
#include <set>

std::vector<int> getMovements() {
    return {
        12, 13, 14,
        21, 23, 24,
        41, 42, 43,
        51, 52, 53, 54
    };
}

bool areConflicted(int movement1, int movement2) {
    int from1 = movement1 / 10;
    int to1 = movement1 % 10;

    int from2 = movement2 / 10;
    int to2 = movement2 % 10;

    if (from1 == 5 || from2 == 5) {
        if (from1 == 5 && from2 != 5) {
            return true;
        }
        if (from2 == 5 && from1 != 5) {
            return true;
        }
    }

    if (from1 == from2 && from1 != 5 && movement1 != movement2) {
        return true;
    }

    if (from1 == to2 && to1 == from2) {
        return true;
    }

    return false;
}

Graph buildGraph() {
    Graph conflictGraph(100);
    std::vector<int> movements = getMovements();

    for (const auto& movement : movements) {
        conflictGraph.addVertex(movement);
    }

    for (size_t i = 0; i < movements.size(); ++i) {
        for (size_t j = i + 1; j < movements.size(); ++j) {
            if (areConflicted(movements[i], movements[j])) {
                conflictGraph.addEdge(movements[i], movements[j]);
                conflictGraph.addEdge(movements[j], movements[i]);
            }
        }
    }

    return conflictGraph;
}

std::map<int, int> colorGraph(Graph& graph, const std::vector<int>& vertices) {
    std::map<int, int> colorMap;
    std::vector<int> sortedVertices = vertices;

    std::sort(sortedVertices.begin(), sortedVertices.end(), [&](int a, int b) { return graph.neighbours(a).size() > graph.neighbours(b).size(); });

    for (const auto& v : sortedVertices ) {
        std::set<int> usedColors;

        for (const auto& n : graph.neighbours(v)) {
            if (colorMap.find(n) != colorMap.end()) {
                usedColors.insert(colorMap[n]);
            }
        }

        int color = 0;
        while (usedColors.count(color)) color++;

        colorMap[v] = color;
    }

    return colorMap;
}

int main() {
    Graph conflictGraph = buildGraph();
    std::vector<int> movements = getMovements();

    std::map<int, int> colors = colorGraph(conflictGraph, movements);

    std::map<int, std::vector<int>> phases;
    for (const auto& m : movements) {
        phases[colors[m]].push_back(m);
    }

    std::cout << "Minimal number of phases:" << phases.size() << std::endl;

        for (const auto& phase : phases) {
        std::cout << "Phase: " << phase.first + 1 << ": ";
        for (const auto& m : phase.second) {
            std::cout << m << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}