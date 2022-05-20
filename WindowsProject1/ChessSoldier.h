#pragma once
#include "Chess.h"

class ChessSoldier : public Chess {
public:
	// Constructors
	ChessSoldier();
	ChessSoldier(const char*, int, int);
	
	// Functions
	void updateAllPossibleMove(std::vector<Chess*>);
};