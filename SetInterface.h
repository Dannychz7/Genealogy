// File: SetInterface.h
// Description: Specification and implementation for the SetInterface data type
// Author: K. Walsh
// Class: CSCI 132
// Date: 25 July 2020

#ifndef SET_INTERFACE_
#define SET_INTERFACE_

#include <vector>

/** A Set holds a collection of items, where no item can appear more
 than once, and the order of items does not matter. If an item is
 already in the Set, attempting to add it again will do nothing.

 A Set is similar to a Bag, except items in a bag can be repeats.
 There is no getFrequencyOf() method for Set, as there is for Bag,
 because the frequency of an item in a Set is always 1.
 
 Note: As items are added and removed, the items can change
 position, so clients should not rely on the items staying in any
 particular fixed order. However, so long as the Set is not
 modified, the items will obviously not change positions, so it is
 okay to iterate over the items, so long as the Set isn't changed
 during the iteration. */
template<class ItemType>
class SetInterface
{
public:
   /** Gets the current number of items in this Set.
    @return  The integer number of items currently in the Set. */
   virtual int size() const = 0;
   
   /** Sees whether this Set is empty.
    @return  True if the Set is empty, or false if not. */
   virtual bool isEmpty() const = 0;

   /** Adds a new item to this Set, if it isn't yet present.
     If the item was already present, then the Set is left unchanged.
     Otherwise, the item is added to the set.
     @post  The item will be in the set.
     @post  The number of items will either be left unchanged, or
            increased by 1.
    @return  true if the item was newly added, false if it was already
             present. */
   virtual bool add(const ItemType& item) = 0;

   /** Removes an item from this Set, if it is present.
     If the item was not already present, then the Set is left unchanged.
     Otherwise, the item is removed from the set.
     @post  The item will not be in the set.
     @post  The number of items will either be left unchanged, or
            decreased by 1.
    @return  true if the item was newly removed, false if it was already
             not present. */
   virtual bool remove(const ItemType& item) = 0;
   
   /** Removes all items from this Set.
    @post  Set contains no items, and the count of items is 0. */
   virtual void clear() = 0;
   
   /** Tests whether this Set contains a given item.
    @param item  The item to locate.
    @return  True if Set contains item, or false otherwise. */
   virtual bool contains(const ItemType& item) const = 0;
   
   /** Returns a new vector with the items that are in this Set.
    @return  A vector containing all the items in the Set. */
   virtual std::vector<ItemType> toVector() const = 0;

   /** Returns one of the items in this Set. 
    @pre  i is between 0 and size()-1, inclusive
    @return  One of the items. */
   virtual ItemType get(int i) const = 0; // fixme: should return type be reference?

   /** Returns a random item from this Set.
    @pre  the Set is not empty.
    @return  One of the items. */
   virtual ItemType pickRandom() const = 0; // fixme: should return type be reference?

   /** Removes and returns a random item from this Set.
    @pre  the Set is not empty.
    @post One of the items of the set is removed.
    @return  The item that was removed. */
   virtual ItemType removeRandom() = 0;

   /** Destroys this Set and frees its assigned memory. (See C++ Interlude 2.) */
   virtual ~SetInterface() { }
}; // end SetInterface

#endif
