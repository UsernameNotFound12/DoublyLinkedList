//
// Created by mfbut on 11/24/2019.
//

#ifndef DLLPROJECT_DOUBLYLINKEDLISTITERATOR_H
#define DLLPROJECT_DOUBLYLINKEDLISTITERATOR_H

#include <iterator>
#include "DoublyLinkedNode.h"

template <typename T>
class DoublyLinkedListIterator {
 public:
  using iterator_category = std::bidirectional_iterator_tag;
  using iterator_concept  = std::bidirectional_iterator_tag;
  using value_type = T;
  using reference = value_type&;
  using const_reference = const value_type&;
  using pointer = value_type*;
  using const_pointer = const value_type*;
  using difference_type = ptrdiff_t;

  explicit DoublyLinkedListIterator(DoublyLinkedNode<T>* node = nullptr) : curNode(node) {}

  //are the two iterators equal?
  bool operator==(const DoublyLinkedListIterator<T>& rhs) const {
   return curNode == rhs.curNode;
  }
  //are the two iterators different?
  bool operator!=(const DoublyLinkedListIterator<T>& rhs) const {
   return !(*this == rhs);
  }
  //is the iterator safe to dereference?
  explicit operator bool() const { return curNode != nullptr; }


  //go to the next element
  DoublyLinkedListIterator<T>& operator++() { //pre
   curNode = curNode->next;
   return *this;
  }
  const DoublyLinkedListIterator<T> operator++(int) { //post
   auto tmp = *this;
   ++(*this);
   return tmp;
  }

  //go to the previous element
  DoublyLinkedListIterator<T>& operator--() { //pre
   curNode = curNode->prev;
   return *this;
  }
  const DoublyLinkedListIterator<T> operator--(int) { //post
   auto tmp = *this;
   --(*this);
   return tmp;
  }

  //get a reference to the value
  [[nodiscard]] const_reference operator*() const {
   if (!curNode) throw DoublyLinkedListOutOfBoundsError();
   return curNode->value;
  }
  [[nodiscard]] reference operator*() {
   if (!curNode) throw DoublyLinkedListOutOfBoundsError();
   return curNode->value;
  }
  DoublyLinkedNode<T>*& getCurNode() { return curNode; }
  const DoublyLinkedNode<T>*& getCurNode() const {
   return reinterpret_cast<const DoublyLinkedNode<T>*&>(curNode);
  }

 private:
  DoublyLinkedNode<T>* curNode;
};



#endif //DLLPROJECT_DOUBLYLINKEDLISTITERATOR_H
