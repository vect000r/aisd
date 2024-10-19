#include "arraylist.hpp"

template <typename T>
ArrayList<T>::ArrayList(const ArrayList& other) : msize(other.msize), last(other.last) {
    tab = new T[msize];
    assert(tab != nullptr);
    for (int i = 0; i < last; ++i) {
        tab[i] = other.tab[i];
    }
}

template <typename T>
ArrayList<T>::ArrayList(ArrayList&& other) : tab(other.tab), msize(other.msize), last(other.last) {
    other.tab = nullptr;
    other.msize = 0;
    other.last = 0;
}

template <typename T>
ArrayList<T>& ArrayList<T>::operator=(const ArrayList& other) {
    if (this != &other) {
        delete [] tab;
        msize = other.msize;
        last = other.last;
        tab = new T[msize];
        assert(tab != nullptr);
        for (int i = 0; i < last; ++i) {
            tab[i] = other.tab[i];
        }
    }
    return *this;   
}

template <typename T>
ArrayList<T>& ArrayList<T>::operator=(ArrayList&& other) {
    if (this != &other) {
        delete [] tab;
        tab = other.tab;
        msize = other.msize;
        last = other.last;
        other.tab = nullptr;
        other.msize = 0;
        other.last = 0;
    }
    return *this;
}

template <typename T>
void ArrayList<T>::push_front(const T& item) {
    if (full()) {
        std::cerr << "push_front: list is full\n";
        exit(1);
    } else {
        for (int i = last; i > 0; --i) {
            tab[i] = tab[i-1];
        }
        tab[0] = item;
        ++last;
    }
}

template <typename T>
void ArrayList<T>::push_back(const T& item) {
    if (full()) {
        std::cerr << "push_back: list is full\n";
        exit(1);
    } else {
        tab[last] = item;
        ++last;
    }
}

template <typename T>
T& ArrayList<T>::front() {
    if (empty()) {
        std::cerr << "front: list is empty\n";
        exit(1);
    } else {
        return tab[0];
    }
}

template <typename T>
T& ArrayList<T>::back() {
    if (empty()) {
        std::cerr << "back: list is empty\n";
        exit(1);
    } else {
        return tab[last-1];
    }
}

template <typename T>
void ArrayList<T>::pop_front() {
    if (empty()) {
        std::cerr << "pop_front: list is empty\n";
        exit(1);
    } else {
        for (int i = 0; i < last-1; ++i) {
            tab[i] = tab[i+1];
        }
        --last;
    }
}

template <typename T>
void ArrayList<T>::pop_back() {
    if (empty()) {
        std::cerr << "pop_back: list is empty\n";
        exit(1);
    } else {
        --last;
    }
}

template <typename T>
void ArrayList<T>::clear() {
    last = 0;
}

template <typename T>
void ArrayList<T>::display() {
    for (int i = 0; i < last; i++) {
        std::cout << tab[i] << " ";
    }
}

template <typename T>
void ArrayList<T>::reverse() {
    for (int i = 0; i < last/2; i++) {
        T temp = tab[i];
        tab[i] = tab[last - i - 1];
        tab[last - i - 1] = temp;
    }
}

template <typename T>
void ArrayList<T>::sort() {
    for (int i = 0; i < last; i++) {
        for (int j = 0; j < last - i - 1; j++) {
            if (tab[j] > tab[j+1]) {
                T temp = tab[j];
                tab[j] = tab[j+1];
                tab[j+1] = temp;
            }
        }
    }
}





template class ArrayList<int>;
//template void ArrayList<int>::push_front(const int& item);