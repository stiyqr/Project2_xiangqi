#include "GameManager.h"
#include "ChessPieces.h"
#include "json.h"
#include <vector>
#include <fstream>

// Initialize static variable
std::ofstream GameManager::logFile;

/////////////// Constructors ///////////////
// Default Constructor
GameManager::GameManager() {
	// Black chess pieces
	on_board.emplace_back(new ChessGeneral("blackGeneralBtn"));
	on_board.emplace_back(new ChessAdvisor("blackAdvisorBtn", 3, 0));
	on_board.emplace_back(new ChessAdvisor("blackAdvisorBtn", 5, 0));
	on_board.emplace_back(new ChessElephant("blackElephantBtn", 2, 0));
	on_board.emplace_back(new ChessElephant("blackElephantBtn", 6, 0));
	on_board.emplace_back(new ChessHorse("blackHorseBtn", 1, 0));
	on_board.emplace_back(new ChessHorse("blackHorseBtn", 7, 0));
	on_board.emplace_back(new ChessChariot("blackChariotBtn", 0, 0));
	on_board.emplace_back(new ChessChariot("blackChariotBtn", 8, 0));

	on_board.emplace_back(new ChessCannon("blackCannonBtn", 1, 2));
	on_board.emplace_back(new ChessCannon("blackCannonBtn", 7, 2));

	on_board.emplace_back(new ChessSoldier("blackSoldierBtn", 0, 3));
	on_board.emplace_back(new ChessSoldier("blackSoldierBtn", 2, 3));
	on_board.emplace_back(new ChessSoldier("blackSoldierBtn", 4, 3));
	on_board.emplace_back(new ChessSoldier("blackSoldierBtn", 6, 3));
	on_board.emplace_back(new ChessSoldier("blackSoldierBtn", 8, 3));

	// Red chess pieces
	on_board.emplace_back(new ChessGeneral("redGeneralBtn"));
	on_board.emplace_back(new ChessAdvisor("redAdvisorBtn", 3, 9));
	on_board.emplace_back(new ChessAdvisor("redAdvisorBtn", 5, 9));
	on_board.emplace_back(new ChessElephant("redElephantBtn", 2, 9));
	on_board.emplace_back(new ChessElephant("redElephantBtn", 6, 9));
	on_board.emplace_back(new ChessHorse("redHorseBtn", 1, 9));
	on_board.emplace_back(new ChessHorse("redHorseBtn", 7, 9));
	on_board.emplace_back(new ChessChariot("redChariotBtn", 0, 9));
	on_board.emplace_back(new ChessChariot("redChariotBtn", 8, 9));

	on_board.emplace_back(new ChessCannon("redCannonBtn", 1, 7));
	on_board.emplace_back(new ChessCannon("redCannonBtn", 7, 7));

	on_board.emplace_back(new ChessSoldier("redSoldierBtn", 0, 6));
	on_board.emplace_back(new ChessSoldier("redSoldierBtn", 2, 6));
	on_board.emplace_back(new ChessSoldier("redSoldierBtn", 4, 6));
	on_board.emplace_back(new ChessSoldier("redSoldierBtn", 6, 6));
	on_board.emplace_back(new ChessSoldier("redSoldierBtn", 8, 6));
}

