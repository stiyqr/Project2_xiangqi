#pragma once

#include "framework.h"

#include <d3d9.h>
#pragma comment (lib,"d3d9.lib")

#include <d3dx9.h>
#pragma comment (lib,"d3dx9.lib")

class Viewer {
public:

	Viewer ( HWND ) noexcept;
	~Viewer () noexcept;

	Viewer ( Viewer&& ) = delete;
	Viewer ( const Viewer& ) = delete;
	Viewer& operator=( Viewer&& ) = delete;
	Viewer& operator=( const Viewer& ) = delete;

	void run () noexcept;
	void reset () noexcept;

	LPDIRECT3D9             Direct3D9;
	LPDIRECT3DDEVICE9       Direct3DDevice9;
	D3DPRESENT_PARAMETERS   Direct3DParams;
};