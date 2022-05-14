#include "ChessElephant.h"
#include "Viewer.h"

ChessElephant::ChessElephant() {}

ChessElephant::ChessElephant(const char* name, int x, int y) {
	id = name;

	if (name == "redElephantBtn") {
		side = Side::RED;
		rank = Rank::ELEPHANT;
		curPos.x = x;
		curPos.y = y;
		img = &viewer.chessRedElephant;
		moveImg = &viewer.possibleRed;
	}
	else if (name == "blackElephantBtn") {
		side = Side::BLACK;
		rank = Rank::ELEPHANT;
		curPos.x = x;
		curPos.y = y;
		img = &viewer.chessBlackElephant;
		moveImg = &viewer.possibleBlack;
	}
}

void ChessElephant::updateAllPossibleMove(std::vector<Chess*>on_board) {
	allPossibleMove.clear();

	if (side == Side::RED) {
		// upper left
		int i = 1;
		bool mustBreak = false;
		while (curPos.x - i >= 0 && curPos.y - i >= 5) {
			for (int j = 0; j < on_board.size(); j++) {
				if (curPos.x - i == on_board[j]->curPos.x && curPos.y - i == on_board[j]->curPos.y) {
					if (side == on_board[j]->side) {
						// the piece is a friend
						mustBreak = true;
						break;
					}
					else {
						// the piece is enemy
						if (i % 2 == 0) allPossibleMove.emplace_back(curPos.x - i, curPos.y - i);
						mustBreak = true;
						break;
					}
				}
			}
			if (mustBreak) break;

			if (i % 2 == 0) allPossibleMove.emplace_back(curPos.x - i, curPos.y - i);
			i++;
		}
		// upper right
		i = 1;
		mustBreak = false;
		while (curPos.x + i <= 8 && curPos.y - i >= 5) {
			for (int j = 0; j < on_board.size(); j++) {
				if (curPos.x + i == on_board[j]->curPos.x && curPos.y + i == on_board[j]->curPos.y) {
					if (side == on_board[j]->side) {
						// the piece is a friend
						mustBreak = true;
						break;
					}
					else {
						// the piece is enemy
						if (i % 2 == 0) allPossibleMove.emplace_back(curPos.x + i, curPos.y - i);
						mustBreak = true;
						break;
					}
				}
			}
			if (mustBreak) break;

			if (i % 2 == 0) allPossibleMove.emplace_back(curPos.x + i, curPos.y - i);
			i++;
		}
		// lower left
		i = 1;
		mustBreak = false;
		while (curPos.x - i >= 0 && curPos.y + i <= 9) {
			for (int j = 0; j < on_board.size(); j++) {
				if (curPos.x - i == on_board[j]->curPos.x && curPos.y + i == on_board[j]->curPos.y) {
					if (side == on_board[j]->side) {
						// the piece is a friend
						mustBreak = true;
						break;
					}
					else {
						// the piece is enemy
						if (i % 2 == 0) allPossibleMove.emplace_back(curPos.x - i, curPos.y + i);
						mustBreak = true;
						break;
					}
				}
			}
			if (mustBreak) break;

			if (i % 2 == 0) allPossibleMove.emplace_back(curPos.x - i, curPos.y + i);
			i++;
		}
		// lower right
		i = 1;
		mustBreak = false;
		while (curPos.x + i <= 8 && curPos.y + i <= 9) {
			for (int j = 0; j < on_board.size(); j++) {
				if (curPos.x + i == on_board[j]->curPos.x && curPos.y + i == on_board[j]->curPos.y) {
					if (side == on_board[j]->side) {
						// the piece is a friend
						mustBreak = true;
						break;
					}
					else {
						// the piece is enemy
						if (i % 2 == 0) allPossibleMove.emplace_back(curPos.x + i, curPos.y + i);
						mustBreak = true;
						break;
					}
				}
			}
			if (mustBreak) break;

			if (i % 2 == 0) allPossibleMove.emplace_back(curPos.x + i, curPos.y + i);
			i++;
		}
	}
	else if (side == Side::BLACK) {
		// upper left
		int i = 1;
		bool mustBreak = false;
		while (curPos.x - i >= 0 && curPos.y - i >= 0) {
			for (int j = 0; j < on_board.size(); j++) {
				if (curPos.x - i == on_board[j]->curPos.x && curPos.y - i == on_board[j]->curPos.y) {
					if (side == on_board[j]->side) {
						// the piece is a friend
						mustBreak = true;
						break;
					}
					else {
						// the piece is enemy
						if (i % 2 == 0) allPossibleMove.emplace_back(curPos.x - i, curPos.y - i);
						mustBreak = true;
						break;
					}
				}
			}
			if (mustBreak) break;

			if (i % 2 == 0) allPossibleMove.emplace_back(curPos.x - i, curPos.y - i);
			i++;
		}
		// upper right
		i = 1;
		mustBreak = false;
		while (curPos.x + i <= 8 && curPos.y - i >= 0) {
			for (int j = 0; j < on_board.size(); j++) {
				if (curPos.x + i == on_board[j]->curPos.x && curPos.y + i == on_board[j]->curPos.y) {
					if (side == on_board[j]->side) {
						// the piece is a friend
						mustBreak = true;
						break;
					}
					else {
						// the piece is enemy
						if (i % 2 == 0) allPossibleMove.emplace_back(curPos.x + i, curPos.y - i);
						mustBreak = true;
						break;
					}
				}
			}
			if (mustBreak) break;

			if (i % 2 == 0) allPossibleMove.emplace_back(curPos.x + i, curPos.y - i);
			i++;
		}
		// lower left
		i = 1;
		mustBreak = false;
		while (curPos.x - i >= 0 && curPos.y + i <= 4) {
			for (int j = 0; j < on_board.size(); j++) {
				if (curPos.x - i == on_board[j]->curPos.x && curPos.y + i == on_board[j]->curPos.y) {
					if (side == on_board[j]->side) {
						// the piece is a friend
						mustBreak = true;
						break;
					}
					else {
						// the piece is enemy
						if (i % 2 == 0) allPossibleMove.emplace_back(curPos.x - i, curPos.y + i);
						mustBreak = true;
						break;
					}
				}
			}
			if (mustBreak) break;

			if (i % 2 == 0) allPossibleMove.emplace_back(curPos.x - i, curPos.y + i);
			i++;
		}
		// lower right
		i = 1;
		mustBreak = false;
		while (curPos.x + i <= 8 && curPos.y + i <= 4) {
			for (int j = 0; j < on_board.size(); j++) {
				if (curPos.x + i == on_board[j]->curPos.x && curPos.y + i == on_board[j]->curPos.y) {
					if (side == on_board[j]->side) {
						// the piece is a friend
						mustBreak = true;
						break;
					}
					else {
						// the piece is enemy
						if (i % 2 == 0) allPossibleMove.emplace_back(curPos.x + i, curPos.y + i);
						mustBreak = true;
						break;
					}
				}
			}
			if (mustBreak) break;

			if (i % 2 == 0) allPossibleMove.emplace_back(curPos.x + i, curPos.y + i);
			i++;
		}
	}
}