// Constructor when loading game
GameManager::GameManager(std::string filename) {

	// Open the saved file
	std::ifstream file{ filename };

	if (file.good()) {
		nlohmann::json js = nlohmann::json::parse(file, nullptr, false, true);

		// Get the current playing player
		js["player"]["current_player"].get_to(current_player);

		// Get all available chess pieces' position, side, and rank
		for (int i = 0; i < 32; i++) {
			Chess::Side side;
			Chess::Rank rank;
			int x, y;

			if (!js.contains("chess_piece_" + std::to_string(i))) break;

			js["chess_piece_" + std::to_string(i)]["side"].get_to(side);
			js["chess_piece_" + std::to_string(i)]["rank"].get_to(rank);
			js["chess_piece_" + std::to_string(i)]["pos_x"].get_to(x);
			js["chess_piece_" + std::to_string(i)]["pos_y"].get_to(y);

#pragma region Create_Chess_Piece
			// Create chess piece according to the loaded information
			switch (rank) {

			case Chess::Rank::GENERAL:
					if (side == Chess::Side::RED) {
						on_board.emplace_back(new ChessGeneral("redGeneralBtn", x, y));
					}
					else if (side == Chess::Side::BLACK) {
						on_board.emplace_back(new ChessGeneral("blackGeneralBtn", x, y));
					}
					break;

			case Chess::Rank::ADVISOR:
					if (side == Chess::Side::RED) {
						on_board.emplace_back(new ChessAdvisor("redAdvisorBtn", x, y));
					}
					else if (side == Chess::Side::BLACK) {
						on_board.emplace_back(new ChessAdvisor("blackAdvisorBtn", x, y));
					}
					break;

			case Chess::Rank::CANNON:
					if (side == Chess::Side::RED) {
						on_board.emplace_back(new ChessCannon("redCannonBtn", x, y));
					}
					else if (side == Chess::Side::BLACK) {
						on_board.emplace_back(new ChessCannon("blackCannonBtn", x, y));
					}
					break;

			case Chess::Rank::CHARIOT:
					if (side == Chess::Side::RED) {
						on_board.emplace_back(new ChessChariot("redChariotBtn", x, y));
					}
					else if (side == Chess::Side::BLACK) {
						on_board.emplace_back(new ChessChariot("blackChariotBtn", x, y));
					}
					break;

			case Chess::Rank::ELEPHANT:
					if (side == Chess::Side::RED) {
						on_board.emplace_back(new ChessElephant("redElephantBtn", x, y));
					}
					else if (side == Chess::Side::BLACK) {
						on_board.emplace_back(new ChessElephant("blackElephantBtn", x, y));
					}
					break;

			case Chess::Rank::HORSE:
					if (side == Chess::Side::RED) {
						on_board.emplace_back(new ChessHorse("redHorseBtn", x, y));
					}
					else if (side == Chess::Side::BLACK) {
						on_board.emplace_back(new ChessHorse("blackHorseBtn", x, y));
					}
					break;

			case Chess::Rank::SOLDIER:
					if (side == Chess::Side::RED) {
						on_board.emplace_back(new ChessSoldier("redSoldierBtn", x, y));
					}
					else if (side == Chess::Side::BLACK) {
						on_board.emplace_back(new ChessSoldier("blackSoldierBtn", x, y));
					}
					break;
			}
#pragma endregion
		}
	}
}

