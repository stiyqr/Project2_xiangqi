#include "MenuManager.h"
#include "GameManager.h"
#include "json.h"
#include <deque>
#include <fstream>

MenuManager::MenuManager() {}

// Functions
void MenuManager::createMainMenu(bool& appRunning, bool& startGame) {
	static bool loadingGame = false;

	// create main menu window
	ImVec2 screenSize = viewer.createWindow(appRunning, viewer.backgroundMenu);
	auto windowPos = viewer.getCursorPos();
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

	// make Load Game button
	viewer.setButtonPos(middle_x + 150, middle_y - 50);
	Viewer::Button loadGameButton("loadFileBtn", viewer.buttonLoadGameImg, viewer.buttonLoadGameHoverImg, Viewer::Button::Type::MAINMENU);

	// make Log Replay button
	viewer.setButtonPos(middle_x - 150, middle_y - 50);
	Viewer::Button logReplayButton("logReplayBtn", viewer.buttonLogReplayImg, viewer.buttonLogReplayHoverImg, Viewer::Button::Type::MAINMENU);

	// Button click controls
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
	else if (loadGameButton) {
		loadingGame = true;
		isLoading = true;
	}
	else if (logReplayButton) {
		std::ifstream file("logFile.txt");

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

		if (reader.empty()) return;

		gmDummy = new GameManager;

		isReading = true;
	}

	//if (loadingGame) {
	//	viewer.setButtonPos(windowPos.x, windowPos.y);
	//	loadGameMenu(loadingGame);
	//}
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

void MenuManager::readFile(bool& appRunning) {
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

			// get the moving piece
			if (!reader.empty() && gmDummy->on_board[i]->curPos == reader[0].startPos) {
				mover = gmDummy->on_board[i];
			}
		}

		if (!reader.empty()) {
			static bool inCheckWarning = false, inCheckmateWarning = false, inStalemateWarning = false;

			////////////////////////////////////////// Check/Checkmate/Stalemate Warning //////////////////////////////////////////
			// display check warning for 1.25 seconds
			if (inCheckWarning) {
				viewer.setButtonPos(windowPos.x, windowPos.y);
				viewer.makeExtraWindow();
				// check warning image
				viewer.addWindowImage(viewer.backgroundCheck);
				viewer.endExtraWindow();

				auto& io = ImGui::GetIO();
				static auto curDurationCheck = 0.f;
				curDurationCheck += io.DeltaTime;
				if (curDurationCheck >= 1.25) {
					// reset state after 1.25 seconds
					inCheckWarning = false;
					curDurationCheck = 0;
				}
			}
			
			// display checkmate warning for 1.25 seconds
			if (inCheckmateWarning) {
				viewer.setButtonPos(windowPos.x, windowPos.y);
				viewer.makeExtraWindow();
				// checkmate warning image
				viewer.addWindowImage(viewer.backgroundCheckmate);
				viewer.endExtraWindow();

				auto& io = ImGui::GetIO();
				static auto curDurationCheckmate = 0.f;
				curDurationCheckmate += io.DeltaTime;
				if (curDurationCheckmate >= 1.25) {
					// reset state after 1.25 seconds
					inCheckmateWarning = false;
					gmDummy->inCheckmate = true;
					curDurationCheckmate = 0;
				}
			}

			// display stalemate warning for 1.25 seconds
			if (inStalemateWarning) {
				viewer.setButtonPos(windowPos.x, windowPos.y);
				viewer.makeExtraWindow();
				// stalemate warning image
				viewer.addWindowImage(viewer.backgroundStalemate);
				viewer.endExtraWindow();

				auto& io = ImGui::GetIO();
				static auto curDurationStalemate = 0.f;
				curDurationStalemate += io.DeltaTime;
				if (curDurationStalemate >= 1.25) {
					// reset state after 1.25 seconds
					inStalemateWarning = false;
					gmDummy->inStalemate = true;
					curDurationStalemate = 0;
				}
			}

			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			// render next move every 2.5 seconds
			auto& io = ImGui::GetIO();
			static auto curDuration = 0.f;
			curDuration += io.DeltaTime;
			if (curDuration >= 2.5) {

				// if a piece is selected, render next movement
				if (mover != nullptr) {
					bool isEnemy = false;
					int enemyIndex = 0;
					// check if next move overlaps with other chess piece (to be eaten)
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

					// if next move overlaps with enemy, eat (erase) enemy
					if (isEnemy) {
						gmDummy->on_board.erase(gmDummy->on_board.begin() + enemyIndex);
					}

					// move piece to end position
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
					// no check or checkmate
					else {
						inCheckWarning = false;
					}

					// check for stalemate
					if (!inCheckWarning && !inCheckmateWarning) {
						if (gmDummy->isStalemate(gmDummy->current_player, gmDummy->on_board)) {
							inStalemateWarning = true;
						}
					}

					// change player side
					if (gmDummy->current_player == Chess::Side::RED) gmDummy->current_player = Chess::Side::BLACK;
					else gmDummy->current_player = Chess::Side::RED;

					// deselect chess piece, pop reader deque
					mover = nullptr;
					reader.pop_front();
				}

				// reset duration
				curDuration = 0;
			}


			
		}
		else {
			// render last move after 2.5 seconds
			auto& io = ImGui::GetIO();
			static auto curDuration = 0.f;
			curDuration += io.DeltaTime;
			if (curDuration >= 2.5) {

				// reset reading state
				isReading = false;
				delete gmDummy;

				// reset duration
				curDuration = 0;
			}
		}
	}
	viewer.endWindow();
}

