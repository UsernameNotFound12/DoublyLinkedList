//
// Created by mfbut on 11/24/2019.
//

#ifndef DLLPROJECT_CONSTDOUBLYLINKEDLISTITERATOR_H
#define DLLPROJECT_CONSTDOUBLYLINKEDLISTITERATOR_H

#include <iterator>
#include "DoublyLinkedNode.h"
#include "DoublyLinkedListOutOfBoundsError.h"

template<typename T>
class ConstDoublyLinkedListIterator {
public:
    using iterator_category = std::bidirectional_iterator_tag;
    using iterator_concept = std::bidirectional_iterator_tag;
    using value_type = T;
    using reference = const value_type&;
    using pointer = const value_type*;
    using difference_type = ptrdiff_t;

    explicit ConstDoublyLinkedListIterator(const DoublyLinkedNode<T>* node = nullptr) : curNode(node) {}

    //are the two iterators equal?
    bool operator==(const ConstDoublyLinkedListIterator<T>& rhs) const {
        return curNode == rhs.curNode;
    }

    //are the two iterators different?
    bool operator!=(const ConstDoublyLinkedListIterator<T>& rhs) const {
        return !(*this == rhs);
    }

    //is the iterator safe to dereference?
    explicit operator bool() const { return curNode != nullptr; }

    //go to the next element
    ConstDoublyLinkedListIterator<T>& operator++() { //pre
        curNode = curNode->next;
        return *this;
    }
    const ConstDoublyLinkedListIterator<T> operator++(int) { //post
        auto tmp = *this;
        ++(*this);
        return tmp;
    }

    //go to the previous element
    ConstDoublyLinkedListIterator<T>& operator--() { //pre
        curNode = curNode->prev;
        return *this;
    }
    const ConstDoublyLinkedListIterator<T> operator--(int) { //post
        auto tmp = *this;
        --(*this);
        return tmp;
    }

    //get a reference to the value
    [[nodiscard]] reference operator*() const {
        if (!curNode) throw DoublyLinkedListOutOfBoundsError();
        return curNode->value;
    }

private:
    const DoublyLinkedNode<T>* curNode;
};

#endif //DLLPROJECT_CONSTDOUBLYLINKEDLISTITERATOR_H
