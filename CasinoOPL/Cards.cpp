#include "Cards.h"
#include "stdafx.h"

using namespace std;

Cards::Cards() {
	this->face = "0";
	this->suit = "0";
}

//Sets the face and suit to the Cards
Cards::Cards(string suit, string face) {
	this->face = face;
	this->suit = suit;
}

// Returns the string value of the card
string Cards::toString() {
	return suit + face;
}


Cards::~Cards()
{
}
