#include "Player.h"
#include "stdafx.h"


Player::Player()
{

}


void Player::play(deque<deque<Cards>> &tableRound) {
	table.clear();
	table = tableRound;
	getAllSubsets();
	lookforSingleBuild();
	findBestSingleBuild();
	printBuilt();

	deque<deque<Cards>> builtsFromTable;
	builtsFromTable.clear();

	builtsFromTable = getBuilts();


	// if statement to check if built still exists on table
	// One players built can be capture by another playing without changing the owner status
	if (hasOwnBuild(builtsFromTable)) {
		cout << "Has Own Build" << endl;
		for (Cards a : build.getBuilt()) {
			cout << a.toString() << " ";
		}
		cout << endl;

	}
	else {
		build.emptyBuilt();
		build.setOwner(false);
	}

	cout << "Players Hand" << endl;
	printHand();
	int buildPosition = 0;

	if (DXCaptureIsPossible()) {
		cout << "Computer choose to capture DX. It wanted to score 2 points by capturing the 10 of Diamonds." << endl;
		captureCards();
		isLastCapture = true;
	}
	else if (aceCaptureIsPossible()) {
		cout << "Computer choose to capture cards that contains ACE. It wanted to get 1 points for each Ace." << endl;
		captureCards();
		isLastCapture = true;
	}
	else if (isBuildCapturePossible(buildPosition)) {
		cout << "Computer choose to capture build. It wanted to maximize the number captured cards." << endl;
		captureBuild(table.at(buildPosition));
		table.erase(table.begin() + buildPosition);
		isLastCapture = true;
	}
	else if (built.size() > 0) {
		cout << "The computer choose to set a build on table. It wanted to maximize the number of cards that could be captured in next turn." << endl;
		addBuiltToTable(built);
		deleteCardTable(built);
		deleteHandCard(built.back());
		isBuildOwner = true;
		build.setBuilt(built);
		isLastCapture = false;
	}
	else if (isThereCapure()) {					// check if capture is possible
		cout << "Capturing normal cards -----------------------------------------------------------" << endl;
		captureCards();
	}
	else {
		cout << "Trail Card ----------------------------------------------------------------------------" << endl;
		Cards temp = getCard();
		addCardTable(temp);
		isLastCapture = false;
	}

	cout << "Players Hand:" << endl;
	printHand();
	printTable();
	cout << "Players Pile" << endl;
	printPile();

	clearDequeValues();
	tableRound = table;
}

bool Player::aceCaptureIsPossible() {
	// hand used to capture
	Cards handUsed;
	// Returns the possible capture
	deque<deque<Cards>> capturePossible = possibleCaptures(handUsed);

	// Stores the best capture possible
	deque<Cards> largeCapture = getBestCapture(capturePossible);

	for (Cards cardInCapture : largeCapture) {
		if (cardInCapture.getFace()== "A" || handUsed.getFace() == "A") {
			return true;
		}
	}
	return false;
}

// Checks if the built on the table is his built
bool Player::hasOwnBuild(deque<deque<Cards>> builtsFromTable) {

	deque<Cards> myBuilt = build.getBuilt();

	if (myBuilt.size() != 0) {
		for (deque<Cards> BuiltTable : builtsFromTable) {
			if (myBuilt.front().toString() == BuiltTable.front().toString()) {
				return true;
			}
		}
	}

	return false;
}

bool Player::DXCaptureIsPossible(){

	// hand used to capture
	Cards handUsed;					

	// Returns the possible capture
	deque<deque<Cards>> capturePossible = possibleCaptures(handUsed);

	// Stores the best capture possible
	deque<Cards> largeCapture = getBestCapture(capturePossible);

	for (Cards cardInCapture : largeCapture) {
		if (cardInCapture.toString() == "DX" || handUsed.toString() == "DX") {
			return true;
		}
	}
	return false;
}

// Returns the best possible captures 
deque<Cards> Player::getBestCapture(deque<deque<Cards>> capturePossible) {
	// Removes the repeated cards in the capture possiblle
	deque<deque<Cards>> tempMatch;
	bool check = false;
	for (deque<Cards> a : capturePossible) {
		for (Cards b : a) {
			if (checkForRepeat(b, tempMatch)) {
				check = true;
				continue;
			}
		}
		if (check == false) {
			tempMatch.push_back(a);
		}
	}


	deque<Cards> largeCapture;			// to store all the cards from best capture is a 1-D array
	for (deque<Cards> a : tempMatch) {
		for (Cards b : a) {
			largeCapture.push_back(b);
		}
	}

	return largeCapture;
}


