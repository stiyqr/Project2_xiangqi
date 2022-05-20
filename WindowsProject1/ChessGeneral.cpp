#include "ChessGeneral.h"
#include "Viewer.h"

/////////////// Constructors ///////////////
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

ChessGeneral::ChessGeneral(const char* name, int x, int y) {
	id = name;

	if (name == "redGeneralBtn") {
		side = Side::RED;
		rank = Rank::GENERAL;
		curPos.x = x;
		curPos.y = y;
		img = &viewer.chessRedGeneral;
		moveImg = &viewer.possibleRed;
	}
	else if (name == "blackGeneralBtn") {
		side = Side::BLACK;
		rank = Rank::GENERAL;
		curPos.x = x;
		curPos.y = y;
		img = &viewer.chessBlackGeneral;
		moveImg = &viewer.possibleBlack;
	}
}

/////////////// Functions ///////////////
// Intent: update general's possible moves
// Pre: pass the vector of all the current pieces on board
// Post: general's possible moves are updated
void ChessGeneral::updateAllPossibleMove(std::vector<Chess*>on_board) {
	allPossibleMove.clear();

	if (side == Side::RED) {
		if (curPos.y < 9 && curPos.x >= 3 && curPos.x <= 5) allPossibleMove.emplace_back(curPos.x, curPos.y + 1);
		if (curPos.y > 7 && curPos.x >= 3 && curPos.x <= 5) allPossibleMove.emplace_back(curPos.x, curPos.y - 1);
		if (curPos.x > 3 && curPos.y >= 7 && curPos.y <= 9) allPossibleMove.emplace_back(curPos.x - 1, curPos.y);
		if (curPos.x < 5 && curPos.y >= 7 && curPos.y <= 9) allPossibleMove.emplace_back(curPos.x + 1, curPos.y);
	}
	else if (side == Side::BLACK) {
		if (curPos.y < 2 && curPos.x >= 3 && curPos.x <= 5) allPossibleMove.emplace_back(curPos.x, curPos.y + 1);
		if (curPos.y > 0 && curPos.x >= 3 && curPos.x <= 5) allPossibleMove.emplace_back(curPos.x, curPos.y - 1);
		if (curPos.x > 3 && curPos.y >= 0 && curPos.y <= 2) allPossibleMove.emplace_back(curPos.x - 1, curPos.y);
		if (curPos.x < 5 && curPos.y >= 0 && curPos.y <= 2) allPossibleMove.emplace_back(curPos.x + 1, curPos.y);
	}
}