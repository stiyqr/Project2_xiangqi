#pragma once
#include "Viewer.h"
#include <vector>

class Chess {
public:
	const char* id;
	bool isActive = false;
	bool isAlive = true;
	Viewer viewer;

public:
	Chess();
	Chess(const char*);
};