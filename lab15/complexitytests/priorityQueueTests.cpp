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

// Test removeMin for heap-based PriorityQueue with additional debugging
void testRemoveMinHeap(const std::vector<int>& sizes) {
    std::vector<std::pair<int, double>> results;
    std::random_device rd;
    std::mt19937 gen(rd());

    for (size_t n : sizes) {
        try {
           
            PriorityHeap pq(n);
            std::uniform_int_distribution<> distrib(0, n*10);  
           
            for (size_t i = 0; i < n; i++) {
                int value = distrib(gen);
                try {
                    pq.add(value);

                } catch (const std::exception& e) {
                    std::cerr << "Error during heap add at i=" << i << ": " << e.what() << std::endl;
                    throw; 
                }
            }
            
            double time = 0.0;
            time = measureTime([&]() {
               
                size_t operations = std::min(n, size_t(100));  
                for (size_t i = 0; i < operations; i++) {
                    pq.removeMin();
                }
            });
            
            // If we did fewer than n operations, scale the time accordingly
            if (n > 100) {
                time = time * (n / 100.0);
            }
            
            results.push_back({n, time});
            std::cout << "Heap-based removeMin test - Size: " << n << ", Time: " << time << " μs" << std::endl;
        }
        catch (const std::exception& e) {
            std::cerr << "Error during heap removeMin test with n=" << n << ": " << e.what() << std::endl;
            results.push_back({n, -1});  
        }
        catch (...) {
            std::cerr << "Unknown error during heap removeMin test with n=" << n << std::endl;
            results.push_back({n, -1});  
        }
    }
    
    saveResults("priorityQueueResults/heap_removeMin_results.txt", results);
}



// Test removeMin for set-based PriorityQueue with additional debugging
void testRemoveMinSet(const std::vector<int>& sizes) {
    std::vector<std::pair<int, double>> results;
    std::random_device rd;
    std::mt19937 gen(rd());

    for (size_t n : sizes) {
        try {
            if (n == 0) {
                results.push_back({0, 0});
                continue;
            }
            
            PriorityQueue pq(n*2);  

            std::uniform_int_distribution<> distrib(0, std::max(1, (int)n-1));  
            
            for (size_t i = 0; i < n; i++) {
                int value = distrib(gen);
                try {
                    pq.add(value);
                    if (i % 500 == 0) { // Log progress for large n
                        std::cout << "Added " << i << " elements so far" << std::endl;
                    }
                } catch (const std::exception& e) {
                    std::cerr << "Error during set add at i=" << i << ": " << e.what() << std::endl;
                    throw; // Re-throw to continue outer error handling
                }
            }
            
            double time = 0.0;
            time = measureTime([&]() {
                size_t operations = std::min(n, size_t(100));  
                for (size_t i = 0; i < operations; i++) {
                    pq.removeMin();
                }
            });
            
            // If we did fewer than n operations, scale the time accordingly
            if (n > 100) {
                time = time * (n / 100.0);
            }
            
            results.push_back({n, time});
            std::cout << "Set-based removeMin test - Size: " << n << ", Time: " << time << " μs" << std::endl;
        }
        catch (const std::exception& e) {
            std::cerr << "Error during set removeMin test with n=" << n << ": " << e.what() << std::endl;
            results.push_back({n, -1});  
        }
        catch (...) {
            std::cerr << "Unknown error during set removeMin test with n=" << n << std::endl;
            results.push_back({n, -1});  
        }
    }
                
    saveResults("priorityQueueResults/set_removeMin_results.txt", results);
}
                
// Test worst-case scenario for heap-based (removing all elements in order)
void testRemoveMinHeapWorstCase(const std::vector<int>& sizes) {
    std::vector<std::pair<int, double>> results;

    for (size_t n : sizes) {
        try {
            PriorityHeap pq(n);
            
            for (size_t i = 0; i < n; i++) {
                try {
                    pq.add(i);

                } catch (const std::exception& e) {
                    std::cerr << "Error during heap worst-case add at i=" << i << ": " << e.what() << std::endl;
                    throw; 
                }
            }
            
            double time = 0.0;
            time = measureTime([&]() {
                for (size_t i = 0; i < n; i++) {
                    pq.removeMin();
                }
            });
            
            results.push_back({n, time});
            std::cout << "Heap-based removeMin worst case - Size: " << n << ", Time: " << time << " μs" << std::endl;
        }
        catch (const std::exception& e) {
            std::cerr << "Error during heap worst-case test with n=" << n << ": " << e.what() << std::endl;
            results.push_back({n, -1});  
        }
        catch (...) {
            std::cerr << "Unknown error during heap worst-case test with n=" << n << std::endl;
            results.push_back({n, -1});  
        }
    }
    
    saveResults("priorityQueueResults/heap_removeMin_worst_results.txt", results);
}

// Test worst-case scenario for set-based (removing all elements from a full set) with debugging
void testRemoveMinSetWorstCase(const std::vector<int>& sizes) {
    std::vector<std::pair<int, double>> results;

    for (size_t n : sizes) {
        try {
            PriorityQueue pq(n*2);  
            
            for (size_t i = 0; i < n; i++) {
                try {
                    pq.add(i);  
                } catch (const std::exception& e) {
                    std::cerr << "Error during set worst-case add at i=" << i << ": " << e.what() << std::endl;
                    throw; 
                }
            }
            
            std::cout << "Testing removeMin operations on set worst-case" << std::endl;
            
            double time = 0.0;
            time = measureTime([&]() {
                for (size_t i = 0; i < n; i++) {
                    pq.removeMin();
                }
            });
            
            results.push_back({n, time});
            std::cout << "Set-based removeMin worst case - Size: " << n << ", Time: " << time << " μs" << std::endl;
        }
        catch (const std::exception& e) {
            std::cerr << "Error during set worst-case test with n=" << n << ": " << e.what() << std::endl;
            results.push_back({n, -1});  
        }
        catch (...) {
            std::cerr << "Unknown error during set worst-case test with n=" << n << std::endl;
            results.push_back({n, -1});  
        }
    }
    
    saveResults("priorityQueueResults/set_removeMin_worst_results.txt", results);
}



int main() {

    std::vector<int> sizes;
    for (int i = 100; i <= 5000; i += 100) {  
        sizes.push_back(i);
    }

    try {
        std::cout << "\n=== RUNNING HEAP AVERAGE CASE TEST ===\n" << std::endl;
        testRemoveMinHeap(sizes);
    } catch (...) {
        std::cerr << "Failed to complete heap average case tests" << std::endl;
    }
    
    try {
        std::cout << "\n=== RUNNING SET AVERAGE CASE TEST ===\n" << std::endl;
        testRemoveMinSet(sizes);
    } catch (...) {
        std::cerr << "Failed to complete set average case tests" << std::endl;
    }
    
    try {
        std::cout << "\n=== RUNNING HEAP WORST CASE TEST ===\n" << std::endl;
        testRemoveMinHeapWorstCase(sizes);
    } catch (...) {
        std::cerr << "Failed to complete heap worst case tests" << std::endl;
    }
    
    try {
        std::cout << "\n=== RUNNING SET WORST CASE TEST ===\n" << std::endl;
        testRemoveMinSetWorstCase(sizes);
    } catch (...) {
        std::cerr << "Failed to complete set worst case tests" << std::endl;
    }

    return 0;
}