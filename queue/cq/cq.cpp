#include <vector>
#include <cassert>
#include "cq.h"
#define DEFAULT_SIZE 50

template <typename T>
cq<T>::cq(void) {
    numOfElements = 0;
    head = 0;
    tail = 0;
    content = std::vector<T>(DEFAULT_SIZE);
}

template <typename T>
void cq<T>::setSize(unsigned int size) {
    head = 0;
    tail = 0;
    numOfElements = 0;
    content = std::vector<T>(size); 
}

template <typename T>
unsigned int cq<T>::getSize() {
    return content.size();
}

template <typename T>
unsigned int cq<T>::getNumOfElements() {
    return numOfElements;
}

template <typename T>
void cq<T>::enQueue(T newElement) {
    assert(numOfElements != content.size());
    content[tail] = newElement;
    tail = (tail + 1) % numOfElements;
    numOfElements++;   
}

template <typename T>
void cq<T>::enQueueFromHead(T newElement) {
    assert(numOfElements != content.size());
    if(head == 0) {
        head = content.size() - 1;
    } else {
        head--;
    }
    content[head] = newElement;
    numOfElements++;
}

template <typename T>
T cq<T>::popQueue() {
    assert(0 != numOfElements);
    unsigned int tmp = head;
    head = (head + 1) % content.size(); 
    return content[tmp];
}


// template class cq<int>;
