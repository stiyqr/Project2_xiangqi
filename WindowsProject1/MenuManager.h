#pragma once
#include "Viewer.h"
#include "Chess.h"
#include <string>
#include <deque>

class GameManager;

class MenuManager
{
public:	
	struct Reader {
	Chess::Side playerSide;
	Chess::Position startPos, endPos;

	Reader(int, int, int, int, int);
};

public:
	Viewer viewer;
	GameManager* gameManagerDummy;
	std::deque<Reader> reader;
	bool isReading = false;

public:
	MenuManager();

	// Functions
	void createMainMenu(bool&, bool&);
	void readFileMenu(bool&);

	std::wstring openfilename(const TCHAR* filter = TEXT("(*.txt) Text Files\0*.txt\0"));


};