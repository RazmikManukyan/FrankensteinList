#ifndef FRANKENSTEIN_S_LIST_FRANKENSTEINLIST_H
#define FRANKENSTEIN_S_LIST_FRANKENSTEINLIST_H
#include <iostream>
#include "Node.h"

template<typename T>
class FrankensteinList {
private:
    void PutInSortedOrder(Node<T>*);
    void clear() noexcept;
public:
    FrankensteinList();
    FrankensteinList(std::initializer_list<T>);
    FrankensteinList(const FrankensteinList<T>&);
    FrankensteinList(FrankensteinList&&);
    ~FrankensteinList();

    FrankensteinList<T>& operator=(const FrankensteinList<T>&);
    FrankensteinList<T>& operator=(FrankensteinList<T>&&);

    void insertAt(const T&, std::size_t);
    Node<T>* getNodeAt(std::size_t);
    void push_front(const T&);
    void pop_front();
    void push_back(const T&);
    void pop_back();
    bool empty() const;
    T& front();
    T& back();
    void printSortedAscendingOrder() const;
    void printSortedDescendingOrder() const;

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
