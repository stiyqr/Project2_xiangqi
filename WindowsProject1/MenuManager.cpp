#include "MenuManager.h"

MenuManager::MenuManager() {}

// Functions
void MenuManager::createTextures () {

	viewer.textures["background"].create ( "../../assets\\mainmenu.png" );
	viewer.textures["startGameBtn"].create ( "../../assets\\button startgame.png" );
	viewer.textures["exitGameBtn"].create ( "../../assets\\button exitgame.png" );
	viewer.textures["readFileBtn"].create ( "../../assets\\button readfile.png" );
	viewer.textures["startGameBtnHvr"].create ( "../../assets\\button startgame hover.png" );
	viewer.textures["exitGameBtnHvr"].create ( "../../assets\\button exitgame hover.png" );
	viewer.textures["readFileBtnHvr"].create ( "../../assets\\button readfile hover.png" );
}

void MenuManager::createMainMenu(bool& appRunning, bool& startGame) {

	ImVec2 screenSize = viewer.createWindow(appRunning, viewer.textures["background"]);
	float middle_x = (screenSize.x / 2) - 100;
	float middle_y = (screenSize.y / 2) + 90;

	// make Start Game button
	viewer.setButtonPos(middle_x, middle_y + 50);
	Viewer::Button startGameBtn("startGameBtn", viewer.textures["startGameBtn"], viewer.textures["startGameBtnHvr"], Viewer::Button::Type::MAINMENU);

	// make Exit Game button
	viewer.setButtonPos(middle_x + 300, middle_y + 50);
	Viewer::Button exitGameBtn("exitGameBtn", viewer.textures["exitGameBtn"], viewer.textures["exitGameBtnHvr"], Viewer::Button::Type::MAINMENU);

	// make Read File button
	viewer.setButtonPos(middle_x - 300, middle_y + 50);
	Viewer::Button readFileBtn("readFileBtn", viewer.textures["readFileBtn"], viewer.textures["readFileBtnHvr"], Viewer::Button::Type::MAINMENU);

	if ( startGameBtn ) {
		startGame = true;
	}
	else if ( exitGameBtn ) {
		appRunning = false;
	}
	else if ( readFileBtn ) {

	}
}