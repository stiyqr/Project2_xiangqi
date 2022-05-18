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
	// Struct for reader (to read file)
	struct Reader {
	Chess::Side playerSide;
	Chess::Position startPos, endPos;
	// Constructor
	Reader(int, int, int, int, int);
};

public:
	Viewer viewer;
	GameManager* gmDummy;
	std::deque<Reader> reader;
	bool isReading = false;
	bool isLoading = false;

public:
	// Constructor
	MenuManager();

	// Functions
	void createMainMenu(bool&, bool&);
	void readFile(bool&);
	GameManager* loadGameMenu(bool&, bool&);
	std::wstring openfilename(const TCHAR* filter = TEXT("(*.txt) Text Files\0*.txt\0"));
};