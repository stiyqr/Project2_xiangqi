#include "ChessAdvisor.h"
#include "Viewer.h"

ChessAdvisor::ChessAdvisor() {}

ChessAdvisor::ChessAdvisor(const char* name, int x, int y) {
	if (name == "redAdvisorBtn") {
		side = Side::RED;
		rank = Rank::ADVISOR;
		curPos.x = x;
		curPos.y = y;
		img = &viewer.chessRedAdvisor;
	}
	else if (name == "blackAdvisorBtn") {
		side = Side::BLACK;
		rank = Rank::ADVISOR;
		curPos.x = x;
		curPos.y = y;
		img = &viewer.chessBlackAdvisor;
	}
}