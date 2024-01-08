// File: LinkedSet.h
// Description: Specification for the LinkedSet data type
// Author: K. Walsh
// Class: CSCI 132
// Date: 25 July 2020

#include "LinkedSet.h"
#include <cassert>
#include <cstdlib> // for rand()
#include <iostream>
#include <iomanip>
#include <string>

template<class ItemType>
LinkedSet<ItemType>::LinkedSet() : head(nullptr)
{
}  // end default constructor
    
template<class ItemType>
LinkedSet<ItemType>::LinkedSet(const LinkedSet<ItemType>& original)
{
   // Point to nodes in original chain
   Node<ItemType>* origChainPtr = original.head;
   
   if (origChainPtr == nullptr)
      head = nullptr;  // Original set is empty
   else
   {
      // Copy first node
      head = new Node<ItemType>();
      head->setItem(origChainPtr->getItem());
      
      // Point to first node in new chain
      Node<ItemType>* newChainPtr = head;
      
      // Advance original-chain pointer
      origChainPtr = origChainPtr->getNext();
      
      // Copy remaining nodes
      while (origChainPtr != nullptr)
      {
         // Get next item from original chain
         ItemType nextItem = origChainPtr->getItem();
         
         // Create a new node containing the next item
         Node<ItemType>* newNodePtr = new Node<ItemType>(nextItem);
         
         // Link new node to end of new chain
         newChainPtr->setNext(newNodePtr);
         
         // Advance pointer to new last node
         newChainPtr = newChainPtr->getNext();
         
         // Advance original-chain pointer
         origChainPtr = origChainPtr->getNext();
      }  // end while
      
      newChainPtr->setNext(nullptr);           // Flag end of chain
   }  // end if
}  // end copy constructor

template<class ItemType>
LinkedSet<ItemType>::~LinkedSet()
{
	clear();
}  // end destructor

template<class ItemType>
int LinkedSet<ItemType>::size() const
{
	int count = 0;
  Node<ItemType>* p = head;
  while (p != nullptr)
  {
    count++;
    p = p->getNext();
  }
  return count;
}  // end size

template<class ItemType>
bool LinkedSet<ItemType>::isEmpty() const
{
	return (head == nullptr);
}  // end isEmpty

template<class ItemType>
bool LinkedSet<ItemType>::add(const ItemType &anItem)
{
  bool wasPresent = contains(anItem);
  if (!wasPresent)
    head = new Node<ItemType>(anItem, head);
  return wasPresent;
}  // end add

template<class ItemType>
bool LinkedSet<ItemType>::remove(const ItemType& anItem)
{
  if (head == nullptr)
  {
    return false; // empty, so nothing to remove
  }
  else if (head != nullptr && head->getItem() == anItem) {
    Node<ItemType>* oldHead = head;
    head = head->getNext();
    delete oldHead;
    return true; // item was at head, and we removed it
  }
  else
  {
    // search for the item somewhere beyond head of linked list
    Node<ItemType>* prev = head;
    Node<ItemType>* cur = head->getNext();
    bool found = false;
    while (cur != nullptr && !found)
    {
      found = (cur->getItem() == anItem);
      if (!found)
      {
        prev = cur;
        cur = cur->getNext();
      }
    }
    if (found)
    {
      Node<ItemType>* next = cur->getNext();
      prev->setNext(next);
      delete cur;
    }
    return found;
  }
}  // end remove

template<class ItemType>
void LinkedSet<ItemType>::clear()
{
  while (head != nullptr)
  {
    Node<ItemType>* oldHead = head;
    head = head->getNext();
    delete oldHead;
  }
}  // end clear

template<class ItemType>
bool LinkedSet<ItemType>::contains(const ItemType& anItem) const
{
  Node<ItemType>* cur = head;
  bool found = false;
  while (cur != nullptr && !found)
  {
    found = (cur->getItem() == anItem);
    cur = cur->getNext();
  }
  return found;
}  // end contains

template<class ItemType>
std::vector<ItemType> LinkedSet<ItemType>::toVector() const
{
  std::vector<ItemType> vec;
  Node<ItemType>* cur = head;
  while (cur != nullptr)
  {
    vec.push_back(cur->getItem());
    cur = cur->getNext();
  }
  return vec;
}  // end toVector

template<class ItemType>
ItemType LinkedSet<ItemType>::get(int i) const
{
  assert(0 <= i && i < size());

	int pos = 0;
  Node<ItemType>* p = head;
  while (pos != i)
  {
    pos++;
    p = p->getNext();
  }
  return p->getItem();
}  // end get
  
template<class ItemType>
ItemType LinkedSet<ItemType>::pickRandom() const
{
  int i = rand() % size();
  return get(i);
}

template<class ItemType>
ItemType LinkedSet<ItemType>::removeRandom()
{
  // For a small set, this implementation is fine:
  ItemType item = pickRandom();
  remove(item);
  return item;
  // Note: for a large set, this is inefficient, as it traverses the linked
  // chain twice: once to pick an item at random, then a second time to find
  // that same item and remove it. A more efficient version would only
  // traverses the chain once to do both operations.
}
    
template<class ItemType>
std::string LinkedSet<ItemType>::toString() const
{
  std::string result = "";
  Node<ItemType>* p = head;
  while (p != nullptr) {
    if (p != head)
      result += ", ";
    result += p->getItem();
    p = p->getNext();
  }
  return result;
}

template<class ItemType>
void LinkedSet<ItemType>::print() const
{
  Node<ItemType>* p = head;
  while (p != nullptr) {
    if (p != head)
      std::cout << ", ";
    std::cout << p->getItem();
    p = p->getNext();
  }
}

template<class ItemType>
void LinkedSet<ItemType>::printWithColumns(int numColumns) const
{
  if (numColumns < 1)
    numColumns = 3;
  int n = size();
  // Divide by numColumns to calculate how many items per column. The arithmetic
  // used here is a clever way to round up to the nearest whole number.
  int itemsPerColumn = (n + numColumns - 1) / numColumns;
  
  // Next, get a pointer to the first item in each column.
  Node<ItemType>** ptrs = new Node<ItemType>*[numColumns];
  Node<ItemType>* p = head;
  for (int i = 0; i < n; i++) {
    if ((i % itemsPerColumn) == 0)
      ptrs[i / itemsPerColumn] = p;
    p = p->getNext();
  }
  
  // Next, print all the items
  for (int i = 0; i < itemsPerColumn; i ++ ) {
    for (int col = 0; col < numColumns; col++) {
      if (ptrs[col] != nullptr) {
        std::cout << "   "; // space before column
        std::cout << std::setw(3) << std::right << (col*itemsPerColumn+i+1) << ". "; // number
        std::cout << std::setw(30) << std::left << ptrs[col]->getItem(); // item
        ptrs[col] = ptrs[col]->getNext(); 
      }
    }
    std::cout << "\n"; // end of line
  }

  delete[] ptrs;
}
