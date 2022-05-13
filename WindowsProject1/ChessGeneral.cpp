#include "ChessGeneral.h"
#include "Viewer.h"

ChessGeneral::ChessGeneral() {}

ChessGeneral::ChessGeneral(const char* name) {
	id = name;

	if (name == "redGeneralBtn") {
		side = Side::RED;
		curPosX = 4;
		curPosY = 9;
		img = &viewer.chessRedGeneral;
	}
	else if (name == "blackGeneralBtn") {
		side = Side::BLACK;
		curPosX = 4;
		curPosY = 0;
		img = &viewer.chessBlackGeneral;
	}
}