/////////////// Functions ///////////////
// Intent: create gameplay board and background
// Pre: pass bools that signify the game is running and is in gameplay
// Post: gameplay window created
void GameManager::createGameBoard(bool& appRunning, bool& startGame) {
	static bool inCheckWarning = false, inCheckmateWarning = false, inStalemateWarning = false, timeoutWarning = false, savingGame = false;
	static Chess* mover = nullptr;

	// Create window with board and get window size
	ImVec2 screenSize = viewer.createWindow(appRunning, viewer.backgroundGame);
	auto windowPos = viewer.getCursorPos();
	float middle_x = (screenSize.x / 2) - 100;
	float middle_y = (screenSize.y / 2) + 140;


	// Control buttons
	viewer.setButtonPos(750, board.yPosition[1] + 10);
	Viewer::Button saveGameButton("saveGameBtn", viewer.buttonSaveGameImg, viewer.buttonSaveGameHoverImg, Viewer::Button::Type::GAMEPLAY);
	viewer.setButtonPos(750, board.yPosition[2] + 30);
	Viewer::Button surrenderButton("surrenderBtn", viewer.buttonSurrenderImg, viewer.buttonSurrenderHoverImg, Viewer::Button::Type::GAMEPLAY);
	viewer.setButtonPos(750, board.yPosition[3] + 50);
	Viewer::Button exitBoardButton("exitBoardBtn", viewer.buttonExitBoardImg, viewer.buttonExitBoardHoverImg, Viewer::Button::Type::GAMEPLAY);
	viewer.setButtonPos(750, board.yPosition[4] + 80);
	Viewer::Button timerBtn("timerBtn", viewer.timerImg, viewer.timerImg, Viewer::Button::Type::GAMEPLAY);

	// Button click controls
	if (saveGameButton) {
		savingGame = true;
	}
	else if (surrenderButton) {
		inCheckmate = true;
		logFile.close();
	}
	else if (exitBoardButton) {
		startGame = false;
		logFile.close();
	}

	// Save game
	if (savingGame) {
		viewer.setButtonPos(windowPos.x, windowPos.y);
		saveGameMenu(savingGame);
	}

	// Current player badge
	viewer.setButtonPos(920, board.yPosition[1] + 40);
	if (current_player == Chess::Side::RED) {
		Viewer::Button countdownRedButton("countdownRedBtn", viewer.countdownRedImg, viewer.countdownRedImg, Viewer::Button::Type::COUNTDOWN);
	}
	else {
		Viewer::Button countdownBlackButton("countdownBlackBtn", viewer.countdownBlackImg, viewer.countdownBlackImg, Viewer::Button::Type::COUNTDOWN);
	}

#pragma region Timers
	// Display timer
	auto& io = viewer.getData();
	timer += io.DeltaTime;
	int seconds = (int)timer % 60;
	int minutes = timer / 60;
	viewer.setButtonPos(805, board.yPosition[6] + 1);
	viewer.addText("%02d  %02d", minutes, seconds);

	// Display countdown timer
	if (!isTimeout) countdown -= io.DeltaTime;
	viewer.setTextSize(0.8);
	viewer.setButtonPos(953, board.yPosition[3] + 20);
	viewer.addColoredText(ImColor{ 135, 25, 26, 255 }, "%05.2f", countdown);
	viewer.setTextSize(1);

	// If countdown reaches 0, player loses
	if (countdown < 0.f) {
		timeoutWarning = true;
		countdown = 1.f;
	}
#pragma endregion


	// Render chess piece one by one
	for (int i = 0; i < on_board.size(); i++) {
		ImVec2 piecePosition, startPos(board.xPosition[on_board[i]->animPos.x], board.yPosition[on_board[i]->animPos.y]);
		ImVec2 endPos(board.xPosition[on_board[i]->curPos.x], board.yPosition[on_board[i]->curPos.y]);

		// Add animation progress
		if (on_board[i]->animProg < 1.f) {
			on_board[i]->animProg += (viewer.getData().DeltaTime * 2);
		}
		// Move animation starting position to current position
		else {
			on_board[i]->animPos = on_board[i]->curPos;
		}

		// Interpolate chess piece position
		piecePosition = ImLerp(startPos, endPos, on_board[i]->animProg);

		// Animate the disappearance of dead chess piece
		if (on_board[i]->isDead) {
			on_board[i]->alpha -= (viewer.getData().DeltaTime * 2);
			if (on_board[i]->alpha <= 0.f) {
				on_board.erase(on_board.begin() + i);
				i--;
			}
		}

		// Put chess pieces in place
		Viewer::ID id(i);
		viewer.setButtonPos(piecePosition);
		Viewer::Button thisBtn(on_board[i]->id, *(on_board[i]->img), *(on_board[i]->img), Viewer::Button::Type::CIRCLE, on_board[i]->alpha);

		// Player selects a chess piece
		if (thisBtn && on_board[i]->side == current_player) {
			on_board[i]->updateAllPossibleMove(on_board);
			mover = on_board[i];
		}
	}

#pragma region Warning_Backgrounds
	// "Check" (not "Checkmate") warning
	if (inCheckWarning) {
		viewer.setButtonPos(windowPos.x, windowPos.y);
		viewer.makeExtraWindow();
		viewer.addWindowImage(viewer.backgroundCheck);
		viewer.endExtraWindow();

		// Display warning for 2.5 seconds
		auto& io = viewer.getData();
		static auto curDuration = 0.f;
		curDuration += io.DeltaTime;
		if (curDuration >= 2.5) {
			inCheckWarning = false;
			curDuration = 0;
		}
	}

	// Checkmate warning
	if (inCheckmateWarning) {
		viewer.setButtonPos(windowPos.x, windowPos.y);
		viewer.makeExtraWindow();
		viewer.addWindowImage(viewer.backgroundCheckmate);
		viewer.endExtraWindow();

		// Display warning for 2.5 seconds
		auto& io = viewer.getData();
		static auto curDuration = 0.f;
		curDuration += io.DeltaTime;
		if (curDuration >= 2.5) {
			inCheckmateWarning = false;
			inCheckmate = true;
			curDuration = 0;
		}
	}

	// "Stalemate" warning
	if (inStalemateWarning) {
		viewer.setButtonPos(windowPos.x, windowPos.y);
		viewer.makeExtraWindow();
		viewer.addWindowImage(viewer.backgroundStalemate);
		viewer.endExtraWindow();

		// Display warning for 2.5 seconds
		auto& io = viewer.getData();
		static auto curDuration = 0.f;
		curDuration += io.DeltaTime;
		if (curDuration >= 2.5) {
			inStalemateWarning = false;
			inStalemate = true;
			curDuration = 0;
		}
	}

	// "Timeout" warning
	if (timeoutWarning) {
		viewer.setButtonPos(windowPos.x, windowPos.y);
		viewer.makeExtraWindow();
		viewer.addWindowImage(viewer.backgroundTimeout);
		viewer.endExtraWindow();

		// Display warning for 2.5 seconds
		auto& io = viewer.getData();
		static auto curDuration = 0.f;
		curDuration += io.DeltaTime;
		if (curDuration >= 2.5) {
			timeoutWarning = false;
			isTimeout = true;
			curDuration = 0;
		}
	}
#pragma endregion

#pragma region Move_Chess_Piece
	// If player selected a chess piece
	if (mover != nullptr) {
		// Make extra window for possible moves buttons
		viewer.setButtonPos(windowPos.x, windowPos.y);
		viewer.makeExtraWindow();
		{
			// Make possible move buttons
			viewer.setButtonPos(board.xPosition[mover->curPos.x], board.yPosition[mover->curPos.y]);
			Viewer::Button backBtn("back", *(mover->img), *(mover->img), Viewer::Button::Type::CIRCLE);

#pragma region Filter_Moves
			// Check if each move is enemy or friend, or "check" position
			for (int i = 0; i < mover->allPossibleMove.size(); i++) {
				bool mustContinue = false;
				bool isEnemy = false;
				int enemyIndex = 0;

				// Loop through all pieces to check overlapping
				for (int j = 0; j < on_board.size(); j++) {
					if (mover->allPossibleMove[i] == on_board[j]->curPos) {
						// Possible move overlaps with friend
						if (on_board[j]->side == mover->side) {
							mover->allPossibleMove.erase(mover->allPossibleMove.begin() + i);

							if (mover->allPossibleMove.empty()) break;
							i--;
							mustContinue = true;
							break;
						}
						// Possible move overlaps with enemy
						else {
							isEnemy = true;
							enemyIndex = j;
						}
					}
				}
				if (mustContinue) continue;

				// No possible move
				if (mover->allPossibleMove.empty()) continue;

				// Pieces cannot move to positions that put their General in "Check" position
				Chess::Position originalPos = mover->curPos;
				mover->curPos = mover->allPossibleMove[i];

				// Black checks the Red General
				if (mover->side == Chess::Side::RED) {
					if (isCheck(Chess::Side::BLACK, on_board)) {
						bool eatEnemy = false;

						// Loop through all pieces to check if the piece that checks the General can be eaten
						for (int j = 0; j < on_board.size(); j++) {
							if (mover->curPos == on_board[j]->curPos) {
								Chess eaten = *on_board[j];
								eaten.updateAllPossibleMove(on_board);

								// The piece that checks the General can be eaten
								for (int k = 0; k < eaten.allPossibleMove.size(); k++) {
									for (int l = 0; l < on_board.size(); l++) {
										if (eaten.allPossibleMove[k] == on_board[l]->curPos) {
											if (on_board[l]->rank == Chess::Rank::GENERAL && on_board[l]->side == Chess::Side::RED) {
												eatEnemy = true;
												break;
											}
										}
									}
									if (eatEnemy) break;
								}
							}
							if (eatEnemy) break;
						}

						// Reset selected piece's position
						mover->curPos = originalPos;

						// If the piece that checks the General can't be eaten, or the selected piece is the checked General,
						// erase the possible move that keeps the General in "Check" position
						if (!eatEnemy || mover->rank == Chess::Rank::GENERAL) {
							mover->allPossibleMove.erase(mover->allPossibleMove.begin() + i);

							if (mover->allPossibleMove.empty()) break;
							i--;
							continue;
						}
					}
					else {
						// Reset selected piece's position
						mover->curPos = originalPos;
					}
				}
				// Red checks the Black General
				else {
					if (isCheck(Chess::Side::RED, on_board)) {
						bool eatEnemy = false;

						// Loop through all pieces to check if the piece that checks the General can be eaten
						for (int j = 0; j < on_board.size(); j++) {
							if (mover->curPos == on_board[j]->curPos) {
								Chess eaten = *on_board[j];
								eaten.updateAllPossibleMove(on_board);

								// The piece that checks the General can be eaten
								for (int k = 0; k < eaten.allPossibleMove.size(); k++) {
									for (int l = 0; l < on_board.size(); l++) {
										if (eaten.allPossibleMove[k] == on_board[l]->curPos) {
											if (on_board[l]->rank == Chess::Rank::GENERAL && on_board[l]->side == Chess::Side::BLACK) {
												eatEnemy = true;
												break;
											}
										}
									}
									if (eatEnemy) break;
								}
							}
							if (eatEnemy) break;
						}

						// Reset selected piece's position
						mover->curPos = originalPos;

						// Delete the move that keeps the General in "Check" position
						if (!eatEnemy || mover->rank == Chess::Rank::GENERAL) {
							mover->allPossibleMove.erase(mover->allPossibleMove.begin() + i);

							if (mover->allPossibleMove.empty()) break;
							i--;
							continue;
						}
					}
					else {
						// Reset selected piece's position
						mover->curPos = originalPos;
					}
				}

				// Pieces cannot move to positions that make the two generals can see each other
				mover->curPos = mover->allPossibleMove[i];

				if (generalMeet()) {
					mover->allPossibleMove.erase(mover->allPossibleMove.begin() + i);

					// Delete the move that makes the General meet each other
					if (mover->allPossibleMove.empty()) {
						mover->curPos = originalPos;
						break;
					}
					i--;
				}
				mover->curPos = originalPos;
#pragma endregion

				// Render the selected chess piece as a back button (cancel move)
				Viewer::ID id(i);
				viewer.setButtonPos(board.xPosition[mover->allPossibleMove[i].x], board.yPosition[mover->allPossibleMove[i].y]);
				Viewer::Button moveBtn("move", *(mover->moveImg), *(mover->moveImg), Viewer::Button::Type::CIRCLE);

				// Player select a possible move
				if (moveBtn) {
					// Eat a chess piece
					if (isEnemy) {
						on_board[enemyIndex]->isDead = true;
					}

					// Output Log
					if (current_player == Chess::Side::RED) {
						logFile << "1 ";
					}
					else {
						logFile << "2 ";
					}
					logFile << "(" << mover->curPos.x << ", " << mover->curPos.y << ")";
					logFile << "(" << mover->allPossibleMove[i].x << ", " << mover->allPossibleMove[i].y << ")\n";

					// Update position for movement animation
					mover->animPos = mover->curPos;
					mover->animProg = 0;

					// Move the selected chess piece
					mover->curPos.x = mover->allPossibleMove[i].x;
					mover->curPos.y = mover->allPossibleMove[i].y;

					// Reset countdown timer
					countdown = 11.f;

					// Check if there is a Check/Checkmate
					if (isCheck(current_player, on_board)) {
						// Checkmate
						if (isCheckmate(current_player, on_board)) {
							inCheckmateWarning = true;
						}
						// "Check" only
						else {
							inCheckWarning = true;
						}
					}
					else {
						// No Check/Checkmate
						inCheckWarning = false;
					}

					// Check for "Stalemate"
					if (!inCheckWarning && !inCheckmateWarning) {
						if (isStalemate(current_player, on_board)) {
							inStalemateWarning = true;
						}
					}

					// Change player side
					if (current_player == Chess::Side::RED) current_player = Chess::Side::BLACK;
					else current_player = Chess::Side::RED;

					// Refresh pointer
					mover = nullptr;
					break;
				}
				// Player cancel move, refresh pointer
				else if (backBtn) {
					mover = nullptr;
					break;
				}
			}
			// Player cancel move, refresh pointer
			if (backBtn) mover = nullptr;
		}
		viewer.endExtraWindow();
	}
#pragma endregion

	// "Checkmate" / "Stalemate" / "Timeout" = game ends
	if (inCheckmate || inStalemate || isTimeout) {
		viewer.setButtonPos(windowPos.x, windowPos.y);
		viewer.makeExtraWindow();
		{
			// Red wins
			if (current_player == Chess::Side::BLACK) 
				viewer.addWindowImage(viewer.backgroundRedWin);
			// Black wins
			else 
				viewer.addWindowImage(viewer.backgroundBlackWin);
			

			// Play again or exit button
			viewer.setButtonPos(middle_x - 150, middle_y);
			Viewer::Button playAgainButton("playAgainBtn", viewer.buttonPlayAgainImg, viewer.buttonPlayAgainHoverImg, Viewer::Button::Type::MAINMENU);
			viewer.setButtonPos(middle_x + 150, middle_y);
			Viewer::Button backToMenuButton("backToMenuBtn", viewer.buttonBackToMenuImg, viewer.buttonBackToMenuHoverImg, Viewer::Button::Type::MAINMENU);

			// Button click controls
			if (playAgainButton) {
				startNewGame = true;
				startGame = false;
				logFile.close();
			}
			else if (backToMenuButton) {
				startGame = false;
				logFile.close();
			}
		}
		viewer.endExtraWindow();
	}
}

