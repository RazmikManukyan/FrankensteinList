#include <iostream>
#include "FrankensteinList.h"


int main() {
    FrankensteinList<int> myList = {5, 6, 2, 1, 8, 1, 9, 0};
    //myList.insertAt(7, 0);
    //myList.insertAt(3, 1);
    //myList.insertAt(15, 2);
    //myList.insertAt(14,3);
    //myList.printSortedAscendingOrder();
    //myList.printSortedDescendingOrder();
    //swap(myList, list);
    for(FrankensteinList<int>::Iterator it = myList.beginAscending(); it != myList.endAscending(); ++it) {
        std::cout << *it << " ";
    }

    //std::cout << myList;

    return 0;
}
