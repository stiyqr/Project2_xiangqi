#include "GameManager.h"
#include "ChessPieces.h"
#include "json.h"
#include <vector>
#include <fstream>

// Initialize static variable
std::ofstream GameManager::logFile;

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

			// create chess piece according to loaded information
			if (rank == Chess::Rank::GENERAL) {
				if (side == Chess::Side::RED) {
					on_board.emplace_back(new ChessGeneral("redGeneralBtn", x, y));
				}
				else if (side == Chess::Side::BLACK) {
					on_board.emplace_back(new ChessGeneral("blackGeneralBtn", x, y));
				}
			}
			else if (rank == Chess::Rank::ADVISOR) {
				if (side == Chess::Side::RED) {
					on_board.emplace_back(new ChessAdvisor("redAdvisorBtn", x, y));
				}
				else if (side == Chess::Side::BLACK) {
					on_board.emplace_back(new ChessAdvisor("blackAdvisorBtn", x, y));
				}
			}
			else if (rank == Chess::Rank::CANNON) {
				if (side == Chess::Side::RED) {
					on_board.emplace_back(new ChessCannon("redCannonBtn", x, y));
				}
				else if (side == Chess::Side::BLACK) {
					on_board.emplace_back(new ChessCannon("blackCannonBtn", x, y));
				}
			}
			else if (rank == Chess::Rank::CHARIOT) {
				if (side == Chess::Side::RED) {
					on_board.emplace_back(new ChessChariot("redChariotBtn", x, y));
				}
				else if (side == Chess::Side::BLACK) {
					on_board.emplace_back(new ChessChariot("blackChariotBtn", x, y));
				}
			}
			else if (rank == Chess::Rank::ELEPHANT) {
				if (side == Chess::Side::RED) {
					on_board.emplace_back(new ChessElephant("redElephantBtn", x, y));
				}
				else if (side == Chess::Side::BLACK) {
					on_board.emplace_back(new ChessElephant("blackElephantBtn", x, y));
				}
			}
			else if (rank == Chess::Rank::HORSE) {
				if (side == Chess::Side::RED) {
					on_board.emplace_back(new ChessHorse("redHorseBtn", x, y));
				}
				else if (side == Chess::Side::BLACK) {
					on_board.emplace_back(new ChessHorse("blackHorseBtn", x, y));
				}
			}
			else if (rank == Chess::Rank::SOLDIER) {
				if (side == Chess::Side::RED) {
					on_board.emplace_back(new ChessSoldier("redSoldierBtn", x, y));
				}
				else if (side == Chess::Side::BLACK) {
					on_board.emplace_back(new ChessSoldier("blackSoldierBtn", x, y));
				}
			}
		}
	}
}

