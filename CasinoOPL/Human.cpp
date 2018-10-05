#include "Human.h"
#include "stdafx.h"


Human::Human()
{
}



// When human turns, this fucntion is called 
void Human::play(deque<deque<Cards>> &curtable) {
	table = curtable;

	printTable();
	printHand();
	printPile();

	//******************************************************
	deque<deque<Cards>> builtsFromTable;
	builtsFromTable.clear();

	builtsFromTable = getBuilts();
	int builtSum = 0;
	// if statement to check if built still exists on table
	// One players built can be capture by another playing without changing the owner status
	if (hasOwnBuild(builtsFromTable)) {
		cout << "Has Own Build" << endl;
		for (Cards a : getBuilt()) {
			cout << a.toString() << " ";
			builtSum = builtSum + getCardNumber(a);
		}
		cout << endl;
	}
	else {
		emptyPlayersBuilt();
		setOwner(false);
	}
	//******************************************************

	int numCardToCapBuilt = 0;
	for (Cards temp : returnHand()) {
		if (getCardNumber(temp) == builtSum) {
			numCardToCapBuilt++;
		}
	}

	cout << "\nYour options are: " << endl;
	showGameOption();

	int moveOption;
	cout << "Enter Your Move Option: ";
	cin >> moveOption;

	if (moveOption == 1) {
		// Capture cards , sets of cards, individual cards and set of cards
		capture(builtSum, numCardToCapBuilt);
		isLastCapture = true;
	}

	else if (moveOption == 2) {
		captureBuild();
		isLastCapture = true;
	}
	else if (moveOption == 3) {
		setBuild();
		isLastCapture = false;
	}
	else if (moveOption == 4) {
		string cardToTrail;
		bool isTrail;
		do {
			cout << "Enter the Card that you want to trail: ";
			cin >> cardToTrail;
			isTrail = Trial(cardToTrail, builtSum, numCardToCapBuilt);
		} while (isTrail == false);

		deleteHandCard(Cards(cardToTrail.substr(0, 1), cardToTrail.substr(1, 1)));
		addCardTable(Cards(cardToTrail.substr(0, 1), cardToTrail.substr(1, 1)));
		isLastCapture = false;
	}

	curtable = table;
	cout << "Players Hand:" << endl;
	printHand();
	printTable();
	cout << "Players Pile" << endl;
	printPile();
}

void Human::captureBuild() {
	string handCard;
	do {
		cout << "Enter Hand Card that you will use to capture: ";
		cin >> handCard;
	} while (!isHandCardLegal(handCard));

	int handNum = getCardNumber(Cards(handCard.substr(0, 1), handCard.substr(1, 1)));

	string buildCards;
	deque<Cards> buildCardsDeque;
	bool check = true;
	do {
		cout << "Enter the cards of build that you want to capture: ";
		cin.ignore();
		getline(cin, buildCards);
		int sum = 0;
		string buff;
		stringstream ss(buildCards);
		deque<Cards> temp;
		while (ss >> buff) {
			if (isTableCardLegal(buff)) {
				sum = sum + getCardNumber(Cards(buff.substr(0, 1), buff.substr(1, 1)));
				temp.push_back(Cards(buff.substr(0, 1), buff.substr(1, 1)));
				check = true;
			}
			else {
				check = false;
			}
		}
		if (sum == handNum) {
			for (Cards a : temp) {
				buildCardsDeque.push_back(a);
			}
			check = true;
		}
	} while (check == false);

	

	for (Cards toPile : buildCardsDeque) {
		addToPile(toPile);
	}
	int position = 0;
	for (deque<Cards> checkBuilt : table) {
		if (buildCardsDeque.front().toString() == checkBuilt.front().toString()) {
			table.erase(table.begin() + position);
		}
	}


	addToPile(Cards(handCard.substr(0, 1), handCard.substr(1, 1)));
	deleteHandCard(Cards(handCard.substr(0, 1), handCard.substr(1, 1)));
}


