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
	}
	else if (name == "blackCannonBtn") {
		side = Side::BLACK;
		rank = Rank::CANNON;
		curPos.x = x;
		curPos.y = y;
		img = &viewer.chessBlackCannon;
	}
}