// Intent: create gameplay board and background
void GameManager::createGameBoard(bool& appRunning, bool& startGame) {
	static bool inCheckWarning = false, inCheckmateWarning = false, inStalemateWarning = false, savingGame = false;
	static Chess* mover = nullptr;

	// Create window with board and get window size
	ImVec2 screenSize = viewer.createWindow(appRunning, viewer.backgroundGame);
	auto windowPos = viewer.getCursorPos();
	float middle_x = (screenSize.x / 2) - 100;
	float middle_y = (screenSize.y / 2) + 140;

	// Display timer
	auto& io = viewer.getData();
	timer += io.DeltaTime;
	int seconds = (int) timer % 60;
	int minutes = timer / 60;
	viewer.setButtonPos(805, board.yPosition[4] + 91);
	viewer.addText("%02d  %02d", minutes, seconds);

	// Control buttons
	viewer.setButtonPos(750, board.yPosition[1]+10);
	Viewer::Button saveGameButton("saveGameBtn", viewer.buttonSaveGameImg, viewer.buttonSaveGameHoverImg, Viewer::Button::Type::GAMEPLAY);
	viewer.setButtonPos(750, board.yPosition[2] + 30);
	Viewer::Button surrenderButton("surrenderBtn", viewer.buttonSurrenderImg, viewer.buttonSurrenderHoverImg, Viewer::Button::Type::GAMEPLAY);
	viewer.setButtonPos(750, board.yPosition[3] + 50);
	Viewer::Button exitBoardButton("exitBoardBtn", viewer.buttonExitBoardImg, viewer.buttonExitBoardHoverImg, Viewer::Button::Type::GAMEPLAY);
	viewer.setButtonPos(750, board.yPosition[4] + 80);
	Viewer::Button timer("timer", viewer.timerImg, viewer.timerImg, Viewer::Button::Type::GAMEPLAY);

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

	// Put all chess pieces in place
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


		Viewer::ID id(i);
		viewer.setButtonPos(piecePosition);
		Viewer::Button thisBtn(on_board[i]->id, *(on_board[i]->img), *(on_board[i]->img), Viewer::Button::Type::CIRCLE, on_board[i]->alpha);

		// Player selects a chess piece
		if (thisBtn && on_board[i]->side == current_player) {
			on_board[i]->updateAllPossibleMove(on_board);
			mover = on_board[i];
		}
	}


	// Check (not checkmate) warning
	if (inCheckWarning) {
		viewer.setButtonPos(windowPos.x, windowPos.y);
		viewer.makeExtraWindow();
		viewer.addWindowImage(viewer.backgroundCheck);
		viewer.endExtraWindow();

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

		auto& io = viewer.getData();
		static auto curDuration = 0.f;
		curDuration += io.DeltaTime;
		if (curDuration >= 2.5) {
			inCheckmateWarning = false;
			inCheckmate = true;
			curDuration = 0;
		}
	}

	// Stalemate warning
	if (inStalemateWarning) {
		viewer.setButtonPos(windowPos.x, windowPos.y);
		viewer.makeExtraWindow();

		viewer.addWindowImage(viewer.backgroundStalemate);
		viewer.endExtraWindow();

		auto& io = viewer.getData();
		static auto curDuration = 0.f;
		curDuration += io.DeltaTime;
		if (curDuration >= 2.5) {
			inStalemateWarning = false;
			inStalemate = true;
			curDuration = 0;
		}
	}


	// If player selected a chess piece
	if (mover != nullptr) {
		// Make extra window for possible moves buttons
		viewer.setButtonPos(windowPos.x, windowPos.y);
		viewer.makeExtraWindow();
		{
			// Make possible move buttons
			viewer.setButtonPos(board.xPosition[mover->curPos.x], board.yPosition[mover->curPos.y]);
			Viewer::Button backBtn("back", *(mover->img), *(mover->img), Viewer::Button::Type::CIRCLE);

			// Check if each move is enemy or friend, or check position
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

				// Pieces cannot move to positions that put their general in check position
				Chess::Position originalPos = mover->curPos;
				mover->curPos = mover->allPossibleMove[i];

				if (mover->side == Chess::Side::RED) {
					// Black checks the Red General
					if (isCheck(Chess::Side::BLACK, on_board)) {
						bool eatEnemy = false;

						// Loop through all pieces to check if the piece that checks the general can be eaten
						for (int j = 0; j < on_board.size(); j++) {
							if (mover->curPos == on_board[j]->curPos) {
								Chess eaten = *on_board[j];
								eaten.updateAllPossibleMove(on_board);

								// The piece that checks the general can be eaten
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

						// If the piece that checks the general can't be eaten, or the selected piece is the checked general,
						// erase the possible move that keeps the general in check position
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
				else {
					if (isCheck(Chess::Side::RED, on_board)) {
						bool eatEnemy = false;

						for (int j = 0; j < on_board.size(); j++) {
							if (mover->curPos == on_board[j]->curPos) {
								Chess eaten = *on_board[j];
								eaten.updateAllPossibleMove(on_board);

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

						mover->curPos = originalPos;

						if (!eatEnemy || mover->rank == Chess::Rank::GENERAL) {
							mover->allPossibleMove.erase(mover->allPossibleMove.begin() + i);

							if (mover->allPossibleMove.empty()) break;
							i--;
							continue;
						}
					}
					else {
						mover->curPos = originalPos;
					}
				}
				

				Viewer::ID id(i);
				viewer.setButtonPos(board.xPosition[mover->allPossibleMove[i].x], board.yPosition[mover->allPossibleMove[i].y]);
				Viewer::Button moveBtn("move", *(mover->moveImg), *(mover->moveImg), Viewer::Button::Type::CIRCLE);

				if (moveBtn) {
					if (isEnemy) {
						//on_board.erase(on_board.begin() + enemyIndex);
						on_board[enemyIndex]->isDead = true;
					}

					// output Log
					if (current_player == Chess::Side::RED) {
						logFile << "1 ";
					}
					else {
						logFile << "2 ";
					}
					logFile << mover->curPos.x << mover->curPos.y << mover->allPossibleMove[i].x << mover->allPossibleMove[i].y << "\n";

					mover->animPos = mover->curPos;
					mover->animProg = 0;

					mover->curPos.x = mover->allPossibleMove[i].x;
					mover->curPos.y = mover->allPossibleMove[i].y;

					// check if there is a check or checkmate
					if (isCheck(current_player, on_board)) {
						// check mate
						if (isCheckmate(current_player, on_board)) {
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
						if (isStalemate(current_player, on_board)) {
							inStalemateWarning = true;
						}
					}

					if (current_player == Chess::Side::RED) current_player = Chess::Side::BLACK;
					else current_player = Chess::Side::RED;

					mover = nullptr;
					break;
				}
				else if (backBtn) {
					mover = nullptr;
					break;
				}
			}
			if (backBtn) mover = nullptr;
		}
		viewer.endExtraWindow();
	}


	if (inCheckmate) {
		viewer.setButtonPos(windowPos.x, windowPos.y);
		viewer.makeExtraWindow();
		{
			// red wins
			if (current_player == Chess::Side::BLACK) {
				viewer.addWindowImage(viewer.backgroundRedWin);
			}
			// black wins
			else {
				viewer.addWindowImage(viewer.backgroundBlackWin);
			}

			viewer.setButtonPos(middle_x - 150, middle_y);
			Viewer::Button playAgainButton("playAgainBtn", viewer.buttonPlayAgainImg, viewer.buttonPlayAgainHoverImg, Viewer::Button::Type::MAINMENU);
			viewer.setButtonPos(middle_x + 150, middle_y);
			Viewer::Button backToMenuButton("backToMenuBtn", viewer.buttonBackToMenuImg, viewer.buttonBackToMenuHoverImg, Viewer::Button::Type::MAINMENU);

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

	if (inStalemate) {
		viewer.setButtonPos(windowPos.x, windowPos.y);
		viewer.makeExtraWindow();
		{
			// red wins
			if (current_player == Chess::Side::BLACK) {
				viewer.addWindowImage(viewer.backgroundRedWin);
			}
			// black wins
			else {
				viewer.addWindowImage(viewer.backgroundBlackWin);
			}

			viewer.setButtonPos(middle_x - 150, middle_y);
			Viewer::Button playAgainButton("playAgainBtn", viewer.buttonPlayAgainImg, viewer.buttonPlayAgainHoverImg, Viewer::Button::Type::MAINMENU);
			viewer.setButtonPos(middle_x + 150, middle_y);
			Viewer::Button backToMenuButton("backToMenuBtn", viewer.buttonBackToMenuImg, viewer.buttonBackToMenuHoverImg, Viewer::Button::Type::MAINMENU);

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

bool GameManager::isCheck(Chess::Side side, std::vector<Chess*> on_board) {
	// check if black is in check (red is attacking)
	if (side == Chess::Side::RED) {
		// check possible move of every red piece
		for (int i = 0; i < on_board.size(); i++) {
			if (on_board[i]->side == Chess::Side::BLACK) continue;

			on_board[i]->updateAllPossibleMove(on_board);

			// compare each possible move to each piece's position
			for (int j = 0; j < on_board[i]->allPossibleMove.size(); j++) {
				for (int k = 0; k < on_board.size(); k++) {
					// if possible move and a other piece position is the same, check if it's the other side's general
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
	// check if red is in check (black is attacking)
	else if (side == Chess::Side::BLACK) {
		// check possible move of every black piece
		for (int i = 0; i < on_board.size(); i++) {
			if (on_board[i]->side == Chess::Side::RED) continue;

			on_board[i]->updateAllPossibleMove(on_board);

			// compare each possible move to each piece's position
			for (int j = 0; j < on_board[i]->allPossibleMove.size(); j++) {
				for (int k = 0; k < on_board.size(); k++) {
					// if possible move and a other piece position is the same, check if it's the other side's general
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

// Pre: the opponent is in check
bool GameManager::isCheckmate(Chess::Side side, std::vector<Chess*> on_board) {
	// black is in check (red is attacking)
	if (side == Chess::Side::RED) {
		// check every possible move of black pieces
		for (int i = 0; i < on_board.size(); i++) {
			if (on_board[i]->side == Chess::Side::RED) continue;

			on_board[i]->updateAllPossibleMove(on_board);
			Chess::Position originalPos = on_board[i]->curPos;

			// move each piece to each possible move and check if black is still in check
			for (int j = 0; j < on_board[i]->allPossibleMove.size(); j++) {

				// move the piece to each possible move
				on_board[i]->curPos = on_board[i]->allPossibleMove[j];

				// check if the general is not in check anymore
				if (!isCheck(Chess::Side::RED, on_board)) {
					on_board[i]->curPos = originalPos;
					return false;
				}
			}

			// move the piece back to its original position
			on_board[i]->curPos = originalPos;
		}
		// the general is still in check even after moving every piece, return true
		return true;
	}
	// red is in check (black is attacking)
	else if (side == Chess::Side::BLACK) {
		// check every possible move of red pieces
		for (int i = 0; i < on_board.size(); i++) {
			if (on_board[i]->side == Chess::Side::BLACK) continue;

			on_board[i]->updateAllPossibleMove(on_board);
			Chess::Position originalPos = on_board[i]->curPos;

			// move each piece to each possible move and check if red is still in check
			for (int j = 0; j < on_board[i]->allPossibleMove.size(); j++) {

				// move the piece to each possible move
				on_board[i]->curPos = on_board[i]->allPossibleMove[j];

				// check if the general is not in check anymore
				if (!isCheck(Chess::Side::BLACK, on_board)) {
					on_board[i]->curPos = originalPos;
					return false;
				}
			}

			// move the piece back to its original position
			on_board[i]->curPos = originalPos;
		}
		// the general is still in check even after moving every piece, return true
		return true;
	}

	return false;
}

bool GameManager::isStalemate(Chess::Side side, std::vector<Chess*>on_board) {
	// check if black is in stalemate (red is attacking)
	if (side == Chess::Side::RED) {
		for (int k = 0; k < on_board.size(); k++) {
			if (on_board[k]->side == Chess::Side::RED) continue;

			// update each piece's possible move
			on_board[k]->updateAllPossibleMove(on_board);

			// check if each move is enemy or friend, or check position
			for (int i = 0; i < on_board[k]->allPossibleMove.size(); i++) {
				bool mustContinue = false;

				if (on_board[k]->allPossibleMove.empty()) continue;

				for (int j = 0; j < on_board.size(); j++) {
					if (on_board[k]->allPossibleMove[i] == on_board[j]->curPos) {
						if (on_board[j]->side == on_board[k]->side) {
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

				// pieces cannot move to positions that put their general in check position
				Chess::Position originalPos = on_board[k]->curPos;
				on_board[k]->curPos = on_board[k]->allPossibleMove[i];

				if (on_board[k]->side == Chess::Side::RED) {
					if (isCheck(Chess::Side::BLACK, on_board)) {
						on_board[k]->curPos = originalPos;
						on_board[k]->allPossibleMove.erase(on_board[k]->allPossibleMove.begin() + i);

						if (on_board[k]->allPossibleMove.empty()) break;
						i--;
						continue;
					}
					else {
						on_board[k]->curPos = originalPos;
					}
				}
				else {
					if (isCheck(Chess::Side::RED, on_board)) {
						on_board[k]->curPos = originalPos;
						on_board[k]->allPossibleMove.erase(on_board[k]->allPossibleMove.begin() + i);

						if (on_board[k]->allPossibleMove.empty()) break;
						i--;
						continue;
					}
					else {
						on_board[k]->curPos = originalPos;
					}
				}
			}

			if (on_board[k]->allPossibleMove.size() > 0) return false;
		}
		return true;
	}
	// check if red is in stalemate (black is attacking)
	else {
		for (int k = 0; k < on_board.size(); k++) {
			if (on_board[k]->side == Chess::Side::BLACK) continue;

			// update each piece's possible move
			on_board[k]->updateAllPossibleMove(on_board);

			// check if each move is enemy or friend, or check position
			for (int i = 0; i < on_board[k]->allPossibleMove.size(); i++) {
				bool mustContinue = false;

				for (int j = 0; j < on_board.size(); j++) {
					if (on_board[k]->allPossibleMove[i] == on_board[j]->curPos) {
						if (on_board[j]->side == on_board[k]->side) {
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

				// pieces cannot move to positions that put their general in check position
				Chess::Position originalPos = on_board[k]->curPos;
				on_board[k]->curPos = on_board[k]->allPossibleMove[i];

				if (on_board[k]->side == Chess::Side::RED) {
					if (isCheck(Chess::Side::BLACK, on_board)) {
						on_board[k]->curPos = originalPos;
						on_board[k]->allPossibleMove.erase(on_board[k]->allPossibleMove.begin() + i);

						if (on_board[k]->allPossibleMove.empty()) break;
						i--;
						continue;
					}
					else {
						on_board[k]->curPos = originalPos;
					}
				}
				else {
					if (isCheck(Chess::Side::RED, on_board)) {
						on_board[k]->curPos = originalPos;
						on_board[k]->allPossibleMove.erase(on_board[k]->allPossibleMove.begin() + i);

						if (on_board[k]->allPossibleMove.empty()) break;
						i--;
						continue;
					}
					else {
						on_board[k]->curPos = originalPos;
					}
				}
			}

			if (on_board[k]->allPossibleMove.size() > 0) return false;
		}
		return true;
	}
}

void GameManager::saveGameMenu(bool& savingGame) {
	viewer.makeExtraWindow();
	viewer.addWindowImage(viewer.backgroundLoadGame);
	{
		viewer.setButtonPos(170, 250);
		Viewer::Button saveSlot1("saveSlot1", viewer.buttonSave1Img, viewer.buttonSave1HoverImg, Viewer::Button::Type::SAVESLOT);
		viewer.setButtonPos(450, 250);
		Viewer::Button saveSlot2("saveSlot2", viewer.buttonSave2Img, viewer.buttonSave2HoverImg, Viewer::Button::Type::SAVESLOT);
		viewer.setButtonPos(750, 250);
		Viewer::Button saveSlot3("saveSlot3", viewer.buttonSave3Img, viewer.buttonSave3HoverImg, Viewer::Button::Type::SAVESLOT);
		viewer.setButtonPos(450, 450);
		Viewer::Button exitSaveMenuButton("exitSaveMenuBtn", viewer.buttonExitBoardImg, viewer.buttonExitBoardHoverImg, Viewer::Button::Type::MAINMENU);

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

void GameManager::saveGame(std::string filename) {
	nlohmann::json js;

	js["player"]["current_player"] = current_player;
	
	for (int i = 0; i < on_board.size(); i++) {
		js["chess_piece_" + std::to_string(i)]["side"] = on_board[i]->side;
		js["chess_piece_" + std::to_string(i)]["rank"] = on_board[i]->rank;
		js["chess_piece_" + std::to_string(i)]["pos_x"] = on_board[i]->curPos.x;
		js["chess_piece_" + std::to_string(i)]["pos_y"] = on_board[i]->curPos.y;
	}

	std::ofstream writeFile{ filename };
	if (writeFile.good()) {
		writeFile << std::setw(1) << js;
	}
}