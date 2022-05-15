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

		gmDummy = new GameManager;

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
			

			for (int i = 0; i < gmDummy->on_board.size(); i++) {
				Viewer::ID id(i);
				viewer.setButtonPos(gmDummy->board.xPosition[gmDummy->on_board[i]->curPos.x], gmDummy->board.yPosition[gmDummy->on_board[i]->curPos.y]);
				Viewer::Button thisBtn(gmDummy->on_board[i]->id, *(gmDummy->on_board[i]->img), *(gmDummy->on_board[i]->img), Viewer::Button::Type::CIRCLE);
			}

			auto& io = ImGui::GetIO();
			static auto curDuration = 0.f;
			curDuration += io.DeltaTime;
			if (curDuration >= 3) {

				for (int i = 0; i < gmDummy->on_board.size(); i++) {
					if (gmDummy->on_board[i]->side == reader[0].playerSide && gmDummy->on_board[i]->curPos == reader[0].startPos) {
						gmDummy->on_board[i]->curPos = reader[0].endPos;
					}
				}

				reader.pop_front();

				curDuration = 0;
			}
		}
		else {
			isReading = false;
			delete gmDummy;
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

void MenuManager::readFile2(bool& appRunning) {
	auto screenSize = viewer.createWindow(appRunning, viewer.backgroundGame);
	{
		auto windowPos = viewer.getCursorPos();

		viewer.setButtonPos(800, 370);
		Viewer::Button exitReaderButton("exitReaderBtn", viewer.buttonExitBoardImg, viewer.buttonExitBoardHoverImg, Viewer::Button::Type::MAINMENU);

		if (exitReaderButton) {
			reader.clear();
			delete gmDummy;
			isReading = false;
		}

		static Chess* mover = nullptr;

		for (int i = 0; i < gmDummy->on_board.size(); i++) {
			Viewer::ID id(i);
			viewer.setButtonPos(gmDummy->board.xPosition[gmDummy->on_board[i]->curPos.x], gmDummy->board.yPosition[gmDummy->on_board[i]->curPos.y]);
			Viewer::Button thisBtn(gmDummy->on_board[i]->id, *(gmDummy->on_board[i]->img), *(gmDummy->on_board[i]->img), Viewer::Button::Type::CIRCLE);

			if (!reader.empty() && gmDummy->on_board[i]->curPos == reader[0].startPos) {
				gmDummy->on_board[i]->updateAllPossibleMove(gmDummy->on_board);
				mover = gmDummy->on_board[i];
			}
		}

		if (!reader.empty()) {
			static bool inCheckWarning = false, inCheckmateWarning = false, inStalemateWarning = false;

			auto& io = ImGui::GetIO();
			static auto curDuration = 0.f;
			if (!inCheckWarning && !inCheckmateWarning && !inStalemateWarning) curDuration += io.DeltaTime;
			if (curDuration >= 2.5) {

				if (mover != nullptr) {
					bool isEnemy = false;
					int enemyIndex = 0;
					for (int j = 0; j < gmDummy->on_board.size(); j++) {
						if (reader[0].endPos == gmDummy->on_board[j]->curPos) {
							// next move overlaps with enemy
							if (gmDummy->on_board[j]->side != mover->side) {
								isEnemy = true;
								enemyIndex = j;
								break;
							}
						}
					}

					if (isEnemy) {
						gmDummy->on_board.erase(gmDummy->on_board.begin() + enemyIndex);
					}


					mover->curPos.x = reader[0].endPos.x;
					mover->curPos.y = reader[0].endPos.y;



					// check if there is a check or checkmate
					if (gmDummy->isCheck(gmDummy->current_player, gmDummy->on_board)) {
						// check mate
						if (gmDummy->isCheckmate(gmDummy->current_player, gmDummy->on_board)) {
							inCheckmateWarning = true;
						}
						// check only
						else {
							inCheckWarning = true;
						}
					}
					else {
						inCheckWarning = false;
					}

					// check for stalemate
					if (!inCheckWarning && !inCheckmateWarning) {
						if (gmDummy->isStalemate(gmDummy->current_player, gmDummy->on_board)) {
							inStalemateWarning = true;
						}
					}

					if (gmDummy->current_player == Chess::Side::RED) gmDummy->current_player = Chess::Side::BLACK;
					else gmDummy->current_player = Chess::Side::RED;



					mover = nullptr;
					reader.pop_front();
				}

				curDuration = 0;
			}


			if (inCheckWarning) {
				viewer.setButtonPos(windowPos.x, windowPos.y);
				viewer.makeExtraWindow();
				viewer.addWindowImage(viewer.backgroundCheck);
				viewer.endExtraWindow();

				auto& io = ImGui::GetIO();
				static auto curDurationCheck = 0.f;
				curDurationCheck += io.DeltaTime;
				if (curDurationCheck >= 2.5) {
					inCheckWarning = false;
					curDurationCheck = 0;
				}
			}

			if (inCheckmateWarning) {
				viewer.setButtonPos(windowPos.x, windowPos.y);
				viewer.makeExtraWindow();

				viewer.addWindowImage(viewer.backgroundCheckmate);
				viewer.endExtraWindow();

				auto& io = ImGui::GetIO();
				static auto curDurationCheckmate = 0.f;
				curDurationCheckmate += io.DeltaTime;
				if (curDurationCheckmate >= 2.5) {
					inCheckmateWarning = false;
					gmDummy->inCheckmate = true;
					curDurationCheckmate = 0;
				}
			}

			if (inStalemateWarning) {
				viewer.setButtonPos(windowPos.x, windowPos.y);
				viewer.makeExtraWindow();

				viewer.addWindowImage(viewer.backgroundStalemate);
				viewer.endExtraWindow();

				auto& io = ImGui::GetIO();
				static auto curDurationStalemate = 0.f;
				curDurationStalemate += io.DeltaTime;
				if (curDurationStalemate >= 2.5) {
					inStalemateWarning = false;
					gmDummy->inStalemate = true;
					curDurationStalemate = 0;
				}
			}
		}
		else {
			auto& io = ImGui::GetIO();
			static auto curDuration = 0.f;
			curDuration += io.DeltaTime;
			if (curDuration >= 2.5) {

				isReading = false;
				delete gmDummy;

				curDuration = 0;
			}
		}
	}
	viewer.endWindow();
}