#include "ChessSoldier.h"
#include "Viewer.h"

/////////////// Constructors ///////////////
ChessSoldier::ChessSoldier() {}

ChessSoldier::ChessSoldier(const char* name, int x, int y) {
	id = name;

	if (name == "redSoldierBtn") {
		side = Side::RED;
		rank = Rank::SOLDIER;
		curPos.x = x;
		curPos.y = y;
		img = &viewer.chessRedSoldier;
		moveImg = &viewer.possibleRed;
	}
	else if (name == "blackSoldierBtn") {
		side = Side::BLACK;
		rank = Rank::SOLDIER;
		curPos.x = x;
		curPos.y = y;
		img = &viewer.chessBlackSoldier;
		moveImg = &viewer.possibleBlack;
	}
}

/////////////// Functions ///////////////
// Intent: update soldier's possible moves
// Pre: pass the vector of all the current pieces on board
// Post: soldier's possible moves are updated
void ChessSoldier::updateAllPossibleMove(std::vector<Chess*>on_board) {
	allPossibleMove.clear();

	if (side == Side::RED) {
		if (curPos.y > 0) allPossibleMove.emplace_back(curPos.x, curPos.y - 1);

		if (curPos.y < 5) {
			if (curPos.x > 0) allPossibleMove.emplace_back(curPos.x - 1, curPos.y);
			if (curPos.x < 8) allPossibleMove.emplace_back(curPos.x + 1, curPos.y);
		}
	}
	else if (side == Side::BLACK) {
		if (curPos.y < 9) allPossibleMove.emplace_back(curPos.x, curPos.y + 1);

		if (curPos.y > 4) {
			if (curPos.x > 0) allPossibleMove.emplace_back(curPos.x - 1, curPos.y);
			if (curPos.x < 8) allPossibleMove.emplace_back(curPos.x + 1, curPos.y);
		}
	}
}