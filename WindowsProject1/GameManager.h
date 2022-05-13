#pragma once
#include "Viewer.h"
#include "Chess.h"
#include "Board.h"
#include <vector>

class GameManager {
public:
	Viewer viewer;
	std::vector<Chess*> on_board;
	Board board;

public:
	GameManager();

	void createGameBoard(bool&, bool&);
	void displayGameBoard(bool&, bool&);
};