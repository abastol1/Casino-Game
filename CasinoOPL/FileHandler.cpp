#include "FileHandler.h"
#include"Cards.h"

using namespace std;

FileHandler::FileHandler()
{
}


void FileHandler::saveGame(int roundNumber, int computerScore, deque<Cards> computerHand, deque<Cards> computerPile, int humanScore, deque<Cards> humanHand, deque<Cards> humanPile, deque<deque<Cards>> table, deque<Cards> buildOwner, string buildOwnerName, deque<Cards> deck, string nextPlayer) {

	string fileName = "savedGame.txt";
	ofstream ofile;

	ofile.open(fileName);

	if (!ofile) {
		cout << "File can not be opened!" << endl;
	}
	ofile << "Round: " << endl;

	ofile << "\nComputer: " << endl;
	ofile << "     Score: " << computerScore << endl;
	ofile << "     Hand: ";
	for (Cards hand : computerHand) {
		ofile << hand.toString() << " ";
	}


	ofile << "\n     Pile: ";
	for (Cards pile : computerPile) {
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
	for (Cards inDeck : deck) {
		ofile << inDeck.toString() << " ";
	}
	cout << endl;
	ofile << "\n\nNext Player: " << nextPlayer << endl;
}

bool FileHandler::isFileOpen(string fileName) {

	return true;
}


void FileHandler::loadGame() {

	string fileName;
	do {
		cout << "Enter the name of the file with extension(.txt): ";
		cin >> fileName;
		ifile.open(fileName);
	} while (!ifile);


	int roundNumber, computerScore, humanScore;

	deque<Cards> computerHand;
	deque<Cards> computerPile;
	deque<Cards> humanHand;
	deque<Cards> humanPile;

	deque<deque<Cards>> table;

	deque<Cards> buildOwner;
	string buildOwnerName;
	deque<Cards> deck;

	string NextPlayer;

	string line;
	int lineIndex = 0;

	while (getline(ifile, line)) {
		int count = 1;
		cout << line << endl;

		if (lineIndex == 0) {
			roundNumber = getInteger(line);
			lineIndex++;
			continue;
		}
		else {
			lineIndex++;
		}
		// Get computer score from line 4
		if (lineIndex == 4) {
			computerScore = getInteger(line);
		}

		if (lineIndex == 9) {
			humanScore = getInteger(line);
		}

		if (lineIndex == 5) {
			storeInDeque(line, computerHand);
		}
		if (lineIndex == 6) {
			storeInDeque(line, computerPile);
		}
		if (lineIndex == 10) {
			storeInDeque(line, humanHand);
		}
		if (lineIndex == 11) {
			storeInDeque(line, humanPile);
		}
		if (lineIndex == 17) {
			storeInDeque(line, deck);
		}
		if (lineIndex == 19) {
			stringstream ss;
			ss << line;
			string temp;
			int count = 1;
			while (!ss.eof()) {
				ss >> temp;
				if (count == 3) {
					NextPlayer = temp;
				}
			}
		}

		if (lineIndex == 13) {
			// get the table with build 
			stringstream ss; 
			ss << line;
			deque<Cards> build;
			string temp; 
			int count = 1;
			bool check = false;
			while (!ss.eof()) {
				ss >> temp;

				if (temp == "[") {
					check = true;
				}
				else if (temp == "]") {
					cout << "Here" << endl;
					table.push_front(build);
					build.clear();
					check = false;
				}
				else if (check == true) {
					build.push_back(Cards(temp.substr(0, 1), temp.substr(1, 1)));
				}
				else if (count!=1) {
					deque<Cards> card; 
					card.clear();
					card.push_back(Cards(temp.substr(0, 1), temp.substr(1, 1)));
					table.push_back(card);
				}
				count++;
			}
		}
		if (lineIndex == 15) {
			stringstream ss;
			ss << line;
			deque<Cards> build;
			build.clear();
			string temp;
			int count = 1;
			bool check = false;
			while (!ss.eof()) {
				ss >> temp;

				if (temp == "[") {
					check = true;
				}
				else if (temp == "]") {
					check = false;
				}
				else if (check == true) {
					buildOwner.push_back(Cards(temp.substr(0, 1), temp.substr(1, 1)));
				}
				else if (count != 1) {
					buildOwnerName = temp;
				}
				count++;
			}
		}
	}


	
	cout << "Round Number ---->" << roundNumber << endl;
	cout << "Computer score --> " << computerScore << endl;
	cout << "Human score -----> " << humanScore << endl;
	cout << "Computer Hand --->";
	printDeque(computerHand);
	cout << "Computer Pile --->";
	printDeque(computerPile);

	cout << "Human Hands ----->";
	printDeque(humanHand);
	cout << "Human Pile ------>";
	printDeque(humanPile);
	cout << "Table Cards ------->" << endl;
	for (deque<Cards> insideTable : table) {
		for (Cards a : insideTable) {
			cout << a.toString() << " ";
		}
		cout << endl;
	}
	cout << endl;

	cout << "Build Owner: ";
	printDeque(buildOwner);
	cout << endl;
	cout << "The name of build owner is " << buildOwnerName << endl;

}

void FileHandler::storeInDeque(string line, deque<Cards>& toStore) {
	stringstream ss;
	ss << line;
	string temp;
	int count = 1;
	while (!ss.eof()) {
		ss >> temp;
		if (count > 1) {
			//storeInDeque(temp, toStore);
			toStore.push_back(Cards(temp.substr(0, 1), temp.substr(1, 1)));
		}
		count++;
	}
}

void FileHandler::printDeque(deque<Cards> toPrint) {
	for (Cards temp : toPrint) {
		cout << temp.toString() << " ";
	}
	cout << endl;
}

int FileHandler::getInteger(string line) {
	stringstream ss;
	// Storing the whole string into string stream 
	ss << line;

	// Running loop till the end of the stream 
	string temp;
	int found;
	while (!ss.eof()) {

		// extracting word by word from stream 
		ss >> temp;

		// Checking the given word is integer or not
		if (stringstream(temp) >> found) {
			return found;
		}

		// To save from space at the end of string
		temp = "";
	}
	return 1;
}

FileHandler::~FileHandler()
{
}