// Intent: check if the opposing General is in "Check" position
// Pre: pass the current player side all chess pieces on board
// Post: return true is opponent is in check, return false otherwise
bool GameManager::isCheck(Chess::Side side, std::vector<Chess*> on_board) {
	// Check if black is in "Check" (red is attacking)
	if (side == Chess::Side::RED) {

		// Check possible move of every red piece
		for (int i = 0; i < on_board.size(); i++) {
			if (on_board[i]->side == Chess::Side::BLACK) continue;

			on_board[i]->updateAllPossibleMove(on_board);

			// Compare each possible move to each piece's position
			for (int j = 0; j < on_board[i]->allPossibleMove.size(); j++) {
				for (int k = 0; k < on_board.size(); k++) {

					// If possible move and a other piece position is the same, check if it's the other side's General
					if (on_board[i]->allPossibleMove[j] == on_board[k]->curPos) {
						if (on_board[k]->rank == Chess::Rank::GENERAL && on_board[k]->side != on_board[i]->side) {
							return true;
						}
					}
				}
			}
		}
		return false;
	}
	// Check if red is in "Check" (black is attacking)
	else if (side == Chess::Side::BLACK) {

		// Check possible move of every black piece
		for (int i = 0; i < on_board.size(); i++) {
			if (on_board[i]->side == Chess::Side::RED) continue;

			on_board[i]->updateAllPossibleMove(on_board);

			// Compare each possible move to each piece's position
			for (int j = 0; j < on_board[i]->allPossibleMove.size(); j++) {
				for (int k = 0; k < on_board.size(); k++) {

					// If possible move and a other piece position is the same, check if it's the other side's General
					if (on_board[i]->allPossibleMove[j] == on_board[k]->curPos) {
						if (on_board[k]->rank == Chess::Rank::GENERAL && on_board[k]->side != on_board[i]->side) {
							return true;
						}
					}
				}
			}
		}
		return false;
	}

	return false;
}

