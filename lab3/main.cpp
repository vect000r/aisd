#include "arraylist.hpp"


int main() {
    ArrayList<int> list1(20);

    // Test size() 
    assert(list1.size() == 0);
    // Test max_size() 
    assert(list1.max_size() == 20);
    // Test push_front() 
    list1.push_front(5);
    assert(list1.size() == 1);
    assert(list1.empty() == 0);
    // Test clear()
    list1.clear();
    assert(list1.size() == 0);
    assert(list1.empty() == 1);
    // Test push_back()
    list1.push_back(5);
    assert(list1.size() == 1);
    assert(list1.empty() == 0);
    // Test front()
    assert(list1.front() == 5);
    // Test back()
    assert(list1.back() == 5);
    // Test pop_front()
    list1.pop_front();
    assert(list1.size() == 0);
    assert(list1.empty() == 1);
    // Test pop_back()
    list1.push_back(5);
    list1.pop_back();
    assert(list1.size() == 0);
    assert(list1.empty() == 1);
    // Test full()
    for (int i = 0; i < 20; i++) {
        list1.push_back(i);
    }
    assert(list1.full() == 1);
    // Test reverse()
    list1.reverse();
    assert(list1.front() == 19);
    assert(list1.back() == 0);
    // Test sort()
    list1.sort();
    assert(list1.front() == 0);
    assert(list1.back() == 19);
    // Test copy constructor
    ArrayList<int> list2(list1);
    assert(list2.front() == 0);
    assert(list2.back() == 19);
    // Test move constructor
    ArrayList<int> list3(std::move(list1));
    assert(list3.front() == 0);
    assert(list3.back() == 19);
    // Test copy assignment operator
    ArrayList<int> list4;
    list4 = list2;
    assert(list4.front() == 0);
    assert(list4.back() == 19);
    // Test move assignment operator
    ArrayList<int> list5;
    list5 = std::move(list3);
    assert(list5.front() == 0);
    assert(list5.back() == 19);
    // Test display()
    list5.display();
    std::cout << std::endl;

    

    std::cout << "All tests passed!" << std::endl;

    return 0;
}