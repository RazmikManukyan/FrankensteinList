
# FrankensteinList README

## Overview
The `FrankensteinList` is a C++ template class designed to provide a flexible and feature-rich doubly linked list implementation. It offers a wide range of operations for manipulating and managing the list's elements. This README will guide you on how to use the `FrankensteinList` class effectively and provide an overview of its functionality.

## Table of Contents
1. [Getting Started](#getting-started)
2. [Constructor](#constructor)
3. [Basic Operations](#basic-operations)
   - [Insertion](#insertion)
   - [Access](#access)
   - [Deletion](#deletion)
   - [Size and Empty Check](#size-and-empty-check)
4. [Advanced Operations](#advanced-operations)
   - [Sorting](#sorting)
   - [Reversing](#reversing)
   - [Merging](#merging)
   - [Unique](#unique)
   - [Iterators](#iterators)
5. [Output](#output)
6. [Comparison Operators](#comparison-operators)
7. [Swap and Merge Functions](#swap-and-merge-functions)

## Getting Started <a name="getting-started"></a>
To use the `FrankensteinList` class in your C++ project, you need to include the appropriate header files and ensure that the necessary dependencies are set up. Here's how you can get started:

1. **Include Headers**: Include the `FrankensteinList.h` and `Node.h` headers in your project.
   
   ```cpp
   #include "FrankensteinList.h"
   ```

2. **Create an Instance**: Instantiate the `FrankensteinList` with the desired data type. For example:

   ```cpp
   FrankensteinList<int> myList;
   ```

3. **Perform Operations**: You can now perform various operations on your list using the provided member functions.

## Constructor <a name="constructor"></a>
The `FrankensteinList` class offers several constructors:

- **Default Constructor**: Creates an empty list.

  ```cpp
  FrankensteinList<int> myList;
  ```

- **Initializer List Constructor**: Initializes the list with elements from an initializer list.

  ```cpp
  FrankensteinList<int> myList = {1, 2, 3, 4, 5};
  ```

- **Copy Constructor**: Creates a new list as a copy of an existing list.

  ```cpp
  FrankensteinList<int> newList(existingList);
  ```

- **Move Constructor**: Creates a new list by moving the content of an existing list.

  ```cpp
  FrankensteinList<int> newList(std::move(existingList));
  ```

## Basic Operations <a name="basic-operations"></a>

### Insertion <a name="insertion"></a>
- `push_front(const T&)`: Insert an element at the front of the list.
- `pop_front()`: Remove the element from the front of the list.
- `push_back(const T&)`: Insert an element at the back of the list.
- `pop_back()`: Remove the element from the back of the list.
- `insertAt(const T&, std::size_t)`: Insert an element at a specified position in the list.

### Access <a name="access"></a>
- `front()`: Get a reference to the front element.
- `back()`: Get a reference to the back element.
- `getNodeAt(std::size_t)`: Get a pointer to the node at a specified position.

### Deletion <a name="deletion"></a>
- `remove(const T&)`: Remove elements with a specific value from the list.
- `erase(const T&)`: Erase the element at a specific position in the list.
- `erase(const T&, std::size_t)`: Erase a range of elements starting at a specific position.

### Size and Empty Check <a name="size-and-empty-check"></a>
- `empty() const`: Check if the list is empty.
- `getSize() const`: Get the current size of the list.
- `resize(std::size_t)`: Resize the list.

## Advanced Operations <a name="advanced-operations"></a>

### Sorting <a name="sorting"></a>
- `sort()`: Sort the list in ascending order.

### Reversing <a name="reversing"></a>
- `reverse()`: Reverse the order of elements in the list.

### Merging <a name="merging"></a>
- `merge(const FrankensteinList<T>&)`: Merge two lists.

### Unique <a name="unique"></a>
- `unique()`: Remove all duplicate elements from the list.

### Iterators <a name="iterators"></a>
- You can use iterators to traverse the list. There are two types of iterators: `Iterator` and `ConstIterator`. You can use them to iterate through the list in either ascending or descending order.

## Output <a name="output"></a>
- `printSortedAscendingOrder()`: Print the list in ascending order.
- `printSortedDescendingOrder()`: Print the list in descending order.

## Comparison Operators <a name="comparison-operators"></a>
- You can compare two `FrankensteinList` instances using the following comparison operators:
  - `==`, `!=`, `<`, `<=`, `>`, `>=`

## Swap and Merge Functions <a name="swap-and-merge-functions"></a>
- `swap(FrankensteinList<T>&, FrankensteinList<T>&)`: Swap the contents of two lists.
- `mergeTwoList(const FrankensteinList<T>&, const FrankensteinList<T>&)`: Merge two lists and return a new merged list.

For more details on each function and its usage, please refer to the source code comments and the provided template implementation file `FrankensteinList.tpp`.

Feel free to use the `FrankensteinList` class to manage collections of data efficiently and flexibly in your C++ projects. If you encounter any issues or have questions, consult the documentation or seek assistance from the community.

## Usage

To use Frankenstein's List in your C++ project, follow these steps:

1. Include the necessary headers in your code:

   ```cpp
   #include "FrankensteinList.h"
   ```

2. Create an instance of `FrankensteinList` with your desired element type:

   ```cpp
   FrankensteinList<int> myList;
   ```

3. Start using the various methods and operations provided by the class to manage your list of elements.

Here's a basic example of using Frankenstein's List:

```cpp
#include <iostream>
#include "FrankensteinList.h"

int main() {
    // Create a list of integers
    FrankensteinList<int> myList;

    // Insert elements at the front
    myList.push_front(10);
    myList.push_front(20);
    myList.push_front(30);

    // Insert elements at the back
    myList.push_back(5);
    myList.push_back(15);

    // Print the list in ascending order
    std::cout << "Ascending order: ";
    myList.printSortedAscendingOrder(); // Output: Ascending order: 5 10 15 20 30

    // Print the list in descending order
    std::cout << "Descending order: ";
    myList.printSortedDescendingOrder(); // Output: Descending order: 30 20 15 10 5

    // Access elements using iterators
    std::cout << "Using iterators: ";
    for (const auto& item : myList) {
        std::cout << item << " ";
    }
    // Output: Using iterators: 5 10 15 20 30

    // Find and remove elements
    int elementToRemove = 15;
    myList.remove(elementToRemove);

    // Print the updated list
    std::cout << "\nList after removing " << elementToRemove << ": ";
    for (const auto& item : myList) {
        std::cout << item << " ";
    }
    // Output: List after removing 15: 5 10 20 30

    // Sort the list
    myList.sort();

    // Print the sorted list
    std::cout << "\nSorted list: ";
    for (const auto& item : myList) {
        std::cout << item << " ";
    }
    // Output: Sorted list: 5 10 20 30

    return 0;
}

```

