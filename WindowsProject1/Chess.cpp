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

Chess::Chess() {}

void Chess::updateAllPossibleMove() {
	// override in child class
}

void Chess::renderAllPossibleMove() {
	// override in child class
}