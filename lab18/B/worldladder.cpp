#include "graph.hpp"
#include <fstream>
#include <unordered_set>
#include <queue>
#include <algorithm>

std::vector<std::string> findShortestPath(Graph& graph, const std::string& start, const std::string& end) {
    if (start == end) return {start};

    std::queue<std::string> q;
    std::unordered_map<std::string, std::string> parent;
    std::unordered_set<std::string> visited;

    q.push(start);
    visited.insert(start);
    parent[start] = "";

    while (!q.empty()) {
        std::string current = q.front();
        q.pop();

        std::vector<std::string> neighbors = graph.neighbours(current);
        for (const std::string& neighbor : neighbors) {
            if (visited.find(neighbor) == visited.end()) {
                visited.insert(neighbor);
                parent[neighbor] = current;
                q.push(neighbor);

                if (neighbor == end) {
                    std::vector<std::string> path;
                    std::string node = neighbor;
                    while (node != "") {
                        path.push_back(node);
                        node = parent[node];
                    }
                    reverse(path.begin(), path.end());
                    return path;
                }
            }
        }
    }

    return {};    
}

int main() {
    std::ifstream file("slowa.txt");
    std::unordered_set<std::string> words_set;
    std::string word;

    while (file >> word) {
        if (word.size() == 4) {
            transform(word.begin(), word.end(), word.begin(), ::tolower);
            words_set.insert(word);
        }
    }

    Graph graph;
    for (const auto& w : words_set) {
        graph.addVertex(w);
    }

    for (const auto& w : words_set) {
        for (int i = 0; i < 4; ++i) {
            std::string temp = w;
            for (char c = 'a'; c <= 'z'; ++c) {
                if (c == temp[i]) continue;
                temp[i] = c;
                if (words_set.count(temp)) {
                    graph.addEdge(w, temp);
                    graph.addEdge(temp, w);
                }
            }
        }
    }

    std::string start, end;
    std::cout << "Provide the starting word: ";
    std::cin >> start;
    std::cout << "Provide the finish word: ";
    std::cin >> end;

    transform(start.begin(), start.end(), start.begin(), ::tolower);
    transform(end.begin(), end.end(), end.begin(), ::tolower);

    if (words_set.find(start) == words_set.end() || words_set.find(end) == words_set.end()) {
        std::cerr << "Error: One of the words is not in the dictionary\n";
        return 1;
    }

    std::vector<std::string> path = findShortestPath(graph, start, end);

    if (path.empty()) {
        std::cout << "Path not found.\n";
    } else {
        std::cout << "Shortest path:\n";
        for (size_t i = 0; i < path.size(); ++i) {
            std::cout << path[i];
            if (i != path.size() - 1) std::cout << " -> ";
        }
        std::cout << "\n";
    }

    return 0;
}