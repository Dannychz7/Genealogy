/********************************************************************
 * Name: Sunset.cpp
 * Date: Fall 2023
 * Course: CSCI 132
 * Assignment: Homework 3
 * Author: K. Walsh, D. Chavez
 * Modified:
 *  23 Feb 2021 - K. Walsh - Rewrite as Battle, with slightly different rules.
 *       Also modify to work with new Card, Deck, and Stack classes.
 *  17 Sep 2023 - K. Walsh - Rewrite as Sunset, with entirely new rules.
 *  29 Sep 2023 - D.Chavez - added new functions, added game code, and bot code
 *
 * Purpose: This is the complete sunset project in which the user has the option of playing
 * or having the bot play for them. The game has options, a, b, pass, and score. A and B allows
 * the user to grab the cards from that pile and to their hand, pass moves either a or b, or
 * both cards to the save pile, and score calculates the score of the cards in the players hands.
 * The bot function works similary, only it asks for a patience level and a target hand variable 
 * which will affect the way the bot functions. This is the Sunset Game. 
 * 
  Sample Code with Player:
      Welcome to Sunset.
      How many cards to deal for each pile? 1
      Do you want to play interactively (yes or no)? 
      yes
      Shuffling cards.
      Status for round 1: 
         You have 0 points so far. 
         Stack A has Blue-Triplet-Squiggle and 0 other cards.
          Stack B has Red-Lone-Box and 0 other cards.
          Saved pile has 0 cards.
          Your hand is empty. 
      What do you want to do (a, b, score, or pass)? 
      a
      You chose: a
      Picking up Blue-Triplet-Squiggle
      Status for round 2: 
          You have 0 points so far. 
          Stack A is empty. 
          Stack B has Red-Lone-Box and 0 other cards.
          Saved pile has 0 cards.
          Your hand has 1 cards: Blue-Triplet-Squiggle
      What do you want to do (a, b, score, or pass)? 
      b
      You chose: b
      Picking up Red-Lone-Box
      Status for round 3: 
          You have 0 points so far. 
          Stack A is empty. 
          Stack B is Empty. 
          Saved pile has 0 cards.
          Your hand has 2 cards: Red-Lone-Box, Blue-Triplet-Squiggle
      What do you want to do (a, b, score, or pass)? 
      score
      You chose: score
      You earned 8 points.
      Game over.
      You earned 8 points for Red-Lone-Box, Blue-Triplet-Squiggle
      You earned 8 total points. 

 ***************************************************************************/

#include <iostream>
#include <cassert>
#include <cmath>  
#include "StackInterface.h"
#include "ArrayStack.h"
#include "LinkedSet.h"
#include "Card.h"
#include "Deck.h"

using namespace std;

/*******************************************************************************
 * Ask user to enter a number.
 * Includes error checking, and re-prompts the user if they make a mistake.
 * Precondition: lo <= hi.
 * Returns: the user's choice, between lo and hi, inclusive.
 *******************************************************************************/
int promptForNumber(string question, int lo, int hi);

/*******************************************************************************
 * Ask user if they want to play interactively or automatically.
 * Includes error checking, and re-prompts the user if they make a mistake.
 * Returns: true if they want interactive, false for automated.
 *******************************************************************************/
std::string promptForInteractive();

/*******************************************************************************
 * If A and B piles are both empty, use the saved cards to replenish those
 * piles. The goal of this function is to ensure there are some cards in the A
 * or B piles, if possible.
 * Precondition: none of the parameters are null.
 * Returns: true if A or B have some cards when this function is finished.
 *******************************************************************************/
bool replenish(StackInterface<Card> *pileA, StackInterface<Card> *pileB, StackInterface<Card> *savePile);

/*******************************************************************************
 * If possible, move one card from the top of the given pile to the hand. Also
 * perform error checking and print status and error messages as appropriate.
 * Precondition: none of the parameters are null.
 *******************************************************************************/
void pickupCard(LinkedSet<Card> *hand, StackInterface<Card> *pile);

/*******************************************************************************
 * If possible, move one card from the given pile to the save pile.
 * Precondition: none of the parameters are null.
 * Returns: true if a card was moved, or false otherwise.
 *******************************************************************************/
bool discard(StackInterface<Card> *savePile, StackInterface<Card> *pile);

