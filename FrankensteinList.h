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
    void unique();//Removes all unique elements
    void merge(const FrankensteinList<T>&);// Merge two lists
    void remove(const T&);// Remove elements with a specific value
    void erase(const T&);// Erase the element at a specific position
    void erase(const T&, std::size_t);// Erase a range of elements starting at a specific position
    void sort();// Sort the list
    void resize(std::size_t);// Resize the list
    void emplace_front(std::size_t);//Adding or removing new elements
    void splice(std::size_t, const FrankensteinList<T>&);// Insert elements from another list at the specified position.
    void assign(std::size_t, const T&);// Assign a specified number of elements with the given value.
    Node<T>* getHead() const;// Get a pointer to the head of the list
    void setHead(Node<T>*);// Set the head pointer
    Node<T>* getTail() const;// Get a pointer to the tail of the list
    void setTail(Node<T>*);// Set the tail pointer
    Node<T>* getAscHead() const;// Get a pointer to the ascending head of the list
    void setAscHead(Node<T>*);// Set the ascending head pointer
    Node<T>* getDescHead() const;// Get a pointer to the descending head of the list
    void setDescHead(Node<T>*);// Set the descending head pointer
    int getSize() const;// Get the current size of the list
    void setSize(int);// Set the size of the list


    // Printing functions
    void printSortedAscendingOrder() const;// Print the list in ascending order
    void printSortedDescendingOrder() const;// Print the list in descending order

    // Friend function for output stream operator
    template<typename U>
    friend std::ostream& operator<<(std::ostream&, const FrankensteinList<U>&);

    // Define an iterator class for FrankensteinList
    enum class IteratorType{head, asc_head};
    class Iterator {
    public:
        Iterator(Node<T>*, IteratorType = IteratorType::head);// Constructor

        T& operator*();// Dereference operator, returns a reference to the current element
        T* operator->();// Arrow operator, returns a pointer to the current element
        Iterator& operator++();// Pre-increment operator, moves the iterator to the next element
        Iterator operator++(int);// Post-increment operator, moves the iterator to the next element and returns the previous position
        bool operator==(const Iterator&);// Equality operator, compares iterators for equality
        bool operator!=(const Iterator&);// Inequality operator, compares iterators for inequality
    private:
        Node<T> *ptr;// Pointer to the current node
        IteratorType type;// Type of iterator (head or asc_head)
    };

    Iterator begin(IteratorType type = IteratorType::head);// Begin iterator function, returns an iterator pointing to the beginning
    Iterator end(IteratorType type = IteratorType::head);// End iterator function, returns an iterator pointing to the end

    // ConstIterator class for FrankensteinList
    class ConstIterator{
    public:
        ConstIterator(const Node<T>*, IteratorType type = IteratorType::head);// Constructor

        const T& operator*() const;// Const dereference operator, returns a reference to the current element
        const T* operator->() const;// Const arrow operator, returns a pointer to the current element
        ConstIterator& operator++();// Pre-increment operator, moves the const iterator to the next element
        ConstIterator operator++(int);// Post-increment operator, moves the const iterator to the next element and returns the previous position
        bool operator==(const ConstIterator&) const;// Equality operator, compares const iterators for equality
        bool operator!=(const ConstIterator&) const;// Inequality operator, compares const iterators for inequality
    private:
        const Node<T>* ptr;// Pointer to the current node
        IteratorType type;// Type of iterator (head or asc_head)
    };

    ConstIterator cbegin(IteratorType type = IteratorType::head) const;// Const begin iterator function, returns a const iterator pointing to the beginning
    ConstIterator cend(IteratorType type = IteratorType::head) const;// Const end iterator function, returns a const iterator pointing to the end
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

//merge two
template<typename T>
FrankensteinList<T> mergeTwoList(const FrankensteinList<T>&, const FrankensteinList<T>&);

#include "FrankensteinList.tpp"

#endif //FRANKENSTEIN_S_LIST_FRANKENSTEINLIST_H
