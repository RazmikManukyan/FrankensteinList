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
        push_back(val);
    }
}

template<typename T>
FrankensteinList<T>::FrankensteinList(const FrankensteinList<T> &oth)
    :head(nullptr), tail(nullptr), asc_head(nullptr), desc_head(nullptr), size(0)
{
    Node<T>* othHead = oth.head;
    while(othHead) {
        this->push_back(othHead->val);
        othHead = othHead->next;
    }
}

template<typename T>
FrankensteinList<T>::FrankensteinList(FrankensteinList<T> &&oth)
    :head(oth.head), tail(oth.tail), asc_head(oth.asc_head), desc_head(oth.desc_head), size(oth.size)
{
    oth.head = nullptr;
    oth.tail = nullptr;
    oth.asc_head = nullptr;
    oth.desc_head = nullptr;
    oth.size = 0;
}

template<typename T>
FrankensteinList<T>::~FrankensteinList() {
    clear();
}

template<typename T>
FrankensteinList<T>& FrankensteinList<T>::operator=(const FrankensteinList<T>& oth) {
    if(this == &oth) {
        return *this;//Avoid self-assignment
    }
    clear();// Clear the current content of this instance

    // Copy the elements from the other instance
    Node<T>* othHead = oth.head;
    while (othHead) {
        PushBack(othHead->val);
        othHead = othHead->next;
    }
    return *this;
}

template<typename T>
FrankensteinList<T>& FrankensteinList<T>::operator=(FrankensteinList<T> &&oth) {
    if(this == &oth) {
        return *this;//Avoid self-assignment
    }
    clear();// Clear the current content of this instance

    // Transfer ownership of the other instance's resources
    this->head = oth.head;
    this->tail = oth.tail;
    this->asc_head = oth.asc_head;
    this->desc_head = oth.desc_head;
    this->size = oth.size;

    // Reset the other instance's pointers and size
    oth.head = nullptr;
    oth.tail = nullptr;
    oth.asc_head = nullptr;
    oth.desc_head = nullptr;
    oth.size = 0;

    return *this;
}

template<typename T>
void FrankensteinList<T>::insertAt(const T &val, std::size_t pos) {
    if (pos > size) {
        throw std::out_of_range("Position is out of range.");
    }

    if (pos == 0) {
        return push_front(val);
    } else if (pos == size) {
        return push_back(val);
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
void FrankensteinList<T>::push_front(const T &val) {
    Node<T>* node = new Node(val);
    if(head) {
        head->prev = node;
    } else {
        tail = node;
    }
    node->next = head;
    head = node;
    ++size;
    PutInSortedOrder(node);
}

template<typename T>
void FrankensteinList<T>::pop_front() {
    if (!head) {
        throw std::runtime_error("List is empty. Cannot pop_front.");
    }

    if(head == tail) {
        // Only one element in the list
        delete head;
        head = nullptr;
        tail = nullptr;
        asc_head = nullptr;
        desc_head = nullptr;
        size = 0;
    } else {
        Node<T>* tmp = head;
        head = head->next;
        head->prev = nullptr;
        if(tmp == asc_head) {
            asc_head = head;
        }
        delete tmp;
        --size;
    }
}

template<typename T>
void FrankensteinList<T>::push_back(const T &val) {
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
    PutInSortedOrder(node);
}

template<typename T>
void FrankensteinList<T>::pop_back() {
    if (!tail) {
        throw std::runtime_error("List is empty. Cannot pop_back.");
    }

    if (tail == head) {
        // Only one element in the list
        delete tail;
        head = nullptr;
        tail = nullptr;
        asc_head = nullptr;
        desc_head = nullptr;
        size = 0;
    } else {
        Node<T>* tmp = tail;
        tail = tail->prev;
        tail->next = nullptr;
        if(tmp == desc_head) {
            desc_head = tail;
        }
        delete tmp;
        --size;
    }
}

template<typename T>
bool FrankensteinList<T>::empty() const {
    return size == 0;
}

template<typename T>
T& FrankensteinList<T>::front() {
    if(!head) {
        throw std::runtime_error("List is empty. Cannot access front element.");
    }
    return head->val;
}

template<typename T>
T& FrankensteinList<T>::back() {
    if(!tail) {
        throw std::runtime_error("List is empty. Cannot access back element.");
    }
    return tail->val;
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