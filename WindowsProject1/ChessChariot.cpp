#include "ChessChariot.h"
#include "Viewer.h"

/////////////// Constructors ///////////////
ChessChariot::ChessChariot() {}

ChessChariot::ChessChariot(const char* name, int x, int y) {
	id = name;

	if (name == "redChariotBtn") {
		side = Side::RED;
		rank = Rank::CHARIOT;
		curPos.x = x;
		curPos.y = y;
		img = &viewer.chessRedChariot;
		moveImg = &viewer.possibleRed;
	}
	else if (name == "blackChariotBtn") {
		side = Side::BLACK;
		rank = Rank::CHARIOT;
		curPos.x = x;
		curPos.y = y;
		img = &viewer.chessBlackChariot;
		moveImg = &viewer.possibleBlack;
	}
}

/////////////// Functions ///////////////
// Intent: update chariot's possible moves
// Pre: pass the vector of all the current pieces on board
// Post: chariot's possible moves are updated
void ChessChariot::updateAllPossibleMove(std::vector<Chess*>on_board) {
	allPossibleMove.clear();

	// up
	int i = 1;
	bool mustBreak = false;
	while (curPos.x >= 0 && curPos.x <= 8 && curPos.y - i >= 0) {
		for (int j = 0; j < on_board.size(); j++) {
			if (curPos.x == on_board[j]->curPos.x && curPos.y - i == on_board[j]->curPos.y) {
				if (side == on_board[j]->side) {
					// the piece is a friend
					mustBreak = true;
					break;
				}
				else {
					// the piece is enemy
					allPossibleMove.emplace_back(curPos.x, curPos.y - i);
					mustBreak = true;
					break;
				}
			}
		}
		if (mustBreak) break;

		allPossibleMove.emplace_back(curPos.x, curPos.y - i);
		i++;
	}

	// down
	i = 1;
	mustBreak = false;
	while (curPos.x >= 0 && curPos.x <= 8 && curPos.y + i <= 9) {
		for (int j = 0; j < on_board.size(); j++) {
			if (curPos.x == on_board[j]->curPos.x && curPos.y + i == on_board[j]->curPos.y) {
				if (side == on_board[j]->side) {
					// the piece is a friend
					mustBreak = true;
					break;
				}
				else {
					// the piece is enemy
					allPossibleMove.emplace_back(curPos.x, curPos.y + i);
					mustBreak = true;
					break;
				}
			}
		}
		if (mustBreak) break;

		allPossibleMove.emplace_back(curPos.x, curPos.y + i);
		i++;
	}

	// left
	i = 1;
	mustBreak = false;
	while (curPos.y >= 0 && curPos.y <= 9 && curPos.x - i >= 0) {
		for (int j = 0; j < on_board.size(); j++) {
			if (curPos.x - i == on_board[j]->curPos.x && curPos.y == on_board[j]->curPos.y) {
				if (side == on_board[j]->side) {
					// the piece is a friend
					mustBreak = true;
					break;
				}
				else {
					// the piece is enemy
					allPossibleMove.emplace_back(curPos.x - i, curPos.y);
					mustBreak = true;
					break;
				}
			}
		}
		if (mustBreak) break;

		allPossibleMove.emplace_back(curPos.x - i, curPos.y);
		i++;
	}

	// right
	i = 1;
	mustBreak = false;
	while (curPos.y >= 0 && curPos.y <= 9 && curPos.x + i <= 8) {
		for (int j = 0; j < on_board.size(); j++) {
			if (curPos.x + i == on_board[j]->curPos.x && curPos.y == on_board[j]->curPos.y) {
				if (side == on_board[j]->side) {
					// the piece is a friend
					mustBreak = true;
					break;
				}
				else {
					// the piece is enemy
					allPossibleMove.emplace_back(curPos.x + i, curPos.y);
					mustBreak = true;
					break;
				}
			}
		}
		if (mustBreak) break;

		allPossibleMove.emplace_back(curPos.x + i, curPos.y);
		i++;
	}
}