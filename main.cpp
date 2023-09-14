#include <iostream>
#include "FrankensteinList.h"


int main() {
    FrankensteinList<int> myList = {1, 2, 3, 4, 5, 6, 7, 8};
    FrankensteinList<int> list = {1, 99, 3, 55, 7, -1, 23};
    //myList.insertAt(7, 0);
    //myList.insertAt(3, 1);
    //myList.insertAt(15, 2);
    //myList.insertAt(14,3);
    //myList.printSortedAscendingOrder();
    //myList.printSortedDescendingOrder();
    //swap(myList, list);
    //FrankensteinList<int>::ConstIterator it = myList.cbegin(FrankensteinList<int>::IteratorType::asc_head);
    //for(; it != myList.cend(); ++it) {
    //    std::cout << *it << " ";
    //}
    //FrankensteinList<int> mergedList = merge(myList, list);
    //std::cout << mergedList;
    //std::cout << myList;
    //myList.unique();
    //myList.reverse();
    //myList.merge(list);
    //myList.erase(0, 9);
    //myList.sort();
    //myList.emplace_front(20);
    //myList.splice(2, list);
    myList.assign(5, 7);
    //myList.printSortedAscendingOrder();
    //myList.printSortedDescendingOrder();
    //myList.merge(list);
    std::cout << myList;
    return 0;
}
