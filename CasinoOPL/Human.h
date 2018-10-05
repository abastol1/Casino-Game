#pragma once
#include "stdafx.h"
#include "Player.h"
class Human : public Player {

public:
	Human();

	// When human turns, this fucntion is called 
	void play(deque<deque<Cards>> &curtable);

	void captureBuild();

	void setBuild();

	// This function is called if the players wants to trail the cards. 
	bool Trial(string card, int builtSum, int numCardToCapBuilt);

	// thsi functions checks whether a trail move is possible with given card
	bool isTrailPossible(string cardToTrail);

	// this function is called if the player wants to capture cards
	void capture(int builtSum, int numCardToCapBuilt);

	deque<Cards> getCardsToCapture(string handCard, int numSets);

	// Checks if the table card entered by user is in the table
	bool isTableCardLegal(string tableCard);

	// checks if the hand card entered by user is in the player's hand
	bool isHandCardLegal(string handCard);
	// Displays menu when its human's turn
	void showMenu();
	// Shows game options (capture, trail, build)
	void showGameOption();
	
	~Human();
};

