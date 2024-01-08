A couple disclaimers about the project
1. A majority of the object files are not owned by myself, they are owned by College of the Holy Cross
2. Although I do not own a majority of the files, I did learn, create, and edit all the files, so the content in all files is familiar with me
3. In Sunset.cpp is where all the client code, user interface, bot code, and all major logic code takes place.
4. All written in C++
5. Description:
     This is a one-player game using a deck of 64 cards, each with a unique design using colors (red, blue, green, yellow), shapes (box, squiggle, line, and oval), and arrangements (single, pair, triplet, or many). There will be two piles of cards, an A pile and a B pile. At the start of the game, the user chooses how many cards they want in each pile, and after shuffling the deck, that many cards are dealt to each pile in alternating fashion. For debugging, starting with just 3 or 4 cards in each pile is reasonable, but your program should work for any number from 1 to 32 (up to half the cards in each pile). There is a third pile of cards, the save pile, that is initially empty. The player will also hold some cards in their hand, but initially the player is holding nothing. The order of the cards in the player’s hand does not matter at all.

How to run the Game: 
clang++ -g -Wall Deck.cpp Card.cpp Sunset.cpp -o sunset
./sunset
