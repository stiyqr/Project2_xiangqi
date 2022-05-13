#include "ChessChariot.h"
#include "Viewer.h"

ChessChariot::ChessChariot() {}

ChessChariot::ChessChariot(const char* name, int x, int y) {
	id = name;

	if (name == "redChariotBtn") {
		side = Side::RED;
		rank = Rank::CHARIOT;
		curPos.x = x;
		curPos.y = y;
		img = &viewer.chessRedChariot;
	}
	else if (name == "blackChariotBtn") {
		side = Side::BLACK;
		rank = Rank::CHARIOT;
		curPos.x = x;
		curPos.y = y;
		img = &viewer.chessBlackChariot;
	}
}