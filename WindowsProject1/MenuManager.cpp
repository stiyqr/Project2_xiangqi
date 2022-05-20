#include "MenuManager.h"
#include "GameManager.h"
#include "json.h"
#include <deque>
#include <fstream>

///////////////////////////////////////////////////// Menu Manager /////////////////////////////////////////////////////

/////////////// Constructor ///////////////
MenuManager::MenuManager() {
	gmDummy = nullptr;
}

/////////////// Functions ///////////////
// Intent: create the main menu window
// Pre: pass the bools that signify the app is running and the gameplay has not started (still in menu)
// Post: main menu window created
void MenuManager::createMainMenu(bool& appRunning, bool& startGame) {
	// Create main menu window
	ImVec2 screenSize = viewer.createWindow(appRunning, viewer.backgroundMenu);
	auto windowPos = viewer.getCursorPos();
	float middle_x = (screenSize.x / 2) - 100;
	float middle_y = (screenSize.y / 2) + 90;

	// Make Start Game button
	viewer.setButtonPos(middle_x, middle_y + 50);
	Viewer::Button startGameButton("startGameBtn", viewer.buttonStartGameImg, viewer.buttonStartGameHoverImg, Viewer::Button::Type::MAINMENU);

	// Make Exit Game button
	viewer.setButtonPos(middle_x + 300, middle_y + 50);
	Viewer::Button exitGameButton("exitGameBtn", viewer.buttonExitGameImg, viewer.buttonExitGameHoverImg, Viewer::Button::Type::MAINMENU);

	// Make Read File button
	viewer.setButtonPos(middle_x - 300, middle_y + 50);
	Viewer::Button readFileButton("readFileBtn", viewer.buttonReadFileImg, viewer.buttonReadFileHoverImg, Viewer::Button::Type::MAINMENU);

	// Make Load Game button
	viewer.setButtonPos(middle_x + 150, middle_y + 105);
	Viewer::Button loadGameButton("loadFileBtn", viewer.buttonLoadGameImg, viewer.buttonLoadGameHoverImg, Viewer::Button::Type::MAINMENU);

	// Make Log Replay button
	viewer.setButtonPos(middle_x - 150, middle_y + 105);
	Viewer::Button logReplayButton("logReplayBtn", viewer.buttonLogReplayImg, viewer.buttonLogReplayHoverImg, Viewer::Button::Type::MAINMENU);

	// Button click controls
	if (startGameButton) {
		startGame = true;
	}
	else if (exitGameButton) {
		appRunning = false;
	}
	else if (readFileButton) {
		// Get file path
		auto path = openfilename();

		// Open file
		std::ifstream file(path);

		if (!file.good())
			return;

		// Copy file contents to the reader vector
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

		// Create a game manager to play file
		gmDummy = new GameManager;
		isReading = true;
	}
	else if (loadGameButton) {
		isLoading = true;
	}
	else if (logReplayButton) {
		// Open log file
		std::ifstream file("logFile.txt");

		if (!file.good())
			return;

		// Copy log file content to reader vector
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

		// No log
		if (reader.empty()) return;

		// Create a game manager to play file
		gmDummy = new GameManager;
		isReading = true;
	}
}

