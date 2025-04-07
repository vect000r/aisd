#include "../setHashed.hpp"
#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <random>
#include <string>

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

// Test push
void testPush(const std::vector<int>& sizes) {
    std::vector<std::pair<int, double>> results;
    std::random_device rd;
    std::mt19937 gen(rd());

    for (size_t n : sizes) {
        SetHashed set(n);
        std::uniform_int_distribution<> distrib(0, n-1);
        
        // Time the operation of adding n random elements
        double time = measureTime([&]() {
            for (size_t i = 0; i < n; i++) {
                set.push(distrib(gen));
            }
        });
        
        results.push_back({n, time});
        std::cout << "Push test - Size: " << n << ", Time: " << time << " μs" << std::endl;
    }
    
    saveResults("setHashedResults/push_results.txt", results);
}

// Test pop
void testPop(const std::vector<int>& sizes) {
    std::vector<std::pair<int, double>> results;
    std::random_device rd;
    std::mt19937 gen(rd());

    for (size_t n : sizes) {
        SetHashed set(n);
        std::uniform_int_distribution<> distrib(0, n-1);
        
        // Pre-populate the set with random elements
        for (size_t i = 0; i < n; i++) {
            set.push(distrib(gen));
        }
        
        // Time the operation of removing n random elements
        double time = measureTime([&]() {
            for (size_t i = 0; i < n; i++) {
                set.pop(distrib(gen));
            }
        });
        
        results.push_back({n, time});
        std::cout << "Pop test - Size: " << n << ", Time: " << time << " μs" << std::endl;
    }
    
    saveResults("setHashedResults/pop_results.txt", results);
}

// Test contains
void testContains(const std::vector<int>& sizes) {
    std::vector<std::pair<int, double>> results;
    std::random_device rd;
    std::mt19937 gen(rd());

    for (size_t n : sizes) {
        SetHashed set(n);
        std::uniform_int_distribution<> distrib(0, n-1);
        
        // Pre-populate the set with random elements
        for (size_t i = 0; i < n/2; i++) {
            set.push(distrib(gen));
        }
        
        // Time the operation of checking n random elements
        double time = measureTime([&]() {
            for (size_t i = 0; i < n; i++) {
                set.contains(distrib(gen));
            }
        });
        
        results.push_back({n, time});
        std::cout << "Contains test - Size: " << n << ", Time: " << time << " μs" << std::endl;
    }
    
    saveResults("setHashedResults/contains_results.txt", results);
}

// Test unionWith
void testUnionWith(const std::vector<int>& sizes) {
    std::vector<std::pair<int, double>> results;
    std::random_device rd;
    std::mt19937 gen(rd());

    for (size_t n : sizes) {
        SetHashed set1(n);
        SetHashed set2(n);
        std::uniform_int_distribution<> distrib(0, n-1);
        
        // Pre-populate the sets with random elements
        for (size_t i = 0; i < n/2; i++) {
            set1.push(distrib(gen));
            set2.push(distrib(gen));
        }
        
        // Time the union operation
        double time = measureTime([&]() {
            SetHashed result = set1.unionWith(set2);
        });
        
        results.push_back({n, time});
        std::cout << "Union test - Size: " << n << ", Time: " << time << " μs" << std::endl;
    }
    
    saveResults("setHashedResults/union_results.txt", results);
}

// Test intersection
void testIntersection(const std::vector<int>& sizes) {
    std::vector<std::pair<int, double>> results;
    std::random_device rd;
    std::mt19937 gen(rd());

    for (size_t n : sizes) {
        SetHashed set1(n);
        SetHashed set2(n);
        std::uniform_int_distribution<> distrib(0, n-1);
        
        // Pre-populate the sets with random elements
        for (size_t i = 0; i < n/2; i++) {
            set1.push(distrib(gen));
            set2.push(distrib(gen));
        }
        
        // Time the intersection operation
        double time = measureTime([&]() {
            SetHashed result = set1.intersection(set2);
        });
        
        results.push_back({n, time});
        std::cout << "Intersection test - Size: " << n << ", Time: " << time << " μs" << std::endl;
    }
    
    saveResults("setHashedResults/intersection_results.txt", results);
}

// Test difference
void testDifference(const std::vector<int>& sizes) {
    std::vector<std::pair<int, double>> results;
    std::random_device rd;
    std::mt19937 gen(rd());

    for (size_t n : sizes) {
        SetHashed set1(n);
        SetHashed set2(n);
        std::uniform_int_distribution<> distrib(0, n-1);
        
        // Pre-populate the sets with random elements
        for (size_t i = 0; i < n/2; i++) {
            set1.push(distrib(gen));
            set2.push(distrib(gen));
        }
        
        // Time the difference operation
        double time = measureTime([&]() {
            SetHashed result = set1.difference(set2);
        });
        
        results.push_back({n, time});
        std::cout << "Difference test - Size: " << n << ", Time: " << time << " μs" << std::endl;
    }
    
    saveResults("setHashedResults/difference_results.txt", results);
}

// Test isIdentical
void testIsIdentical(const std::vector<int>& sizes) {
    std::vector<std::pair<int, double>> results;
    std::random_device rd;
    std::mt19937 gen(rd());

    for (size_t n : sizes) {
        SetHashed set1(n);
        SetHashed set2(n);
        std::uniform_int_distribution<> distrib(0, n-1);
        
        // Pre-populate the sets with random elements
        for (size_t i = 0; i < n/2; i++) {
            set1.push(distrib(gen));
            set2.push(distrib(gen));
        }
        
        // Time the isIdentical operation
        double time = measureTime([&]() {
            bool identical = set1.isIdentical(set2);
        });
        
        results.push_back({n, time});
        std::cout << "isIdentical test - Size: " << n << ", Time: " << time << " μs" << std::endl;
    }
    
    saveResults("setHashedResults/isIdentical_results.txt", results);
}

int main() {
    std::vector<int> sizes;
    for (int i = 100; i <= 1000; ++i) {
        sizes.push_back(i);
    }

    testPush(sizes);
    testPop(sizes);
    testContains(sizes);
    testUnionWith(sizes);
    testIntersection(sizes);
    testDifference(sizes);
    testIsIdentical(sizes);

    return 0;
}