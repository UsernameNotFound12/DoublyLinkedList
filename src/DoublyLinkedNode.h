//
// Created by mfbut on 2/11/2019.
//

#ifndef LINKEDLIST_DOUBLELINKEDNODE_H
#define LINKEDLIST_DOUBLELINKEDNODE_H

template<typename T>
class DoublyLinkedNode {
 public:
  //your methods
 explicit DoublyLinkedNode(const T& val, DoublyLinkedNode<T>* prev = nullptr, DoublyLinkedNode<T>* next = nullptr)
     : value(val), next(next), prev(prev) {}
 T value;
 DoublyLinkedNode<T>* next;
 DoublyLinkedNode<T>* prev;

};

#endif //LINKEDLIST_DOUBLELINKEDNODE_H
