// Specification of Card class and related types to represent a single playing card.
// Author: CSCI 132 Instructors
// Date: Fall 2020 
// Modified:
//  23 Feb 2021 - K. Walsh - Reformatted and added comments. Removed unnecessary
//       includes and namespace lines. Added new toString() method, and renamed
//       or removed some other methods.
//  17 Sep 2023 - K. Walsh - Rewrote for Sunset game.

#ifndef CARD_
#define CARD_

#include <string>
#include <ostream>

// In the Sunset game, each card has a shape, a color, and an arrangement. For
// example, there is a Blue-Pair-Squiggle card, with a pair of blue squiggles. And
// there is a Red-Many-Box card, with a bunch of red boxes on it.

// CardShape is a data type representing the possible shapes for cards. You can
// mostly treat CardShape just like 'int', and can treat the values (OVAL, BOX,
// SQUIGGLE, and LINE) just like constants, each having a different integer value.
// The value of the shapes is not very meaningful, but it is sequential starting
// with OVAL, counting up to LINE.
enum CardShape { OVAL = 1, BOX, SQUIGGLE, LINE };

// CardArrangement is a data type representing the possible arrangements that
// appear on cards. You can mostly treat CardArrangement just like 'int', and
// can treat the values (LONE, PAIR, etc.) just like constants, each having a
// different integer value. The actual numerical value of the cards is as you
// would expect, with LONE equal to 1, PAIR equal to 2, TRIPLET equal to 3,
// and so on.
enum CardArrangement { LONE = 1, PAIR, TRIPLET, MANY };

// CardColor is a data type representing the possible colors that appear on
// cards. You can mostly treat CardColor just like 'int', and can treat the
// values (RED, GREEN, etc.) just like constants, each having a different
// integer value. The actual numerical value of the cards is as you would
// expect, with RED equal to 1, GREEN equal to 2, and so on.
enum CardColor { RED = 1, GREEN, BLUE, YELLOW };

// A Card object represents a single playing card. Card objects are
// immutable: none of the methods modify the object in any way.
class Card {
  
  public:

    // Construct a new "Red-Lone-Oval" card.
    Card();

    // Construct a new card with the given color, arrangement, and shape.
    Card(CardColor color, CardArrangement arrangement, CardShape shape); 

    // Get the color of this card.
    CardColor getColor() const;

    // Get the arrangement of this card.
    CardArrangement getArrangement() const;

    // Get the shape of this card.
    CardShape getShape() const;  

    // Print the color of this card to standard output, in a nice format.
    void printColor() const;

    // Print the arrangement of this card to standard output, in a nice format.
    void printArrangement() const;

    // Print the shape of this card to standard output, in a nice format.
    void printShape() const;

    // Print a description of this card to standard output, in a nice format.
    void printCard() const;

    // Get a description of this card, in a nice format.
    std::string toString() const;

    // These next two methods are used to compare two cards for equality.
    friend bool operator== (const Card& c1, const Card& c2);
    friend bool operator!= (const Card& c1, const Card& c2);
 
    // This method is the same as toString(), but will be called automatically by C++.
    operator std::string() const { return toString(); }

  private:
    CardColor color;
    CardArrangement arrangement;
    CardShape shape;

    // Note: these must go in the same order as the CardShape enum, above.
    static const std::string shapeDescriptions[];

    // Note: these must go in the same order as the CardArrangement enum, above.
    static const std::string arrangementDescriptions[];

    // Note: these must go in the same order as the CardColor enum, above.
    static const std::string colorDescriptions[];
};

// This last unusual function allows a Card object to be printed to cout using
// the "<<" operator, like this:
//   Card x = ...;
//   cout << "You have a " << x << ", how nice!\n";
std::ostream& operator<<(std::ostream& outstream, const Card &c);

#endif
