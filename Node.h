#ifndef FRANKENSTEIN_S_LIST_NODE_H
#define FRANKENSTEIN_S_LIST_NODE_H

template<typename T>
struct Node {
   explicit Node(T v, Node<T>* n = nullptr, Node<T>* p = nullptr, Node<T>* g = nullptr, Node<T>* l = nullptr)
        :val(v), next(n), prev(p), greater(g), lesser(l) {}

   T val;
   Node<T>* next;
   Node<T>* prev;
   Node<T>* greater;
   Node<T>* lesser;
};

#endif //FRANKENSTEIN_S_LIST_NODE_H
