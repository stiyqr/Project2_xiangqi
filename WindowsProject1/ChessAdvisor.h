#pragma once
#include "Chess.h"

class ChessAdvisor : public Chess {
public:
	// Constructors
	ChessAdvisor();
	ChessAdvisor(const char*, int, int);

	// Functions
	void updateAllPossibleMove(std::vector<Chess*>) override;
};