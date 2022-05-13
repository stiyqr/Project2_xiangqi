#include "ChessSoldier.h"
#include "Viewer.h"

ChessSoldier::ChessSoldier() {}

ChessSoldier::ChessSoldier(const char* name, int x, int y) {
	id = name;

	if (name == "redSoldierBtn") {
		side = Side::RED;
		rank = Rank::SOLDIER;
		curPos.x = x;
		curPos.y = y;
		img = &viewer.chessRedSoldier;
	}
	else if (name == "blackSoldierBtn") {
		side = Side::BLACK;
		rank = Rank::SOLDIER;
		curPos.x = x;
		curPos.y = y;
		img = &viewer.chessBlackSoldier;
	}
}