// Intent: read file from Reader
// Pre: Reader has content, also pass bool that signifies the app is running
// Post: file content from Reader is played
void MenuManager::readFile(bool& appRunning) {
	auto screenSize = viewer.createWindow(appRunning, viewer.backgroundGame);
	{
		auto windowPos = viewer.getCursorPos();
		static Chess* mover = nullptr;

		// Display timer
		auto& io = viewer.getData();
		gmDummy->timer += io.DeltaTime;
		int seconds = (int)gmDummy->timer % 60;
		int minutes = gmDummy->timer / 60;
		viewer.setButtonPos(805, gmDummy->board.yPosition[4] + 91);
		viewer.addText("%02d  %02d", minutes, seconds);

		// Control buttons
		viewer.setButtonPos(750, gmDummy->board.yPosition[3] + 50);
		Viewer::Button exitReaderButton("exitReaderBtn", viewer.buttonExitBoardImg, viewer.buttonExitBoardHoverImg, Viewer::Button::Type::GAMEPLAY);
		viewer.setButtonPos(750, gmDummy->board.yPosition[4] + 80);
		Viewer::Button timer("timer", viewer.timerImg, viewer.timerImg, Viewer::Button::Type::GAMEPLAY);

		// Button click control
		if (exitReaderButton) {
			reader.clear();
			delete gmDummy;
			isReading = false;
		}

		// Render chess piece one by one
		for (int i = 0; i < gmDummy->on_board.size(); i++) {
			ImVec2 piecePosition, startPos(gmDummy->board.xPosition[gmDummy->on_board[i]->animPos.x], gmDummy->board.yPosition[gmDummy->on_board[i]->animPos.y]);
			ImVec2 endPos(gmDummy->board.xPosition[gmDummy->on_board[i]->curPos.x], gmDummy->board.yPosition[gmDummy->on_board[i]->curPos.y]);

			// Add animation progress
			if (gmDummy->on_board[i]->animProg < 1.f) {
				gmDummy->on_board[i]->animProg += (viewer.getData().DeltaTime * 2);
			}
			// Move animation starting position to current position
			else {
				gmDummy->on_board[i]->animPos = gmDummy->on_board[i]->curPos;
			}

			// Interpolate chess piece position
			piecePosition = ImLerp(startPos, endPos, gmDummy->on_board[i]->animProg);

			// Animate the disappearance of dead chess piece
			if (gmDummy->on_board[i]->isDead) {
				gmDummy->on_board[i]->alpha -= (viewer.getData().DeltaTime * 2);
				if (gmDummy->on_board[i]->alpha <= 0.f) {
					gmDummy->on_board.erase(gmDummy->on_board.begin() + i);
					i--;
				}
			}
			
			// Put chess pieces in place
			Viewer::ID id(i);
			viewer.setButtonPos(piecePosition);
			Viewer::Button thisBtn(gmDummy->on_board[i]->id, *(gmDummy->on_board[i]->img), *(gmDummy->on_board[i]->img), Viewer::Button::Type::CIRCLE, gmDummy->on_board[i]->alpha);

			// get the moving piece
			if (!reader.empty() && gmDummy->on_board[i]->curPos == reader[0].startPos) {
				mover = gmDummy->on_board[i];
			}
		}

		// Play file while reader is not empty
		if (!reader.empty()) {
			static bool inCheckWarning = false, inCheckmateWarning = false, inStalemateWarning = false;

			////////////////////////////////////////// Check/Checkmate/Stalemate Warning //////////////////////////////////////////
			// Display "Check" warning for 1.25 seconds
			if (inCheckWarning) {
				viewer.setButtonPos(windowPos.x, windowPos.y);
				viewer.makeExtraWindow();
				// "Check" warning image
				viewer.addWindowImage(viewer.backgroundCheck);
				viewer.endExtraWindow();

				auto& io = viewer.getData();
				static auto curDurationCheck = 0.f;
				curDurationCheck += io.DeltaTime;
				if (curDurationCheck >= 1.25) {
					// Reset state after 1.25 seconds
					inCheckWarning = false;
					curDurationCheck = 0;
				}
			}
			
			// Display "Checkmate" warning for 1.25 seconds
			if (inCheckmateWarning) {
				viewer.setButtonPos(windowPos.x, windowPos.y);
				viewer.makeExtraWindow();
				// "Checkmate" warning image
				viewer.addWindowImage(viewer.backgroundCheckmate);
				viewer.endExtraWindow();

				auto& io = viewer.getData();
				static auto curDurationCheckmate = 0.f;
				curDurationCheckmate += io.DeltaTime;
				if (curDurationCheckmate >= 1.25) {
					// Reset state after 1.25 seconds
					inCheckmateWarning = false;
					gmDummy->inCheckmate = true;
					curDurationCheckmate = 0;
				}
			}

			// Display "Stalemate" warning for 1.25 seconds
			if (inStalemateWarning) {
				viewer.setButtonPos(windowPos.x, windowPos.y);
				viewer.makeExtraWindow();
				// "Stalemate" warning image
				viewer.addWindowImage(viewer.backgroundStalemate);
				viewer.endExtraWindow();

				auto& io = viewer.getData();
				static auto curDurationStalemate = 0.f;
				curDurationStalemate += io.DeltaTime;
				if (curDurationStalemate >= 1.25) {
					// Reset state after 1.25 seconds
					inStalemateWarning = false;
					gmDummy->inStalemate = true;
					curDurationStalemate = 0;
				}
			}

			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			// Render next move every 2.5 seconds
			auto& io = viewer.getData();
			static auto curDuration = 0.f;
			curDuration += io.DeltaTime;
			if (curDuration >= 2.5) {

				// If a piece is selected, render next movement
				if (mover != nullptr) {
					bool isEnemy = false;
					int enemyIndex = 0;
					// Check if next move overlaps with other chess piece (to be eaten)
					for (int j = 0; j < gmDummy->on_board.size(); j++) {
						if (reader[0].endPos == gmDummy->on_board[j]->curPos) {
							// Next move overlaps with enemy
							if (gmDummy->on_board[j]->side != mover->side) {
								isEnemy = true;
								enemyIndex = j;
								break;
							}
						}
					}

					// If next move overlaps with enemy, eat (erase) enemy
					if (isEnemy) {
						gmDummy->on_board[enemyIndex]->isDead = true;
					}

					// Update position for movement animation
					mover->animPos = mover->curPos;
					mover->animProg = 0;

					// Move piece to end position
					mover->curPos.x = reader[0].endPos.x;
					mover->curPos.y = reader[0].endPos.y;

					// Check if there is a "Check" or "Checkmate"
					if (gmDummy->isCheck(gmDummy->current_player, gmDummy->on_board)) {
						// Checkmate
						if (gmDummy->isCheckmate(gmDummy->current_player, gmDummy->on_board)) {
							inCheckmateWarning = true;
						}
						// "Check" only
						else {
							inCheckWarning = true;
						}
					}
					// no "Check" or "Checkmate"
					else {
						inCheckWarning = false;
					}

					// Check for "Stalemate"
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
			// Render the last move after 2.5 seconds
			auto& io = viewer.getData();
			static auto curDuration = 0.f;
			curDuration += io.DeltaTime;
			if (curDuration >= 2.5) {

				// Reset reading state and duration variable
				isReading = false;
				curDuration = 0;
			}
		}
	}
	viewer.endWindow();
}

// Intent: load a saved game from the selected slot
// Pre: pass the variables that indicate the game is running and gameplay hasn't started
// Post: the selected file is accessed and opened
GameManager* MenuManager::loadGameMenu(bool& appRunning, bool& startGame) {
	GameManager* gameManager = nullptr;
	static bool displayWarning = false;

	viewer.createWindow(appRunning, viewer.backgroundLoadGame);
	{
		// Slots and exit buttons
		viewer.setButtonPos(170, 250);
		Viewer::Button loadSlot1("loadSlot1", viewer.buttonSave1Img, viewer.buttonSave1HoverImg, Viewer::Button::Type::SAVESLOT);
		viewer.setButtonPos(455, 250);
		Viewer::Button loadSlot2("loadSlot2", viewer.buttonSave2Img, viewer.buttonSave2HoverImg, Viewer::Button::Type::SAVESLOT);
		viewer.setButtonPos(750, 250);
		Viewer::Button loadSlot3("loadSlot3", viewer.buttonSave3Img, viewer.buttonSave3HoverImg, Viewer::Button::Type::SAVESLOT);
		viewer.setButtonPos(455, 450);
		Viewer::Button exitSaveMenuButton("exitSaveMenuBtn", viewer.buttonExitBoardImg, viewer.buttonExitBoardHoverImg, Viewer::Button::Type::MAINMENU);

		// Button click control
		if (loadSlot1) {
			// Load saved file from the first slot
			std::ifstream file("savefile1.txt");
			if (file.is_open()) {
				gameManager = new GameManager("savefile1.txt");
				isLoading = false;
				startGame = true;
			}
			// If there is no saved file in the first slot
			else {
				displayWarning = true;
			}
		}
		else if (loadSlot2) {
			// Load saved file from the second slot
			std::ifstream file("savefile2.txt");
			if (file.is_open()) {
				gameManager = new GameManager("savefile2.txt");
				isLoading = false;
				startGame = true;
			}
			// If there is no saved file in the second slot
			else {
				displayWarning = true;
			}
		}
		else if (loadSlot3) {
			// Load saved file from the third slot
			std::ifstream file("savefile3.txt");
			if (file.is_open()) {
				gameManager = new GameManager("savefile3.txt");
				isLoading = false;
				startGame = true;
			}
			// If there is no saved file in the third slot
			else {
				displayWarning = true;
			}
		}
		else if (exitSaveMenuButton) {
			isLoading = false;
		}

		// Display warning if there is no saved file in the selected slot
		if (displayWarning) {
			viewer.setButtonPos(0, 0);
			viewer.makeExtraWindow();
			viewer.setButtonPos(471, 380);
			viewer.addText("No saved file in this slot");
			viewer.endExtraWindow();

			// Display warning for 1 second
			auto& io = viewer.getData();
			static auto curDuration = 0.f;
			curDuration += io.DeltaTime;
			if (curDuration >= 1) {
				displayWarning = false;
				curDuration = 0;
			}
		}

	}
	viewer.endWindow();

	return gameManager;
}


///////////////////////////////////////////////////// Struct Reader /////////////////////////////////////////////////////

/////////////// Constructors ///////////////
MenuManager::Reader::Reader(int playerNum, int x1, int y1, int x2, int y2) {
	if (playerNum == 1) playerSide = Chess::Side::RED;
	else playerSide = Chess::Side::BLACK;

	startPos.x = x1;
	startPos.y = y1;
	endPos.x = x2;
	endPos.y = y2;
}