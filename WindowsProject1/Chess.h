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

	const char* id{};
	Side side{};
	Rank rank{};
	bool isDead = false;
	Viewer viewer;
	Viewer::Texture* img{};
	Viewer::Texture* moveImg{};
	Position curPos;
	Position animPos;
	float animProg = 1;
	float alpha = 1;
	std::vector<Position> allPossibleMove;

public:
	Chess();

	virtual void updateAllPossibleMove(std::vector<Chess*>);
};