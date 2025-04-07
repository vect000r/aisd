#include "../dictionarySimple.hpp"
#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <random>
#include <string>
#include <sys/stat.h>
#include <algorithm>    

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

// Function to generate a random string of specified length
std::string generateRandomString(int length, std::mt19937& gen) {
    std::string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    std::uniform_int_distribution<> distrib(0, chars.size() - 1);
    
    std::string result;
    result.reserve(length);
    for (int i = 0; i < length; i++) {
        result += chars[distrib(gen)];
    }
    return result;
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

// Test insert operation
void testInsert(const std::vector<int>& sizes, const std::string& resultDir) {
    std::vector<std::pair<int, double>> results;
    std::random_device rd;
    std::mt19937 gen(rd());
    
    for (int n : sizes) {
        // Create a new dictionary for each test
        dictionarySimple dict;
        std::vector<std::string> strings;
        
        // Generate n random strings (to avoid regenerating in the timed section)
        for (int i = 0; i < n; i++) {
            strings.push_back(generateRandomString(10, gen));
        }
        
        // Time the operation of inserting n strings
        double time = measureTime([&]() {
            for (int i = 0; i < n && !dict.isFull(); i++) {
                dict.insert(strings[i]);
            }
        });
        
        results.push_back({n, time});
        std::cout << "Insert test - Size: " << n << ", Time: " << time << " μs" << std::endl;
    }
    
    saveResults(resultDir + "/insert_results.txt", results);
}

// Test contains operation
void testContains(const std::vector<int>& sizes, const std::string& resultDir) {
    std::vector<std::pair<int, double>> results;
    std::random_device rd;
    std::mt19937 gen(rd());
    
    for (int n : sizes) {
        // Create a new dictionary for each test
        dictionarySimple dict;
        std::vector<std::string> stringsInDict;
        std::vector<std::string> stringsToSearch;
        
        // Insert n/2 strings into the dictionary
        for (int i = 0; i < n/2 && !dict.isFull(); i++) {
            std::string s = generateRandomString(10, gen);
            dict.insert(s);
            stringsInDict.push_back(s);
        }
        
        // Use half strings from the dictionary and half new strings
        for (int i = 0; i < n/2; i++) {
            if (i < stringsInDict.size()) {
                stringsToSearch.push_back(stringsInDict[i]);
            }
        }
        
        for (int i = stringsToSearch.size(); i < n; i++) {
            stringsToSearch.push_back(generateRandomString(10, gen));
        }
        
        // Time the operation of checking n strings
        double time = measureTime([&]() {
            bool dummy;
            for (const auto& s : stringsToSearch) {
                dummy = dict.contains(s);
            }
        });
        
        results.push_back({n, time});
        std::cout << "Contains test - Size: " << n << ", Time: " << time << " μs" << std::endl;
    }
    
    saveResults(resultDir + "/contains_results.txt", results);
}

// Test remove operation
void testRemove(const std::vector<int>& sizes, const std::string& resultDir) {
    std::vector<std::pair<int, double>> results;
    std::random_device rd;
    std::mt19937 gen(rd());
    
    for (int n : sizes) {
        // Create a new dictionary for each test
        dictionarySimple dict;
        std::vector<std::string> stringsInDict;
        
        // Insert n strings into the dictionary
        for (int i = 0; i < n && !dict.isFull(); i++) {
            std::string s = generateRandomString(10, gen);
            dict.insert(s);
            stringsInDict.push_back(s);
        }
        
        // Shuffle the strings to randomize removal order
        std::shuffle(stringsInDict.begin(), stringsInDict.end(), gen);
        
        // Time the operation of removing all strings
        double time = measureTime([&]() {
            for (const auto& s : stringsInDict) {
                dict.remove(s);
            }
        });
        
        results.push_back({n, time});
        std::cout << "Remove test - Size: " << n << ", Time: " << time << " μs" << std::endl;
    }
    
    saveResults(resultDir + "/remove_results.txt", results);
}

int main() {
    std::string resultDir = "dictionarySimpleResults";
    ensureDirectoryExists(resultDir);
    
    std::vector<int> sizes;
    for (int i = 100; i <= 1000; ++i) {
        sizes.push_back(i);
    }
    
    testInsert(sizes, resultDir);
    testContains(sizes, resultDir);
    testRemove(sizes, resultDir);
    
    return 0;
}