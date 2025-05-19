#include "../priorityQueue.hpp"  // Heap-based implementation
#include "../priorityHeap.hpp"  // Set-based implementation (your original)
#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <random>
#include <string>
#include <algorithm>

// Function to measure time for an operation
template<typename Func>
double measureTime(Func operation) {
    auto start = std::chrono::high_resolution_clock::now();
    operation();
    auto end = std::chrono::high_resolution_clock::now();
    
    // Return time in microseconds
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}

// Function to save results to file
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

// Test removeMin for heap-based PriorityQueue
void testRemoveMinHeap(const std::vector<int>& sizes) {
    std::vector<std::pair<int, double>> results;
    std::random_device rd;
    std::mt19937 gen(rd());

    for (size_t n : sizes) {
        PriorityQueue pq(n);
        std::uniform_int_distribution<> distrib(0, n*10);  // Large range to ensure variety
        
        // Pre-populate the priority queue with random elements
        for (size_t i = 0; i < n; i++) {
            pq.add(distrib(gen));
        }
        
        // Time the operation of removing min element
        double time = 0.0;
        try {
            time = measureTime([&]() {
                // We'll test removeMin multiple times to get a more stable measurement
                size_t operations = std::min(n, size_t(100));  // At most 100 operations for large n
                for (size_t i = 0; i < operations && !pq.isEmpty(); i++) {
                    pq.removeMin();
                }
            });
            
            // If we did fewer than n operations, scale the time accordingly
            if (n > 100) {
                time = time * (n / 100.0);
            }
        }
        catch (const std::exception& e) {
            std::cerr << "Error during heap removeMin test with n=" << n << ": " << e.what() << std::endl;
            time = -1;  // Mark as error
        }
        
        results.push_back({n, time});
        std::cout << "Heap-based removeMin test - Size: " << n << ", Time: " << time << " μs" << std::endl;
    }
    
    saveResults("priorityQueueResults/heap_removeMin_results.txt", results);
}

// Test removeMin for set-based PriorityQueue
void testRemoveMinSet(const std::vector<int>& sizes) {
    std::vector<std::pair<int, double>> results;
    std::random_device rd;
    std::mt19937 gen(rd());

    for (size_t n : sizes) {
        PriorityQueue pq(n*2);  // Make capacity twice the number of elements to avoid range issues
        std::uniform_int_distribution<> distrib(0, n-1);  // Keep values within size range
        
        // Pre-populate the priority queue with random elements
        for (size_t i = 0; i < n; i++) {
            pq.add(distrib(gen));
        }
        
        // Time the operation of removing min element
        double time = 0.0;
        try {
            time = measureTime([&]() {
                // We'll test removeMin multiple times to get a more stable measurement
                size_t operations = std::min(n, size_t(100));  // At most 100 operations for large n
                for (size_t i = 0; i < operations && !pq.isEmpty(); i++) {
                    pq.removeMin();
                }
            });
            
            // If we did fewer than n operations, scale the time accordingly
            if (n > 100) {
                time = time * (n / 100.0);
            }
        }
        catch (const std::exception& e) {
            std::cerr << "Error during set removeMin test with n=" << n << ": " << e.what() << std::endl;
            time = -1;  // Mark as error
        }
        
        results.push_back({n, time});
        std::cout << "Set-based removeMin test - Size: " << n << ", Time: " << time << " μs" << std::endl;
    }
    
    saveResults("priorityQueueResults/set_removeMin_results.txt", results);
}

// Test worst-case scenario for heap-based (removing all elements in order)
void testRemoveMinHeapWorstCase(const std::vector<int>& sizes) {
    std::vector<std::pair<int, double>> results;

    for (size_t n : sizes) {
        PriorityQueue pq(n);
        
        // Populate with n elements in reverse order to create a complete heap
        for (size_t i = 0; i < n; i++) {
            pq.add(i);
        }
        
        // Time the operation of removing all elements
        double time = 0.0;
        try {
            time = measureTime([&]() {
                for (size_t i = 0; i < n && !pq.isEmpty(); i++) {
                    pq.removeMin();
                }
            });
        }
        catch (const std::exception& e) {
            std::cerr << "Error during heap worst-case test with n=" << n << ": " << e.what() << std::endl;
            time = -1;  // Mark as error
        }
        
        results.push_back({n, time});
        std::cout << "Heap-based removeMin worst case - Size: " << n << ", Time: " << time << " μs" << std::endl;
    }
    
    saveResults("priorityQueueResults/heap_removeMin_worst_results.txt", results);
}

// Test worst-case scenario for set-based (removing all elements from a full set)
void testRemoveMinSetWorstCase(const std::vector<int>& sizes) {
    std::vector<std::pair<int, double>> results;

    for (size_t n : sizes) {
        PriorityQueue pq(n*2);  // Double capacity to ensure we have enough space
        
        // Populate with n elements in a way that might create a worst-case
        for (size_t i = 0; i < n; i++) {
            pq.add(i);  // Add sequential elements to ensure we can find them
        }
        
        // Time the operation of removing all elements
        double time = 0.0;
        try {
            time = measureTime([&]() {
                for (size_t i = 0; i < n && !pq.isEmpty(); i++) {
                    pq.removeMin();
                }
            });
        }
        catch (const std::exception& e) {
            std::cerr << "Error during set worst-case test with n=" << n << ": " << e.what() << std::endl;
            time = -1;  // Mark as error
        }
        
        results.push_back({n, time});
        std::cout << "Set-based removeMin worst case - Size: " << n << ", Time: " << time << " μs" << std::endl;
    }
    
    saveResults("priorityQueueResults/set_removeMin_worst_results.txt", results);
}

int main() {
    // Create the results directory if it doesn't exist
    std::system("mkdir -p priorityQueueResults");
    
    // Define a range of sizes to test
    std::vector<int> sizes;
    for (int i = 100; i <= 5000; i += 100) {  // Testing from 100 to 5000 by steps of 100
        sizes.push_back(i);
    }

    // Run average-case tests
    testRemoveMinHeap(sizes);
    testRemoveMinSet(sizes);
    
    // Run worst-case tests
    testRemoveMinHeapWorstCase(sizes);
    testRemoveMinSetWorstCase(sizes);

    return 0;
}