/*******************************************************************************
 * Calculate the value of a given hand, using the Sunset game scoring rules. If
 * the hand is empty, then no calculation is done and 0 is returned instead.
 * Precondition: the parameter is not null.
 * Returns: the number of points the hand is worth (between 1 and 64 points (between 1 through n^3)
 * depending on the combination of cards), or returns 0 if the hand was empty.
 *******************************************************************************/
int scoreSelection(const LinkedSet<Card> *hand); 

/*******************************************************************************
 * Checks whether adding the given card would increase the value of a hand.
 * Returns: true if adding card c would increase the score for the hand, and
 * returns false otherwise;
 *******************************************************************************/
bool improvesScore(const LinkedSet<Card> *hand, const Card &c); 

/*******************************************************************************
 * If the A pile is empty, B pile is empty, and the save pile is empty, then
 * game is over. Returns: true or false depending if the piles are empty,
 * returns false by defult;
 *******************************************************************************/
bool gameOver(const StackInterface<Card> *pileA, StackInterface<Card> *pileB, StackInterface<Card> *savePile, std::string option);

/*******************************************************************************
 * Ask user what they want to do with the cards in the piles
 * Includes error checking, and re-prompts the user if they make a mistake.
 * Returns: string option of what they chose
 *******************************************************************************/
string promptForGameOptions();

/*******************************************************************************
 * The main game loop.
 *******************************************************************************/
