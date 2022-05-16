#pragma once
#include "Chess.h"

class ChessGeneral : public Chess {
public:
	ChessGeneral();
	ChessGeneral(const char*);
	ChessGeneral(const char*, int, int);

	void updateAllPossibleMove(std::vector<Chess*>) override;
};