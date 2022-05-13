#include "ChessAdvisor.h"
#include "Viewer.h"

ChessAdvisor::ChessAdvisor() {}

ChessAdvisor::ChessAdvisor(const char* name, int x, int y) {
	if (name == "redAdvisorBtn") {
		side = Side::RED;
		rank = Rank::ADVISOR;
		curPos.x = x;
		curPos.y = y;
		img = &viewer.chessRedAdvisor;
		moveImg = &viewer.possibleRed;
	}
	else if (name == "blackAdvisorBtn") {
		side = Side::BLACK;
		rank = Rank::ADVISOR;
		curPos.x = x;
		curPos.y = y;
		img = &viewer.chessBlackAdvisor;
		moveImg = &viewer.possibleBlack;
	}
}

void ChessAdvisor::updateAllPossibleMove(std::vector<Chess*>on_board) {
	allPossibleMove.clear();

	if (side == Side::RED) {
		if (curPos.x > 3) {
			if (curPos.y > 7) allPossibleMove.emplace_back(curPos.x - 1, curPos.y - 1);
			if (curPos.y < 9) allPossibleMove.emplace_back(curPos.x - 1, curPos.y + 1);
		}
		if (curPos.x < 5) {
			if (curPos.y > 7) allPossibleMove.emplace_back(curPos.x + 1, curPos.y - 1);
			if (curPos.y < 9) allPossibleMove.emplace_back(curPos.x + 1, curPos.y + 1);
		}
	}
	else if (side == Side::BLACK) {
		if (curPos.x > 3) {
			if (curPos.y > 0) allPossibleMove.emplace_back(curPos.x - 1, curPos.y - 1);
			if (curPos.y < 2) allPossibleMove.emplace_back(curPos.x - 1, curPos.y + 1);
		}
		if (curPos.x < 5) {
			if (curPos.y > 0) allPossibleMove.emplace_back(curPos.x + 1, curPos.y - 1);
			if (curPos.y < 2) allPossibleMove.emplace_back(curPos.x + 1, curPos.y + 1);
		}
	}
}