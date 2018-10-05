#pragma once
#include "stdafx.h"
#include "Cards.h"
#include "DeckOfCards.h"
#include "Build.h"

using namespace std;

class Player {

private:
	int score;

	bool isBuildOwner = false;

	deque<Cards> playersHand;
	deque<Cards> playersPile;

	deque <deque<Cards>> subset;

	Build build;
	
	
	deque<deque<Cards>> subsets;
	deque<deque<Cards>> possibleBuilds;
	deque<Cards> built;
	deque<deque<Cards>> tempTable;
	deque<deque<Cards>> matches;

protected:
	deque<deque<Cards>> table;

	//Checks if the player has capture 
	bool isLastCapture;

public:
	Player();

	bool checkForLastCapture() {
		return isLastCapture;
	}

	void play(deque<deque<Cards>> &tableRound);
	// Checks where possible capture contains any Ace ccards (worth 1 point)
	bool aceCaptureIsPossible();
	// Checks if the built on the table is his built
	bool hasOwnBuild(deque<deque<Cards>> builtsFromTable);

	bool DXCaptureIsPossible();
	// Returns the best possible captures 
	deque<Cards> getBestCapture(deque<deque<Cards>> capturePossible);

	// returns the possible captures of in the table using your hand
	deque<deque<Cards>> possibleCaptures( Cards &handUsed);
	bool isBuildCapturePossible(int &position);


	//int getPositionOwnBuild();
	//int getPositionOtherBuild();
	//bool hasOwnBuild(deque<deque<Cards>> buildInTable);
	//bool canCapOtherBuild(deque<deque<Cards>> buildInTable);


	int getSumOfMyBuild();

	deque<deque<Cards>>  getBuilts();

	void addCardTable(Cards fromPlayer);

	bool checkForTrail();

	void clearDequeValues();

	void captureCards();

	bool checkForRepeat(Cards a, deque<deque<Cards>> tempMatch);

	int getNumberOfCards(deque<deque<Cards>> xyz);

	deque<deque<Cards>> getPossible(Cards handCheck);

	bool checkAceS2(deque<Cards>& aceORS2);

	void getMatchesForCapture();

	bool isThereCapure();

	void printMatches();

	void deleteCardTable(deque<Cards> deleteFrom);

	bool checkCard(Cards temp, deque<Cards> deleteFrom);

	void addBuiltToTable(deque<Cards> add);

	void printTable();

	bool checkIfTableHasBuild();

	void findBestSingleBuild();

	void lookforSingleBuild();

	void addToPossibleBuild(deque<Cards> fromTable, Cards fromPlayer);

	void getAllSubsets();

	void printBuilt();

	// Get all the subset of cards on Table
	deque< deque<Cards> > getAllSubsets(deque<Cards> set);

	void setBuildInBuildClass(deque<Cards> buildToSet) {
		isBuildOwner = true;
		build.setBuilt(buildToSet);
	}

	deque<Cards> getBuilt() {
		return build.getBuilt();
	}

	void emptyPlayersBuilt() {
		build.emptyBuilt();
	}

	void setOwner(bool own) {
		build.setOwner(own);
	}

	void setTable(deque<deque<Cards>> &currtable) {
		table = currtable;
	}

	bool checkIfBuildOwner() {
		return isBuildOwner;
	}
	string getOwner() {
		return build.getOwner();
	}

	//if table contains build, then capture
	void ifBuildCapture(deque<deque<Cards>> &table);


	bool isBuildPossible();

	void captureBuild(deque<Cards> buildInTable);

	void deleteHandCard(Cards h) {
		int position = 0;
		for (Cards temp : playersHand) {
			if (temp.toString() == h.toString()) {
				playersHand.erase(playersHand.begin() + position);
			}
			position++;
		}

	}

	void deleteDealtCard(Cards dealtCard);

	// Adds Cards to the player hands
	void addCard(Cards hand);

	// Get card from the playersHand
	Cards getCard();

	//Returns players Hand
	deque<Cards> returnHand() {
		return playersHand;
	}

	//Returns players pile
	deque<Cards> returnPile() {
		return playersPile;
	}

	// Receives card from table and adds it to playerspile
	void addToPile(Cards temp);

	// Prints all the cards that are in player's hand
	void printHand();

	// Prints all the cards that are in player's pile
	void printPile();

	// Returns the number of Ace cards in player's pile
	int getAceNum();
	// Returns the size of the player's pile
	int getPileSize();

	// set score of the player after every round
	void setScore(int num) {
		score = score + num;
	}

	// get score of the player
	int getScore() {
		return score;
	}

	// Returns the number of spade cards in player's pile
	int getSpadesNum();


	// Returns true if the player has ten of diamonds. if not returns false
	bool hasTenOfDiamonds();

	// Returns true if the player has two of spades. if not returns false
	bool hasTwoOfSpades();

	int getCardNumber(Cards findNum) {
		int value = 0;

		if (findNum.getFace() == "X") {
			value = 10;
		}
		else if (findNum.getFace() == "J") {
			value = 11;
		}
		else if (findNum.getFace() == "Q") {
			value = 12;
		}
		else if (findNum.getFace() == "K") {
			value = 13;
		}
		else if (findNum.getFace() == "A") {
			value = 1;
		}
		else {
			value = stoi(findNum.getFace());
		}
		return value;
	}

	// Displays menu when its human's turn
	void showMenu();
	// Shows game option
	void showGameOption();

	~Player();
	
};

