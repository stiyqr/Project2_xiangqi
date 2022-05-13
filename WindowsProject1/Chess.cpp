#include "Chess.h"

Chess::Position::Position() {}

Chess::Position::Position(int x, int y) {
	this->x = x;
	this->y = y;
}

Chess::Position& Chess::Position::operator=(Position pos) {
	this->x = pos.x;
	this->y = pos.y;
	return *this;
}

bool Chess::Position::operator==(Position pos) {
	return x == pos.x && y == pos.y;
}

Chess::Chess() {}

void Chess::updateAllPossibleMove(std::vector<Chess*>on_board) {
	// override in child class
}

void Chess::renderAllPossibleMove() {
	// override in child class
}