#pragma once
#include <fstream>
#include<sstream>
#include "stdafx.h"
#include "Cards.h"

using namespace std;

class FileHandler{

private:
	ofstream ofile;
	ifstream ifile;
public:
	FileHandler();

	// Saves the game into a text file 
	void saveGame(int roundNumber, int computerScore, deque<Cards> computerHand, deque<Cards> computerPile, int humanScore, deque<Cards> humanHand, deque<Cards> humanPile, deque<deque<Cards>> table, deque<Cards> buildOwner, string buildOwnerName, deque<Cards> deck, string nextPlayer  );

	bool isFileOpen(string fileName);

	// Resume the state of game by opening the game from text file
	void loadGame();

	void storeInDeque(string line, deque<Cards>& toStore);

	void printDeque(deque<Cards> toPrint);

	int getInteger(string line);

	~FileHandler();
};

