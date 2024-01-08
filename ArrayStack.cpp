// Created by Frank M. Carrano and Timothy M. Henry.
// Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.
// Modified: 
//   23 Feb 2021 - K. Walsh - Added comments, fixed formatting issues.
// 
// Implementation of ArrayStack, an array-based stack class, following the
// interface defined in StackInterface.

#include "ArrayStack.h"
#include <cassert>

template<class ItemType>
ArrayStack<ItemType>::ArrayStack() {
  top = -1;
}  // end default constructor

template<class ItemType>
bool ArrayStack<ItemType>::isEmpty() const {
   return top < 0;
}  // end isEmpty

template<class ItemType>
bool ArrayStack<ItemType>::push(const ItemType& newEntry) {
   bool result = false;
   if (top < DEFAULT_CAPACITY - 1) // Does stack have room for newEntry?
   {
      top++;
      items[top] = newEntry;
      result = true;
   }  // end if

   return result;
}  // end push

template<class ItemType>
bool ArrayStack<ItemType>::pop() {
   bool result = false;
   if (!isEmpty())
   {
      top--;
      result = true;
   }  // end if

   return result;
}  // end pop

template<class ItemType>
int ArrayStack<ItemType>::compact(int k) {   
   ArrayStack<ItemType> stackB;

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
}  // compact()

template<class ItemType>
ItemType ArrayStack<ItemType>::peek() const {
   assert (!isEmpty()); // Enforce precondition during debugging

   // Stack is not empty; return top
   return items[top];
}  // end peek

template<class ItemType>
int ArrayStack<ItemType>::size() const {
  return (top+1);
}

