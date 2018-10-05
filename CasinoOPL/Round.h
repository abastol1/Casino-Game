#pragma once
#include "stdafx.h"
#include "Cards.h"
#include "DeckOfCards.h"
#include "Human.h"
#include "Computer.h"

using namespace std;


class Round {

private:
	// Stores the round number
	int roundNumber;

	// Deque to stores the cards on table
	deque<deque<Cards>> table;
	DeckOfCards deck;

	// Human object
	Computer player1;

	// Computer object
	Human player2;

	string nextPlayer;

	//FileHandler filehandler;
	

public:
	Round(string next);

	// Deals 4 cards to Table, player 1 and player2
	void setHands();

	// Prints all the details (Cards in Deck, Cards on table, and in players hand
	void printAllDetails();

	// Plays the game after round constructor is called
	void playGame();

	void printTable();

	// Menu for Saving, making move, asking for help and quit the game
	void showMenu();

	// Calculates the score of players after the round is completed using Player's Pile
	void calculateScore();

	void saveGame();

	//Get Computer Score
	int getComputerScore() {
		return player1.getScore();
	}

	//Get Human Score
	int getHumanScore() {
		return player2.getScore();
	}

	~Round();
};

