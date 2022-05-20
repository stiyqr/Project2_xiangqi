#pragma once
#include "Chess.h"

class ChessGeneral : public Chess {
public:
	// Constructors
	ChessGeneral();
	ChessGeneral(const char*);
	ChessGeneral(const char*, int, int);

	// Functions
	void updateAllPossibleMove(std::vector<Chess*>) override;
};