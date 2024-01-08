// Specification of Deck class to store a deck of playing cards.
// Author: CSCI 132 Instructors
// Date: Fall 2020 
// Modified:
//  23 Feb 2021 - K. Walsh - Reformatted comments.
//       implement using Stack instead of array. Change shuffle behavior
//       so it must be called multiple times. Add and rename methods.
//  17 Sep 2023 - K. Walsh - Rewrote for Sunset game.

#include "Card.h"
#include "Deck.h"
#include "ArrayStack.h"
#include <cassert>

Deck::Deck() {
  pile = new ArrayStack<Card>();
  for (int c = RED; c <= YELLOW; c++) {
    for (int a = LONE; a <= MANY; a++) {
      for (int s = OVAL; s <= LINE; s++) {
        pile->push(Card((CardColor)c, (CardArrangement)a, (CardShape)s));
      }
    }
  }
} // end default constructor

Deck::~Deck() {
  delete pile;
  pile = nullptr;
} // end destructor

void Deck::shuffle() {
  int n = pile->size();

  // Shuffling a pile with only 1 cards, or no cards, is pointless.
  if (n < 2)
    return;

  // Divide the pile into two stacks, of roughly equal size.
  // Pick a cut, roughly 25-75% of the way through the pile.
  // Note: Since n >= 2, then n*1/4 is always less than or
  // equal to n*3/4, which is a precondition for randInRange().
  int cut = randInRange(n*1/4, n*3/4);
  ArrayStack<Card> stacks[2];
  for (int i = 0; i < cut; i++) {
    Card c = pile->peek();
    pile->pop();
    stacks[0].push(c);
  }
  while (!isEmpty()) {
    Card c = pile->peek();
    pile->pop();
    stacks[1].push(c);
  }

  // Now put all the cards back into a single pile, picking
  // at random from the two smaller stacks.
  while (!stacks[0].isEmpty() || !stacks[1].isEmpty()) {
    int i;
    if (stacks[0].isEmpty()) 
      i = 1;
    else if (stacks[1].isEmpty()) 
      i = 0;
    else
      i = randInRange(0, 1);
    Card c = stacks[i].peek();
    stacks[i].pop();
    pile->push(c);
  }
} // end shuffle()

Card Deck::dealCard() {
  assert(!pile->isEmpty());
  Card c = pile->peek();
  pile->pop();
  return c;
} // end dealCard()

bool Deck::isEmpty() const {
  return pile->isEmpty();
}

int Deck::randInRange(int lo, int hi)
{
  double v = (double)rand();    // 0 <= v && v <= RAND_MAX
  double f = v / ((double)RAND_MAX+1);  // 0 <= f && f < 1.0
  return lo + (int)(f * (hi - lo + 1));
}  // end randInRange

