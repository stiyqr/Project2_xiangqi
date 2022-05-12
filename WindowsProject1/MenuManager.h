#pragma once
#include "Viewer.h"

class MenuManager
{
public:
	Viewer viewer;

public:
	MenuManager();

	// Functions
	void createTextures ();
	void createMainMenu(bool&, bool&);
};