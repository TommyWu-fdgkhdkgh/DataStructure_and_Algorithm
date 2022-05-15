#if !defined(__CQ_H__)
#define __CQ_H__

#include <vector>
#include <cassert>

template <typename T>
class cq {
private:
   unsigned int numOfElements;
   unsigned int head;
   unsigned int tail;
   std::vector<T> content;

public:  
    cq();
    void setSize(unsigned int size);
    unsigned int getSize();
    unsigned int getNumOfElements();
    void enQueue(T newElement);
    void enQueueFromHead(T newElement);
    T popQueue();
};

#endif /* __CQ_H__ */