// returns the possible captures of in the table using your hand
deque<deque<Cards>> Player::possibleCaptures(Cards &handUsed) {
	deque<deque<Cards>> capturePossible;
	int size = 0;
	deque<deque<Cards>> captureTemp;
	
	
	// gets the maximum number of cards that can be captured using cards from playersHand
	for (Cards b : playersHand) {
		captureTemp = getPossible(b);
		int num = getNumberOfCards(captureTemp);
		if (num > size) {
			handUsed = b;
			capturePossible.clear();
			capturePossible = captureTemp;
			size = num;
		}
		captureTemp.clear();
	}

	return capturePossible;
}



bool Player::isBuildCapturePossible(int &position) {
	
	for (deque<Cards> insideTable : table) {
		int sum = 0;
		if (insideTable.size() > 1) {
			for (Cards temp : insideTable) {
				sum = sum + getCardNumber(temp);
			}
			for (Cards handC : playersHand) {
				if (sum == getCardNumber(handC)) {
					return true;
				}
			}
		}
		position++;
	}
	return false;
}


int Player::getSumOfMyBuild() {
	deque<Cards> myBuild = build.getBuilt();
	int sum = 0;
	for (Cards temp : myBuild) {
		sum = sum + getCardNumber(temp);
	}
	return sum;
}

deque<deque<Cards>> Player::getBuilts() {
	deque<deque<Cards>> toReturn;
	for (deque<Cards> insideTable : table) {
		if (insideTable.size() > 1) {
			toReturn.push_back(insideTable);
		}
	}
	return toReturn;
}

void Player::addCardTable(Cards fromPlayer) {
	deque<Cards> temp;
	temp.push_back(fromPlayer);
	table.push_back(temp);
}

bool Player::checkForTrail() {
	if (checkIfBuildOwner() == false) {
		for (Cards handCard : playersHand) {
			for (deque<Cards> insideTable : table) {
				if (insideTable.size() == 1) {
					for (Cards tableCard : insideTable) {
						if (handCard.getFace() == tableCard.getFace()) {
							return false;
						}
					}
				}
			}
		}
		return true;
	}
	else {
		return false;
	}
}


void Player::clearDequeValues() {
	subsets.clear();
	possibleBuilds.clear();
	built.clear();
	tempTable.clear();
	matches.clear();
}

// Captures individual cards, set of cards, or combination of individual and set of cards
void Player::captureCards() {

	Cards handUsed;					// hand used to capture

// Returns the possible capture
	deque<deque<Cards>> capturePossible = possibleCaptures(handUsed);

	// Stores the best capture possible
	deque<Cards> largeCapture = getBestCapture(capturePossible);

	cout << "Large Capture is " << endl;
	for (Cards x : largeCapture) {
		cout << x.toString() << " ";
	}
	cout << "The card that is used to capture is " << handUsed.toString() << endl;
	cout << endl;

	for (Cards capt : largeCapture) {
		addToPile(capt);
	}
	deleteCardTable(largeCapture);
	deleteHandCard(handUsed);
	addToPile(handUsed);

}

// Only stores the unique value for capture
bool Player::checkForRepeat(Cards a, deque<deque<Cards>> tempMatch) {
	for (deque<Cards> x : tempMatch) {
		for (Cards y : x) {
			if (y.toString() == a.toString()) {
				return true;
			}
		}
	}
	return false;
}

// Gets the number of cards that can be captured 
int Player::getNumberOfCards(deque<deque<Cards>> xyz) {
	int num = 0;
	for (deque<Cards> xy : xyz) {
		for (Cards ab : xy) {
			num++;
		}
	}
	return num;
}

deque<deque<Cards>> Player::getPossible(Cards handCheck) {
	deque<deque<Cards>> forCheck;
	subsets.clear();
	getAllSubsets();
	for (deque<Cards> a : subsets) {
		int sum = 0;
		for (Cards b : a) {
			sum = sum + getCardNumber(b);
		}
		if (sum == getCardNumber(handCheck)) {
			forCheck.push_back(a);
		}
	}
	return forCheck;
}

