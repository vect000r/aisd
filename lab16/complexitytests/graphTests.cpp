#include "../graph.hpp"
#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <random>
#include <string>
#include <algorithm>

template<typename Func>
double measureTime(Func operation) {
    auto start = std::chrono::high_resolution_clock::now();
    operation();
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}

void saveResults(const std::string& filename, const std::vector<std::pair<int, double>>& results) {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const auto& result : results) {
            file << result.first << " " << result.second << std::endl;
        }
        file.close();
        std::cout << "Results saved to " << filename << std::endl;
    } else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
}

void populateGraphWithEdges(Graph& graph, int numVertices, double edgeDensity = 0.3) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> prob(0.0, 1.0);
    
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            if (i != j && prob(gen) < edgeDensity) {
                graph.addEdge(i, j);
            }
        }
    }
}

void testRemoveVertexAverage(const std::vector<int>& sizes) {
    std::vector<std::pair<int, double>> results;
    std::random_device rd;
    std::mt19937 gen(rd());

    std::cout << "Testing removeVertex - Average Case (random positions)" << std::endl;

    for (int n : sizes) {
        try {
            Graph graph(n);
            populateGraphWithEdges(graph, n);
            
            int verticesToRemove = std::max(1, n / 10);
            double totalTime = 0.0;
            
            for (int i = 0; i < verticesToRemove && graph.size() > 0; i++) {
                std::uniform_int_distribution<> distrib(0, graph.size() - 1);
                int vertexToRemove = distrib(gen);
                
                double time = measureTime([&]() {
                    graph.removeVertex(vertexToRemove);
                });
                
                totalTime += time;
            }
            
            double avgTimePerOperation = totalTime / verticesToRemove;
            results.push_back({n, avgTimePerOperation});
            
            std::cout << "Average case - Size: " << n << ", Avg time per removal: " 
                      << avgTimePerOperation << " μs" << std::endl;
                      
        } catch (const std::exception& e) {
            std::cerr << "Error during average case test with n=" << n << ": " << e.what() << std::endl;
            results.push_back({n, -1});
        }
    }
    
    saveResults("graphResults/removeVertex_average_results.txt", results);
}

void testRemoveVertexWorstCase(const std::vector<int>& sizes) {
    std::vector<std::pair<int, double>> results;

    std::cout << "Testing removeVertex - Worst Case (always remove vertex 0)" << std::endl;

    for (int n : sizes) {
        try {
            Graph graph(n);
            populateGraphWithEdges(graph, n);
            
            int verticesToRemove = std::max(1, n / 10);
            double totalTime = 0.0;
            
            for (int i = 0; i < verticesToRemove && graph.size() > 0; i++) {
                double time = measureTime([&]() {
                    graph.removeVertex(0);
                });
                
                totalTime += time;
            }
            
            double avgTimePerOperation = totalTime / verticesToRemove;
            results.push_back({n, avgTimePerOperation});
            
            std::cout << "Worst case - Size: " << n << ", Avg time per removal: " 
                      << avgTimePerOperation << " μs" << std::endl;
                      
        } catch (const std::exception& e) {
            std::cerr << "Error during worst case test with n=" << n << ": " << e.what() << std::endl;
            results.push_back({n, -1});
        }
    }
    
    saveResults("graphResults/removeVertex_worst_results.txt", results);
}

void testRemoveVertexBestCase(const std::vector<int>& sizes) {
    std::vector<std::pair<int, double>> results;

    std::cout << "Testing removeVertex - Best Case (always remove last vertex)" << std::endl;

    for (int n : sizes) {
        try {
            Graph graph(n);
            populateGraphWithEdges(graph, n);
            
            int verticesToRemove = std::max(1, n / 10);
            double totalTime = 0.0;
            
            for (int i = 0; i < verticesToRemove && graph.size() > 0; i++) {
                int lastVertex = graph.size() - 1;
                
                double time = measureTime([&]() {
                    graph.removeVertex(lastVertex);
                });
                
                totalTime += time;
            }
            
            double avgTimePerOperation = totalTime / verticesToRemove;
            results.push_back({n, avgTimePerOperation});
            
            std::cout << "Best case - Size: " << n << ", Avg time per removal: " 
                      << avgTimePerOperation << " μs" << std::endl;
                      
        } catch (const std::exception& e) {
            std::cerr << "Error during best case test with n=" << n << ": " << e.what() << std::endl;
            results.push_back({n, -1});
        }
    }
    
    saveResults("graphResults/removeVertex_best_results.txt", results);
}

void testSingleRemovalScaling(const std::vector<int>& sizes) {
    std::vector<std::pair<int, double>> results;

    std::cout << "Testing single removeVertex scaling with graph size" << std::endl;

    for (int n : sizes) {
        try {
            Graph graph(n);
            populateGraphWithEdges(graph, n);
            
            int vertexToRemove = n / 2;
            
            double time = measureTime([&]() {
                graph.removeVertex(vertexToRemove);
            });
            
            results.push_back({n, time});
            
            std::cout << "Single removal - Size: " << n << ", Time: " 
                      << time << " μs" << std::endl;
                      
        } catch (const std::exception& e) {
            std::cerr << "Error during single removal test with n=" << n << ": " << e.what() << std::endl;
            results.push_back({n, -1});
        }
    }
    
    saveResults("graphResults/removeVertex_single_scaling_results.txt", results);
}

int main() {
    std::cout << "Make sure the 'graphResults' directory exists before running tests." << std::endl;
    
    std::vector<int> sizes;
    for (int i = 50; i <= 1000; i += 50) {
        sizes.push_back(i);
    }

    try {
        std::cout << "\n=== RUNNING REMOVE VERTEX AVERAGE CASE TEST ===\n" << std::endl;
        testRemoveVertexAverage(sizes);
    } catch (...) {
        std::cerr << "Failed to complete average case tests" << std::endl;
    }
    
    try {
        std::cout << "\n=== RUNNING REMOVE VERTEX WORST CASE TEST ===\n" << std::endl;
        testRemoveVertexWorstCase(sizes);
    } catch (...) {
        std::cerr << "Failed to complete worst case tests" << std::endl;
    }
    
    try {
        std::cout << "\n=== RUNNING REMOVE VERTEX BEST CASE TEST ===\n" << std::endl;
        testRemoveVertexBestCase(sizes);
    } catch (...) {
        std::cerr << "Failed to complete best case tests" << std::endl;
    }
    
    try {
        std::cout << "\n=== RUNNING SINGLE REMOVAL SCALING TEST ===\n" << std::endl;
        testSingleRemovalScaling(sizes);
    } catch (...) {
        std::cerr << "Failed to complete single removal scaling tests" << std::endl;
    }

    return 0;
}