#pragma once
#include "Chess.h"

class ChessElephant : public Chess {
public:
	ChessElephant();
	ChessElephant(const char*, int, int);

	void updateAllPossibleMove(std::vector<Chess*>);
};