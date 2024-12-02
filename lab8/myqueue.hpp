#ifndef MYQUEUE_HPP
#define MYQUEUE_HPP

#include <cassert>
#include <iostream>

template <typename T>
class MyQueue {
    T* tab;
    std::size_t msize; // największa możliwa liczba elementów plus jeden
    std::size_t head; // pierwszy do pobrania
    std::size_t tail; // pierwsza wolna pozycja
public:
    // default constructor
    MyQueue(std::size_t s=10) : msize(s+1), head(0), tail(0) {
        tab = new T[s+1];
        assert(tab != nullptr);
    }
    
    // destructor
    ~MyQueue() { delete [] tab; }
    
    // copy constructor
    MyQueue(const MyQueue& other) : msize(other.msize), head(other.head), tail(other.tail) {
        tab = new T[other.msize];
        for (std::size_t i = 0; i < other.msize; ++i) {
            tab[i] = other.tab[i];
        }
    }
    
    // move constructor
    MyQueue(MyQueue&& other) noexcept 
        : tab(other.tab), msize(other.msize), head(other.head), tail(other.tail) {
        other.tab = nullptr;
        other.msize = 1;
        other.head = other.tail = 0;
    }
    
    // copy assignment operator
    MyQueue& operator=(const MyQueue& other) {
        if (this != &other) {
            delete [] tab;
            msize = other.msize;
            head = other.head;
            tail = other.tail;
            tab = new T[other.msize];
            for (std::size_t i = 0; i < other.msize; ++i) {
                tab[i] = other.tab[i];
            }
        }
        return *this;
    }
    
    // move assignment operator
    MyQueue& operator=(MyQueue&& other) noexcept {
        if (this != &other) {
            delete [] tab;
            tab = other.tab;
            msize = other.msize;
            head = other.head;
            tail = other.tail;
            other.tab = nullptr;
            other.msize = 1;
            other.head = other.tail = 0;
        }
        return *this;
    }
    
    bool empty() const { return head == tail; }
    bool full() const { return (head + msize - 1) % msize == tail; }
    std::size_t size() const { return (tail - head + msize) % msize; }
    std::size_t max_size() const { return msize - 1; }
    
    // dodanie na koniec
    void push(const T& item) {
        assert(!full());
        tab[tail] = item;
        tail = (tail + 1) % msize;
    }
    
    void push(T&& item) {
        assert(!full());
        tab[tail] = std::move(item);
        tail = (tail + 1) % msize;
    }
    
    T& front() {
        assert(!empty());
        return tab[head];
    }
    
    T& back() {
        assert(!empty());
        return tab[(tail + msize - 1) % msize];
    }
    
    // usuwa początek
    void pop() {
        assert(!empty());
        head = (head + 1) % msize;
    }
    
    // czyszczenie listy z elementów
    void clear() {
        head = tail = 0;
    }
    
    void display() const {
        if (empty()) {
            std::cout << "Queue is empty\n";
            return;
        }
        std::size_t current = head;
        while (current != tail) {
            std::cout << '\t' << tab[current];
            current = (current + 1) % msize;
        }
        std::cout << '\n';
    }
};

#endif