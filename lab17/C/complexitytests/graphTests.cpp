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

void createHighDegreeVertex(Graph& graph, int vertex, int numVertices, double inDegreeRatio = 0.8) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> prob(0.0, 1.0);
    
    for (int i = 0; i < numVertices; i++) {
        if (i != vertex && prob(gen) < inDegreeRatio) {
            graph.addEdge(i, vertex);
        }
    }
}

void createLowDegreeVertex(Graph& graph, int vertex, int numVertices, double inDegreeRatio = 0.1) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> prob(0.0, 1.0);
    
    for (int i = 0; i < numVertices; i++) {
        if (i != vertex && prob(gen) < inDegreeRatio) {
            graph.addEdge(i, vertex);
        }
    }
}

void populateGraphWithRandomEdges(Graph& graph, int numVertices, double edgeDensity = 0.3) {
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

void testRemoveVertexWorstCase(const std::vector<int>& sizes) {
    std::vector<std::pair<int, double>> results;

    std::cout << "Testing removeVertex - Worst Case (high in-degree vertex)" << std::endl;

    for (int n : sizes) {
        try {
            std::vector<double> times;
            const int numTrials = 10;
            
            for (int trial = 0; trial < numTrials; trial++) {
                Graph graph(n);
                int targetVertex = n / 2;
                
                createHighDegreeVertex(graph, targetVertex, n, 0.9);
                populateGraphWithRandomEdges(graph, n, 0.2);
                
                double time = measureTime([&]() {
                    graph.removeVertex(targetVertex);
                });
                
                times.push_back(time);
            }
            
            double avgTime = 0.0;
            for (double t : times) {
                avgTime += t;
            }
            avgTime /= numTrials;
            
            results.push_back({n, avgTime});
            
            std::cout << "Worst case - Size: " << n << ", Avg time: " 
                      << avgTime << " μs" << std::endl;
                      
        } catch (const std::exception& e) {
            std::cerr << "Error during worst case test with n=" << n << ": " << e.what() << std::endl;
            results.push_back({n, -1});
        }
    }
    
    saveResults("graphResults/removeVertex_worst_results.txt", results);
}

void testRemoveVertexBestCase(const std::vector<int>& sizes) {
    std::vector<std::pair<int, double>> results;

    std::cout << "Testing removeVertex - Best Case (low in-degree vertex)" << std::endl;

    for (int n : sizes) {
        try {
            std::vector<double> times;
            const int numTrials = 10;
            
            for (int trial = 0; trial < numTrials; trial++) {
                Graph graph(n);
                int targetVertex = n / 2;
                
                createLowDegreeVertex(graph, targetVertex, n, 0.05);
                populateGraphWithRandomEdges(graph, n, 0.2);
                
                double time = measureTime([&]() {
                    graph.removeVertex(targetVertex);
                });
                
                times.push_back(time);
            }
            
            double avgTime = 0.0;
            for (double t : times) {
                avgTime += t;
            }
            avgTime /= numTrials;
            
            results.push_back({n, avgTime});
            
            std::cout << "Best case - Size: " << n << ", Avg time: " 
                      << avgTime << " μs" << std::endl;
                      
        } catch (const std::exception& e) {
            std::cerr << "Error during best case test with n=" << n << ": " << e.what() << std::endl;
            results.push_back({n, -1});
        }
    }
    
    saveResults("graphResults/removeVertex_best_results.txt", results);
}

void testRemoveVertexAverageCase(const std::vector<int>& sizes) {
    std::vector<std::pair<int, double>> results;

    std::cout << "Testing removeVertex - Average Case (random graphs)" << std::endl;

    for (int n : sizes) {
        try {
            std::vector<double> times;
            const int numTrials = 10;
            
            for (int trial = 0; trial < numTrials; trial++) {
                Graph graph(n);
                populateGraphWithRandomEdges(graph, n, 0.3);
                
                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_int_distribution<> distrib(0, n - 1);
                int targetVertex = distrib(gen);
                
                double time = measureTime([&]() {
                    graph.removeVertex(targetVertex);
                });
                
                times.push_back(time);
            }
            
            double avgTime = 0.0;
            for (double t : times) {
                avgTime += t;
            }
            avgTime /= numTrials;
            
            results.push_back({n, avgTime});
            
            std::cout << "Average case - Size: " << n << ", Avg time: " 
                      << avgTime << " μs" << std::endl;
                      
        } catch (const std::exception& e) {
            std::cerr << "Error during average case test with n=" << n << ": " << e.what() << std::endl;
            results.push_back({n, -1});
        }
    }
    
    saveResults("graphResults/removeVertex_average_results.txt", results);
}

void testRemoveVertexScalingWithEdges(const std::vector<int>& sizes) {
    std::vector<std::pair<int, double>> results;

    std::cout << "Testing removeVertex scaling with number of edges" << std::endl;

    for (int n : sizes) {
        try {
            std::vector<double> densityTimes;
            std::vector<double> densities = {0.1, 0.3, 0.5, 0.7, 0.9};
            
            for (double density : densities) {
                Graph graph(n);
                populateGraphWithRandomEdges(graph, n, density);
                
                int targetVertex = n / 2;
                createHighDegreeVertex(graph, targetVertex, n, density);
                
                double time = measureTime([&]() {
                    graph.removeVertex(targetVertex);
                });
                
                densityTimes.push_back(time);
            }
            
            double avgTime = 0.0;
            for (double t : densityTimes) {
                avgTime += t;
            }
            avgTime /= densityTimes.size();
            
            results.push_back({n, avgTime});
            
            std::cout << "Edge scaling - Size: " << n << ", Avg time across densities: " 
                      << avgTime << " μs" << std::endl;
                      
        } catch (const std::exception& e) {
            std::cerr << "Error during edge scaling test with n=" << n << ": " << e.what() << std::endl;
            results.push_back({n, -1});
        }
    }
    
    saveResults("graphResults/removeVertex_edge_scaling_results.txt", results);
}

void testRemoveVertexInDegreeImpact(const std::vector<int>& sizes) {
    std::vector<std::pair<int, double>> results;

    std::cout << "Testing removeVertex with varying in-degrees" << std::endl;

    for (int n : sizes) {
        try {
            std::vector<double> inDegreeTimes;
            std::vector<double> inDegreeRatios = {0.05, 0.2, 0.4, 0.6, 0.8, 0.95};
            
            for (double ratio : inDegreeRatios) {
                Graph graph(n);
                int targetVertex = n / 2;
                
                createHighDegreeVertex(graph, targetVertex, n, ratio);
                populateGraphWithRandomEdges(graph, n, 0.2);
                
                double time = measureTime([&]() {
                    graph.removeVertex(targetVertex);
                });
                
                inDegreeTimes.push_back(time);
            }
            
            double avgTime = 0.0;
            for (double t : inDegreeTimes) {
                avgTime += t;
            }
            avgTime /= inDegreeTimes.size();
            
            results.push_back({n, avgTime});
            
            std::cout << "In-degree impact - Size: " << n << ", Avg time across in-degrees: " 
                      << avgTime << " μs" << std::endl;
                      
        } catch (const std::exception& e) {
            std::cerr << "Error during in-degree test with n=" << n << ": " << e.what() << std::endl;
            results.push_back({n, -1});
        }
    }
    
    saveResults("graphResults/removeVertex_indegree_results.txt", results);
}

int main() {
    std::cout << "Make sure the 'graphResults' directory exists before running tests." << std::endl;
    
    std::vector<int> sizes;
    for (int i = 100; i <= 2000; i += 100) {
        sizes.push_back(i);
    }

    try {
        std::cout << "\n=== RUNNING REMOVE VERTEX BEST CASE TEST ===\n" << std::endl;
        testRemoveVertexBestCase(sizes);
    } catch (...) {
        std::cerr << "Failed to complete best case tests" << std::endl;
    }

    try {
        std::cout << "\n=== RUNNING REMOVE VERTEX AVERAGE CASE TEST ===\n" << std::endl;
        testRemoveVertexAverageCase(sizes);
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
        std::cout << "\n=== RUNNING EDGE SCALING TEST ===\n" << std::endl;
        testRemoveVertexScalingWithEdges(sizes);
    } catch (...) {
        std::cerr << "Failed to complete edge scaling tests" << std::endl;
    }
    
    try {
        std::cout << "\n=== RUNNING IN-DEGREE IMPACT TEST ===\n" << std::endl;
        testRemoveVertexInDegreeImpact(sizes);
    } catch (...) {
        std::cerr << "Failed to complete in-degree impact tests" << std::endl;
    }

    return 0;
}