// Intent: check if the opposing General is in "Checkmate" position
// Pre: the opponent is in "Check" position, pass the current player side all chess pieces on board
// Post: return true is opponent is in "Checkmate", return false otherwise
bool GameManager::isCheckmate(Chess::Side side, std::vector<Chess*> on_board) {
	// Black is in "Check" (red is attacking)
	if (side == Chess::Side::RED) {

		// Check every possible move of black pieces
		for (int i = 0; i < on_board.size(); i++) {
			if (on_board[i]->side == Chess::Side::RED) continue;

			// Save original position
			on_board[i]->updateAllPossibleMove(on_board);
			Chess::Position originalPos = on_board[i]->curPos;

			// Move each piece to each possible move and check if black is still in check
			for (int j = 0; j < on_board[i]->allPossibleMove.size(); j++) {

				// Move the piece to each possible move
				on_board[i]->curPos = on_board[i]->allPossibleMove[j];

				// Check if the General is not in "Check" anymore
				if (!isCheck(Chess::Side::RED, on_board)) {
					on_board[i]->curPos = originalPos;
					return false;
				}
			}

			// Move the piece back to its original position
			on_board[i]->curPos = originalPos;
		}
		// The General is still in "Check" even after moving every piece, return true
		return true;
	}
	// Red is in "Check" (black is attacking)
	else if (side == Chess::Side::BLACK) {

		// Check every possible move of red pieces
		for (int i = 0; i < on_board.size(); i++) {
			if (on_board[i]->side == Chess::Side::BLACK) continue;

			// Save original position
			on_board[i]->updateAllPossibleMove(on_board);
			Chess::Position originalPos = on_board[i]->curPos;

			// Move each piece to each possible move and check if red is still in check
			for (int j = 0; j < on_board[i]->allPossibleMove.size(); j++) {

				// Move the piece to each possible move
				on_board[i]->curPos = on_board[i]->allPossibleMove[j];

				// Check if the General is not in "Check" anymore
				if (!isCheck(Chess::Side::BLACK, on_board)) {
					on_board[i]->curPos = originalPos;
					return false;
				}
			}

			// Move the piece back to its original position
			on_board[i]->curPos = originalPos;
		}
		// The General is still in "Check" even after moving every piece, return true
		return true;
	}

	return false;
}

