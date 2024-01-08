// Created by Frank M. Carrano and Timothy M. Henry.
// Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.
// Modified: 
//   23 Feb 2021 - K. Walsh - Added comments, fixed formatting issues.
//
// Specification of ArrayStack, an array-based stack class, following the
// interface defined in StackInterface.
// This implementation does not use pointers or dynamically allocate any memory.
// Instead, it uses an array with fixed, constant capacity.
#ifndef ARRAY_STACK_
#define ARRAY_STACK_

#include "StackInterface.h"

template<class ItemType>
class ArrayStack : public StackInterface<ItemType> {

  public:

    // Default constructor, creates an empty stack.
    ArrayStack();

    // Note: this class does not use pointers or any dynamically allocated
    // memory, so the default compiler-provided copy-constructor,
    // assignment-operator, and destructor are sufficient.

    // Methods inherited from StackInterface.
    // See StackInterface.h for documentation.
    bool isEmpty() const;
    bool push(const ItemType& newEntry);
    bool pop();
    int compact(int i);
    ItemType peek() const;
    int size() const;

  protected:
    // This stack implementation uses a fixed size array to hold the stack
    // contents. Items are stored with the bottom-most stack item at position 0
    // in the array, and subsequent items are placed at higher positions. We
    // maintain a single integer, top, to indicate which position in the array
    // holds the top-most item. We set top to -1 when the stack is empty.
    // Invariant:
    //   Either top is -1, or array positions 0 through top are filled with
    //   valid items, with older items at lower positions and newer items at
    //   higher positions. The rest of the array (positions top+1 through
    //   DEFAULT_CAPACITY-1) are ignored.

    // Capacity used for all Stack objects.
    static const int DEFAULT_CAPACITY = 64;

    // An array to hold the contents of the stack. This is not dynamically
    // allocated. Instead, it is part of the stack object itself.
    ItemType items[DEFAULT_CAPACITY];

    // The index of the top-most item in the stack, or -1 if the stack is empty.
    int top;

}; // end ArrayStack

#include "ArrayStack.cpp"
#endif
