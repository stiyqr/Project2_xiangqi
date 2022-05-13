#pragma once
#include "Chess.h"

class ChessCannon : public Chess {
public:
	ChessCannon();
	ChessCannon(const char*, int, int);

	void updateAllPossibleMove(std::vector<Chess*>);
};