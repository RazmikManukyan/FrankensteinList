# Frankenstein's List

Frankenstein's List is a C++ template class that provides a flexible and feature-rich doubly-linked list implementation. It supports various operations for manipulating and managing a list of elements, including insertion, deletion, sorting, merging, and more.

## Table of Contents
- [Introduction](#introduction)
- [Features](#features)
- [Usage](#usage)
- [Examples](#examples)
- [Contributing](#contributing)


## Introduction

The FrankensteinList class is designed to be a versatile and efficient container for managing collections of elements. It offers a wide range of functionality, including:

- **Element Manipulation**: Insertion, removal, and access to elements at specified positions.
- **List Operations**: Sorting, reversing, merging, and resizing the list.
- **Iterator Support**: Iterating over the list in both ascending and descending orders.
- **Comparison Operators**: Comparing lists for equality, inequality, and order.
- **Customization**: You can specify whether you want iterators to traverse the list in ascending or descending order.
- https://medium.com/@vardanator/self-organizing-sorted-linked-list-in-c-ae24b7e0b600
  
## Features

- **Doubly-Linked List**: Provides a doubly-linked list data structure.
- **Dynamic Sizing**: The list dynamically resizes as elements are added or removed.
- **Iterator Support**: Allows you to iterate over the list in various ways.
- **Customization**: You can choose to iterate the list in ascending or descending order.
- **Efficient Operations**: Optimized for fast insertion, deletion, and sorting.
- **Comparison Operators**: Supports comparison operations for easy list comparisons.
- **Move Semantics**: Utilizes move semantics for efficient memory management.
- **Clear Function**: Clears the list and deallocates memory.
- **Initializer List Constructor**: Construct a list using an initializer list.
- **Printing Functions**: Print the list in ascending or descending order.

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

## Examples

For more detailed usage examples, you can check the [examples](examples/) directory in this repository.

## Contributing

Contributions to Frankenstein's List are welcome! If you find any issues or have suggestions for improvements, please open an issue or submit a pull request on the [GitHub repository](https://github.com/your-repo-url).

