#include "Viewer.h"

///////////////////////////////////////////////////// Texture /////////////////////////////////////////////////////

void Viewer::Texture::create ( const char* fileName ) {
    assert ( D3DXCreateTextureFromFileA ( DirectX::direct3DDevice9, fileName, &this->data ) == S_OK );
}

void Viewer::Texture::create ( const wchar_t* fileName ) {
    assert ( D3DXCreateTextureFromFileW ( DirectX::direct3DDevice9, fileName, &this->data ) == S_OK );
}

LPDIRECT3DTEXTURE9& Viewer::Texture::operator()() { return data; }

///////////////////////////////////////////////////// Button /////////////////////////////////////////////////////

std::unordered_map<std::string, bool> Viewer::Button::mainMenuHover;

Viewer::Button::Button() {}

Viewer::Button::Button(const char* name, Type type) {
    if (type == Type::MAINMENU) {
        buttonType = Type::MAINMENU;
        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 6);
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ ImColor{139, 129, 119, 0} });
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ ImColor{100, 93, 85, 0} });
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ ImColor{69, 63, 57, 0} });
        isClicked = ImGui::Button(name, ImVec2(200, 50));
    }
    else if (type == Type::CIRCLE) {
        buttonType = Type::CIRCLE;
        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 50);
        isClicked = ImGui::Button(name, ImVec2(100, 100));

    }
}

Viewer::Button::Button(const char* id, Texture img, Texture img2, Type type) {
    if (type == Type::MAINMENU) {
        buttonType = Type::MAINMENU;
        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 50);
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ ImColor{139, 129, 119, 0} });
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ ImColor{255, 231, 0, 0} });
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ ImColor{255, 255, 255, 0} });
        isClicked = ImGui::ImageButton(mainMenuHover[id] ? img2() : img(), ImVec2(200, 50));
        mainMenuHover[id] = ImGui::IsItemHovered();
    }
}

// Destructor
Viewer::Button::~Button() {
    if (buttonType == Type::MAINMENU) {
        ImGui::PopStyleVar();
        ImGui::PopStyleColor(3);
    }
    else ImGui::PopStyleVar();
}

Viewer::Button::operator bool()const { return isClicked; }

///////////////////////////////////////////////////// DirectX9 /////////////////////////////////////////////////////

// Initialize static variable
LPDIRECT3D9			    Viewer::DirectX::direct3D9;
LPDIRECT3DDEVICE9	    Viewer::DirectX::direct3DDevice9;
D3DPRESENT_PARAMETERS   Viewer::DirectX::direct3DParams;

BOOL Viewer::DirectX::CreateDeviceD3D(HWND hWnd) {

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

VOID Viewer::DirectX::CleanupDeviceD3D() {

    if (direct3DDevice9) { direct3DDevice9->Release(); direct3DDevice9 = NULL; }
    if (direct3D9) { direct3D9->Release(); direct3D9 = NULL; }
}

VOID Viewer::DirectX::ResetDevice() {

    ImGui_ImplDX9_InvalidateDeviceObjects();

    HRESULT hr = direct3DDevice9->Reset(&direct3DParams);
    if (hr == D3DERR_INVALIDCALL)
        IM_ASSERT(0);

    ImGui_ImplDX9_CreateDeviceObjects();
}

BOOL Viewer::DirectX::InitDisplay(HWND hWnd) {

    // Initialize Direct3D
    if (!CreateDeviceD3D(hWnd)) {
        CleanupDeviceD3D();
        return FALSE;
    }

    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGui_ImplWin32_Init(hWnd);
    ImGui_ImplDX9_Init(direct3DDevice9);

    // Initialize font
    auto& io = ImGui::GetIO();
    io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\tahoma.ttf", 20);

    return TRUE;
}

void Viewer::DirectX::onResize(WPARAM wParam, LPARAM lParam)noexcept {
    if (!direct3DDevice9 || wParam == SIZE_MINIMIZED) return;

    // Handle render buffer size to window size
    direct3DParams.BackBufferWidth = LOWORD(lParam);
    direct3DParams.BackBufferHeight = HIWORD(lParam);
    ResetDevice();
}


///////////////////////////////////////////////////// Viewer Functions /////////////////////////////////////////////////////

Viewer::Viewer () { }

void Viewer::render() {
    // Start the Dear ImGui frame
    ImGui_ImplDX9_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    // Initialize main frame fullscreen window
    auto& io = ImGui::GetIO();
    ImGui::SetNextWindowSize(io.DisplaySize, ImGuiCond_Always);
    ImGui::SetNextWindowPos(ImVec2{ 0,0 }, ImGuiCond_Always);
}

void Viewer::endRender() {
    ImGui::EndFrame();

    // Rendering through directx9
    DirectX::direct3DDevice9->SetRenderState(D3DRS_ZENABLE, FALSE);
    DirectX::direct3DDevice9->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
    DirectX::direct3DDevice9->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);
    DirectX::direct3DDevice9->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR(), 1.f, 0);

    if ( DirectX::direct3DDevice9->BeginScene() >= 0) {
        ImGui::Render();
        ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
        DirectX::direct3DDevice9->EndScene();
    }

    HRESULT result = DirectX::direct3DDevice9->Present(NULL, NULL, NULL, NULL);
    // Handle loss of D3D9 device
    if (result == D3DERR_DEVICELOST && DirectX::direct3DDevice9->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
        DirectX::ResetDevice();
}

void Viewer::endAll() {
    ImGui_ImplDX9_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    DirectX::CleanupDeviceD3D();
}

ImVec2 Viewer::createWindow(bool& appRunning, Texture background) {
    // Main Menu's window settings
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{});
    ImGui::Begin("##MainMenu", &appRunning, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);

    // Set background
    ImVec2 screenSize = ImGui::GetContentRegionAvail();
    float middle_x = (screenSize.x / 2) - 100;
    float middle_y = (screenSize.y / 2) + 90;
    ImGui::Image(background(), screenSize);

    return screenSize;
}

void Viewer::endWindow() {
    ImGui::End();
    ImGui::PopStyleVar();
}

void Viewer::setButtonPos(float x, float y) {
    ImGui::SetCursorPos(ImVec2(x, y));
}