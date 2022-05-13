#include "GameManager.h"
#include "ChessGeneral.h"

GameManager::GameManager() {}

void GameManager::createGameBoard(bool& appRunning, bool& startGame) {
	ImVec2 screenSize = viewer.createWindow(appRunning, viewer.backgroundGame);

	// Control buttons
	viewer.setButtonPos(800, 460);
	Viewer::Button backToMenuButton("backToMenuBtn", viewer.buttonBackToMenuImg, viewer.buttonBackToMenuHoverImg, Viewer::Button::Type::MAINMENU);

	// chess piece
	viewer.setButtonPos(610, 460);
	ChessGeneral redGeneralButton("redGeneralBtn");

	// Mouse click controls
	if (backToMenuButton) {
		startGame = false;
	}
}