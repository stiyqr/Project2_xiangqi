#include "ChessCannon.h"
#include "Viewer.h"

/////////////// Constructors ///////////////
ChessCannon::ChessCannon() {}

ChessCannon::ChessCannon(const char* name, int x, int y) {
	id = name;

	if (name == "redCannonBtn") {
		side = Side::RED;
		rank = Rank::CANNON;
		curPos.x = x;
		curPos.y = y;
		img = &viewer.chessRedCannon;
		moveImg = &viewer.possibleRed;
	}
	else if (name == "blackCannonBtn") {
		side = Side::BLACK;
		rank = Rank::CANNON;
		curPos.x = x;
		curPos.y = y;
		img = &viewer.chessBlackCannon;
		moveImg = &viewer.possibleBlack;
	}
}

/////////////// Functions ///////////////
// Intent: update cannon's possible moves
// Pre: pass the vector of all the current pieces on board
// Post: cannon's possible moves are updated
void ChessCannon::updateAllPossibleMove(std::vector<Chess*> on_board) {
	allPossibleMove.clear();

	// Up
	int i = 1;
	int found = 0;
	bool isEnemy = false;
	// Check for enemy
	while (curPos.x >= 0 && curPos.x <= 8 && curPos.y - i >= 0) {
		for (int j = 0; j < on_board.size(); j++) {
			// Found another piece
			if (curPos.x == on_board[j]->curPos.x && curPos.y - i == on_board[j]->curPos.y) {
				found++;

				// Found an enemy behind a piece
				if (found >= 2 && side != on_board[j]->side) {
					isEnemy = true;
					break;
				}
			}
		}

		// Movement when cannon can eat an enemy
		if (found >= 2 && isEnemy) {
			allPossibleMove.emplace_back(curPos.x, curPos.y - i);
			break;
		}

		i++;
	}

	// If no enemy, move like chariot
	i = 1;
	if (!isEnemy) {
		bool mustBreak = false;
		while (curPos.x >= 0 && curPos.x <= 8 && curPos.y - i >= 0) {
			for (int j = 0; j < on_board.size(); j++) {

				// Check is there is a piece that obstructs the movement
				if (curPos.x == on_board[j]->curPos.x && curPos.y - i == on_board[j]->curPos.y) {
					mustBreak = true;
					break;
				}
			}
			if (mustBreak) break;

			allPossibleMove.emplace_back(curPos.x, curPos.y - i);
			i++;
		}
	}


	// Down
	i = 1;
	found = 0;
	isEnemy = false;
	// Check for enemy
	while (curPos.x >= 0 && curPos.x <= 8 && curPos.y + i <= 9) {
		for (int j = 0; j < on_board.size(); j++) {
			// Found another piece
			if (curPos.x == on_board[j]->curPos.x && curPos.y + i == on_board[j]->curPos.y) {
				found++;

				// Found an enemy behind a piece
				if (found >= 2 && side != on_board[j]->side) {
					isEnemy = true;
					break;
				}
			}
		}

		// Movement when cannon can eat an enemy
		if (found >= 2 && isEnemy) {
			allPossibleMove.emplace_back(curPos.x, curPos.y + i);
			break;
		}

		i++;
	}

	// If no enemy, move like chariot
	i = 1;
	if (!isEnemy) {
		bool mustBreak = false;
		while (curPos.x >= 0 && curPos.x <= 8 && curPos.y + i <= 9) {
			for (int j = 0; j < on_board.size(); j++) {

				// Check is there is a piece that obstructs the movement
				if (curPos.x == on_board[j]->curPos.x && curPos.y + i == on_board[j]->curPos.y) {
					mustBreak = true;
					break;
				}
			}
			if (mustBreak) break;

			allPossibleMove.emplace_back(curPos.x, curPos.y + i);
			i++;
		}
	}


	// Left
	i = 1;
	found = 0;
	isEnemy = false;
	// Check for enemy
	while (curPos.x >= 0 && curPos.x <= 8 && curPos.x - i >= 0) {
		for (int j = 0; j < on_board.size(); j++) {
			// Found another piece
			if (curPos.x - i == on_board[j]->curPos.x && curPos.y == on_board[j]->curPos.y) {
				found++;

				// Found an enemy behind a piece
				if (found >= 2 && side != on_board[j]->side) {
					isEnemy = true;
					break;
				}
			}
		}

		// Movement when cannon can eat an enemy
		if (found >= 2 && isEnemy) {
			allPossibleMove.emplace_back(curPos.x - i, curPos.y);
			break;
		}

		i++;
	}

	// If no enemy, move like chariot
	i = 1;
	if (!isEnemy) {
		bool mustBreak = false;
		while (curPos.y >= 0 && curPos.y <= 9 && curPos.x - i >= 0) {
			for (int j = 0; j < on_board.size(); j++) {

				// Check is there is a piece that obstructs the movement
				if (curPos.x - i == on_board[j]->curPos.x && curPos.y == on_board[j]->curPos.y) {
					mustBreak = true;
					break;
				}
			}
			if (mustBreak) break;

			allPossibleMove.emplace_back(curPos.x - i, curPos.y);
			i++;
		}
	}


	// Right
	i = 1;
	found = 0;
	isEnemy = false;
	// Check for enemy
	while (curPos.x >= 0 && curPos.x <= 8 && curPos.x + i <= 8) {
		for (int j = 0; j < on_board.size(); j++) {
			// Found another piece
			if (curPos.x + i == on_board[j]->curPos.x && curPos.y == on_board[j]->curPos.y) {
				found++;

				// Found an enemy behind a piece
				if (found >= 2 && side != on_board[j]->side) {
					isEnemy = true;
					break;
				}
			}
		}

		// Movement if cannon can eat an enemy
		if (found >= 2 && isEnemy) {
			allPossibleMove.emplace_back(curPos.x + i, curPos.y);
			break;
		}

		i++;
	}

	// If no enemy, move like chariot
	i = 1;
	if (!isEnemy) {
		bool mustBreak = false;
		while (curPos.y >= 0 && curPos.y <= 9 && curPos.x + i <= 8) {
			for (int j = 0; j < on_board.size(); j++) {

				// Check is there is a piece that obstructs the movement
				if (curPos.x + i == on_board[j]->curPos.x && curPos.y == on_board[j]->curPos.y) {
					mustBreak = true;
					break;
				}
			}
			if (mustBreak) break;

			allPossibleMove.emplace_back(curPos.x + i, curPos.y);
			i++;
		}
	}
}