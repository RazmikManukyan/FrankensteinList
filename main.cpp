#include <iostream>
#include "FrankensteinList.h"


int main() {
    FrankensteinList<int> myList = {3, 4 ,6, 7, 5, 9};
    FrankensteinList<int> list = {2, 5, 1, 6, 9, 3};
    //myList.insertAt(7, 0);
    //myList.insertAt(3, 1);
    //myList.insertAt(15, 2);
    //myList.insertAt(14,3);
    //myList.printSortedAscendingOrder();
    //myList.printSortedDescendingOrder();
    swap(myList, list);
    std::cout << myList;

    return 0;
}
