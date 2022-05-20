#include "Chess.h"

///////////////////////////////////////////////////// Struct Position /////////////////////////////////////////////////////

/////////////// Constructors ///////////////
// Default constructor
Chess::Position::Position() {}

// Constructor with position input
Chess::Position::Position(int x, int y) {
	this->x = x;
	this->y = y;
}

/////////////// Operator Overloads ///////////////
Chess::Position& Chess::Position::operator=(Position pos) {
	this->x = pos.x;
	this->y = pos.y;
	return *this;
}

bool Chess::Position::operator==(Position pos) {
	return x == pos.x && y == pos.y;
}


///////////////////////////////////////////////////// Chess Class /////////////////////////////////////////////////////

/////////////// Constructors ///////////////
Chess::Chess() {}

/////////////// Functions ///////////////
void Chess::updateAllPossibleMove(std::vector<Chess*>on_board) {
	// override in child class
}