GameManager* MenuManager::loadGameMenu(bool& appRunning, bool& startGame) {
	GameManager* gameManager = nullptr;

	viewer.createWindow(appRunning, viewer.backgroundLoadGame);
	{
		viewer.setButtonPos(170, 250);
		Viewer::Button loadSlot1("loadSlot1", viewer.buttonSave1Img, viewer.buttonSave1HoverImg, Viewer::Button::Type::SAVESLOT);
		viewer.setButtonPos(450, 250);
		Viewer::Button loadSlot2("loadSlot2", viewer.buttonSave2Img, viewer.buttonSave2HoverImg, Viewer::Button::Type::SAVESLOT);
		viewer.setButtonPos(750, 250);
		Viewer::Button loadSlot3("loadSlot3", viewer.buttonSave3Img, viewer.buttonSave3HoverImg, Viewer::Button::Type::SAVESLOT);
		viewer.setButtonPos(450, 450);
		Viewer::Button exitSaveMenuButton("exitSaveMenuBtn", viewer.buttonExitBoardImg, viewer.buttonExitBoardHoverImg, Viewer::Button::Type::MAINMENU);

		if (loadSlot1) {
			std::ifstream file("savefile1.txt");
			if (file.is_open()) {
				gameManager = new GameManager("savefile1.txt");
				isLoading = false;
				startGame = true;
			}
		}
		else if (loadSlot2) {
			std::ifstream file("savefile2.txt");
			if (file.is_open()) {
				gameManager = new GameManager("savefile2.txt");
				isLoading = false;
				startGame = true;
			}
		}
		else if (loadSlot3) {
			std::ifstream file("savefile3.txt");
			if (file.is_open()) {
				gameManager = new GameManager("savefile3.txt");
				isLoading = false;
				startGame = true;
			}
		}
		else if (exitSaveMenuButton) {
			isLoading = false;
		}

	}
	//viewer.endExtraWindow();
	viewer.endWindow();

	return gameManager;
}

void MenuManager::loadGame(std::string filename) {
	std::ifstream file{ filename };

	if (file.good()) {

		nlohmann::json js = nlohmann::json::parse(file, nullptr, false, true);

		if (!js.is_discarded()) {

		}
	}
}


MenuManager::Reader::Reader(int playerNum, int x1, int y1, int x2, int y2) {
	if (playerNum == 1) playerSide = Chess::Side::RED;
	else playerSide = Chess::Side::BLACK;

	startPos.x = x1;
	startPos.y = y1;
	endPos.x = x2;
	endPos.y = y2;
}