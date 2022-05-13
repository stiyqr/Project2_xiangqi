#include "GameManager.h"
#include "ChessGeneral.h"

GameManager::GameManager() {
	on_board.emplace_back(ChessGeneral("redGeneralBtn"));
	on_board.emplace_back(ChessGeneral("blackGeneralBtn"));
}

void GameManager::createGameBoard(bool& appRunning, bool& startGame) {
	ImVec2 screenSize = viewer.createWindow(appRunning, viewer.backgroundGame);

	// Control buttons
	viewer.setButtonPos(800, 370);
	Viewer::Button backToMenuButton("backToMenuBtn", viewer.buttonBackToMenuImg, viewer.buttonBackToMenuHoverImg, Viewer::Button::Type::MAINMENU);

	// Chess pieces
	for (int i = 0; i < on_board.size(); i++) {
		viewer.setButtonPos(board.xPosition[on_board[i].curPosX], board.yPosition[on_board[i].curPosY]);
		Viewer::Button thisBtn(on_board[i].id, *(on_board[i].img), *(on_board[i].img), Viewer::Button::Type::CIRCLE);

		if (thisBtn) {
			startGame = false;
		}
	}

	// Mouse click controls
	if (backToMenuButton) {
		startGame = false;
	}
}

void GameManager::displayGameBoard(bool& appRunning, bool& startGame) {
	ImVec2 screenSize = viewer.createWindow(appRunning, viewer.backgroundGame);

	viewer.setButtonPos(800, 370);
	Viewer::Button backToMenuButton("backToMenuBtn", viewer.buttonBackToMenuImg, viewer.buttonBackToMenuHoverImg, Viewer::Button::Type::MAINMENU);

	// Chess pieces
	for (int i = 0; i < on_board.size(); i++) {
		viewer.setButtonPos(board.xPosition[on_board[i].curPosX], board.yPosition[on_board[i].curPosY]);
		on_board[i];
	}

	// Mouse click controls
	if (backToMenuButton) {
		startGame = false;
	}
}