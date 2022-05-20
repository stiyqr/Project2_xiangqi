#pragma once
#include "Chess.h"

class ChessElephant : public Chess {
public:
	// Constructors
	ChessElephant();
	ChessElephant(const char*, int, int);

	// Functions
	void updateAllPossibleMove(std::vector<Chess*>);
};