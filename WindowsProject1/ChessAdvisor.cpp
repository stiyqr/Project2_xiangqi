#include "ChessAdvisor.h"
#include "GameManager.h"
#include "Viewer.h"

/////////////// Constructors ///////////////
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


/////////////// Functions ///////////////
// Intent: update advisor's possible moves
// Pre: pass the vector of all the current pieces on board
// Post: advisor's possible moves are updated
void ChessAdvisor::updateAllPossibleMove(std::vector<Chess*>on_board) {
	allPossibleMove.clear();

	// If the advisor is on the red side
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
	// If the advisor is on the black side
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