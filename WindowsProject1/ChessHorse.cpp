#include "ChessHorse.h"
#include "Viewer.h"

ChessHorse::ChessHorse() {}

ChessHorse::ChessHorse(const char* name, int x, int y) {
	id = name;

	if (name == "redHorseBtn") {
		side = Side::RED;
		rank = Rank::HORSE;
		curPos.x = x;
		curPos.y = y;
		img = &viewer.chessRedHorse;
	}
	else if (name == "blackHorseBtn") {
		side = Side::BLACK;
		rank = Rank::HORSE;
		curPos.x = x;
		curPos.y = y;
		img = &viewer.chessBlackHorse;
	}
}