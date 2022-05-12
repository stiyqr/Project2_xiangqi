#include "GameManager.h"

GameManager& GameManager::instance () noexcept {
	static GameManager gameManager;
	return gameManager;
}

GameManager::~GameManager () noexcept {

	viewer.reset ();
	window.reset ();
}