#include "arraylist.hpp"

int main() {
    ArrayList<int> list1(20); 
    list1.push_front(1);
    list1.push_front(2);
    list1.push_front(3);
    list1.push_front(4);
    list1.push_front(5);
    list1.push_front(6);
    list1.display();
    list1.sort();
    list1.display();
    list1.reverse();
    list1.display();
    list1.pop_back();
    list1.display();
    list1.pop_front();
    list1.display();
    return 0;
}