#ifndef AAA_HEADER
#define AAA_HEADER

#include "stdafx.h"

using namespace std;

class Cards {

private:

	// Stores the value of face of the card
	string face;

	// Stores the type of suit of the card
	string suit;
public:
	Cards();

	//Sets the face and suit to the Cards
	Cards(string face, string suit);

	// Returns the string value of the card
	string toString();

	// Returns the string value of the Suit
	string getSuit() {
		return suit;
	}

	// Returns the string value of the Suit
	string getFace() {
		return face;
	}

	~Cards();

};

#endif

