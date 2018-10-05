#include "Round.h"
#include "stdafx.h"
#include "FileHandler.h"


using namespace std;

Round::Round(string next) {

	setHands();
	nextPlayer = next;
	playGame();
	calculateScore();
}

// Deals 4 cards to Table, player 1 and player2
void Round::setHands() {

	deck.shuffleCards();
	// deals 4 cards to the table 
	deck.dealCards(table);



	//Adds four cards to player 1 hand
	for (int i = 0; i < 4; i++) {
		player1.addCard(deck.returnFrontCard());
	}

	//Adds four cards to player 2 hand
	for (int i = 0; i < 4; i++) {
		player2.addCard(deck.returnFrontCard());
	}
}

// Prints all the details (Cards in Deck, Cards on table, and in players hand
void Round::printAllDetails() {

	// Prints the hands of player 1
	cout << "Human Hand:" << endl;
	player1.printHand();

	// Prints the piles of player 1
	cout << "Human Pile:" << endl;
	player1.printPile();

	//Prints the hands of player 1
	cout << "Computer Hand:" << endl;
	player2.printHand();

	//Prints the piles of player 1
	cout << "Computer Pile:" << endl;
	player2.printPile();

	// Prints the cards on the table
	cout << "Table: " << endl;
	printTable();

	// Deals cards from deck of cards
	deck.printDeck();
}


// Plays the game after round constructor is called
void Round::playGame() {



	showMenu();

	int userChoice;
	cout << "*******************************************" << endl;
	cout << "Please Enter Your Choice: ";
	cin >> userChoice;

	if (userChoice == 1) {
		saveGame();
		//filehandler.saveGame(roundNumber, player1.getScore(), player1.returnHand(), player1.returnPile(), player2.getScore(), player2.returnHand(), player2.returnPile(), table, player1.getBuilt() , "Human", deck.getDeck(), nextPlayer );
	}
	else if (userChoice == 2) {

		while (true) {
			if (nextPlayer == "Human") {
				player2.play(table);
				nextPlayer = "Computer";
				//played++;

			}
			else {
				cout << "Temp temp table table ------" << endl;
				printTable();
				player1.play(table);
				nextPlayer = "Human";
				//comp++;
			}

			cout << "*************************** " << nextPlayer << "'s Turn***************************" << endl;

			if ((deck.getDeck().size() == 0) && (player1.returnHand().size() == 0) && (player2.returnHand().size() == 0)) {
				if (player1.checkForLastCapture() == true) {
					for (deque<Cards> temp : table) {
						player1.addToPile(temp.front());
					}
					table.clear();
				}
				else {
					for (deque<Cards> temp : table) {
						player2.addToPile(temp.front());
					}
					table.clear();
				}
				cout << "-----------------------------Round Ended-----------------------------" << endl;
				break;
			}
			if ((player2.returnHand().size() == 0) && (player1.returnHand().size() == 0) && deck.getDeck().size() != 0) {
				for (int i = 0; i < 4; i++) {
					player2.addCard(deck.returnFrontCard());
				}
				for (int i = 0; i < 4; i++) {
					player1.addCard(deck.returnFrontCard());
				}
			}
		}
	}
	else if (userChoice == 3) {
		// Ask for help
	}
	else if (userChoice == 4) {
		//Quit the game
	}
	cout << "Table in BUild" << endl;
	printTable();
}



	//while (true) {

	//	/*if ((played == comp) && (player1.returnHand().size() != player2.returnHand().size())) {
	//		system("pause");
	//	}*/


	//	printAllDetails();
	//}


	void Round::printTable() {
		for (deque<Cards> insideTable : table) {
			for (Cards tableCard : insideTable) {
				cout << tableCard.toString() << " ";
			}
			cout << endl;
		}
	}


	// Menu for Saving, making move, asking for help and quit the game
	void Round::showMenu() {
		cout << "1. Save  the game" << endl;
		cout << "2. Make a move" << endl;
		cout << "3. Ask for a help" << endl;
		cout << "4. Quit the game\n" << endl;
	}

	// Calculates the score of players after the round is completed using Player's Pile
	void Round::calculateScore() {

		// The player with the most cards in the pile gets 3 points. In the event of a tie, neither player gets points. 
		if (player1.getPileSize() > player2.getPileSize()) {
			player1.setScore(3);
		}
		else if (player1.getPileSize() < player2.getPileSize()) {
			player2.setScore(3);
		}

		//The player with the most spades gets 1 point. In the event of a tie, neither player gets points.
		if (player1.getSpadesNum() > player2.getSpadesNum()) {
			player1.setScore(1);
		}
		else if (player1.getSpadesNum() < player2.getSpadesNum()) {
			player2.setScore(1);
		}

		//The player with 10 of Diamonds gets 2 points.
		if (player1.hasTenOfDiamonds()) {
			player1.setScore(2);
		}
		else if (player2.hasTenOfDiamonds()) {
			player2.setScore(2);
		}

		//The player with 2 of Spades gets 1 point. 
		if (player1.hasTwoOfSpades()) {
			player1.setScore(1);
		}
		else if (player2.hasTwoOfSpades()) {
			player2.setScore(1);
		}

		// Each player gets one point per Ace. 

		int acePlayer1 = player1.getAceNum();
		int acePlayer2 = player2.getAceNum();

		player1.setScore(acePlayer1);
		player2.setScore(acePlayer2);

		cout << "Computer Score -->" << player1.getScore() << endl;
		cout << "Human Score -->" << player2.getScore() << endl;
	}


	void Round::saveGame() {

		string fileName = "savedGame.txt";
		ofstream ofile;

		ofile.open(fileName);

		if (!ofile) {
			cout << "File can not be opened!" << endl;
		}
		ofile << "Round: " << endl;

		ofile << "\nComputer: " << endl;
		ofile << "     Score: " << player1.getScore() << endl;
		ofile << "     Hand: ";
		for (Cards hand : player1.returnHand()) {
			ofile << hand.toString() << " ";
		}


		ofile << "\n     Pile: ";
		for (Cards pile : player1.returnPile()) {
			ofile << pile.toString() << " ";
		}
		cout << endl;

		ofile << "\nHuman: " << endl;
		ofile << "     Score: " << player2.getScore() << endl;
		ofile << "     Hand: ";
		for (Cards hand : player2.returnHand()) {
			ofile << hand.toString() << " ";
		}


		ofile << "\n     Pile: ";
		for (Cards pile : player2.returnPile()) {
			ofile << pile.toString() << " ";
		}
		cout << endl;

		ofile << "\n\nTable: ";
		for (deque<Cards> insideTable : table) {
			if (insideTable.size() == 1) {
				ofile << insideTable.front().toString() << " ";
			}
			else {
				ofile << "[ ";
				for (Cards tableCard : insideTable) {
					ofile << tableCard.toString() << " ";
				}
				ofile << "] ";
			}
		}

		ofile << "\n\nBuild Owner: ";
		ofile << "\n\nDeck: ";
		for (Cards inDeck :deck.getDeck() ) {
			ofile << inDeck.toString() << " ";
		}
		cout << endl;
		ofile << "\n\nNext Player: " << nextPlayer << endl;
	}


	Round::~Round()
	{
	}


	