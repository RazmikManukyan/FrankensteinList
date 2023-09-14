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
    if(pos < 0|| pos >= size) {
        throw std::out_of_range("Position is out of range.");
    }

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
    Node<T>* tmp;

    // Traverse the list and reverse the links between nodes
    while(curr) {
        tmp = curr->next;
        curr->next = curr->prev;
        curr->prev = curr->next;
        curr = tmp;
    }

    // Swap the head and tail pointers
    std::swap(head, tail);
}

// Function to remove duplicate elements in the list
template<typename T>
void FrankensteinList<T>::unique() {
    if(!asc_head) return;// If the list is empty or already sorted, return

    Node<T>* curr = asc_head;
    Node<T>* prev = nullptr;

    while(curr) {
        Node<T>* next = curr->greater;

        // Check if the current node has the same value as the next node
        if(next && curr->val == next->val) {
            if(prev) {
                prev->greater = next;// Connect the previous node to the next node
                if(next->greater) {
                    next->greater->lesser = curr;
                }
                if(curr == head) {
                    head = head->next;
                }
                if(curr == tail) {
                    tail = tail->prev;
                } else if (curr->prev && curr->next) {
                    curr->prev->next = curr->next;
                    curr->next->prev = curr->prev;
                }
                delete curr;// Delete the current node
            } else {
                asc_head = next;
                next->lesser = nullptr;
                if(curr == head) {
                    head = head->next;
                }
                if(curr == tail) {
                    tail = tail->prev;
                } else if (curr->prev && curr->next) {
                    curr->prev->next = curr->next;
                    curr->next->prev = curr->prev;
                }
                delete curr;// Delete the current node
            }
            curr = next;
            --size;
        } else {
            prev = curr;
            curr = next;
        }
    }
}


// Function to merge another list into this list
template<typename T>
void FrankensteinList<T>::merge(const FrankensteinList<T> &oth) {
    FrankensteinList<T>::ConstIterator it = oth.cbegin();
    while(it != oth.cend()) {
        this->push_back(*it);// Push elements from 'oth' into this list
        ++it;
    }
}

// Function to remove all occurrences of a value from the list
template<typename T>
void FrankensteinList<T>::remove(const T &val) {
    Node<T>* curr = asc_head;
    Node<T>* prev = nullptr;

    while(curr) {
        if(curr->val == val) {
            Node<T>* next = curr->greater;
            if(prev) {
                prev->greater = next;
                if(next) {
                    next->lesser = prev;
                }
                if(curr == head) {
                    head = head->next;
                } else if(curr == tail) {
                    tail = tail->prev;
                } else {
                    curr->prev->next = curr->next;
                    curr->next->prev = curr->prev;
                }
                delete curr;
                curr = next;
                --size;
            } else {
                asc_head = next;
                if(next) {
                    next->lesser = nullptr;
                }
                if(curr == head) {
                    head = head->next;
                } else if(curr == tail) {
                    tail = tail->prev;
                } else {
                    curr->prev->next = curr->next;
                    curr->next->prev = curr->prev;
                }
                delete curr;
                curr = next;
                --size;
            }
        } else {
            prev = curr;
            curr = curr->greater;
        }
    }
}

// Function to erase an element at a specific position
template<typename T>
void FrankensteinList<T>::erase(const T &pos) {
    if(pos < 0 || pos >= size) {
        throw std::out_of_range("Position is out of range.");
    }
    if(pos == 0) {
        pop_front();// Remove the first element
        return;
    } else if(pos == size - 1) {
        pop_back();// Remove the last element
    } else {
        Node<T> *curr = getNodeAt(pos);
        curr->next->prev = curr->prev;
        curr->prev->next = curr->next;
        curr->greater->lesser = curr->lesser;
        curr->lesser->greater = curr->greater;
        delete curr;// Delete the node at the specified position
        --size;
    }
}

// Function to erase a range of elements starting from a specific position
template<typename T>
void FrankensteinList<T>::erase(const T &pos, std::size_t count) {
    if(pos < 0 || pos > size || pos + count > size) {
        throw std::out_of_range("Position is out of range.");
    }
    if(count == 0) return;

    if(pos == 0) {
        while(count) {
            pop_front();// Remove elements from the front
            --count;
            --size;
        }
    } else if(pos + count == size) {
        while(count) {
            pop_back();// Remove elements from the back
            --count;
            --size;
        }
    } else {
        Node<T>* start = getNodeAt(pos);
        Node<T>* end = getNodeAt(pos + count - 1);

        start->prev->next = end->next;
        end->next->prev = start->prev;

        Node<T>* curr = start;
        while(curr != end->next) {
            Node<T>* next = curr->greater;
            curr->greater->lesser = curr->lesser;
            curr->lesser->greater = curr->greater;
            delete curr;// Delete nodes in the specified range
            curr = next;
            --size;
        }
    }
}

