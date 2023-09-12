#include <iostream>
#include "FrankensteinList.h"


int main() {
    FrankensteinList<int> myList = {5, 3, 4 ,6, 7, 2};
    myList.pop_back();
    //myList.insertAt(7, 0);
    //myList.insertAt(3, 1);
    //myList.insertAt(15, 2);
    //myList.insertAt(14,3);
    myList.printSortedAscendingOrder();
    myList.printSortedDescendingOrder();
    //std::cout << list;

    return 0;
}
