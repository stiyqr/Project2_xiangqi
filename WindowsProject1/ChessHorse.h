#pragma once
#include "Chess.h"

class ChessHorse : public Chess {
public:
	ChessHorse();
	ChessHorse(const char*, int, int);

	void updateAllPossibleMove(std::vector<Chess*>) override;
};