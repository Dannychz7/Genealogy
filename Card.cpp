// Author: CSCI 132 Instructors
// Date: Fall 2020 
// Modified:
//  23 Feb 2021 - K. Walsh - Reformatted and added comments. Removed unnecessary
//       includes and namespace lines. Added new toString() method, and renamed
//       or removed some other methods.

#include "Card.h"
#include <iostream>
#include <iomanip>
#include <cassert>

using namespace std;

static const bool USE_TERMINAL_COLORS = true;

const std::string Card::shapeDescriptions[] = {
  "Oval", "Box", "Squiggle", "Line"
};

const std::string Card::arrangementDescriptions[] = {
  "Lone", "Pair", "Triplet", "Many"
};

const std::string Card::colorDescriptions[] = {
  "Red", "Green", "Blue", "Yellow"
};

Card::Card() {
  color = RED;
  arrangement = LONE;
  shape = OVAL;
}

Card::Card(CardColor color, CardArrangement arrangement, CardShape shape) {
  assert(RED <= color && color <= YELLOW);
  assert(LONE <= arrangement && arrangement <= MANY);
  assert(OVAL <= shape && shape <= LINE);
  this->color = color;
  this->arrangement = arrangement;
  this->shape = shape;
}
    
CardColor Card::getColor() const {
  return color;
}

CardArrangement Card::getArrangement() const {
  return arrangement;
}

CardShape Card::getShape() const {
  return shape;
}

void Card::printColor() const {
  int i = color - RED;
  cout << colorDescriptions[i];
}

void Card::printArrangement() const {
  int j = arrangement - LONE;
  cout << arrangementDescriptions[j];
}

void Card::printShape() const {
  int k = shape - OVAL;
  cout << shapeDescriptions[k];
}

void Card::printCard() const {
  cout << toString();
}

std::string Card::toString() const {
  int i = color - RED;
  int j = arrangement - LONE;
  int k = shape - OVAL;
  string desc = colorDescriptions[i] + "-" + arrangementDescriptions[j] + "-" + shapeDescriptions[k];
  if (USE_TERMINAL_COLORS) {
    string termcolor = "";
    if (color == RED) termcolor = "\033[31m"; // change terminal to red
    else if (color == BLUE) termcolor = "\033[34m"; // change terminal to blue
    else if (color == GREEN) termcolor = "\033[32m"; // change terminal to green
    else if (color == YELLOW) termcolor = "\033[33m"; // change terminal to yellow
    string termreset = "\033[0m"; // reset terminal back to default color
    return termcolor + desc + termreset;
  } else {
    return desc;
  }
}

bool operator== (const Card& c1, const Card& c2) {
  return c1.shape == c2.shape && c1.arrangement == c2.arrangement && c1.color == c2.color;
}

bool operator!= (const Card& c1, const Card& c2) {
  return ! (c1 == c2);
}

ostream& operator<<(ostream& outstream, const Card &c) {
  return (outstream << c.toString());
}
