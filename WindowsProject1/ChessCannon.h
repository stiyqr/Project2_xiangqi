#pragma once
#include "Chess.h"

class ChessCannon : public Chess {
public:
	// Constructors
	ChessCannon();
	ChessCannon(const char*, int, int);

	// Functions
	void updateAllPossibleMove(std::vector<Chess*>);
};