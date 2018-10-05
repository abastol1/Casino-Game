#pragma once
#include "stdafx.h"
#include "Cards.h"

using namespace std; 

class DeckOfCards {

private:
	// Stores all the cards in the deque of deck
	deque <Cards> deck;

public:
	DeckOfCards();

	// Prints all the cards that are present in the deck
	void printDeck();

	deque<Cards> getDeck() {
		return deck;
	}

	void shuffleCards();

	// Deal 4 cards to the table
	void dealCards(deque<deque<Cards>> &table);

	// Returns the front card of the deck
	Cards returnFrontCard();

	~DeckOfCards();
};