// Intent: check if the opponent is in "Stalemate"
// Pre: pass the current player side all chess pieces on board
// Post: return true is opponent is in "Stalemate" (have no more possible move), return false otherwise
bool GameManager::isStalemate(Chess::Side side, std::vector<Chess*>on_board) {
	// Check if black is in "Stalemate" (red is attacking)
	if (side == Chess::Side::RED) {
		for (int k = 0; k < on_board.size(); k++) {
			if (on_board[k]->side == Chess::Side::RED) continue;

			// Update each piece's possible move
			on_board[k]->updateAllPossibleMove(on_board);

			// Check if each move is enemy or friend, or "Check" position
			for (int i = 0; i < on_board[k]->allPossibleMove.size(); i++) {
				bool mustContinue = false;

				if (on_board[k]->allPossibleMove.empty()) continue;

				// If a possible move overlaps with enemy, erase the possible move
				for (int j = 0; j < on_board.size(); j++) {
					if (on_board[k]->allPossibleMove[i] == on_board[j]->curPos) {
						if (on_board[j]->side == on_board[k]->side) {
							// Erasing move
							on_board[k]->allPossibleMove.erase(on_board[k]->allPossibleMove.begin() + i);

							if (on_board[k]->allPossibleMove.empty()) break;
							i--;
							mustContinue = true;
							break;
						}
					}
				}
				if (mustContinue) continue;

				if (on_board[k]->allPossibleMove.empty()) continue;

				// Pieces cannot move to positions that put their general in "Check" position
				Chess::Position originalPos = on_board[k]->curPos;
				on_board[k]->curPos = on_board[k]->allPossibleMove[i];

				// If a possible move makes the General in "Check" position, erase the possible move
				if (on_board[k]->side == Chess::Side::BLACK) {
					if (isCheck(Chess::Side::RED, on_board)) {

						// Reset position and erase the move that keeps the general in "Check" position
						on_board[k]->curPos = originalPos;
						on_board[k]->allPossibleMove.erase(on_board[k]->allPossibleMove.begin() + i);

						if (on_board[k]->allPossibleMove.empty()) break;
						i--;
						continue;
					}
					else {
						// Return to original position
						on_board[k]->curPos = originalPos;
					}
				}
			}
			// If still have possible move(s), return false (not "Stalemate")
			if (on_board[k]->allPossibleMove.size() > 0) return false;
		}
		return true;
	}
	// Check if red is in "Stalemate" (black is attacking)
	else {
		for (int k = 0; k < on_board.size(); k++) {
			if (on_board[k]->side == Chess::Side::BLACK) continue;

			// Update each piece's possible move
			on_board[k]->updateAllPossibleMove(on_board);

			// Check if each move is enemy or friend, or "Check" position
			for (int i = 0; i < on_board[k]->allPossibleMove.size(); i++) {
				bool mustContinue = false;

				if (on_board[k]->allPossibleMove.empty()) continue;

				// If a possible move overlaps with enemy, erase the possible move
				for (int j = 0; j < on_board.size(); j++) {
					if (on_board[k]->allPossibleMove[i] == on_board[j]->curPos) {
						if (on_board[j]->side == on_board[k]->side) {
							// Erasing move
							on_board[k]->allPossibleMove.erase(on_board[k]->allPossibleMove.begin() + i);

							if (on_board[k]->allPossibleMove.empty()) break;
							i--;
							mustContinue = true;
							break;
						}
					}
				}
				if (mustContinue) continue;

				if (on_board[k]->allPossibleMove.empty()) continue;

				// Pieces cannot move to positions that put their general in "Check" position
				Chess::Position originalPos = on_board[k]->curPos;
				on_board[k]->curPos = on_board[k]->allPossibleMove[i];

				if (on_board[k]->side == Chess::Side::RED) {
					if (isCheck(Chess::Side::BLACK, on_board)) {

						// Reset position and erase the move that keeps the general in "Check" position
						on_board[k]->curPos = originalPos;
						on_board[k]->allPossibleMove.erase(on_board[k]->allPossibleMove.begin() + i);

						if (on_board[k]->allPossibleMove.empty()) break;
						i--;
						continue;
					}
					else {
						// Return to original position
						on_board[k]->curPos = originalPos;
					}
				}
			}
			// If still have possible move(s), return false (not "Stalemate")
			if (on_board[k]->allPossibleMove.size() > 0) return false;
		}
		return true;
	}
}

