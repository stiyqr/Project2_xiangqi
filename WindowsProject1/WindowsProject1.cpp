// WindowsProject1.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "WindowsProject1.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx9.h"
#include "imgui/imgui_impl_win32.h"

#define MAX_LOADSTRING 100
#define IMGUI_DEFINE_MATH_OPERATORS

#include "imgui/imgui_internal.h"
#include <d3dx9.h>
#pragma comment (lib, "d3dx9.lib")
#include <d3d9.h>
#pragma comment (lib,"d3d9.lib")
#include "Button.h"

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

// Global Variables for directx 9:
LPDIRECT3D9              direct3D9;
LPDIRECT3DDEVICE9        direct3DDevice9;
D3DPRESENT_PARAMETERS    direct3DParams;

struct Texture {
    void create(CONST TCHAR* fileName);//啊
    auto& operator()() { return data; }
private:
    LPDIRECT3DTEXTURE9 data;
};

Texture background;

// Forward declarations of functions for directx 9:
BOOL CreateDeviceD3D(HWND hWnd);
VOID CleanupDeviceD3D();
VOID ResetDevice();

// Global Variables for imgui:
bool ImGuiMenu = true;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

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

        // Start the Dear ImGui frame
        ImGui_ImplDX9_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();
        {
            // Initialize main frame fullscreen
            auto& io = ImGui::GetIO();
            ImGui::SetNextWindowSize(io.DisplaySize, ImGuiCond_Always);
            ImGui::SetNextWindowPos(ImVec2{ 0,0 }, ImGuiCond_Always);

            // Start rendering the menu through imgui functions
            if (ImGuiMenu) {

                static bool startGame = false;
                if (!startGame) {
                    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{});
                    if (ImGui::Begin("##Hello", &ImGuiMenu, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize)) {
                        auto screenSize = ImGui::GetContentRegionAvail();
                        ImGui::Image(background(), screenSize);

                        // Set button position and style
                        float middle_x = (screenSize.x / 2) - 100;
                        float middle_y = (screenSize.y / 2) + 90;

                        // make Read File button
                        ImGui::SetCursorPos(ImVec2(middle_x - 300, middle_y));
                        Button readFileButton("Read File", Button::Type::MAINMENU);

                        // make Start Game button
                        ImGui::SetCursorPos(ImVec2(middle_x, middle_y));
                        Button startGameButton("Start Game", Button::Type::MAINMENU);

                        // make Exit Game button
                        ImGui::SetCursorPos(ImVec2(middle_x + 300, middle_y));
                        Button exitGameButton("Exit Game", Button::Type::MAINMENU);

                        // Button click processes
                        if (startGameButton) {
                            startGame = true;
                        }
                        else if (exitGameButton) {
                            ImGuiMenu = false;
                        }
                    }
                    ImGui::End();
                    ImGui::PopStyleVar();
                }

                if (startGame) {
                    ImGui::Begin("begin2", &ImGuiMenu, ImGuiWindowFlags_NoResize);
                    {
                        Button button2("button2", Button::Type::MAINMENU);
                        if (button2) {
                            startGame = false;
                        }
                    }
                    ImGui::End();
                }
            }

            ImGui::ShowDemoWindow();
        }
        ImGui::EndFrame();

        // Rendering through directx9
        direct3DDevice9->SetRenderState(D3DRS_ZENABLE, FALSE);
        direct3DDevice9->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
        direct3DDevice9->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);
        direct3DDevice9->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR(), 1.f, 0);

        if (direct3DDevice9->BeginScene() >= 0) {
            ImGui::Render();
            ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
            direct3DDevice9->EndScene();
        }

        HRESULT result = direct3DDevice9->Present(NULL, NULL, NULL, NULL);
        // Handle loss of D3D9 device
        if (result == D3DERR_DEVICELOST && direct3DDevice9->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
            ResetDevice();
    }

    ImGui_ImplDX9_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    CleanupDeviceD3D();

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

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd) return FALSE;

   // Initialize Direct3D
   if (!CreateDeviceD3D(hWnd)) {
       CleanupDeviceD3D();
       return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   ImGui::CreateContext();
   ImGui::StyleColorsDark();

   ImGui_ImplWin32_Init(hWnd);
   ImGui_ImplDX9_Init(direct3DDevice9);

   // Initialize background texture
   background.create(TEXT("D:\\dayi\\OOP\\PROJECT 2 xiangqi\\assets\\mainmenu.png"));

   // Initialize font
   auto& io = ImGui::GetIO();
   io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\tahoma.ttf", 20);

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
    if (message == WM_KEYDOWN) {
        if (wParam == VK_HOME)
            message = WM_DESTROY;
    }

    // Handle imgui menu input
    if (!ImGuiMenu)
        message = WM_DESTROY;
    else {
        extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND, UINT, WPARAM, LPARAM);
        if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
            return true;
    }

    switch (message)
    {
    // Handle render buffer size to window size
    case WM_SIZE:
    {
        if (direct3DDevice9 != NULL && wParam != SIZE_MINIMIZED) {
            direct3DParams.BackBufferWidth = LOWORD(lParam);
            direct3DParams.BackBufferHeight = HIWORD(lParam);
            ResetDevice();
        }
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

BOOL CreateDeviceD3D(HWND hWnd) {

    if ((direct3D9 = Direct3DCreate9(D3D_SDK_VERSION)) == NULL)
        return FALSE;

    // Create the D3DDevice
    ZeroMemory(&direct3DParams, sizeof(direct3DParams));
    direct3DParams.Windowed = TRUE;
    direct3DParams.SwapEffect = D3DSWAPEFFECT_DISCARD;
    direct3DParams.BackBufferFormat = D3DFMT_UNKNOWN; // Need to use an explicit format with alpha if needing per-pixel alpha composition.
    direct3DParams.EnableAutoDepthStencil = TRUE;
    direct3DParams.AutoDepthStencilFormat = D3DFMT_D16;
    direct3DParams.PresentationInterval = D3DPRESENT_INTERVAL_ONE;           // Present with vsync
    //g_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;   // Present without vsync, maximum unthrottled framerate
    if (direct3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &direct3DParams, &direct3DDevice9) < 0)
        return FALSE;

    return TRUE;
}

VOID CleanupDeviceD3D() {

    if (direct3DDevice9) { direct3DDevice9->Release(); direct3DDevice9 = NULL; }
    if (direct3D9) { direct3D9->Release(); direct3D9 = NULL; }
}

VOID ResetDevice() {

    ImGui_ImplDX9_InvalidateDeviceObjects();

    HRESULT hr = direct3DDevice9->Reset(&direct3DParams);
    if (hr == D3DERR_INVALIDCALL)
        IM_ASSERT(0);

    ImGui_ImplDX9_CreateDeviceObjects();
}

VOID Texture::create(CONST TCHAR* fileName) {
    assert(D3DXCreateTextureFromFile(direct3DDevice9, fileName, &this->data) == S_OK);
    
}