#pragma once
#include "Viewer.h"
#include <vector>


class Chess {
public:
	enum class Side { RED, BLACK };
	enum class Rank { GENERAL, ADVISOR, ELEPHANT, HORSE, CHARIOT, CANNON, SOLDIER};

	struct Position {
		int x, y;
	};

	const char* id;
	Side side;
	Rank rank;
	bool isActive = false;
	bool isAlive = true;
	Viewer viewer;
	Viewer::Texture* img;
	Position curPos;
	std::vector<Position> allPossibleMove;

	

public:
	Chess();

	
};