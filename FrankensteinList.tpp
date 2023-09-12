#include "FrankensteinList.h"

template<typename T>
FrankensteinList<T>::FrankensteinList()
    :head(nullptr), tail(nullptr), asc_head(nullptr), desc_head(nullptr), size(0)
{
}

template<typename T>
FrankensteinList<T>::FrankensteinList(std::initializer_list<T> list)
    :head(nullptr), tail(nullptr), asc_head(nullptr), desc_head(nullptr), size(0)
{
    for(const T& val : list) {
        PushBack(val);
    }
}

template<typename T>
FrankensteinList<T>::~FrankensteinList() {
    clear();
}

template<typename T>
void FrankensteinList<T>::insertAt(const T &val, std::size_t pos) {
    if (pos > size) {
        throw std::out_of_range("Position is out of range.");
    }

    if (pos == 0) {
        return PushFront(val);
    } else if (pos == size) {
        return PushBack(val);
    }

    Node<T>* node = new Node(val);
    Node<T>* curr = getNodeAt(pos);
    node->next = curr;
    node->prev = curr->prev;
    curr->prev->next = node;
    curr->prev = node;

    ++size;
    PutInSortedOrder(node);
}

template<typename T>
void FrankensteinList<T>::PutInSortedOrder(Node<T> *node) {
    if (!node) return;

    // Handle asc_head (ascending order)
    if (!asc_head || node->val < asc_head->val) {
        node->greater = asc_head;
        asc_head = node;
    } else {
        Node<T>* curr = asc_head;
        while (curr->greater && curr->greater->val < node->val) {
            curr = curr->greater;
        }
        node->greater = curr->greater;
        curr->greater = node;
    }

    // Handle desc_head (descending order)
    if (!desc_head || node->val > desc_head->val) {
        node->lesser = desc_head;
        desc_head = node;
    } else {
        Node<T>* curr = desc_head;
        while (curr->lesser && curr->lesser->val > node->val) {
            curr = curr->lesser;
        }
        node->lesser = curr->lesser;
        curr->lesser = node;
    }
}

template<typename T>
Node<T>* FrankensteinList<T>::getNodeAt(std::size_t pos) {
    std::size_t count = 0;
    Node<T>* curr = head;
    while(count != pos) {
        curr = curr->next;
        ++count;
    }
    return curr;
}

template<typename T>
void FrankensteinList<T>::PushFront(const T &val) {
    Node<T>* node = new Node(val);
    if(head) {
        head->prev = node;
    } else {
        tail = node;
    }
    node->next = head;
    head = node;
    ++size;
}

template<typename T>
void FrankensteinList<T>::PushBack(const T &val) {
    Node<T>* node = new Node(val);
    if(!head) {
        head = node;
        tail = node;
    } else {
        tail->next = node;
        node->prev = tail;
        tail = node;
    }
    ++size;
}

template<typename T>
void FrankensteinList<T>::printSortedAscendingOrder() const{
    Node<T>* curr = asc_head;
    while(curr) {
        std::cout << curr->val << " ";
        curr = curr->greater;
    }
    std::cout << std::endl;
}

template<typename T>
void FrankensteinList<T>::printSortedDescendingOrder() const{
    Node<T>* curr = desc_head;
    while(curr) {
        std::cout << curr->val << " ";
        curr = curr->lesser;
    }
    std::cout << std::endl;
}

template<typename T>
void FrankensteinList<T>::clear() noexcept {
    Node<T>* cur = head;
    while(cur) {
        Node<T>* next = cur->next;
        delete cur;
        cur = next;
    }

    head = nullptr;
    tail = nullptr;
    asc_head = nullptr;
    desc_head = nullptr;
    size = 0;
}

template<typename T>
std::ostream &operator<<(std::ostream &os, const FrankensteinList<T> &list) {
    Node<T>* curr = list.head;
    while (curr) {
        os << curr->val << " ";
        curr = curr->next;
    }
    return os;
}