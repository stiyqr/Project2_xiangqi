#pragma once
#include "Chess.h"

class ChessChariot : public Chess {
public:
	// Constructors
	ChessChariot();
	ChessChariot(const char*, int, int);

	// Functions
	void updateAllPossibleMove(std::vector<Chess*>);
};