int main(int argc, char **argv) {

  // Seed the random number generator using command-line parameter (optional, terrible for debugging).
  srand(argc > 1 ? atoi(argv[1]) : 0);

  Deck sunsetDeck;                 // Deck of cards
 
  ArrayStack<Card> *a = new ArrayStack<Card> (); //A pile
  ArrayStack<Card> *b = new ArrayStack<Card> (); //B pile
  ArrayStack<Card> *save = new ArrayStack<Card> (); //moves the top card from both A and B piles to the top of the save pile
  LinkedSet<Card> *hand = new LinkedSet<Card> (); //Linked Set to score the hand of the player
  ArrayStack<string> scoredHands; //Array stack to store all the scoring hands
  ArrayStack<int> scoredPoints; //Array Stack to store all the scoring integers 

  int cardsDelt; //User input of cards delt
  int roundCount = 1; //Keeps track of round number
  int points = 0; //Keeps track of points for the player
  string gameOption = ""; //Keeps track of the option the user entered
  string interactive = ""; //Keeps track of ir user entered yes of no 
  
  //Variables for the bot
  int patienceLevel = 0;
  int numPatience = 0;
  int targetHandSize = 0;

  // Greeting and user input.
  cout << "Welcome to Sunset." << endl;
  cardsDelt = promptForNumber("How many cards to deal for each pile?", 1, 32); //Asks and stores nums to CardsDelt
  interactive = promptForInteractive();

  //takes user input for Target size and Patience level for greedy strategy
  if(interactive == "no" || interactive == "n") 
  {
    targetHandSize = promptForNumber("Target size for greedy strategy?", 2, 10);
    patienceLevel = promptForNumber("Patience level for greedy strategy?", 0, 32);
  }

  // Shuffle the deck, seven times.
  cout << "Shuffling cards." << endl;
  for (int i = 0; i < 7; i++)
    sunsetDeck.shuffle();

  //Deals the cards into two piles
  for (int i = 0; i < cardsDelt; i++) 
  {
    a->push(sunsetDeck.dealCard());
    b->push(sunsetDeck.dealCard());
  }

  //The Loop for the game
  while(gameOver(a, b, save, gameOption) != true) 
  {
    cout << "Status for round " << roundCount << ": \n";
    cout << "    You have " << points << " points so far. \n";
    
    if (!a->isEmpty()) 
    {
      cout << "    Stack A has " << a->peek() << " and " << a->size() - 1 << " other cards." <<  "\n";
    } else 
    {
      cout << "    Stack A is empty. \n";
    }
    if (!b->isEmpty()) 
    {
      cout << "    Stack B has " << b->peek() << " and " << b->size() - 1 << " other cards." <<  "\n";    
    } else 
    {
      cout << "    Stack B is Empty. \n";
    }

    cout << "    Saved pile has " << save->size() << " cards." << "\n";

    if (hand->isEmpty()) 
    {
      cout << "    Your hand is empty. \n";
    } else 
    {
      cout << "    Your hand has " << hand->size() << " cards: ";
      hand->print();
      cout << "\n";
    }

    //Bot code for scoring, passing, and picking up hands
    if (interactive == "no" || interactive == "n") {
      
      if (a->isEmpty() && b->isEmpty()) 
      {
        gameOption = "score";
        numPatience = 0;
        cout << "You chose " << gameOption << " \n";
      } else if(patienceLevel <= numPatience) 
      {
        gameOption = "score";
        numPatience = 0;
        cout << "You chose " << gameOption << " \n";
      } else if(!a->isEmpty() && improvesScore(hand, a->peek()) == true) 
      {
        gameOption = "a";
        numPatience = 0;
        cout << "You chose " << gameOption << " \n";
      } else if (!b->isEmpty() && improvesScore(hand, b->peek()) == true) 
      {
        gameOption = "b";
        numPatience = 0;
        cout << "You chose " << gameOption <<  " \n";
      } else if(hand->size() == targetHandSize) 
      {
        gameOption = "score";
        numPatience = 0;
        cout << "You chose " << gameOption <<  " \n";
      } else 
      {
        gameOption = "pass";
        cout << "You chose " << gameOption << " \n";
        numPatience++;
      }

    } else 
    {
      gameOption = promptForGameOptions(); //Prompts the user what they want to do next
      cout << "You chose: "  << gameOption << "\n";
    }
  
    //Game code for user input if interactive is yes 
    if(gameOption == "a") 
    {
      if(a->isEmpty()) 
      {
         cout << "Sorry that pile is empty."; 
      } else 
      {
        pickupCard(hand, a);
        cout << "Picking up ";
        cout << hand->get(0); 
      }
    } else if (gameOption == "b")
    {
      if(b->isEmpty()) 
      {
        cout << "Sorry that pile is empty.";
      } else 
      {
        pickupCard(hand, b);
        cout << "Picking up "; 
        cout << hand->get(0);
      }
    } else if(gameOption == "pass") 
    {
      if(a->isEmpty() && b->isEmpty()) 
      {
        cout << "Sorry, both piles are empty.";
      } else if(!a->isEmpty() && !b->isEmpty()) 
      {
        discard(save, a);
        discard(save, b);
        points = points - 2;
      } else if(!a->isEmpty() && b->isEmpty()) 
      {
        discard(save, a);
        points = points - 1;
      } else if(a->isEmpty() && !b->isEmpty()) 
      {
        discard(save, b);
        points = points - 1;
      }
    } else if (gameOption == "score") 
    {
      if(hand->isEmpty()) 
      {
        cout << "Sorry, your hand is empty. ";
      } else 
      {
        cout << "You earned " << scoreSelection(hand) << " points.";
        scoredPoints.push(scoreSelection(hand));
        scoredHands.push(hand->toString());
        points += scoreSelection(hand);
        hand->clear();
      }
    }

    if(a->isEmpty() && b->isEmpty() && !save->isEmpty()) 
    {
      replenish(a, b, save);
    }
    roundCount++;
    cout << "\n";

  } //end game loop

  cout << "Game over.\n";

  //Prints the game summary of all the hands, points, and total points earned
  while(!scoredHands.isEmpty() && !scoredPoints.isEmpty()) 
  {
    cout << "You earned " << scoredPoints.peek() << " points for " << scoredHands.peek() << "\n";
    scoredPoints.pop();
    scoredHands.pop();
  }

  cout << "You earned " << points << " total points. \n";

} //end main()

int promptForNumber(string question, int lo, int hi) 
{
  int response;

  bool done = false;
  while (!done) { // keep asking until success
    cout << question << " ";
    cin >> response; // get user input
    if (cin.fail()) { // check if user typed a non-integer
      cout << "Please enter an integer.\n";
       cin.clear(); // this resets the standard input's error status.
       string junk;
       getline(cin, junk); // this reads and discards the rest of the bad input line.
    } else if (response < lo || response > hi) { // check range
      cout << "Please enter a number from " << lo << " to " << hi << ".\n";
    } else {
      done = true;
    }
  } // end loop looking for valid input

  return response;

} // end promptForNumber()

std::string promptForInteractive() 
{
  string answer;

  bool done = false;
  while (!done) { // keep asking until success
    cout << "Do you want to play interactively (yes or no)? \n";
    cin >> answer; // get user input
    if (answer != "yes" && answer != "no" && answer != "y" && answer != "n")
      cout << "Please enter a valid input.\n";
    else
      done = true;
  } // end loop looking for valid input

  return answer;

} //End promptForInteractive()


