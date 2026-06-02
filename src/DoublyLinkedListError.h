//
// Created by mfbut on 11/24/2019.
//

#ifndef TESTDOUBLELINKEDLIST_DOUBLYLINKEDLISTERROR_H
#define TESTDOUBLELINKEDLIST_DOUBLYLINKEDLISTERROR_H
#include <exception>
#include <string>

 class DoublyLinkedListError : public std::exception{
 public:
  explicit DoublyLinkedListError(const std::string& msg) : msg_(msg) {}
  const char* what() const noexcept override { return msg_.c_str(); }
 private:
  std::string msg_;

};

#endif //TESTDOUBLELINKEDLIST_DOUBLYLINKEDLISTERROR_H
