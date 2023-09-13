#ifndef FRANKENSTEIN_S_LIST_FRANKENSTEINLIST_H
#define FRANKENSTEIN_S_LIST_FRANKENSTEINLIST_H
#include <iostream>
#include "Node.h"

template<typename T>
class FrankensteinList {
private:
    void PutInSortedOrder(Node<T>*);// Helper function for sorting the list
    void clear() noexcept;// Helper function for clearing the list
public:

    // Constructors and destructor
    FrankensteinList();// Default constructor
    FrankensteinList(std::initializer_list<T>);// Constructor with initializer lis
    FrankensteinList(const FrankensteinList<T>&);// Copy constructor
    FrankensteinList(FrankensteinList&&) noexcept;// Move constructor
    ~FrankensteinList();// Destructor

    // Assignment operators
    FrankensteinList<T>& operator=(const FrankensteinList<T>&);// Copy assignment operator
    FrankensteinList<T>& operator=(FrankensteinList<T>&&) noexcept ;// Move assignment operator

    void insertAt(const T&, std::size_t);// Insert an element at a specified position
    Node<T>* getNodeAt(std::size_t);// Get a pointer to the node at a specified position
    void push_front(const T&);// Insert an element at the front
    void pop_front();// Remove the element from the front
    T& front();// Get a reference to the front element
    void push_back(const T&);// Insert an element at the back
    void pop_back();// Remove the element from the back
    T& back();// Get a reference to the back element
    bool empty() const;// Check if the list is empty
    void reverse();// Reverse the order of elements in the list
    const Node<T>* getHead() const;// Get a pointer to the head of the list
    const Node<T>* getTail() const;// Get a pointer to the tail of the list
    const Node<T>* getAscHead() const;// Get a pointer to the ascending head of the list
    const Node<T>* getDescHead() const;// Get a pointer to the descending head of the list
    int getSize() const;// Get the current size of the list


    // Printing functions
    void printSortedAscendingOrder() const;// Print the list in ascending order
    void printSortedDescendingOrder() const;// Print the list in descending order

    // Friend function for output stream operator
    template<typename U>
    friend std::ostream& operator<<(std::ostream&, const FrankensteinList<U>&);
private:
    Node<T>* head;// Pointer to the head of the list
    Node<T>* tail;// Pointer to the tail of the list
    Node<T>* asc_head;// access nodes in ascending order
    Node<T>* desc_head;// access nodes in descending order
    std::size_t size;// Current size of the list
};

// Comparison operators
template<typename T>
bool operator==(const FrankensteinList<T>&, const FrankensteinList<T>&);
template<typename T>
bool operator!=(const FrankensteinList<T>&, const FrankensteinList<T>&);
template<typename T>
bool operator<(const FrankensteinList<T>&, const FrankensteinList<T>&);
template<typename T>
bool operator<=(const FrankensteinList<T>&, const FrankensteinList<T>&);
template<typename T>
bool operator>(const FrankensteinList<T>&, const FrankensteinList<T>&);
template<typename T>
bool operator>=(const FrankensteinList<T>&, const FrankensteinList<T>&);


//swap two lists
template<typename T>
void swap(FrankensteinList<T>&, FrankensteinList<T>&);

#include "FrankensteinList.tpp"

#endif //FRANKENSTEIN_S_LIST_FRANKENSTEINLIST_H
