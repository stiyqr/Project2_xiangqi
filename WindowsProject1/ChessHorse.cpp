#include "ChessHorse.h"
#include "Viewer.h"

ChessHorse::ChessHorse() {}

ChessHorse::ChessHorse(const char* name, int x, int y) {
	id = name;

	if (name == "redHorseBtn") {
		side = Side::RED;
		rank = Rank::HORSE;
		curPos.x = x;
		curPos.y = y;
		img = &viewer.chessRedHorse;
		moveImg = &viewer.possibleRed;
	}
	else if (name == "blackHorseBtn") {
		side = Side::BLACK;
		rank = Rank::HORSE;
		curPos.x = x;
		curPos.y = y;
		img = &viewer.chessBlackHorse;
		moveImg = &viewer.possibleBlack;
	}
}

void ChessHorse::updateAllPossibleMove(std::vector<Chess*> on_board) {
	allPossibleMove.clear();

	bool up = true, down = true, left = true, right = true;

	for (int i = 0; i < on_board.size(); i++) {
		// up
		if (curPos.x == on_board[i]->curPos.x && curPos.y - 1 == on_board[i]->curPos.y) {
			up = false;
		}
		if (curPos.y - 2 < 0) up = false;
		// down
		if (curPos.x == on_board[i]->curPos.x && curPos.y + 1 == on_board[i]->curPos.y) {
			down = false;
		}
		if (curPos.y + 2 > 9) down = false;
		// left
		if (curPos.x - 1 == on_board[i]->curPos.x && curPos.y == on_board[i]->curPos.y) {
			left = false;
		}
		if (curPos.x - 2 < 0) left = false;
		// right
		if (curPos.x + 1 == on_board[i]->curPos.x && curPos.y == on_board[i]->curPos.y) {
			right = false;
		}
		if (curPos.x + 2 > 8) right = false;
	}

	if (up) {
		if (curPos.x > 0 && curPos.y > 1) allPossibleMove.emplace_back(curPos.x - 1, curPos.y - 2);
		if (curPos.x < 8 && curPos.y > 1) allPossibleMove.emplace_back(curPos.x + 1, curPos.y - 2);
	}
	if (down) {
		if (curPos.x > 0 && curPos.y < 8) allPossibleMove.emplace_back(curPos.x - 1, curPos.y + 2);
		if (curPos.x < 8 && curPos.y < 8) allPossibleMove.emplace_back(curPos.x + 1, curPos.y + 2);
	}
	if (left) {
		if (curPos.x > 1 && curPos.y > 1) allPossibleMove.emplace_back(curPos.x - 2, curPos.y - 1);
		if (curPos.x > 1 && curPos.y < 9) allPossibleMove.emplace_back(curPos.x - 2, curPos.y + 1);
	}
	if (right) {
		if (curPos.x < 7 && curPos.y > 1) allPossibleMove.emplace_back(curPos.x + 2, curPos.y - 1);
		if (curPos.x < 7 && curPos.y < 9) allPossibleMove.emplace_back(curPos.x + 2, curPos.y + 1);
	}
}