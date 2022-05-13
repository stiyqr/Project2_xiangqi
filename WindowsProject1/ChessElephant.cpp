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
	}
	else if (name == "blackElephantBtn") {
		side = Side::BLACK;
		rank = Rank::ELEPHANT;
		curPos.x = x;
		curPos.y = y;
		img = &viewer.chessBlackElephant;
	}
}