// Default constructor
template<typename T>
FrankensteinList<T>::FrankensteinList()
        :head(nullptr), tail(nullptr), asc_head(nullptr), desc_head(nullptr), size(0)
{
}

// Constructor with initializer list
template<typename T>
FrankensteinList<T>::FrankensteinList(std::initializer_list<T> list)
        :head(nullptr), tail(nullptr), asc_head(nullptr), desc_head(nullptr), size(0)
{
    for(const T& val : list) {
        push_back(val);
    }
}

// Copy constructor
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

// Move constructor
template<typename T>
FrankensteinList<T>::FrankensteinList(FrankensteinList<T> &&oth) noexcept
        :head(oth.head), tail(oth.tail), asc_head(oth.asc_head), desc_head(oth.desc_head), size(oth.size)
{
    oth.head = nullptr;
    oth.tail = nullptr;
    oth.asc_head = nullptr;
    oth.desc_head = nullptr;
    oth.size = 0;
}

// Destructor
template<typename T>
FrankensteinList<T>::~FrankensteinList() {
    clear();
}

// Copy assignment operator
template<typename T>
FrankensteinList<T>& FrankensteinList<T>::operator=(const FrankensteinList<T>& oth) {
    if(this == &oth) {
        return *this; // Avoid self-assignment
    }
    clear(); // Clear the current content of this instance

    // Copy the elements from the other instance
    Node<T>* othHead = oth.head;
    while (othHead) {
        push_back(othHead->val);
        othHead = othHead->next;
    }
    return *this;
}

// Move assignment operator
template<typename T>
FrankensteinList<T>& FrankensteinList<T>::operator=(FrankensteinList<T> &&oth) noexcept {
    if(this == &oth) {
        return *this; // Avoid self-assignment
    }
    clear(); // Clear the current content of this instance

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

// Insert an element at a specified position
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

// Helper function for maintaining sorted order
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

// Get a pointer to the node at a specified position
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

// Insert an element at the front
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

// Remove the element from the front
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
        if(tmp == asc_head) {
            tmp->greater->lesser = tmp->lesser;
            asc_head = asc_head->greater;
        } else if(tmp == desc_head) {
            tmp->lesser->greater = tmp->greater;
            desc_head = desc_head->lesser;
        } else {
            tmp->greater->lesser = tmp->lesser;
            tmp->lesser->greater = tmp->greater;
        }
        head = head->next;
        head->prev = nullptr;
        delete tmp;
    }
    --size;
}

// Get a reference to the front element
template<typename T>
T& FrankensteinList<T>::front() {
    if(!head) {
        throw std::runtime_error("List is empty. Cannot access front element.");
    }
    return head->val;
}

// Insert an element at the back
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

// Remove the element from the back
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
        if(tmp == desc_head) {
            tmp->lesser->greater = tmp->greater;
            desc_head = desc_head->lesser;
        } else if(tmp == asc_head) {
            tmp->greater->lesser = tmp->lesser;
            asc_head = asc_head->greater;
        } else {
            tmp->lesser->greater = tmp->greater;
            tmp->greater->lesser = tmp->lesser;
        }
        tail = tail->prev;
        tail->next = nullptr;
        delete tmp;
    }
    --size;
}

// Get a reference to the back element
template<typename T>
T& FrankensteinList<T>::back() {
    if(!tail) {
        throw std::runtime_error("List is empty. Cannot access back element.");
    }
    return tail->val;
}

// Check if the list is empty
template<typename T>
bool FrankensteinList<T>::empty() const {
    return size == 0;
}

// Reverse the order of elements in the list
template<typename T>
void FrankensteinList<T>::reverse() {
    // If the list is empty or has only one element, no need to reverse
    if(size <= 1) return;

    Node<T>* curr = head;
    Node<T>* prev = nullptr;
    Node<T>* next = nullptr;

    // Traverse the list and reverse the links between nodes
    while(curr) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }

    // Swap the head and tail pointers
    std::swap(head, tail);
}

// Get a pointer to the head of the list
template<typename T>
const Node<T>* FrankensteinList<T>::getHead() const {
    return head;
}

