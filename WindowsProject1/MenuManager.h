#pragma once
#include "Viewer.h"
#include "Chess.h"
#include <string>
#include <deque>

// forward declaration
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
	GameManager* gmDummy;
	std::deque<Reader> reader;
	bool isReading = false;
	bool isLoading = false;

public:
	MenuManager();

	// Functions
	void createMainMenu(bool&, bool&);
	void readFileMenu(bool&);
	void readFile(bool&);
	std::wstring openfilename(const TCHAR* filter = TEXT("(*.txt) Text Files\0*.txt\0"));
	GameManager* loadGameMenu(bool&, bool&);
	void loadGame(std::string);
};