// Function to sort the list
template<typename T>
void FrankensteinList<T>::sort() {
    if(!head) return;// If the list is empty, return

    head = asc_head;
    tail = desc_head;
    Node<T>* curr = head;
    while(curr) {
        curr->next = curr->greater;
        curr->prev = curr->lesser;
        curr = curr->next;
    }
}

template<typename T>
void FrankensteinList<T>::resize(std::size_t newSize) {
    if(newSize == size){
        return;
    } else if (newSize < size) {
        int count = size - newSize;
        while (count) {
            pop_back();
            --count;
        }
    } else {
        int count = newSize - size;
        while (count) {
            push_back(0); // Default-constructed elements
            --count;
        }
    }
    size = newSize;
}

template<typename T>
void FrankensteinList<T>::emplace_front(std::size_t newSize) {
    if(newSize == size) return;// If 'newSize' is the same as the current size, no action is needed.
    if(newSize > size) {
        int count = newSize - size;
        while(count) {
            push_front(0);// Add elements with value 0 to the front
            --count;
        }
    } else {
        int count = size - newSize;
        while(count) {
            pop_front();// Remove elements from the front
            --count;
        }
    }
}

template<typename T>
void FrankensteinList<T>::splice(std::size_t pos, const FrankensteinList<T> &list) {
    // Iterate through the elements in 'list' using a constant iterator.
    FrankensteinList<T>::ConstIterator it = list.cbegin();
    while(it != list.cend()) {
        // Insert each element from 'list' into the current list at the specified 'pos'.
        insertAt(*it, pos);
        // Move to the next element in 'list'.
        ++it;
    }
}

// Assign a specified number of elements with the given value.
template<typename T>
void FrankensteinList<T>::assign(std::size_t count, const T& val) {
    clear();
    while(count) {
        push_back(val);
        --count;
    }
}

// Get a pointer to the head of the list
template<typename T>
Node<T>* FrankensteinList<T>::getHead() const {
    return head;
}

// Set a pointer to the head of the list
template<typename T>
void FrankensteinList<T>::setHead(Node<T>* h) {
    head = h;
}

// Get a pointer to the tail of the list
template<typename T>
Node<T>* FrankensteinList<T>::getTail() const {
    return tail;
}

// Set a pointer to the tail of the list
template<typename T>
void FrankensteinList<T>::setTail(Node<T> *t) {
    tail = t;
}

// Get a pointer to the ascending head of the list
template<typename T>
Node<T>* FrankensteinList<T>::getAscHead() const {
    return asc_head;
}
// Set a pointer to the ascending head of the list
template<typename T>
void FrankensteinList<T>::setAscHead(Node<T> *aH) {
    asc_head = aH;
}

// Get a pointer to the descending head of the list
template<typename T>
Node<T>* FrankensteinList<T>::getDescHead() const {
    return desc_head;
}

// Set a pointer to the descending head of the list
template<typename T>
void FrankensteinList<T>::setDescHead(Node<T> *dH) {
    desc_head = dH;
}

// Get the current size of the list
template<typename T>
int FrankensteinList<T>::getSize() const {
    return size;
}

// Get the current size of the list
template<typename T>
void FrankensteinList<T>::setSize(int s) {
    size = s;
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
    std::cout << std::endl;
    return os;
}

// Iterator constructor
template<typename T>
FrankensteinList<T>::Iterator::Iterator(Node<T> *node, IteratorType t)
    :ptr(node), type(t)
{
}

// Dereference operator for Iterator (non-const)
template<typename T>
T& FrankensteinList<T>::Iterator::operator*() {
    if(!ptr){
        throw std::runtime_error("Iterator is not dereferencable.");
    }
    return ptr->val;
}

// Arrow operator for Iterator (non-const)
template<typename T>
T* FrankensteinList<T>::Iterator::operator->() {
    if(!ptr) {
        throw std::runtime_error("Iterator is not dereferencable.");
    }
    return &(ptr->val);
}

// Prefix increment operator for Iterator
template<typename T>
typename FrankensteinList<T>::Iterator& FrankensteinList<T>::Iterator::operator++() {
    ptr = (type == IteratorType::head) ? ptr->next : ptr->greater;
    return *this;
}


// Postfix increment operator for Iterator
template<typename T>
typename FrankensteinList<T>::Iterator FrankensteinList<T>::Iterator::operator++(int) {
    FrankensteinList<T>::Iterator tmp = *this;
    ++(*this);
    return tmp;
}

// Equality comparison operator for Iterator
template<typename T>
bool FrankensteinList<T>::Iterator::operator==(const FrankensteinList<T>::Iterator &oth){
    return ptr == oth.ptr;
}

// Inequality comparison operator for Iterator
template<typename T>
bool FrankensteinList<T>::Iterator::operator!=(const FrankensteinList::Iterator &oth){
    return !(ptr == oth.ptr);
}

// Iterator begin function
template<typename T>
typename FrankensteinList<T>::Iterator FrankensteinList<T>::begin(FrankensteinList<T>::IteratorType type) {
    return Iterator((type == IteratorType::head) ? head : asc_head, type);
}

