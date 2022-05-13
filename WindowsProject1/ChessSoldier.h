#pragma once
#include "Chess.h"

class ChessSoldier : public Chess {
public:
	ChessSoldier();
	ChessSoldier(const char*, int, int);

	void updateAllPossibleMove();
};