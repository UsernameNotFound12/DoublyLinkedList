//
// Created by mfbut on 11/24/2019.
//

#ifndef TESTDOUBLELINKEDLIST_DOUBLYLINKEDLISTEMPTYERROR_H
#define TESTDOUBLELINKEDLIST_DOUBLYLINKEDLISTEMPTYERROR_H
#include "DoublyLinkedListError.h"

class DoublyLinkedListEmptyError : public DoublyLinkedListError {
    public:
        DoublyLinkedListEmptyError() : DoublyLinkedListError("operation cannot be performed on an empty list") {}
};


#endif //TESTDOUBLELINKEDLIST_DOUBLYLINKEDLISTEMPTYERROR_H
