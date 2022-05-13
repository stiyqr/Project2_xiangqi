#pragma once
#include "Chess.h"

class ChessGeneral : public Chess {
public:
	ChessGeneral();
	ChessGeneral(const char*);

	void updateAllPossibleMove(std::vector<Chess*>) override;
};