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
	}
	else if (name == "blackGeneralBtn") {
		side = Side::BLACK;
		rank = Rank::GENERAL;
		curPos.x = 4;
		curPos.y = 0;
		img = &viewer.chessBlackGeneral;
	}
}