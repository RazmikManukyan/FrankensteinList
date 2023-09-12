#ifndef FRANKENSTEIN_S_LIST_FRANKENSTEINLIST_H
#define FRANKENSTEIN_S_LIST_FRANKENSTEINLIST_H
#include <iostream>
#include "Node.h"

template<typename T>
class FrankensteinList {
private:
    void PushFront(const T&);
    void PushBack(const T&);
    void PutInSortedOrder(Node<T>*);

public:
    FrankensteinList();
    FrankensteinList(std::initializer_list<T>);
    ~FrankensteinList();

    void insertAt(const T&, std::size_t);

    Node<T>* getNodeAt(std::size_t);

    void printSortedAscendingOrder() const;
    void printSortedDescendingOrder() const;
    void clear() noexcept;

    template<typename U>
    friend std::ostream& operator<<(std::ostream&, const FrankensteinList<U>&);
private:
public:
    Node<T>* head;
    Node<T>* tail;
    Node<T>* asc_head;// access nodes in ascending order
    Node<T>* desc_head;// access nodes in descending order
    std::size_t size;
};

#include "FrankensteinList.tpp"

#endif //FRANKENSTEIN_S_LIST_FRANKENSTEINLIST_H
