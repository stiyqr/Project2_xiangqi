#pragma once
#include "Viewer.h"
#include "Chess.h"

class GameManager {
public:
	Viewer viewer;

public:
	GameManager();

	void createGameBoard();
};