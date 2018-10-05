#include "DeckOfCards.h"
#include "stdafx.h"


DeckOfCards::DeckOfCards() {
	// A for Ace, X for 10, J for Jack, Q for Queen and K for King
	string faces[] = { "A", "2", "3", "4", "5", "6", "7", "8", "9", "X", "J", "Q", "K" };

	// H for Hearts , C for Clubs, S for Spades, D for Diamonds
	string suits[] = { "H" , "C", "S", "D" };

	for (int i = 0; i < 13; i++) {
		for (int j = 0; j < 4; j++) {
			Cards temp(suits[j], faces[i]);
			deck.push_front(temp);
		}
	}
}

void DeckOfCards::shuffleCards() {
	// Randomly shuffles the card that are in the Deque
	unsigned seed = (unsigned int) (chrono::system_clock::now().time_since_epoch().count());

	// Shuffles the deck of cards using STL
	shuffle(deck.begin(), deck.end(), default_random_engine(seed));
}

Cards DeckOfCards::returnFrontCard() {
	Cards temp = deck.front();
	deck.pop_front();
	return temp;
}

// Prints all the cards that are present in the deck
void DeckOfCards::printDeck() {
	cout << "Deck:" << endl;
	cout << string(50, '-') << endl;
	for (auto deckCards : deck) {
		cout << deckCards.toString() << " ";
	}
	cout << "\n\n";
}


// Deal 4 cards to the table
void DeckOfCards::dealCards(deque<deque<Cards>> &table) {
	deque<Cards> topushinTable;
	for (int i = 0; i < 4; i++) {
		Cards temp = deck.front();
		deck.pop_front();
		topushinTable.clear();
		topushinTable.push_front(temp);
		table.push_back(topushinTable);
	}
/*	cout << "topushinTable" << endl;
	Cards temp = topushinTable.front();
	topushinTable.push_back(temp);
	for (Cards temp : topushinTable) {
		cout << temp.toString() << " ";
	}
	cout << endl;

	table.push_front(topushinTable); */

}


DeckOfCards::~DeckOfCards()
{
}
