#pragma once

#include "framework.h"
#include "WindowsProject1.h"

class Viewer;

class Window {
public:
	static LRESULT CALLBACK Proc ( HWND, UINT, WPARAM, LPARAM ) noexcept;

	Window ( HINSTANCE, INT ) noexcept;
	~Window () noexcept;

	Window ( Window&& ) = delete;
	Window ( const Window& ) = delete;
	Window& operator=( Window&& ) = delete;
	Window& operator=( const Window& ) = delete;

	[[nodiscard]] INT run ( Viewer&, void( *callback )( ) ) noexcept;

	HINSTANCE instance;
	WCHAR text[64];          
	WCHAR className[64];
	WNDCLASSEX classEx;
	HWND handle;
	MSG message;
	TCHAR path[MAX_PATH];
	bool running;
};