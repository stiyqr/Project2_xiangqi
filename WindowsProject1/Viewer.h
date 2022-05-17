#pragma once
#include "main.h"
#include <iostream>
#include <unordered_map>

class Viewer {
public:
    // Struct for image texture
    struct Texture {
        void create(CONST TCHAR* fileName);
		auto& operator()();
    private:
        LPDIRECT3DTEXTURE9 data;
    };

    // Class for buttons
	class Button {
	private:
		bool isClicked = false;
		std::string id;
		static std::unordered_map<std::string, bool>mainMenuHover, saveSlotHover;
	public:
		enum class Type { MAINMENU, CIRCLE, SAVESLOT };
		Type buttonType;

		// Constructor
		Button();
		Button(const char*, Texture, Texture, Type, float = 1);

		// Destructor
		~Button();

		// Overload
		operator bool()const;
	};

	// Class for DirectX9
	class DirectX {
	public:
		// Global Variables for directx 9:
		LPDIRECT3D9					direct3D9;
		static LPDIRECT3DDEVICE9	direct3DDevice9;
		D3DPRESENT_PARAMETERS		direct3DParams;
		Viewer& imgs;

	public:
		// Constructor
		DirectX(Viewer&);

		// Functions
		BOOL CreateDeviceD3D(HWND hWnd);
		BOOL InitDisplay(HWND);
		VOID InitImgs();
		VOID CleanupDeviceD3D();
		VOID ResetDevice();
		VOID onResize(WPARAM, LPARAM)noexcept;
	};

	// Class for ID to differentiate ImGui widgets
	class ID {
	public:
		ID(int);
		~ID();
	};

	// Viewer functions
	Viewer();
	void render();
	void endRender();
	void endAll();
	ImVec2 createWindow(bool&, Texture);
	void endWindow();
	void setButtonPos(float, float);
	void setButtonPos(const ImVec2&);
	ImVec2 getCursorPos();
	void makeExtraWindow();
	void endExtraWindow();
	void addWindowImage(Texture);
	void addText(const char*);
	ImGuiIO& getData();

public:
	DirectX directx;

	// Textures
	/////////////// Main Menu ///////////////
	static Texture backgroundMenu;
	static Texture backgroundLoadGame;
	static Texture buttonStartGameImg;
	static Texture buttonExitGameImg;
	static Texture buttonReadFileImg;
	static Texture buttonStartGameHoverImg;
	static Texture buttonExitGameHoverImg;
	static Texture buttonReadFileHoverImg;
	static Texture buttonLoadGameImg;
	static Texture buttonLoadGameHoverImg;
	static Texture buttonLogReplayImg;
	static Texture buttonLogReplayHoverImg;

	/////////////// Gameplay ///////////////
	// Backgrounds
	static Texture backgroundGame;
	static Texture backgroundSaveGame;
	static Texture backgroundRedWin;
	static Texture backgroundBlackWin;
	static Texture backgroundCheck;
	static Texture backgroundCheckmate;
	static Texture backgroundStalemate;

	// Buttons
	static Texture buttonBackToMenuImg;
	static Texture buttonBackToMenuHoverImg;
	static Texture buttonPlayAgainImg;
	static Texture buttonPlayAgainHoverImg;
	static Texture buttonSurrenderImg;
	static Texture buttonSurrenderHoverImg;
	static Texture buttonExitBoardImg;
	static Texture buttonExitBoardHoverImg;
	static Texture buttonSaveGameImg;
	static Texture buttonSaveGameHoverImg;
	static Texture buttonSave1Img;
	static Texture buttonSave2Img;
	static Texture buttonSave3Img;
	static Texture buttonSave1HoverImg;
	static Texture buttonSave2HoverImg;
	static Texture buttonSave3HoverImg;

	/////////////// Chess pieces ///////////////
	static Texture chessRedGeneral;
	static Texture chessRedElephant;
	static Texture chessRedAdvisor;
	static Texture chessRedCannon;
	static Texture chessRedChariot;
	static Texture chessRedHorse;
	static Texture chessRedSoldier;
	static Texture chessBlackGeneral;
	static Texture chessBlackElephant;
	static Texture chessBlackAdvisor;
	static Texture chessBlackCannon;
	static Texture chessBlackChariot;
	static Texture chessBlackHorse;
	static Texture chessBlackSoldier;

	// Possible move chess piece
	static Texture possibleRed;
	static Texture possibleBlack;
};