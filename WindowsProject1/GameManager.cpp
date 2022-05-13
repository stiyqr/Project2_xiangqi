#include "GameManager.h"
#include "ChessPieces.h"
#include <vector>

GameManager::GameManager() {
	// Black chess pieces
	on_board.emplace_back(ChessGeneral("blackGeneralBtn"));
	on_board.emplace_back(ChessAdvisor("blackAdvisorBtn", 3, 0));
	on_board.emplace_back(ChessAdvisor("blackAdvisorBtn", 5, 0));
	on_board.emplace_back(ChessElephant("blackElephantBtn", 2, 0));
	on_board.emplace_back(ChessElephant("blackElephantBtn", 6, 0));
	on_board.emplace_back(ChessHorse("blackHorseBtn", 1, 0));
	on_board.emplace_back(ChessHorse("blackHorseBtn", 7, 0));
	on_board.emplace_back(ChessChariot("blackChariotBtn", 0, 0));
	on_board.emplace_back(ChessChariot("blackChariotBtn", 8, 0));

	on_board.emplace_back(ChessCannon("blackCannonBtn", 1, 2));
	on_board.emplace_back(ChessCannon("blackCannonBtn", 7, 2));

	on_board.emplace_back(ChessSoldier("blackSoldierBtn", 0, 3));
	on_board.emplace_back(ChessSoldier("blackSoldierBtn", 2, 3));
	on_board.emplace_back(ChessSoldier("blackSoldierBtn", 4, 3));
	on_board.emplace_back(ChessSoldier("blackSoldierBtn", 6, 3));
	on_board.emplace_back(ChessSoldier("blackSoldierBtn", 8, 3));

	// Red chess pieces
	on_board.emplace_back(ChessGeneral("redGeneralBtn"));
	on_board.emplace_back(ChessAdvisor("redAdvisorBtn", 3, 9));
	on_board.emplace_back(ChessAdvisor("redAdvisorBtn", 5, 9));
	on_board.emplace_back(ChessElephant("redElephantBtn", 2, 9));
	on_board.emplace_back(ChessElephant("redElephantBtn", 6, 9));
	on_board.emplace_back(ChessHorse("redHorseBtn", 1, 9));
	on_board.emplace_back(ChessHorse("redHorseBtn", 7, 9));
	on_board.emplace_back(ChessChariot("redChariotBtn", 0, 9));
	on_board.emplace_back(ChessChariot("redChariotBtn", 8, 9));

	on_board.emplace_back(ChessCannon("redCannonBtn", 1, 7));
	on_board.emplace_back(ChessCannon("redCannonBtn", 7, 7));

	on_board.emplace_back(ChessSoldier("redSoldierBtn", 0, 6));
	on_board.emplace_back(ChessSoldier("redSoldierBtn", 2, 6));
	on_board.emplace_back(ChessSoldier("redSoldierBtn", 4, 6));
	on_board.emplace_back(ChessSoldier("redSoldierBtn", 6, 6));
	on_board.emplace_back(ChessSoldier("redSoldierBtn", 8, 6));
}

void GameManager::createGameBoard(bool& appRunning, bool& startGame) {
	ImVec2 screenSize = viewer.createWindow(appRunning, viewer.backgroundGame);

	// Control buttons
	viewer.setButtonPos(800, 370);
	Viewer::Button backToMenuButton("backToMenuBtn", viewer.buttonBackToMenuImg, viewer.buttonBackToMenuHoverImg, Viewer::Button::Type::MAINMENU);

	// Chess pieces
	static Chess* mover = nullptr;
	for (int i = 0; i < on_board.size(); i++) {
		Viewer::ID id(i);
		viewer.setButtonPos(board.xPosition[on_board[i].curPos.x], board.yPosition[on_board[i].curPos.y]);
		Viewer::Button thisBtn(on_board[i].id, *(on_board[i].img), *(on_board[i].img), Viewer::Button::Type::CIRCLE);

		if (thisBtn) {
			if (mover == &on_board[i]) {
				mover = nullptr;
			}
			else {
				//on_board[i].updateAllPossibleMove();
				mover = &on_board[i];
			}
		}
	}

	if (mover != nullptr) {
		//for (int i = 0; i < mover->allPossibleMove; i++) {
			//viewer.setButtonPos(board.xPosition[allPossibleMove[i].curPos.x])
		//}
		//mover->renderAllPossibleMove();
	}

	// Mouse click controls
	if (backToMenuButton) {
		startGame = false;
	}
}

void GameManager::displayGameBoard(bool& appRunning, bool& startGame) {
	ImVec2 screenSize = viewer.createWindow(appRunning, viewer.backgroundGame);

	viewer.setButtonPos(800, 370);
	Viewer::Button backToMenuButton("backToMenuBtn", viewer.buttonBackToMenuImg, viewer.buttonBackToMenuHoverImg, Viewer::Button::Type::MAINMENU);

	// Chess pieces
	for (int i = 0; i < on_board.size(); i++) {
		viewer.setButtonPos(board.xPosition[on_board[i].curPos.x], board.yPosition[on_board[i].curPos.y]);
		on_board[i];
	}

	// Mouse click controls
	if (backToMenuButton) {
		startGame = false;
	}
}