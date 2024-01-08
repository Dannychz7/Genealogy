// File: LinkedSet.h
// Description: Specification for the LinkedSet data type
// Author: K. Walsh
// Class: CSCI 132
// Date: 25 July 2020

#ifndef LINKED_SET_H_
#define LINKED_SET_H_

#include "SetInterface.h"
#include "Node.h"
#include <string>

template<class ItemType>
class LinkedSet : public SetInterface<ItemType>
{
  private:
    Node<ItemType>* head; // Pointer to first node in the chain

  public:
    // Constructors and destructor:
    LinkedSet();                                    // Default constructor
    LinkedSet(const LinkedSet<ItemType>& original); // Copy constructor 
    virtual ~LinkedSet();                           // Destructor

    // Set operations:
    int size() const;
    bool isEmpty() const;
    bool add(const ItemType& anItem);
    bool remove(const ItemType& anItem);
    void clear();
    bool contains(const ItemType& anItem) const;
    std::vector<ItemType> toVector() const;
    ItemType get(int i) const; // fixme: should return type be reference?
    ItemType pickRandom() const; // fixme: should return type be reference?
    ItemType removeRandom();
    void print() const; // prints items all on one line, with commas and spaces.
    void printWithColumns(int numColumns) const; // prints in columns, numbered.
    std::string toString() const;
};  // end LinkedSet

#include "LinkedSet.cpp"
#endif
