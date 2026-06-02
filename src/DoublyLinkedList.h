//
// Created by mfbut on 2/11/2019.
//

#ifndef LINKEDLIST_DOUBLYLINKEDLIST_H
#define LINKEDLIST_DOUBLYLINKEDLIST_H

#include <vector>
#include <memory>
#include "DoublyLinkedNode.h"
#include "DoublyLinkedListEmptyError.h"
#include "ConstDoublyLinkedListIterator.h"
#include "DoublyLinkedListIterator.h"
#include "ConstReverseDoublyLinkedIterator.h"
#include "ReverseDoublyLinkedListIterator.h"

template<typename T>
class DoublyLinkedList {
public:
    using Node_Ptr = DoublyLinkedNode<T>*;

    using iterator = DoublyLinkedListIterator<T>; //put the type of your iterator here
    using const_iterator = ConstDoublyLinkedListIterator<T>; //put the type of your const iterator here
    using reverse_iterator = ReverseDoublyLinkedListIterator<T>; //put the type of your reverse iterator here
    using const_reverse_iterator = ConstReverseDoublyLinkedListIterator<T>;
    //put the type of your const reverse iterator here

    //create a Doubly Linked List that has the same values
    //as in the vector and in the same order
    explicit DoublyLinkedList(const std::vector<T>& values) : DoublyLinkedList() {
        for (const auto& v : values) push_back(v);
    }

    //create an empty DoublyLinkedList
    DoublyLinkedList() : head_(nullptr), tail_(nullptr), size_(0) {}


    virtual ~DoublyLinkedList() { clear(); }

    //remove all of the elements from your list
    void clear() {
        while (!empty()) pop_front();
    }

    //get a reference to the front element in the list
    const T& front() const {
        if (empty()) throw DoublyLinkedListEmptyError();
        return head_->value;
    }

    T& front() {
        if (empty()) throw DoublyLinkedListEmptyError();
        return head_->value;
    }

    //get a reference to the last element in the list
    [[nodiscard]] const T& back() const {
        if (empty()) throw DoublyLinkedListEmptyError();
        return tail_->value;
    }

    [[nodiscard]] T& back() {
        if (empty()) throw DoublyLinkedListEmptyError();
        return tail_->value;
    }

    //add a value to the front of the list
    void push_front(const T& value) {
        auto* node = new DoublyLinkedNode<T>(value, nullptr, head_);
        if (empty()) { head_ = tail_ = node; }
        else { head_->prev = node; head_ = node; }
        ++size_;
    }

    //add a value to the back of the list
    void push_back(const T& value) {
        auto* node = new DoublyLinkedNode<T>(value, tail_, nullptr);
        if (empty()) { head_ = tail_ = node; }
        else { tail_->next = node; tail_ = node; }
        ++size_;
    }

    void pop_front() {
        auto* old = head_;
        head_ = head_->next;
        if (head_) head_->prev = nullptr;
        else       tail_ = nullptr;
        delete old;
        --size_;
    }

    void pop_back() {
        auto* old = tail_;
        tail_ = tail_->prev;
        if (tail_) tail_->next = nullptr;
        else       head_ = nullptr;
        delete old;
        --size_;
    }

    //is the list empty?
    [[nodiscard]] bool empty() const { return size_ == 0; }

    //return the number of elements in the list
    [[nodiscard]] int size() const { return size_; }

    //return a constant bidirectional iterator to the front of the list
    [[nodiscard]] const_iterator begin() const { return const_iterator(head_); }

    [[nodiscard]] const_iterator end() const { return const_iterator(nullptr); }

    //return a nonconstant bidirectional iterator to the front of the list
    [[nodiscard]] iterator begin() { return iterator(head_); }

    [[nodiscard]] iterator end() { return iterator(nullptr); }

    [[nodiscard]] const_reverse_iterator crbegin() const { return const_reverse_iterator(tail_); }

    [[nodiscard]] const_reverse_iterator crend() const { return const_reverse_iterator(nullptr); }

    [[nodiscard]] reverse_iterator rbegin() { return reverse_iterator(tail_); }

    [[nodiscard]] reverse_iterator rend() { return reverse_iterator(nullptr); }

    //insert the value at the position in the list
    //I promise not to use the iterator again after the insertion is done
    //An example if we had the list 1 <-> 9 <-> 17
    //And the iterator was pointing to the 9 and we wanted to
    //insert -22 the result would be
    //1 <-> 22 <-> 9 <-> 17
    void insert(iterator& position, const T& value) {
        if (!position) { push_back(value); return; }
        auto* cur = position.getCurNode();
        if (cur == head_) { push_front(value); return; }
        auto* node = new DoublyLinkedNode<T>(value, cur->prev, cur);
        cur->prev->next = node;
        cur->prev = node;
        ++size_;
    }

    //remove the element at the position pointed to
    //by the iterator.
    //I promise not to use the iterator again after the erase is done
    //An example if we had the list 1 <-> 9 <-> 17
    //And when the wanted to erase the iterator was at the 9
    //1 <-> 17
    void erase(iterator& position) {
        auto* cur = position.getCurNode();
        if (cur == head_ && cur == tail_) {
            head_ = tail_ = nullptr;
        } else if (cur == head_) {
            head_ = cur->next;
            head_->prev = nullptr;
        } else if (cur == tail_) {
            tail_ = cur->prev;
            tail_->next = nullptr;
        } else {
            cur->prev->next = cur->next;
            cur->next->prev = cur->prev;
        }
        delete cur;
        --size_;
    }

private:
    // your class members
    DoublyLinkedNode<T>* head_;
    DoublyLinkedNode<T>* tail_;
    int size_;
};

//write to the stream each element in the list in order
//with a space in between them
template<typename T>
std::ostream& operator<<(std::ostream& out, const DoublyLinkedList<T>& doublyLinkedList) {
    auto it = doublyLinkedList.begin();
    while (it != doublyLinkedList.end()) {
        out << *it;
        ++it;
        if (it != doublyLinkedList.end()) out << " ";
    }
    return out;
}

//read elements from the stream as long as it is good
// or until a newline (\n) is encountered
//if a newline is encountered it should be consumed
template<typename T>
std::istream& operator>>(std::istream& in, DoublyLinkedList<T>& doublyLinkedList) {
    T value;
    while (in.good() && in.peek() != '\n') {
        if (in >> value) doublyLinkedList.push_back(value);
    }
    if (in.peek() == '\n') in.ignore();
    return in;
}

#endif //LINKEDLIST_DOUBLYLINKEDLIST_H