bool Player::checkAceS2(deque<Cards> &aceORS2) {
	size_t size = 0;
	for (deque<Cards> insideMatch : matches) {
		for (Cards a : insideMatch) {
			if (a.getFace() == "A" || a.toString() == "S2") {
				if (insideMatch.size() > size) {
					aceORS2.clear();
					for (Cards b : insideMatch) {
						Cards temp = insideMatch.front();
						insideMatch.pop_front();
						aceORS2.push_back(temp);
					}
				}
				size = insideMatch.size();
			}
		}
	}
	if (aceORS2.size() != 0) {
		return true;
	}
	return false;
}

void Player::getMatchesForCapture() {

	for (deque<Cards> c : table) {
		int sum = 0;
		for (Cards a : c) {
			sum = sum + getCardNumber(a);
		}

		for (Cards b : playersHand) {
			if (getCardNumber(b) == sum) {
				c.push_back(b);
				matches.push_back(c);
			}
		}
	}
}

bool Player::isThereCapure() {
	getAllSubsets();
	getMatchesForCapture();

	cout << "Matches ----->" << endl;
	for (deque<Cards> temp : matches) {
		for (Cards a : temp) {
			cout << a.toString() << " ";
		}
		cout << endl;
	}


	if (matches.size() > 0) {
		return true;
	}
	return false;
}

void Player::printMatches() {
	for (deque<Cards> insideMatch : matches) {
		for (Cards cardInMatch : insideMatch) {
			cout << cardInMatch.toString() << " ";
		}
		cout << endl;
	}
	cout << endl;
}

// Deletes cards from table that are part of build
void Player::deleteCardTable(deque<Cards> deleteFrom) {

	bool received;
	int position = 0;
	for (deque<Cards> inTable : table) {
		if (inTable.size() == 1) {
			received = checkCard(inTable.front(), deleteFrom);
			if (received == true) {
				tempTable.push_back(inTable);
			}
		}
		else {
			tempTable.push_back(inTable);
		}
	}
	cout << endl;
	table.clear();
	table = tempTable;
}

bool Player::checkCard(Cards temp, deque<Cards> deleteFrom) {
	bool ans = true;
	for (Cards a : deleteFrom) {
		if (a.toString() == temp.toString()) {
			ans = false;
			break;
		}
		else {

		}
	}
	return ans;
}

// Adds build to the table
void Player::addBuiltToTable(deque<Cards> add) {
	table.push_front(add);
}

// Prints all cards from table
void Player::printTable() {
	cout << "Table:" << endl;
	cout << string(50, '-') << endl;

	for (deque<Cards> temp : table) {
		for (Cards insideTable : temp) {
			cout << insideTable.toString() << " ";
		}
		cout << endl;
	}
	cout << endl << endl;
}

bool Player::checkIfTableHasBuild() {

	for (deque<Cards> temp : table) {
		if (temp.size() > 1) {
			return true;
		}
	}
	return false;
}

// Finds the build with largest number of cards
void Player::findBestSingleBuild() {
	//deque<Cards> built;
	size_t size = 0;
	deque<Cards> temp;
	for (deque<Cards> a : possibleBuilds) {
		if (a.size() > size) {
			temp = a;
		}
		size = a.size();
	}
	for (Cards toBuilt : temp) {
		built.push_back(toBuilt);
	}
}

void Player::lookforSingleBuild() {
	int number;
	size_t size = 0;
	deque<Cards> temp;
	for (Cards playerCard : playersHand) {

		number = getCardNumber(playerCard);

		for (deque<Cards> a : subsets) {
			int sum = 0;
			for (Cards b : a) {
				sum = sum + getCardNumber(b);
			}
			int totalSum = number + sum;

			for (Cards playerCard2 : playersHand) {
				int playerNumber = getCardNumber(playerCard2);
				if ((totalSum == playerNumber) && (playerCard2.toString() != playerCard.toString())) {
					addToPossibleBuild(a, playerCard);
				}
			}
			size = a.size();
		}
	}
}


// Stores all the possible builds to an deque of deque
void Player::addToPossibleBuild(deque<Cards>fromTable, Cards fromPlayer) {

	deque<Cards> temp;
	for (Cards a : fromTable) {
		temp.push_back(a);
	}
	temp.push_back(fromPlayer);
	possibleBuilds.push_back(temp);
}

