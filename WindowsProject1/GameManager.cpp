#include "GameManager.h"
#include "ChessPieces.h"
#include <vector>
#include <fstream>

GameManager::GameManager() {
	logFile.open("logFile.txt");

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

void GameManager::createGameBoard(bool& appRunning, bool& startGame) {
	static bool inCheckWarning = false, inCheckmateWarning = false, inStalemateWarning = false, savingGame = false;

	ImVec2 screenSize = viewer.createWindow(appRunning, viewer.backgroundGame);
	auto windowPos = viewer.getCursorPos();
	float middle_x = (screenSize.x / 2) - 100;
	float middle_y = (screenSize.y / 2) + 140;

	// Control buttons
	viewer.setButtonPos(800, 370);
	Viewer::Button exitBoardButton("exitBoardBtn", viewer.buttonExitBoardImg, viewer.buttonExitBoardHoverImg, Viewer::Button::Type::MAINMENU);
	viewer.setButtonPos(800, 280);
	Viewer::Button surrenderButton("surrenderBtn", viewer.buttonSurrenderImg, viewer.buttonSurrenderHoverImg, Viewer::Button::Type::MAINMENU);
	viewer.setButtonPos(800, 190);
	Viewer::Button saveGameButton("saveGameBtn", viewer.buttonSaveGameImg, viewer.buttonSaveGameHoverImg, Viewer::Button::Type::MAINMENU);

	// Button click controls
	if (exitBoardButton) {
		startGame = false;
		logFile.close();
	}
	else if (surrenderButton) {
		inCheckmate = true;
		logFile.close();
	}
	else if (saveGameButton) {
		savingGame = true;
	}

	if (savingGame) {
		viewer.setButtonPos(windowPos.x, windowPos.y);
		saveGameMenu(appRunning, savingGame);
	}

	// Chess pieces
	static Chess* mover = nullptr;

	for (int i = 0; i < on_board.size(); i++) {
		Viewer::ID id(i);
		viewer.setButtonPos(board.xPosition[on_board[i]->curPos.x], board.yPosition[on_board[i]->curPos.y]);
		Viewer::Button thisBtn(on_board[i]->id, *(on_board[i]->img), *(on_board[i]->img), Viewer::Button::Type::CIRCLE);

		if (thisBtn && on_board[i]->side == current_player) {
			on_board[i]->updateAllPossibleMove(on_board);
			mover = on_board[i];
		}
	}


	if (inCheckWarning) {
		viewer.setButtonPos(windowPos.x, windowPos.y);
		viewer.makeExtraWindow();
		viewer.addWindowImage(viewer.backgroundCheck);
		viewer.endExtraWindow();

		auto& io = ImGui::GetIO();
		static auto curDuration = 0.f;
		curDuration += io.DeltaTime;
		if (curDuration >= 2.5) {
			inCheckWarning = false;
			curDuration = 0;
		}
	}

	if (inCheckmateWarning) {
		viewer.setButtonPos(windowPos.x, windowPos.y);
		viewer.makeExtraWindow();

		viewer.addWindowImage(viewer.backgroundCheckmate);
		viewer.endExtraWindow();

		auto& io = ImGui::GetIO();
		static auto curDuration = 0.f;
		curDuration += io.DeltaTime;
		if (curDuration >= 2.5) {
			inCheckmateWarning = false;
			inCheckmate = true;
			curDuration = 0;
		}
	}

	if (inStalemateWarning) {
		viewer.setButtonPos(windowPos.x, windowPos.y);
		viewer.makeExtraWindow();

		viewer.addWindowImage(viewer.backgroundStalemate);
		viewer.endExtraWindow();

		auto& io = ImGui::GetIO();
		static auto curDuration = 0.f;
		curDuration += io.DeltaTime;
		if (curDuration >= 2.5) {
			inStalemateWarning = false;
			inStalemate = true;
			curDuration = 0;
		}
	}


	if (mover != nullptr) {
		viewer.setButtonPos(windowPos.x, windowPos.y);
		viewer.makeExtraWindow();
		{
			viewer.setButtonPos(board.xPosition[mover->curPos.x], board.yPosition[mover->curPos.y]);
			Viewer::Button backBtn("back", *(mover->img), *(mover->img), Viewer::Button::Type::CIRCLE);

			// check if each move is enemy or friend, or check position
			for (int i = 0; i < mover->allPossibleMove.size(); i++) {
				bool mustContinue = false;
				bool isEnemy = false;
				int enemyIndex = 0;
				for (int j = 0; j < on_board.size(); j++) {
					if (mover->allPossibleMove[i] == on_board[j]->curPos) {
						// possible move overlaps with friend
						if (on_board[j]->side == mover->side) {
							mover->allPossibleMove.erase(mover->allPossibleMove.begin() + i);

							if (mover->allPossibleMove.empty()) break;
							i--;
							mustContinue = true;
							break;
						}
						// possible move overlaps with enemy
						else {
							isEnemy = true;
							enemyIndex = j;
						}
					}
				}
				if (mustContinue) continue;

				if (mover->allPossibleMove.empty()) continue;

				// pieces cannot move to positions that put their general in check position
				Chess::Position originalPos = mover->curPos;
				mover->curPos = mover->allPossibleMove[i];

				if (mover->side == Chess::Side::RED) {
					if (isCheck(Chess::Side::BLACK, on_board)) {
						bool eatEnemy = false;

						for (int j = 0; j < on_board.size(); j++) {
							if (mover->curPos == on_board[j]->curPos) {
								Chess eaten = *on_board[j];
								eaten.updateAllPossibleMove(on_board);

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
						on_board.erase(on_board.begin() + enemyIndex);
					}

					// output Log
					if (current_player == Chess::Side::RED) {
						logFile << "1 ";
					}
					else {
						logFile << "2 ";
					}
					logFile << mover->curPos.x << mover->curPos.y << mover->allPossibleMove[i].x << mover->allPossibleMove[i].y << "\n";

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
		//mover->renderAllPossibleMove();
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

void GameManager::saveGameMenu(bool& appRunning, bool& savingGame) {
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

		}
		else if (saveSlot2) {

		}
		else if (saveSlot3) {

		}
		else if (exitSaveMenuButton) {
			savingGame = false;
		}
	}
	viewer.endExtraWindow();
}