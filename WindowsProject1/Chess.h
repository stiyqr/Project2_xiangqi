#pragma once
#include "Viewer.h"
#include <vector>


class Chess {
public:
	enum class Side { RED, BLACK };
	enum class Rank { GENERAL, ADVISOR, ELEPHANT, HORSE, CHARIOT, CANNON, SOLDIER};

	struct Position {
		int x, y;

		Position();
		Position(int, int);

		Position& operator=(Position);
		bool operator==(Position);
	};

	const char* id;
	Side side;
	Rank rank;
	bool isActive = false;
	bool isAlive = true;
	Viewer viewer;
	Viewer::Texture* img;
	Viewer::Texture* moveImg;
	Position curPos;
	std::vector<Position> allPossibleMove;

public:
	Chess();

	virtual void updateAllPossibleMove(std::vector<Chess*>);
};