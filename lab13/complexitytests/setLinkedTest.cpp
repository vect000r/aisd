#include "../setLinked.hpp"
#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <random>
#include <string>
#include <sys/stat.h>

// Function to ensure directory exists
void ensureDirectoryExists(const std::string& dirName) {
    struct stat info;
    if (stat(dirName.c_str(), &info) != 0) {
        #ifdef _WIN32
        int result = mkdir(dirName.c_str());
        #else
        int result = mkdir(dirName.c_str(), 0777);
        #endif
        if (result == 0) {
            std::cout << "Directory created: " << dirName << std::endl;
        } else {
            std::cerr << "Failed to create directory: " << dirName << std::endl;
        }
    }
}

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
void testAdd(const std::vector<int>& sizes, const std::string& resultDir) {
    std::vector<std::pair<int, double>> results;
    std::random_device rd;
    std::mt19937 gen(rd());

    for (size_t n : sizes) {
        SetLinked set(n);
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
    
    saveResults(resultDir + "/add_results.txt", results);
}

// Test contains operation
void testContains(const std::vector<int>& sizes, const std::string& resultDir) {
    std::vector<std::pair<int, double>> results;
    std::random_device rd;
    std::mt19937 gen(rd());

    for (size_t n : sizes) {
        SetLinked set(n);
        std::uniform_int_distribution<> distrib(0, n-1);
        
        // Pre-populate the set with half the elements
        for (size_t i = 0; i < n/2; i++) {
            set.add(i);
        }
        
        // Time the operation of checking n random elements
        double time = measureTime([&]() {
            bool dummy;
            for (size_t i = 0; i < n; i++) {
                dummy = set.contains(distrib(gen));
            }
        });
        
        results.push_back({n, time});
        std::cout << "Contains test - Size: " << n << ", Time: " << time << " μs" << std::endl;
    }
    
    saveResults(resultDir + "/contains_results.txt", results);
}

// Test union operation
void testUnion(const std::vector<int>& sizes, const std::string& resultDir) {
    std::vector<std::pair<int, double>> results;
    std::random_device rd;
    std::mt19937 gen(rd());

    for (size_t n : sizes) {
        SetLinked set1(n);
        SetLinked set2(n);
        std::uniform_int_distribution<> distrib(0, n-1);
        
        // Pre-populate the sets with random elements
        for (size_t i = 0; i < n/2; i++) {
            set1.add(distrib(gen));
            set2.add(distrib(gen));
        }
        
        // Time the union operation
        double time = measureTime([&]() {
            SetLinked result = set1.unionWith(set2);
        });
        
        results.push_back({n, time});
        std::cout << "Union test - Size: " << n << ", Time: " << time << " μs" << std::endl;
    }
    
    saveResults(resultDir + "/union_results.txt", results);
}

// Test intersection operation
void testIntersection(const std::vector<int>& sizes, const std::string& resultDir) {
    std::vector<std::pair<int, double>> results;
    std::random_device rd;
    std::mt19937 gen(rd());

    for (size_t n : sizes) {
        SetLinked set1(n);
        SetLinked set2(n);
        std::uniform_int_distribution<> distrib(0, n-1);
        
        // Pre-populate the sets with random elements
        for (size_t i = 0; i < n/2; i++) {
            int val = distrib(gen);
            set1.add(val);
            set2.add(val); // Add some common elements
        }
        
        // Add some unique elements to each set
        for (size_t i = 0; i < n/4; i++) {
            set1.add(distrib(gen) + n);
            set2.add(distrib(gen) + n*2);
        }
        
        // Time the intersection operation
        double time = measureTime([&]() {
            SetLinked result = set1.intersection(set2);
        });
        
        results.push_back({n, time});
        std::cout << "Intersection test - Size: " << n << ", Time: " << time << " μs" << std::endl;
    }
    
    saveResults(resultDir + "/intersection_results.txt", results);
}

// Test isIdentical operation
void testIsIdentical(const std::vector<int>& sizes, const std::string& resultDir) {
    std::vector<std::pair<int, double>> results;

    for (size_t n : sizes) {
        SetLinked set1(n);
        SetLinked set2(n);
        
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
    
    saveResults(resultDir + "/isidentical_results.txt", results);
}

int main() {
    // Create results directory
    std::string resultDir = "setLinkedResults";
    ensureDirectoryExists(resultDir);
    
    // Define test sizes - using exponentially increasing values
    // For linked implementation, we might want to use smaller sizes for some tests
    std::vector<int> sizes;
    for (int i = 100; i <= 1000; ++i) {
        sizes.push_back(i);
    }
    
    
    // Run tests
    testAdd(sizes, resultDir);
    testContains(sizes, resultDir);
    testUnion(sizes, resultDir); // Using smaller sizes for potentially O(n²) operations
    testIntersection(sizes, resultDir);
    testIsIdentical(sizes, resultDir);
    
    return 0;
}