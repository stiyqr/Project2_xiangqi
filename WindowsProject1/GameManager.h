#pragma once
#include "Viewer.h"
#include "Chess.h"
#include "Board.h"
#include <vector>
#include <fstream>

class GameManager {
public:
	std::vector<Chess*> on_board;
	Chess::Side current_player = Chess::Side::RED;
	Board board;
	Viewer viewer;
	bool inCheckmate = false;
	bool inStalemate = false;
	bool startNewGame = false;
	float timer = 0.f;
	static std::ofstream logFile;

public:
	// Constructors
	GameManager();
	GameManager(std::string);

	// Functions
	void createGameBoard(bool&, bool&);
	bool isCheck(Chess::Side, std::vector<Chess*>);
	bool isCheckmate(Chess::Side, std::vector<Chess*>);
	bool isStalemate(Chess::Side, std::vector<Chess*>);
	void saveGameMenu(bool&);
	void saveGame(std::string);
};