void Human::setBuild(){
	string handCard;
	do {
		cout << "Enter Hand Card that you will use to set build: ";
		cin >> handCard;
	} while (!isHandCardLegal(handCard));

	int handNum = getCardNumber(Cards(handCard.substr(0, 1), handCard.substr(1, 1)));

	string buildCards;
	deque<Cards> buildCardsDeque;
	bool check = true;
	do {
		cout << "Enter the cards to set a build: ";
		cin.ignore();
		getline(cin, buildCards);
		int sum = 0;
		string buff;
		stringstream ss(buildCards);
		deque<Cards> temp;
		while (ss >> buff) {
			if (isTableCardLegal(buff)) {
				sum = sum + getCardNumber(Cards(buff.substr(0, 1), buff.substr(1, 1)));
				temp.push_back(Cards(buff.substr(0, 1), buff.substr(1, 1)));
				check = true;
			}
			else {
				check = false;
			}
		}
		for (Cards a : returnHand()) {
			check = false;
			if ((sum + handNum) == getCardNumber(a)) {
				check = true;
				buildCardsDeque = temp;
				break;
			}
			if (check == true) {
				break;
			}
		}
	} while (check == false);


	deleteHandCard(Cards(handCard.substr(0, 1), handCard.substr(1, 1)));
	deleteCardTable(buildCardsDeque);
	buildCardsDeque.push_back(Cards(handCard.substr(0, 1), handCard.substr(1, 1)));
	
	addBuiltToTable(buildCardsDeque);
	setBuildInBuildClass(buildCardsDeque);
}
bool Human::Trial(string card, int builtSum, int numCardToCapBuilt) {

	if (isHandCardLegal(card)) {
		if ((getCardNumber(Cards(card.substr(0, 1), card.substr(1, 1))) == builtSum) && numCardToCapBuilt == 1) {
			return false;
		}
		else {
			for (deque<Cards> insideTable : table) {
				for (Cards tab : insideTable) {
					if (tab.getFace() == card.substr(1,1)) {
						return false;
					}
				}
			}
			return true;
		}
	}
	else {
		return false;
	}
}


void Human::capture(int builtSum, int numCardToCapBuilt) {
	int numSets;
	cout << "How many set(s) do you want to capture?" << endl;
	cin >> numSets;
	string handCard;
	do {
		cout << "Enter Hand Card that you will use to capture: ";
		cin >> handCard;
	} while (!isHandCardLegal(handCard) && ((getCardNumber(Cards(handCard.substr(0, 1), handCard.substr(1, 1))) == builtSum) && numCardToCapBuilt == 1));

	string temp;
	deque<Cards> cardsToCapture = getCardsToCapture(handCard, numSets);

	// deletes card dealt by human

	cout << "Cards to capture" << endl;
	for (Cards a : cardsToCapture) {
		cout << a.toString() << " ";
	}
	cout << endl;

	// Deletes the cards from human hand and table and adds to the pile of human
	deleteHandCard(Cards(handCard.substr(0, 1), handCard.substr(1, 1)));
	addToPile(Cards(handCard.substr(0, 1), handCard.substr(1, 1)));

	for (Cards capt : cardsToCapture) {
		addToPile(capt);
	}
	deleteCardTable(cardsToCapture);
}


deque<Cards> Human::getCardsToCapture(string handCard, int numSets) {

	string oneSet; 
	bool check = true;
	deque<Cards> toreturn;
	int handNum = getCardNumber(Cards(handCard.substr(0, 1), handCard.substr(1, 1)));
	cout << "Enter sets from table that you want to capture: " << endl;
	for (int i = 0; i < numSets; i++) {
		cout << " i -->" << numSets << endl;
		do {
			cin.ignore();
			getline(cin, oneSet);
			int sum = 0;
			string buff;
			stringstream ss(oneSet);
			deque<Cards> temp;
			while (ss >> buff) {
				if (isTableCardLegal(buff)) {
					//cout << "Is legal" << endl;
					sum = sum + getCardNumber(Cards(buff.substr(0, 1), buff.substr(1, 1)));
					temp.push_back(Cards(buff.substr(0, 1), buff.substr(1, 1)));
					check = true;
				}
				else {
					//cout << "No 1" << endl;
					check = false;
				}
			}

			if (sum == handNum) {
				//cout << "Sum is " << sum << endl;
				for (Cards a : temp) {
					toreturn.push_back(a);
				}
				check = true;
			}
			else {
				//cout << "No 2" << endl;
				check = false;
			}

		} while (check == false);
	}
	return toreturn;
}

// Checks if the table card entered by user is in the table
bool Human::isTableCardLegal(string tableCard) {

	for (deque<Cards> insideTable : table) {
		for (Cards tableC : insideTable) {
			if (tableC.toString() == tableCard) {
				return true;
			}
		}
	}
	return false;
}

// checks if the hand card entered by user is in the player's hand
bool Human::isHandCardLegal(string handCard) {
	for (Cards hand : returnHand()) {
		if (hand.toString() == handCard) {
			return true;
		}
	}
	return false;
}

// Displays menu when its human's turn
void Human::showMenu() {
	cout << "1. Save  the game" << endl;
	cout << "2. Make a move" << endl;
	cout << "3. Ask for a help" << endl;
	cout << "4. Quit the game\n" << endl;
}

void Human::showGameOption() {
	cout << "1. Capture" << endl;
	cout << "2. Capture Build" << endl;
	cout << "3. Set Build" << endl;
	cout << "4. Trail\n" << endl;
}

Human::~Human()
{
}
