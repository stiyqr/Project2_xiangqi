#include "MenuManager.h"

MenuManager::MenuManager() {}

// Functions
void MenuManager::createMainMenu(bool& appRunning, bool& startGame) {
	ImVec2 screenSize = viewer.createWindow(appRunning, viewer.backgroundMenu);
	float middle_x = (screenSize.x / 2) - 100;
	float middle_y = (screenSize.y / 2) + 90;

	// make Start Game button
	viewer.setButtonPos(middle_x, middle_y + 50);
	Viewer::Button startGameButton("startGameBtn", viewer.buttonStartGameImg, viewer.buttonStartGameHoverImg, Viewer::Button::Type::MAINMENU);

	// make Exit Game button
	viewer.setButtonPos(middle_x + 300, middle_y + 50);
	Viewer::Button exitGameButton("exitGameBtn", viewer.buttonStartGameImg, viewer.buttonStartGameHoverImg, Viewer::Button::Type::MAINMENU);

	// make Read File button
	viewer.setButtonPos(middle_x - 300, middle_y + 50);
	Viewer::Button readFileButton("readFileBtn", viewer.buttonStartGameImg, viewer.buttonStartGameHoverImg, Viewer::Button::Type::MAINMENU);

	if (startGameButton) {
		startGame = true;
	}
	else if (exitGameButton) {
		appRunning = false;
	}
	else if (readFileButton) {

	}
}

void MenuManager::createGameBoard(bool& appRunning, bool& startGame) {
	ImVec2 screenSize = viewer.createWindow(appRunning, viewer.backgroundGame);

	// chess piece
	viewer.setButtonPos(0, 0);
	//Viewer::Button redGeneral("redGeneralBtn", v)
}