// Iterator end function
template<typename T>
typename FrankensteinList<T>::Iterator FrankensteinList<T>::end(FrankensteinList<T>::IteratorType type) {
    return Iterator(nullptr, IteratorType::head);
}

// ConstIterator constructor
template<typename T>
FrankensteinList<T>::ConstIterator::ConstIterator(const Node<T> *node, IteratorType t)
    :ptr(node), type(t)
{
}

// Dereference operator for ConstIterator (const)
template<typename T>
const T& FrankensteinList<T>::ConstIterator::operator*() const {
    if (!ptr) {
        throw std::runtime_error("Iterator is not dereferencable.");
    }
    return ptr->val;
}

// Arrow operator for ConstIterator (const)
template<typename T>
const T* FrankensteinList<T>::ConstIterator::operator->() const {
    if (!ptr) {
        throw std::runtime_error("Iterator is not dereferencable.");
    }
    return &(ptr->val);
}

// Prefix increment operator for ConstIterator
template<typename T>
typename FrankensteinList<T>::ConstIterator &FrankensteinList<T>::ConstIterator::operator++() {
    ptr = type == IteratorType::head ? ptr->next : ptr->greater;
    return *this;
}

// Postfix increment operator for ConstIterator
template<typename T>
typename FrankensteinList<T>::ConstIterator FrankensteinList<T>::ConstIterator::operator++(int) {
    FrankensteinList<T>::ConstIterator tmp = *this;
    ++(*this);
    return tmp;
}

// Equality comparison operator for ConstIterator
template<typename T>
bool FrankensteinList<T>::ConstIterator::operator==(const FrankensteinList<T>::ConstIterator &oth) const {
    return ptr == oth.ptr;
}

// Inequality comparison operator for ConstIterator
template<typename T>
bool FrankensteinList<T>::ConstIterator::operator!=(const FrankensteinList<T>::ConstIterator &oth) const {
    return ptr != oth.ptr;
}

// ConstIterator begin function
template<typename T>
typename FrankensteinList<T>::ConstIterator FrankensteinList<T>::cbegin(FrankensteinList<T>::IteratorType type) const {
    return ConstIterator((type == IteratorType::head) ? head : asc_head, type);
}

// ConstIterator end function
template<typename T>
typename FrankensteinList<T>::ConstIterator FrankensteinList<T>::cend(FrankensteinList<T>::IteratorType type) const {
    return ConstIterator(nullptr, type);
}

// Comparison operators
// Equality operator
template<typename T>
bool operator==(const FrankensteinList<T>& first, const FrankensteinList<T>& second) {
    // Compare sizes first
    if(first.getSize() != second.getSize()) return false;

    // Compare the elements in both lists
    Node<T>* firstHead = first.getHead();
    Node<T>* secondHead = second.getHead();

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
template<typename T>
bool operator!=(const FrankensteinList<T>& first, const FrankensteinList<T>& second) {
    return !(first == second);
}

// Less than operator
template<typename T>
bool operator<(const FrankensteinList<T>& first, const FrankensteinList<T>& second) {
    if(first.getSize() != second.getSize()) return false;

    Node<T>* firstHead = first.getHead();
    Node<T>* secondHead = second.getHead();

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

    Node<T>* firstHead = first.getHead();
    Node<T>* secondHead = second.getHead();

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

    Node<T>* firstHead = first.getHead();
    Node<T>* secondHead = second.getHead();

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

    Node<T>* firstHead = first.getHead();
    Node<T>* secondHead = second.getHead();

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

    auto* tmpH = first.getHead();
    first.setHead(second.getHead());
    second.setHead(tmpH);

    auto* tmpT = first.getTail();
    first.setTail(second.getTail());
    second.setTail(tmpT);

    auto* tmpAH = first.getAscHead();
    first.setAscHead(second.getAscHead());
    second.setAscHead(tmpAH);

    auto* tmpDH = first.getDescHead();
    first.setDescHead(second.getDescHead());
    second.setDescHead(tmpDH);

    int s = first.getSize();
    first.setSize(second.getSize());
    second.setSize(s);
}

//merge two list in third list
template<typename T>
FrankensteinList<T> merge(const FrankensteinList<T>& first, const FrankensteinList<T>& second) {
    FrankensteinList<T> mergedList;

    typename FrankensteinList<T>::ConstIterator it1 = first.cbegin(FrankensteinList<T>::IteratorType::asc_head);
    typename FrankensteinList<T>::ConstIterator it2 = second.cbegin(FrankensteinList<T>::IteratorType::asc_head);

    while(it1 != first.cend() && it2 != second.cend()) {
        if(*it1 < *it2) {
            mergedList.push_back(*it1);
            ++it1;
        } else {
            mergedList.push_back(*it2);
            ++it2;
        }
    }

    while(it1 != first.cend()) {
        mergedList.push_back(*it1);
        ++it1;
    }

    while(it2 != second.cend()) {
        mergedList.push_back(*it2);
        ++it2;
    }

    return mergedList;
}
