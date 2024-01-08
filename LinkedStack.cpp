//  Created by Frank M. Carrano and Timothy M. Henry.
//  Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.

/** Listing 7-4.
    @file LinkedStack.cpp */

#include <cassert>        // For assert
#include "LinkedStack.h"  // Header file

template<class ItemType>
LinkedStack<ItemType>::LinkedStack() : topPtr(nullptr)
{
}  // end default constructor

template<class ItemType>
LinkedStack<ItemType>::LinkedStack(const LinkedStack<ItemType>& aStack)
{
  // Point to nodes in original chain
  Node<ItemType>* origChainPtr = aStack.topPtr;

  if (origChainPtr == nullptr)
    topPtr = nullptr;  // Original stack is empty
  else
  {
    // Copy first node
    topPtr = new Node<ItemType>();
    topPtr->setItem(origChainPtr->getItem());

    // Point to first node in new chain
    Node<ItemType>* newChainPtr = topPtr;

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
LinkedStack<ItemType>::~LinkedStack()
{
  // Pop until stack is empty
  while (!isEmpty())
    pop();
}  // end destructor

template<class ItemType>
bool LinkedStack<ItemType>::push(const ItemType& newItem)
{
  Node<ItemType>* newNodePtr = new Node<ItemType>(newItem, topPtr);				
  topPtr = newNodePtr;
  newNodePtr = nullptr;

  return true;
}  // end push

template<class ItemType>
bool LinkedStack<ItemType>::pop()
{
  bool result = false;
  if (!isEmpty())
  {
    // Stack is not empty; delete top
    Node<ItemType>* nodeToDeletePtr = topPtr;
    topPtr = topPtr->getNext();

    // Return deleted node to system
    nodeToDeletePtr->setNext(nullptr);
    delete nodeToDeletePtr;
    nodeToDeletePtr = nullptr;

    result = true;
  }  // end if

  return result;	
}  // end pop

template<class ItemType>
int LinkedStack<ItemType>::compact(int k) 
{
  LinkedStack<ItemType> stackB;

  if(size() < k) 
  {
    return 0;
  } else 
  {
    while(!isEmpty()) 
    {
      stackB.push(peek());
      pop();
    }

    int throwAway = stackB.size() - k;
    for(int i = 0; i < throwAway; i++) 
    {
      stackB.pop();
    }
      
    while(!stackB.isEmpty()) 
    {
      push(stackB.peek());
      stackB.pop();
    }  
    
    return throwAway;
  }
}


template<class ItemType>	
ItemType LinkedStack<ItemType>::peek() const
{
  assert(!isEmpty());  // Enforce precondition during debugging

  return topPtr->getItem();

}  // end peek

template<class ItemType>
bool LinkedStack<ItemType>::isEmpty() const
{
  return topPtr == nullptr;
}  // end isEmpty

template<class ItemType>
int LinkedStack<ItemType>::size() const
{
  // This Stack implmentation does not have a dedicated variable to store the
  // count of items, so we need to loop through the linked chain instead.
  int count = 0;
  Node<ItemType>* curPtr = topPtr; // start at beginning of chain
  while (curPtr != nullptr) { // loop until the end
    count++;
    curPtr = curPtr->getNext(); // move one step forward in chain
  }
  return count;
}
  

// End of implementation file.
