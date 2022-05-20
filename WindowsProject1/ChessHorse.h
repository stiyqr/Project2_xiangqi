#pragma once
#include "Chess.h"

class ChessHorse : public Chess {
public:
	// Constructors
	ChessHorse();
	ChessHorse(const char*, int, int);

	// Functions
	void updateAllPossibleMove(std::vector<Chess*>) override;
};