#pragma once
#include "main.h"
#include <iostream>
#include <unordered_map>

class Viewer {
public:
    // Struct for image texture
    struct Texture {
        void create(const char* fileName);
        void create(const wchar_t* fileName);
		LPDIRECT3DTEXTURE9& operator()();
    private:
        LPDIRECT3DTEXTURE9 data;
    };

    // Class for buttons
	class Button {
	private:
		bool isClicked = false;
		std::string id;
		static std::unordered_map<std::string, bool>mainMenuHover;
	public:
		enum class Type { MAINMENU, CIRCLE };
		Type buttonType;

		// Constructor
		Button();
		Button(const char*, Type);
		Button(const char*, Texture, Texture, Type);

		~Button();

		operator bool()const;
	};

	// Class for DirectX9
	class DirectX {
	public:
		// Global Variables for directx 9:
		static LPDIRECT3D9			 direct3D9;
		static LPDIRECT3DDEVICE9	 direct3DDevice9;
		static D3DPRESENT_PARAMETERS direct3DParams;
	public:
		// DirectX Functions
		static BOOL CreateDeviceD3D(HWND hWnd);
		static BOOL InitDisplay ( HWND );
		static VOID CleanupDeviceD3D ();
		static VOID ResetDevice ();
		static VOID onResize ( WPARAM, LPARAM ) noexcept;
	};

	// Viewer functions
	Viewer();
	void render();
	void endRender();
	void endAll();
	ImVec2 createWindow(bool&, Texture);
	void endWindow();
	void setButtonPos(float, float);

public:
	std::unordered_map<std::string, Texture> textures;
};