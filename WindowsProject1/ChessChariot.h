#pragma once
#include "Chess.h"

class ChessChariot : public Chess {
public:
	ChessChariot();
	ChessChariot(const char*, int, int);

	void updateAllPossibleMove(std::vector<Chess*>);
};