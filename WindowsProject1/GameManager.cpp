#include "GameManager.h"
#include "ChessPieces.h"
#include <vector>

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

void GameManager::createGameBoard(bool& appRunning, bool& startGame) {
	ImVec2 screenSize = viewer.createWindow(appRunning, viewer.backgroundGame);
	auto position = viewer.getCursorPos();

	// Control buttons
	viewer.setButtonPos(800, 370);
	Viewer::Button backToMenuButton("backToMenuBtn", viewer.buttonBackToMenuImg, viewer.buttonBackToMenuHoverImg, Viewer::Button::Type::MAINMENU);

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

	if (mover != nullptr) {
		viewer.setButtonPos(position.x, position.y);
		viewer.makeMoveWindow();
		{
			viewer.setButtonPos(board.xPosition[mover->curPos.x], board.yPosition[mover->curPos.y]);
			Viewer::Button backBtn("back", *(mover->img), *(mover->img), Viewer::Button::Type::CIRCLE);

			for (int i = 0; i < mover->allPossibleMove.size(); i++) {
				bool isFriend = false, isEnemy = false;
				int enemyIndex = 0;
				for (int j = 0; j < on_board.size(); j++) {
					if (mover->allPossibleMove[i] == on_board[j]->curPos) {
						if (on_board[j]->side == mover->side) {
							isFriend = true;
						}
						else {
							isEnemy = true;
							enemyIndex = j;
						}
					}
				}

				if (isFriend) continue;

				Viewer::ID id(i);
				viewer.setButtonPos(board.xPosition[mover->allPossibleMove[i].x], board.yPosition[mover->allPossibleMove[i].y]);
				Viewer::Button moveBtn("move", *(mover->moveImg), *(mover->moveImg), Viewer::Button::Type::CIRCLE);

				if (moveBtn) {
					if (isEnemy) {
						on_board.erase(on_board.begin() + enemyIndex);
					}

					mover->curPos.x = mover->allPossibleMove[i].x;
					mover->curPos.y = mover->allPossibleMove[i].y;
					mover = nullptr;

					if (current_player == Chess::Side::RED) current_player = Chess::Side::BLACK;
					else current_player = Chess::Side::RED;

					break;
				}
				else if (backBtn) {
					mover = nullptr;
					break;
				}
			}
			if (backBtn) mover = nullptr;
		}
		viewer.endMoveWindow();
		//mover->renderAllPossibleMove();
	}




	// Mouse click controls
	if (backToMenuButton) {
		startGame = false;
	}
}