// Get a pointer to the tail of the list
template<typename T>
const Node<T>* FrankensteinList<T>::getTail() const {
    return tail;
}
// Get a pointer to the ascending head of the list
template<typename T>
const Node<T>* FrankensteinList<T>::getAscHead() const {
    return asc_head;
}
// Get a pointer to the descending head of the list
template<typename T>
const Node<T>* FrankensteinList<T>::getDescHead() const {
    return desc_head;
}

// Get the current size of the list
template<typename T>
int FrankensteinList<T>::getSize() const {
    return size;
}

// Print the list in ascending order
template<typename T>
void FrankensteinList<T>::printSortedAscendingOrder() const{
    Node<T>* curr = asc_head;
    while(curr) {
        std::cout << curr->val << " ";
        curr = curr->greater;
    }
    std::cout << std::endl;
}

// Print the list in descending order
template<typename T>
void FrankensteinList<T>::printSortedDescendingOrder() const{
    Node<T>* curr = desc_head;
    while(curr) {
        std::cout << curr->val << " ";
        curr = curr->lesser;
    }
    std::cout << std::endl;
}

// Helper function for clearing the list
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

// Overload the output stream operator for printing the list
template<typename T>
std::ostream &operator<<(std::ostream &os, const FrankensteinList<T> &list) {
    Node<T>* curr = list.head;
    while (curr) {
        os << curr->val << " ";
        curr = curr->next;
    }
    return os;
}

template<typename T>
FrankensteinList<T>::Iterator::Iterator(Node<T> *node)
    :ptr(node)
{
}

template<typename T>
T& FrankensteinList<T>::Iterator::operator*() {
    if(!ptr){
        throw std::runtime_error("Iterator is not dereferencable.");
    }
    return ptr->val;
}

template<typename T>
T* FrankensteinList<T>::Iterator::operator->() {
    if(!ptr) {
        throw std::runtime_error("Iterator is not dereferencable.");
    }
    return &(ptr->val);
}

template<typename T>
typename FrankensteinList<T>::Iterator& FrankensteinList<T>::Iterator::operator++() {
    ptr = ptr->next;
    return *this;
}

template<typename T>
typename FrankensteinList<T>::Iterator FrankensteinList<T>::Iterator::operator++(int) {
    FrankensteinList<T>::Iterator tmp = *this;
    ++(*this);
    return tmp;
}

template<typename T>
bool FrankensteinList<T>::Iterator::operator==(const FrankensteinList<T>::Iterator &oth){
    return ptr == oth.ptr;
}

template<typename T>
bool FrankensteinList<T>::Iterator::operator!=(const FrankensteinList::Iterator &oth){
    return !(ptr == oth.ptr);
}

template<typename T>
typename FrankensteinList<T>::Iterator FrankensteinList<T>::begin() {
    return Iterator(head);
}

template<typename T>
typename FrankensteinList<T>::Iterator FrankensteinList<T>::end() {
    return Iterator(nullptr);
}

template<typename T>
typename FrankensteinList<T>::Iterator FrankensteinList<T>::beginAscending() {
    return Iterator(asc_head);
}

template<typename T>
typename FrankensteinList<T>::Iterator FrankensteinList<T>::endAscending() {
    return Iterator(desc_head);
}

template<typename T>
FrankensteinList<T>::ConstIterator::ConstIterator(const Node<T> *node)
    :ptr(node)
{
}

template<typename T>
const T& FrankensteinList<T>::ConstIterator::operator*() const {
    if (!ptr) {
        throw std::runtime_error("Iterator is not dereferencable.");
    }
    return ptr->val;
}

template<typename T>
const T* FrankensteinList<T>::ConstIterator::operator->() const {
    if (!ptr) {
        throw std::runtime_error("Iterator is not dereferencable.");
    }
    return &(ptr->val);
}

template<typename T>
typename FrankensteinList<T>::ConstIterator &FrankensteinList<T>::ConstIterator::operator++() {
    ptr = ptr->next;
    return *this;
}

