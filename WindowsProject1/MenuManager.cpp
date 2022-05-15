#include "MenuManager.h"
#include "GameManager.h"
#include <deque>
#include <fstream>

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
	Viewer::Button exitGameButton("exitGameBtn", viewer.buttonExitGameImg, viewer.buttonExitGameHoverImg, Viewer::Button::Type::MAINMENU);

	// make Read File button
	viewer.setButtonPos(middle_x - 300, middle_y + 50);
	Viewer::Button readFileButton("readFileBtn", viewer.buttonReadFileImg, viewer.buttonReadFileHoverImg, Viewer::Button::Type::MAINMENU);

	if (startGameButton) {
		startGame = true;
	}
	else if (exitGameButton) {
		appRunning = false;
	}
	else if (readFileButton) {
		auto path = openfilename();

		std::ifstream file(path);

		if (!file.good())
			return;

		char line[99];
		while (file.getline(line, 99)) {
			std::vector<int> data;
			for (auto& i : line) {
				if (i >= '0' && i <= '9')
					data.emplace_back(i - '0');
			}
			reader.emplace_back(data[0], data[1], data[2], data[3], data[4]);
		}

		file.close();

		gameManagerDummy = new GameManager;

		isReading = true;
	}
}

void MenuManager::readFileMenu(bool& appRunning) {
	viewer.createWindow(appRunning, viewer.backgroundGame);
	{
		viewer.setButtonPos(800, 370);
		Viewer::Button exitReaderButton("exitReaderBtn", viewer.buttonExitBoardImg, viewer.buttonExitBoardHoverImg, Viewer::Button::Type::MAINMENU);

		if (exitReaderButton) {
			reader.clear();
		}

		if (!reader.empty()) {
			

			for (int i = 0; i < gameManagerDummy->on_board.size(); i++) {
				Viewer::ID id(i);
				viewer.setButtonPos(gameManagerDummy->board.xPosition[gameManagerDummy->on_board[i]->curPos.x], gameManagerDummy->board.yPosition[gameManagerDummy->on_board[i]->curPos.y]);
				Viewer::Button thisBtn(gameManagerDummy->on_board[i]->id, *(gameManagerDummy->on_board[i]->img), *(gameManagerDummy->on_board[i]->img), Viewer::Button::Type::CIRCLE);
			}

			auto& io = ImGui::GetIO();
			static auto curDuration = 0.f;
			curDuration += io.DeltaTime;
			if (curDuration >= 3) {

				for (int i = 0; i < gameManagerDummy->on_board.size(); i++) {
					if (gameManagerDummy->on_board[i]->side == reader[0].playerSide && gameManagerDummy->on_board[i]->curPos == reader[0].startPos) {
						gameManagerDummy->on_board[i]->curPos = reader[0].endPos;
					}
				}

				reader.pop_front();

				curDuration = 0;
			}
		}
		else {
			isReading = false;
			delete gameManagerDummy;
		}
	}
	viewer.endWindow();
}

MenuManager::Reader::Reader(int playerNum, int x1, int y1, int x2, int y2) {
	if (playerNum == 1) playerSide = Chess::Side::RED;
	else playerSide = Chess::Side::BLACK;

	startPos.x = x1;
	startPos.y = y1;
	endPos.x = x2;
	endPos.y = y2;
}