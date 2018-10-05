#pragma once
#include "stdafx.h"
#include "Cards.h"
//#include "Player.h"

using namespace std;

class Build {

private:
	deque<Cards> built;
	string buildOwner;
	bool isOwner;

public:
	Build() {

	}

	// thsi functions returns the built of the player
	deque<Cards> getBuilt() {
		return built;
	}

	string getOwner() {
		return buildOwner;
	}

	void setBuilt(deque<Cards> builtReceived) {
		built = builtReceived;
	}

	void setOwner(bool isOwn) {
		isOwner = isOwn;
	}

	void emptyBuilt() {
		built.clear();
	}


};