template<typename T>
typename FrankensteinList<T>::ConstIterator FrankensteinList<T>::ConstIterator::operator++(int) {
    FrankensteinList<T>::ConstIterator tmp = *this;
    ++(*this);
    return tmp;
}

template<typename T>
bool FrankensteinList<T>::ConstIterator::operator==(const FrankensteinList<T>::ConstIterator &oth) const {
    return ptr == oth.ptr;
}

template<typename T>
bool FrankensteinList<T>::ConstIterator::operator!=(const FrankensteinList<T>::ConstIterator &oth) const {
    return ptr != oth.ptr;
}

template<typename T>
typename FrankensteinList<T>::ConstIterator FrankensteinList<T>::cbegin() const {
    return ConstIterator(head);
}

template<typename T>
typename FrankensteinList<T>::ConstIterator FrankensteinList<T>::cend() const {
    return ConstIterator(nullptr);
}

// Comparison operators
// Equality operator
template<typename T>
bool operator==(const FrankensteinList<T>& first, const FrankensteinList<T>& second) {
    // Compare sizes first
    if(first.getSize() != second.getSize()) return false;

    // Compare the elements in both lists
    const Node<T>* firstHead = first.getHead();
    const Node<T>* secondHead = second.getHead();

    while(firstHead && secondHead) {
        if(firstHead->val != secondHead->val) {
            return false; // Elements are not equal
        }
        firstHead = firstHead->next;
        secondHead = secondHead->next;
    }

    // If both lists reached the end, they are equal
    return !firstHead && !secondHead;
}

// Inequality operator
//template<typename T>
//bool operator!=(const FrankensteinList<T>& first, const FrankensteinList<T>& second) {
//    return !(first == second);
//}

// Less than operator
template<typename T>
bool operator<(const FrankensteinList<T>& first, const FrankensteinList<T>& second) {
    if(first.getSize() != second.getSize()) return false;

    const Node<T>* firstHead = first.getHead();
    const Node<T>* secondHead = second.getHead();

    while(firstHead && secondHead) {
        if(firstHead->val >= secondHead->val) {
            return false;
        }
        firstHead = firstHead->next;
        secondHead = secondHead->next;
    }

    return !firstHead && !secondHead;
}

// Less than or equal to operator
template<typename T>
bool operator<=(const FrankensteinList<T>& first, const FrankensteinList<T>& second){
    if(first.getSize() != second.getSize()) return false;

    const Node<T>* firstHead = first.getHead();
    const Node<T>* secondHead = second.getHead();

    while(firstHead && secondHead) {
        if(firstHead->val > secondHead->val) {
            return false;
        }
        firstHead = firstHead->next;
        secondHead = secondHead->next;
    }

    return !firstHead && !secondHead;
}

// Greater than operator
template<typename T>
bool operator>(const FrankensteinList<T>& first, const FrankensteinList<T>& second){
    if(first.getSize() != second.getSize()) return false;

    const Node<T>* firstHead = first.getHead();
    const Node<T>* secondHead = second.getHead();

    while(firstHead && secondHead) {
        if(firstHead->val <= secondHead->val) {
            return false;
        }
        firstHead = firstHead->next;
        secondHead = secondHead->next;
    }

    return !firstHead && !secondHead;
}

// Greater than or equal to operator
template<typename T>
bool operator>=(const FrankensteinList<T>& first, const FrankensteinList<T>& second){
    if(first.getSize() != second.getSize()) return false;

    const Node<T>* firstHead = first.getHead();
    const Node<T>* secondHead = second.getHead();

    while(firstHead && secondHead) {
        if(firstHead->val < secondHead->val) {
            return false;
        }
        firstHead = firstHead->next;
        secondHead = secondHead->next;
    }

    return !firstHead && !secondHead;
}

template<typename T>
void swap(FrankensteinList<T>& first, FrankensteinList<T>& second) {
    // Swap the members of the first and second objects
    using std::swap;

    std::swap(first.getHead(), first.getHead());
    std::swap(first.getTail(), second.getTail());
    std::swap(first.getAscHead(), second.getAscHead());
    std::swap(first.getDescHead(), second.getDescHead());
    std::swap(first.getSize(), second.getSize());
}
