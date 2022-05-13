#include "ChessGeneral.h"
#include "Viewer.h"

ChessGeneral::ChessGeneral() {}

ChessGeneral::ChessGeneral(const char* name) {
	id = name;

	if (name == "redGeneralBtn") {
		side = Side::RED;
		rank = Rank::GENERAL;
		curPos.x = 4;
		curPos.y = 9;
		img = &viewer.chessRedGeneral;
		moveImg = &viewer.possibleRed;
	}
	else if (name == "blackGeneralBtn") {
		side = Side::BLACK;
		rank = Rank::GENERAL;
		curPos.x = 4;
		curPos.y = 0;
		img = &viewer.chessBlackGeneral;
		moveImg = &viewer.possibleBlack;
	}
}

void ChessGeneral::updateAllPossibleMove() {
	allPossibleMove.clear();

	// up, down, left, right
	if (curPos.y > 0) allPossibleMove.emplace_back(curPos.x, curPos.y - 1);
	if (curPos.y < 9) allPossibleMove.emplace_back(curPos.x, curPos.y + 1);
	if (curPos.x > 0) allPossibleMove.emplace_back(curPos.x - 1, curPos.y);
	if (curPos.x < 8) allPossibleMove.emplace_back(curPos.x + 1, curPos.y);
}