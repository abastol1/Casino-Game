#pragma once

#include "stdafx.h"
#include "Cards.h"
#include "Round.h"

class Tournament {

private:
	int computerScore =0;
	int humanScore=0;
	int roundNumber = 1;
	

public:
	//constructor
	Tournament();

	void PlayGame() {
		cout << "----------------------------------------------------------------" << endl;
		cout << "----------------------------------------------------------------" << endl;
		cout << "---------------------------Coin Toss----------------------------" << endl;
		int coin;
		cout << "Enter 1 for head, 2 for tail: ";
		cin >> coin;

		srand(time(NULL));
		int randNum = rand() % 2 + 1;

		string nextPlayer;

		if (coin == randNum) {
			cout << "You won the toss, You can play first" << endl;
			nextPlayer = "Human";
		}
		else {
			nextPlayer = "Computer";
			cout << "You lost the toss, Computer will play first" << endl;
		}
		
		while (true) {

			
			Round round(nextPlayer);
			computerScore += round.getComputerScore();
			humanScore += round.getHumanScore();
			roundNumber++;

			cout << "Total Score: Computer -->" << computerScore << endl;
			cout << "Total Score: Human --> " << humanScore << endl;
			
			if ( computerScore >= 21 || humanScore >= 21) {

				if (computerScore > humanScore) {
					cout << "The Winner Is Computer with "<<computerScore<<" points." << endl;
				}
				else if (humanScore > computerScore) {
					cout << "You Won wih " << humanScore << " points." << endl;
				}
				else {
					cout << "The Game Ended In Tie!" << endl;
				}
				cout << "---------------------------------------------------------------" << endl;
				cout << "---------------------------------------------------------------" << endl;
				cout << "---------------------------------------------------------------" << endl;
				cout << "-------------------------ENDDDDDDDDDDDDDD----------------------" << endl;
				break;
			}

			system("pause");
		}
	}

	~Tournament();



};
