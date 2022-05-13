#pragma once
#include "Viewer.h"
#include "Chess.h"
#include "Board.h"
#include <vector>

class GameManager {
public:
	std::vector<Chess*> on_board;
	Chess::Side current_player = Chess::Side::RED;
	Board board;
	Viewer viewer;

public:
	GameManager();

	void createGameBoard(bool&, bool&);
};