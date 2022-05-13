#pragma once
#include "Viewer.h"
#include <vector>


class Chess {
public:
	enum class Side { RED, BLACK };

	const char* id;
	Side side;
	bool isActive = false;
	bool isAlive = true;
	Viewer viewer;
	int curPosX;
	int curPosY;
	Viewer::Texture* img;

public:
	Chess();
};