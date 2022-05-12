#pragma once
#include "Viewer.h"

class MenuManager
{
public:
	Viewer viewer;

public:
	MenuManager();

	// Functions
	void createMainMenu(bool&, bool&);
	void createGameBoard(bool&, bool&);
};