// Created by Frank M. Carrano and Timothy M. Henry.
// Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.
// Modified: 
//   23 Feb 2021 - K. Walsh - Added comments, fixed formatting issues.
// Specification of StackInterface, an abstract class representing a stack.

#ifndef STACK_INTERFACE_
#define STACK_INTERFACE_

template<class ItemType>
class StackInterface {
  public:
    // isEmpty() checks if this stack is empty.
    // Returns true if the stack is empty, and false otherwise.
    virtual bool isEmpty() const = 0;

    // push(newEntry) adds a new item on the top of this stack.
    // Returns:
    //   true if the new item was successfully added, and
    //   false otherwise, e.g. if there was no space remaining.
    // Postcondition:
    //   If successful, newEntry is now at the top of this stack,
    //   otherwise the stack is left unmodified.
    virtual bool push(const ItemType& newEntry) = 0;

    /** Removes the top of this stack.
     @post  If the operation was successful, the top of the stack has been removed.
     @return  True if the removal is successful or false if not. */
    // pop() removes (and discards) an item from the top of the stack.
    // Returns:
    //   true if an item was successfully removed, and 
    //   false otherwise, i.e. if the stack was empty.
    // Postcondition:
    //   If successful, the top of the stack has been removed, otherwise
    //   the stack is left unmodified.
    // Note:
    //   If the items stored in this stack are pointers to dynamically allocated
    //   objects, it is the client's responsibility to delete those objects. The
    //   pop() function removes an item from the stack, but does not invoke
    //   'delete' to free any dynamically allocated memory that might be
    //   associated with that item.
    virtual bool pop() = 0;

    // peek() gets a copy of the item at the top of the stack.
    // Returns:
    //   A copy of the item at the top of the stack.
    // Precondition:
    //   The stack must not be empty.
    virtual ItemType peek() const = 0;

     
    // compact () removes items from the bottom of the stack until there are only k items remaining. 
    // Returns:
    //   An integar result of items removed
    // Precondition:
    //   The stack must not be empty.
   virtual int compact(int i) = 0;

    // size() gets the size of this stack.
    // Returns:
    //   The number of items currently stored in the stack.
    virtual int size() const = 0;

    // The destructor destroys this stack and frees any allocated memory.
    virtual ~StackInterface() { }

}; // end StackInterface

#endif
