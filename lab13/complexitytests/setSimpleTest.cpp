#include "../setSimple.hpp"
#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <random>
#include <string>

// powtorzyc pomiar sto razy i wziąć średnią
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

// Test add operation
void testAdd(const std::vector<int>& sizes) {
    std::vector<std::pair<int, double>> results;
    std::random_device rd;
    std::mt19937 gen(rd());

    for (size_t n : sizes) {
        SetSimple set(n);
        std::uniform_int_distribution<> distrib(0, n-1);
        
        // Time the operation of adding n random elements
        double time = measureTime([&]() {
            for (size_t i = 0; i < n; i++) {
                set.add(distrib(gen));
            }
        });
        
        results.push_back({n, time});
        std::cout << "Add test - Size: " << n << ", Time: " << time << " μs" << std::endl;
    }
    
    saveResults("setSimpleResults/add_results.txt", results);
}

// Test contains operation
void testContains(const std::vector<int>& sizes) {
    std::vector<std::pair<int, double>> results;
    std::random_device rd;
    std::mt19937 gen(rd());

    for (size_t n : sizes) {
        SetSimple set(n);
        std::uniform_int_distribution<> distrib(0, n-1);
        
        // Pre-populate the set
        for (size_t i = 0; i < n/2; i++) {
            set.add(i);
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
    
    saveResults("setSimpleResults/contains_results.txt", results);
}

// Test union operation
void testUnion(const std::vector<int>& sizes) {
    std::vector<std::pair<int, double>> results;
    std::random_device rd;
    std::mt19937 gen(rd());

    for (size_t n : sizes) {
        SetSimple set1(n);
        SetSimple set2(n);
        std::uniform_int_distribution<> distrib(0, n-1);
        
        // Pre-populate the sets with random elements
        for (size_t i = 0; i < n/2; i++) {
            set1.add(distrib(gen));
            set2.add(distrib(gen));
        }
        
        // Time the union operation
        double time = measureTime([&]() {
            SetSimple result = set1.unionWith(set2);
        });
        
        results.push_back({n, time});
        std::cout << "Union test - Size: " << n << ", Time: " << time << " μs" << std::endl;
    }
    
    saveResults("setSimpleResults/union_results.txt", results);
}

// Test intersection operation
void testIntersection(const std::vector<int>& sizes) {
    std::vector<std::pair<int, double>> results;
    std::random_device rd;
    std::mt19937 gen(rd());

    for (size_t n : sizes) {
        SetSimple set1(n);
        SetSimple set2(n);
        std::uniform_int_distribution<> distrib(0, n-1);
        
        // Pre-populate the sets with random elements
        for (size_t i = 0; i < n/2; i++) {
            set1.add(distrib(gen));
            set2.add(distrib(gen));
        }
        
        // Time the intersection operation
        double time = measureTime([&]() {
            SetSimple result = set1.intersection(set2);
        });
        
        results.push_back({n, time});
        std::cout << "Intersection test - Size: " << n << ", Time: " << time << " μs" << std::endl;
    }
    
    saveResults("setSimpleResults/intersection_results.txt", results);
}

// Test isIdentical operation
void testIsIdentical(const std::vector<int>& sizes) {
    std::vector<std::pair<int, double>> results;

    for (size_t n : sizes) {
        SetSimple set1(n);
        SetSimple set2(n);
        
        // Make identical sets
        for (size_t i = 0; i < n/2; i++) {
            set1.add(i);
            set2.add(i);
        }
        
        // Time the isIdentical operation
        double time = measureTime([&]() {
            bool identical = set1.isIdentical(set2);
        });
        
        results.push_back({n, time});
        std::cout << "IsIdentical test - Size: " << n << ", Time: " << time << " μs" << std::endl;
    }
    
    saveResults("setSimpleResults/isidentical_results.txt", results);
}

int main() {
    // Define test sizes - using exponentially increasing values
    std::vector<int> sizes = {10, 100, 1000, 10000, 100000, 1000000};
    
    // Run tests
    testAdd(sizes);
    testContains(sizes);
    testUnion(sizes);
    testIntersection(sizes);
    testIsIdentical(sizes);
    
    return 0;
}