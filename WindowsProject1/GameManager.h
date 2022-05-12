#pragma once

#include "Window.h"
#include "Viewer.h"

class GameManager {
public:
	static GameManager& instance () noexcept;

	GameManager ( GameManager&& ) = delete;
	GameManager ( const GameManager& ) = delete;
	GameManager& operator=( GameManager&& ) = delete;
	GameManager& operator=( const GameManager& ) = delete;

	std::unique_ptr<Window> window;
	std::unique_ptr<Viewer> viewer;

private:
	GameManager () = default;
	~GameManager() noexcept;
};