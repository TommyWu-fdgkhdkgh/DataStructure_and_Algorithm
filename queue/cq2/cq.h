#if !defined(__CQ_H__)
#define __CQ_H__

#include <vector>
#include <cassert>
#define DEFAULT_SIZE 50

template <typename T>
class cq {
private:
   unsigned int numOfElements;
   unsigned int head;
   unsigned int tail;
   std::vector<T> content;

public:  
    cq() {
        numOfElements = 0;
        head = 0;
        tail = 0;
        content = std::vector<T>(DEFAULT_SIZE);
    }

    void setSize(unsigned int size) {
        head = 0;
        tail = 0;
        numOfElements = 0;
        content = std::vector<T>(size); 
    }

    unsigned int getSize() {
        return content.size();
    }

    unsigned int getNumOfElements() {
        return numOfElements;
    }

    void enQueue(T newElement) {
        assert(numOfElements != content.size());
        content[tail] = newElement;
        tail = (tail + 1) % numOfElements;
        numOfElements++;   
    }

    void enQueueFromHead(T newElement) {
        assert(numOfElements != content.size());
        if(head == 0) {
            head = content.size() - 1;
        } else {
            head--;
        }
        content[head] = newElement;
        numOfElements++;
    }

    T popQueue() {
        assert(0 != numOfElements);
        unsigned int tmp = head;
        head = (head + 1) % content.size(); 
        return content[tmp];
    }
};

#endif /* __CQ_H__ */
