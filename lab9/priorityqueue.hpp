#include <vector>
#include <algorithm>
#include <iostream>

template <typename T>
class MyPriorityQueue {
    std::vector<T> lst; 

public:
    // Default Constructor
    MyPriorityQueue(std::size_t s = 10) { lst.reserve(s); }

    // Destructor
    ~MyPriorityQueue() { lst.clear(); }

    // Copy Constructor
    MyPriorityQueue(const MyPriorityQueue& other) : lst(other.lst) {}

    // Move Constructor
    MyPriorityQueue(MyPriorityQueue&& other) noexcept : lst(std::move(other.lst)) {}

    // Copy assignment operator
    MyPriorityQueue& operator=(const MyPriorityQueue& other) {
        if (this != &other) {
            lst = other.lst;
        }
        return *this;
    }

    // Move assignment operator
    MyPriorityQueue& operator=(MyPriorityQueue&& other) noexcept {
        if (this != &other) {
            lst = std::move(other.lst);
        }
        return *this;
    }

    bool empty() const { return lst.empty(); }

    std::size_t size() const { return lst.size(); }

    // Push (lvalue)
    void push(const T& item) {
        lst.push_back(item);
        std::push_heap(lst.begin(), lst.end());
    }

    // Push (rvalue)
    void push(T&& item) {
        lst.push_back(std::move(item));
        std::push_heap(lst.begin(), lst.end());
    }

    // Return the top element (without deleting)
    T& top() {
        if (lst.empty()) {
            throw std::runtime_error("Priority queue is empty");
        }
        return lst.front();
    }

    // Delete the top element
    void pop() {
        if (lst.empty()) {
            throw std::runtime_error("Priority queue is empty");
        }
        std::pop_heap(lst.begin(), lst.end());
        lst.pop_back();
    }

    void clear() { lst.clear(); }

    void display() {
        for (const auto& item : lst) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }
};
