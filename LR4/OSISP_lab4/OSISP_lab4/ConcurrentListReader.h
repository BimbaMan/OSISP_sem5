#ifndef CONCURRENT_LIST_READER_H
#define CONCURRENT_LIST_READER_H

#include "ConcurrentListNode.h"

template <typename T>
class ConcurrentListReader
{
    public:
    ConcurrentListReader(ConcurrentListNode<T>* node);
    ~ConcurrentListReader();

    bool moveNext();
    T& value();

    private:
    ConcurrentListNode<T>* curr;
    ConcurrentListNode<T>* next;
};

template<typename T>
inline ConcurrentListReader<T>::ConcurrentListReader(ConcurrentListNode<T>* node)
{
    this->curr = node;
    this->next = node;
}

template<typename T>
inline ConcurrentListReader<T>::~ConcurrentListReader()
{

}

template<typename T>
inline bool ConcurrentListReader<T>::moveNext()
{
    this->curr = this->next;

    if (this->curr == nullptr)
        return false;

    this->next = this->next->next;
    return true;
}

template<typename T>
inline T& ConcurrentListReader<T>::value()
{
    return this->curr->value;
}

#endif