bool replenish(StackInterface<Card> *pileA, StackInterface<Card> *pileB, StackInterface<Card> *savePile)
{
  // First check the two piles.
  if (!pileA->isEmpty() || !pileB->isEmpty())
    return true; // no need to replenish, there are piles are not both empty.
 
  // Next, move all cards from save pile to the A and B piles.
  int n = 0;
  while (!savePile->isEmpty()) {
    // Move one card to A
    pileA->push(savePile->peek());
    savePile->pop();
    n++;
    // Move one card to B, but only if we still have saved cards.
    if (savePile->isEmpty())
      break;
    pileB->push(savePile->peek());
    savePile->pop();
    n++;
  }
  // Print summary, if cards were moved.
  if (n > 0) {
    cout << "Moved " << n << " cards from save pile to replenish the A and B piles.\n";
    return true;
  } else {
    // failed to replenish
    return false;
  }

} // end replenish()

void pickupCard(LinkedSet<Card> *hand, StackInterface<Card> *pile) 
{
  if(!pile->isEmpty())
  {
    hand->add(pile->peek());
    pile->pop();
  }

}// end pickupCard()

bool discard(StackInterface<Card> *savePile, StackInterface<Card> *pile) 
{
  if(10 < savePile->size())
  {
    cout << "Too many savePile cards. Discarded 2 of them. \n";
    return savePile->compact(10);
  } else if(!pile->isEmpty())
  {
    savePile->push(pile->peek());
    pile->pop();
    return true;

  } else 
  {
    return false;
  }

} //end discard()

int scoreSelection(const LinkedSet<Card> *hand) 
{
  LinkedSet<CardColor> *handColors = new LinkedSet<CardColor> ();
  LinkedSet<CardArrangement> *handArrangement = new LinkedSet<CardArrangement> ();
  LinkedSet<CardShape> *handShape = new LinkedSet<CardShape> ();

  int handSize = hand->size(); //Number of cards in the hand
  int score = 1;
  
  for (int i = 0; i < hand->size(); i++) //Loops that inputs colors into a bag
  {
    Card c = hand->get(i);
    handColors->add(c.getColor());
  }
  for (int i = 0; i < hand->size(); i++) //Loop that inputs hand Arrangements into a bag
  {
    Card c = hand->get(i);
    handArrangement->add(c.getArrangement());
  }
  for (int i = 0; i < hand->size(); i++) //Loop that inputs shapes into a bag
  {
    Card c = hand->get(i);
    handShape->add(c.getShape());
  }

  //Conditionals to check if the colors, shapes, and arrangments are all the same or unique
  if (handColors->size() == 1 || handColors->size() == handSize)
  {
    score = score * handSize;
  } 
  if (handShape->size() == 1 || handShape->size() == handSize) 
  {
    score = score * handSize;
  } 
  if (handArrangement->size() == 1 || handArrangement->size() == handSize) 
  {
    score = score * handSize;
  }

  return score;

} //end scoreSelection()

bool gameOver(const StackInterface<Card> *pileA, StackInterface<Card> *pileB, StackInterface<Card> *savePile, std::string option) 
{
  if(pileA->isEmpty() && pileB->isEmpty() && savePile->isEmpty() && option == "score") 
  {
    return true;
  } else
  {
    return false;
  }

} //End gameOver()

std::string promptForGameOptions() 
{
  string answer;

  bool done = false;
  while (!done) { // keep asking until success
    cout << "What do you want to do (a, b, score, or pass)? ";
    cin >> answer; // get user input
    if (answer != "a" && answer != "b" && answer != "score" && answer != "pass")
      cout << "Please enter a valid input.\n";
    else
      done = true;
  } // end loop looking for valid input

  return answer;

} //End promptForGameOptions()

bool improvesScore(const LinkedSet<Card> *hand, const Card &c) {
  // Calculate the value of the existing hand (will be zero if hand is empty).
  int oldPoints = scoreSelection(hand);

  // Make a new temporary set using the copy constructor, and calculate the new value.
  LinkedSet<Card> *biggerHand = new LinkedSet<Card>(*hand);
  biggerHand->add(c);
  int newPoints = scoreSelection(biggerHand);

  // Clean up the temporary set.
  delete biggerHand;
  biggerHand = nullptr;

  // Return either true or false.
  return (newPoints > oldPoints);

} // end improvesScore()

