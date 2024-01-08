/*******************************************************************
 * Name: Compaction.cpp
 * Date: Fall 2023
 * Course: CSCI 132
 * Assignment: Homework 3
 * Author: K. Walsh
 * Modified:
 *  17 Sep 2023 - K. Walsh - New code for testing Stack compaction.
 *
 * Purpose: This program is a test harness for the SetInterface::compact()
 * method. It tests the implementations of that method in either or both of
 * ArrayStack and LinkedStack.
 ***************************************************************************/

#include "ArrayStack.h"
#include "LinkedStack.h"
#include <iostream>
#include <cassert>

using namespace std;

// This function takes a pointer to an empty stack, adds ten numbers to the
// stack, then compacts it using the parameter k. Before and after calling the
// compact function, checks are made to ensure the stack seems to be in a
// reasonable state (correct size, correct value on top of stack, etc.)
void testCompactMethod(string kind, StackInterface<int> *stack, int k)
{
  // Push ten numbers on to the stack.
  cout << "Pushing ten powers of two, in order: 1, 2, 4, 8, ..., 512.\n";
  int pwr = 1;
  for (int i = 0; i < 10; i++) {
    stack->push(pwr);
    pwr *= 2;
  }

  // Make sure the stack seems reasonable.
  assert(stack->size() == 10); // should be 10 items in the stack
  assert(!stack->isEmpty()); // should not be empty
  assert(stack->peek() == 512); // 512 is 2 to the 9th power, should be on top

  // Call the compact() function.
  cout << "Calling " << kind << "::compact(" << k << ")\n";
  int removed = stack->compact(k);
  
  // For all the checks below, k>10 has the same effect as k=10.
  if (k > 10)
    k = 10;

  // Lastly, check the stack is still reasonable after calling compact().
  assert(removed == 10-k); // should have removed all but k items
  assert(stack->size() == k); // should be k items left
  // Let's pop them all and check the values just to make sure there are still k
  // numnbers, each with the expected power-of-two value.
  pwr = 512;
  for (int i = 0; i < k; i++) {
    assert(stack->peek() == pwr);
    pwr = pwr / 2;
    bool popped = stack->pop();
    assert(popped);
  }
  // At this point, the stack should be empty. Let's double check.
  assert(stack->isEmpty());
  assert(stack->size() == 0);
}

int main(void) {

  // We run a handful of differen tests, some for ArrayStack and some for
  // LinkedStack. The same tests are run for both classes.

  // You can comment out these next lines if you don't want to test ArrayStack.
  cout << "==== Beginning Test for ArrayStack ====\n";
  testCompactMethod("ArrayStack", new ArrayStack<int>(), 13);
  testCompactMethod("ArrayStack", new ArrayStack<int>(), 11);
  testCompactMethod("ArrayStack", new ArrayStack<int>(), 10);
  testCompactMethod("ArrayStack", new ArrayStack<int>(), 5);
  testCompactMethod("ArrayStack", new ArrayStack<int>(), 1);
  testCompactMethod("ArrayStack", new ArrayStack<int>(), 0);

  // You can comment out these next lines if you don't want to test LinkedStack.
  cout << "==== Beginning Test for LinkedStack ====\n";
  testCompactMethod("LinkedStack", new LinkedStack<int>(), 13);
  testCompactMethod("LinkedStack", new LinkedStack<int>(), 11);
  testCompactMethod("LinkedStack", new LinkedStack<int>(), 10);
  testCompactMethod("LinkedStack", new LinkedStack<int>(), 5);
  testCompactMethod("LinkedStack", new LinkedStack<int>(), 1);
  testCompactMethod("LinkedStack", new LinkedStack<int>(), 0);

  cout << "=== End of tests, no problems detected ====\n";
}
