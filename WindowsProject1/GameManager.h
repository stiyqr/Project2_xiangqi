#pragma once
#include "Viewer.h"
#include "Chess.h"

class GameManager {
public:
	Viewer viewer;
	//std::vector

public:
	GameManager();

	void createGameBoard(bool&, bool&);
};