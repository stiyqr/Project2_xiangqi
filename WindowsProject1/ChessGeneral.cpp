#include "ChessGeneral.h"
#include "Viewer.h"

ChessGeneral::ChessGeneral() {}

ChessGeneral::ChessGeneral(const char* name) {
	id = name;

	if (name == "redGeneralBtn") {
		Viewer::Button redGeneralButton(name, viewer.chessRedGeneral, viewer.chessRedGeneral, Viewer::Button::Type::CIRCLE);
	}
	else if (name == "blackGeneralBtn") {
		//Viewer::Button redGeneralButton(name, viewer.chessBlackGeneral, viewer.chessBlackGeneral, Viewer::Button::Type::CIRCLE);
	}
}