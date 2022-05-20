// WindowsProject1.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "main.h"
#include "resource.h"
#include <string>
#include <commdlg.h>

#include "Viewer.h"
#include "MenuManager.h"
#include "GameManager.h"
#include "Chess.h"

#define MAX_LOADSTRING 100


// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
HWND hWnd;                                      // for window
Viewer viewer;                                  // for GUI
MenuManager mainMenu;                           // for Main Menu
GameManager* gameManager = nullptr;             // for Game Manager
Chess chess;                                    // for chess pieces
bool appRunning = true;                         // game is running

// Windows Project given template
// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDOWSPROJECT1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);

        // Open file explorer when want to select file
        if (mainMenu.openFile) {
            // Get file path
            auto path = mainMenu.openFileName();

            // User didn't select any file
            if (path.empty()) {
                mainMenu.openFile = false;
                continue;
            }

            // Open file
            std::ifstream file(path);

            if (!file.good()) continue;

            // Copy file contents to the reader vector
            char line[99];
            while (file.getline(line, 99)) {
                std::vector<int> data;
                for (auto& i : line) {
                    if (i >= '0' && i <= '9')
                        data.emplace_back(i - '0');
                }
                mainMenu.reader.emplace_back(data[0], data[1], data[2], data[3], data[4]);
            }
            file.close();

            // Create a game manager to play file and refresh variables to read file
            mainMenu.gmDummy = new GameManager;
            mainMenu.isReading = true;
            mainMenu.openFile = false;
        }

    }
    viewer.endAll();

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW | CS_CLASSDC;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = NULL;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW ^ WS_MAXIMIZEBOX,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd) return FALSE;

   // Initialize all display
   viewer.directx.InitDisplay(hWnd);

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    // Handle imgui menu input
    if (!appRunning)
        message = WM_DESTROY;
    else {
        extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND, UINT, WPARAM, LPARAM);
        if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
            return true;
    }

    switch (message)
    {
    case WM_PAINT:
    {
        // The game is here
        // Start rendering the menu
        viewer.render();
        {
            if (appRunning) {
                // Main Menu or Gameplay
                static bool startGame = false, newGame = false;

                // Main Menu
                if (!startGame) {
                    // Starting new game right away, delete last Game Manager
                    if (gameManager && gameManager->startNewGame == true) {
                        delete gameManager;
                        gameManager = nullptr;
                        startGame = true;
                        newGame = true;
                    }
                    else {
                        // Stay in main menu
                        if (mainMenu.isReading == false && mainMenu.isLoading == false) {
                            mainMenu.createMainMenu(appRunning, startGame);
                            mainMenu.viewer.endWindow();
                            if (startGame) newGame = true;
                            // Delete Game Manager if exist
                            if (gameManager) {
                                delete gameManager;
                                gameManager = nullptr;
                            }
                        }
                        else if (mainMenu.isLoading == true) {
                            // Load file
                            if (gameManager) delete gameManager;
                            gameManager = mainMenu.loadGameMenu(appRunning, startGame);
                            newGame = true;
                        }
                        else if (mainMenu.isReading == true) {
                            // Read file
                            mainMenu.readFile(appRunning);
                        }
                    }
                }

                // Gameplay
                if (startGame) {
                    // Refresh log file
                    if (newGame) {
                        GameManager::logFile.open("logFile.txt");
                        newGame = false;
                    }
                    // Create new game
                    if (!gameManager) gameManager = new GameManager;
                    gameManager->createGameBoard(appRunning, startGame);
                    viewer.endWindow();
                }
            }
        }
        viewer.endRender();
    }
    break;
    // Handle render buffer size to window size
    case WM_SIZE:
    {
        viewer.directx.onResize(wParam,lParam);
        break;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

#if !UNICODE
string openfilename(const TCHAR* filter) {
#else
std::wstring MenuManager::openFileName(const TCHAR* filter) {
#endif

    OPENFILENAME ofn{};
    TCHAR fileName[MAX_PATH]{};
    
    ofn.lStructSize = sizeof ofn;
    ofn.hwndOwner = hWnd;
    ofn.lpstrFilter = filter;
    ofn.lpstrFile = fileName;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
    ofn.lpstrDefExt = TEXT("");;

#if !UNICODE
    string fileNameStr;
#else
    std::wstring fileNameStr;
#endif;

    if (GetOpenFileName(&ofn))
        fileNameStr = fileName;

    return fileNameStr;
}