#include "ChessCannon.h"
#include "Viewer.h"

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

void ChessCannon::updateAllPossibleMove(std::vector<Chess*> on_board) {
	allPossibleMove.clear();

	// up
	int i = 1;
	int found = 0;
	bool skipOne = false, isEnemy = false;;
	while (curPos.x >= 0 && curPos.x <= 8 && curPos.y - i >= 0) {
		for (int j = 0; j < on_board.size(); j++) {
			if (curPos.x == on_board[j]->curPos.x && curPos.y - i == on_board[j]->curPos.y) {
				found++;

				if (found >= 2 && side != on_board[j]->side) isEnemy = true;
				else skipOne = true;

				break;
			}
		}

		if (skipOne) {
			skipOne = false;
			i++;
			continue;
		}

		if (found >= 2) {
			if (isEnemy) allPossibleMove.emplace_back(curPos.x, curPos.y - i);
			break;
		}

		if (found) allPossibleMove.emplace_back(curPos.x, curPos.y - i);
		i++;
	}

	// down
	i = 1;
	found = 0;
	skipOne = false;
	isEnemy = false;
	while (curPos.x >= 0 && curPos.x <= 8 && curPos.y + i <= 9) {
		for (int j = 0; j < on_board.size(); j++) {
			if (curPos.x == on_board[j]->curPos.x && curPos.y + i == on_board[j]->curPos.y) {
				found++;

				if (found >= 2 && side != on_board[j]->side) isEnemy = true;
				else skipOne = true;

				break;
			}
		}

		if (skipOne) {
			skipOne = false;
			i++;
			continue;
		}

		if (found >= 2) {
			if (isEnemy) allPossibleMove.emplace_back(curPos.x, curPos.y + i);
			break;
		}

		if (found) allPossibleMove.emplace_back(curPos.x, curPos.y + i);
		i++;
	}

	// left
	i = 1;
	found = 0;
	skipOne = false;
	isEnemy = false;
	while (curPos.x >= 0 && curPos.x <= 8 && curPos.x - i >= 0) {
		for (int j = 0; j < on_board.size(); j++) {
			if (curPos.x - i == on_board[j]->curPos.x && curPos.y == on_board[j]->curPos.y) {
				found++;

				if (found >= 2 && side != on_board[j]->side) isEnemy = true;
				else skipOne = true;

				break;
			}
		}

		if (skipOne) {
			skipOne = false;
			i++;
			continue;
		}

		if (found >= 2) {
			if (isEnemy) allPossibleMove.emplace_back(curPos.x - i, curPos.y);
			break;
		}

		if (found) allPossibleMove.emplace_back(curPos.x - i, curPos.y);
		i++;
	}

	// right
	i = 1;
	found = 0;
	skipOne = false;
	isEnemy = false;
	while (curPos.x >= 0 && curPos.x <= 8 && curPos.x + i <= 8) {
		for (int j = 0; j < on_board.size(); j++) {
			if (curPos.x + i == on_board[j]->curPos.x && curPos.y == on_board[j]->curPos.y) {
				found++;

				if (found >= 2 && side != on_board[j]->side) isEnemy = true;
				else skipOne = true;

				break;
			}
		}

		if (skipOne) {
			skipOne = false;
			i++;
			continue;
		}

		if (found >= 2) {
			if (isEnemy) allPossibleMove.emplace_back(curPos.x + i, curPos.y);
			break;
		}

		if (found) allPossibleMove.emplace_back(curPos.x + i, curPos.y);
		i++;
	}
}