void Player::getAllSubsets() {
	deque<Cards> empty;

	// Deque to store all the cards of the table except cards that are in build
	deque<Cards> tTable;

	for (deque<Cards> insideTable : table) {
		if (insideTable.size() == 1) {
			for (Cards a : insideTable) {
				tTable.push_back(a);
			}
		}
	}
	subsets.clear();
	subsets.push_back(empty);
	for (size_t i = 0; i < tTable.size(); i++)
	{
		deque< deque<Cards> > subsetTemp = subsets;

		for (size_t j = 0; j < subsetTemp.size(); j++)
			subsetTemp[j].push_back(tTable[i]);

		for (size_t j = 0; j < subsetTemp.size(); j++)
			subsets.push_back(subsetTemp[j]);
	}
	subsets.pop_front();
}

void Player::printBuilt() {
	cout << "Build:" << endl;
	if (!built.empty()) {
		for (Cards a : built) {
			cout << a.toString() << " ";
		}
		cout << endl;
	}
}


bool Player::isBuildPossible() {
	return true;
}

// Checks if the table has any build
void Player::ifBuildCapture(deque<deque<Cards>> &table) {
	int position = 0;
	for (deque<Cards> insideTable : table) {
		if (insideTable.size() > 1) {
			captureBuild(insideTable);
			table.erase(table.begin() + position);
		}
		position++;
	}

}

// Capture the build that is on table
void Player::captureBuild(deque<Cards> buildInTable) {
	Cards h = buildInTable.back();
	int sum = 0;
	for (Cards temp : buildInTable) {
		sum = sum + getCardNumber(temp);
		addToPile(temp);
	}
	cout << "Sum of build is " << sum << endl;
	for (Cards a : playersHand) {
		if (getCardNumber(a) == sum) {
			cout << "The card that is going to be delete is " << a.toString() << endl;
			deleteHandCard(a);
			addToPile(a);
			return;
		}
	}

}



void Player::deleteDealtCard(Cards dealtCard) {
	int position = 0;
	for (Cards a : playersHand) {
		if (dealtCard.toString() == a.toString()) {
			playersHand.erase(playersHand.begin() + position);
		}
		position++;
	}
}


//Adds four cards to the player's hand
void Player::addCard(Cards hand) {
	playersHand.push_back(hand);
}

// Get card from the playersHand
Cards Player::
getCard() {
	Cards temp = playersHand.front();
	playersHand.pop_front();
	return temp;
}

// Receives card from table and adds it to playerspile
void Player::addToPile(Cards temp) {
	playersPile.push_back(temp);
}

// Returns the size of the player's pile
int Player::getPileSize() {
	return playersPile.size();
}

// Returns the number of spade cards in player's pile
int Player::getSpadesNum() {
	int numSpades = 0;
	for (auto pile : playersPile) {
		if (pile.getSuit() == "S") {
			numSpades++;
		}
	}
	return numSpades;
}

// Returns the number of Ace cards in player's pile
int Player::getAceNum() {
	int numAce = 0;
	for (auto pile : playersPile) {
		if (pile.getFace() == "A") {
			numAce++;
		}
	}
	return numAce;
}

// Returns true if the player has ten of diamonds. if not returns false
bool Player::hasTenOfDiamonds() {
	for (auto pile : playersPile) {
		if (pile.toString() == "DX") {
			return true;
		}
	}
	return false;
}

// Returns true if the player has two of spades. if not returns false
bool Player::hasTwoOfSpades() {
	for (auto pile : playersPile) {
		if (pile.toString() == "S2") {
			return true;
		}
	}
	return false;
}

// Prints all the cards that are in player's hand
void Player::printHand() {
	cout << string(50, '-') << endl;
	for (auto hand : playersHand) {
		cout << hand.toString() << " ";
	}
	cout << "\n\n";
}

// Prints all the cards that are in player's pile
void Player::printPile() {
	cout << string(50, '-') << endl;
	for (auto pile : playersPile) {
		cout << pile.toString() << " ";
	}
	cout << "\n\n";
}


deque<deque<Cards> > Player::getAllSubsets(deque<Cards> set) {
	deque< deque<Cards> > subset;
	deque<Cards> empty;
	subset.push_back(empty);
	for (size_t i = 0; i < set.size(); i++)
	{
		deque< deque<Cards> > subsetTemp = subset;

		for (size_t j = 0; j < subsetTemp.size(); j++)
			subsetTemp[j].push_back(set[i]);

		for (size_t j = 0; j < subsetTemp.size(); j++)
			subset.push_back(subsetTemp[j]);
	}
	return subset;
}






Player::~Player()
{
}