// Intent: check if the two generals can see each other
// Pre: pass all the chess pieces on board
// Post: returnt true is the generals can see each other, return false otherwise
bool GameManager::generalMeet() {
	int redGeneralIndex = -1, blackGeneralIndex = -1;

	// Find each general's index
	for (int i = 0; i < on_board.size(); i++) {
		if (on_board[i]->rank == Chess::Rank::GENERAL) {
			if (on_board[i]->side == Chess::Side::RED) redGeneralIndex = i;
			else blackGeneralIndex = i;
		}
		if (redGeneralIndex >= 0 && blackGeneralIndex >= 0) break;
	}

	// If red and black general is in the same column
	if (on_board[redGeneralIndex]->curPos.x == on_board[blackGeneralIndex]->curPos.x) {

		// Check if there is other chess piece in the same column
		for (int i = 0; i < on_board.size(); i++) {
			if (on_board[i]->rank != Chess::Rank::GENERAL && on_board[i]->curPos.x == on_board[redGeneralIndex]->curPos.x) 
				return false;
		}
		return true;
	}
	// The red and black general is not in the same column
	else return false;
}

// Intent: menu for saving game
// Pre: player clicks save game button
// Post: player opens this save game menu
void GameManager::saveGameMenu(bool& savingGame) {
	viewer.makeExtraWindow();
	viewer.addWindowImage(viewer.backgroundLoadGame);
	{
		// Save slot buttons
		viewer.setButtonPos(170, 250);
		Viewer::Button saveSlot1("saveSlot1", viewer.buttonSave1Img, viewer.buttonSave1HoverImg, Viewer::Button::Type::SAVESLOT);
		viewer.setButtonPos(450, 250);
		Viewer::Button saveSlot2("saveSlot2", viewer.buttonSave2Img, viewer.buttonSave2HoverImg, Viewer::Button::Type::SAVESLOT);
		viewer.setButtonPos(750, 250);
		Viewer::Button saveSlot3("saveSlot3", viewer.buttonSave3Img, viewer.buttonSave3HoverImg, Viewer::Button::Type::SAVESLOT);
		viewer.setButtonPos(450, 450);
		Viewer::Button exitSaveMenuButton("exitSaveMenuBtn", viewer.buttonExitBoardImg, viewer.buttonExitBoardHoverImg, Viewer::Button::Type::MAINMENU);

		// Button click controls
		if (saveSlot1) {
			saveGame("savefile1.txt");
			savingGame = false;
		}
		else if (saveSlot2) {
			saveGame("savefile2.txt");
			savingGame = false;
		}
		else if (saveSlot3) {
			saveGame("savefile3.txt");
			savingGame = false;
		}
		else if (exitSaveMenuButton) {
			savingGame = false;
		}
	}
	viewer.endExtraWindow();
}

// Intent: save game mechanism
// Pre: pass save file name
// Post: game saved in the passed save file name
void GameManager::saveGame(std::string filename) {
	nlohmann::json js;

	// Save the current playing player's side
	js["player"]["current_player"] = current_player;
	
	// Save all the pieces' rank, side, and position
	for (int i = 0; i < on_board.size(); i++) {
		js["chess_piece_" + std::to_string(i)]["side"] = on_board[i]->side;
		js["chess_piece_" + std::to_string(i)]["rank"] = on_board[i]->rank;
		js["chess_piece_" + std::to_string(i)]["pos_x"] = on_board[i]->curPos.x;
		js["chess_piece_" + std::to_string(i)]["pos_y"] = on_board[i]->curPos.y;
	}

	// Write the save file
	std::ofstream writeFile{ filename };
	if (writeFile.good()) {
		writeFile << std::setw(1) << js;
	}
}