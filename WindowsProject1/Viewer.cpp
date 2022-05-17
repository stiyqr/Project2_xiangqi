#include "Viewer.h"


// Static declaration
/////////////// Main Menu ///////////////
Viewer::Texture Viewer::backgroundMenu;
Viewer::Texture Viewer::backgroundLoadGame;
Viewer::Texture Viewer::buttonStartGameImg;
Viewer::Texture Viewer::buttonExitGameImg;
Viewer::Texture Viewer::buttonReadFileImg;
Viewer::Texture Viewer::buttonStartGameHoverImg;
Viewer::Texture Viewer::buttonExitGameHoverImg;
Viewer::Texture Viewer::buttonReadFileHoverImg;
Viewer::Texture Viewer::buttonLoadGameImg;
Viewer::Texture Viewer::buttonLoadGameHoverImg;
Viewer::Texture Viewer::buttonLogReplayImg;
Viewer::Texture Viewer::buttonLogReplayHoverImg;

/////////////// Gameplay ///////////////
Viewer::Texture Viewer::backgroundGame;
Viewer::Texture Viewer::backgroundSaveGame;
Viewer::Texture Viewer::backgroundRedWin;
Viewer::Texture Viewer::backgroundBlackWin;
Viewer::Texture Viewer::backgroundCheck;
Viewer::Texture Viewer::backgroundCheckmate;
Viewer::Texture Viewer::backgroundStalemate;

Viewer::Texture Viewer::buttonBackToMenuImg;
Viewer::Texture Viewer::buttonBackToMenuHoverImg;
Viewer::Texture Viewer::buttonPlayAgainImg;
Viewer::Texture Viewer::buttonPlayAgainHoverImg;
Viewer::Texture Viewer::buttonSurrenderImg;
Viewer::Texture Viewer::buttonSurrenderHoverImg;
Viewer::Texture Viewer::buttonExitBoardImg;
Viewer::Texture Viewer::buttonExitBoardHoverImg;
Viewer::Texture Viewer::buttonSaveGameImg;
Viewer::Texture Viewer::buttonSaveGameHoverImg;
Viewer::Texture Viewer::buttonSave1Img;
Viewer::Texture Viewer::buttonSave2Img;
Viewer::Texture Viewer::buttonSave3Img;
Viewer::Texture Viewer::buttonSave1HoverImg;
Viewer::Texture Viewer::buttonSave2HoverImg;
Viewer::Texture Viewer::buttonSave3HoverImg;

/////////////// Chess Pieces ///////////////
Viewer::Texture Viewer::chessRedGeneral;
Viewer::Texture Viewer::chessRedElephant;
Viewer::Texture Viewer::chessRedAdvisor;
Viewer::Texture Viewer::chessRedCannon;
Viewer::Texture Viewer::chessRedChariot;
Viewer::Texture Viewer::chessRedHorse;
Viewer::Texture Viewer::chessRedSoldier;
Viewer::Texture Viewer::chessBlackGeneral;
Viewer::Texture Viewer::chessBlackElephant;
Viewer::Texture Viewer::chessBlackAdvisor;
Viewer::Texture Viewer::chessBlackCannon;
Viewer::Texture Viewer::chessBlackChariot;
Viewer::Texture Viewer::chessBlackHorse;
Viewer::Texture Viewer::chessBlackSoldier;

Viewer::Texture Viewer::possibleRed;
Viewer::Texture Viewer::possibleBlack;

///////////////////////////////////////////////////// Texture /////////////////////////////////////////////////////

void Viewer::Texture::create(CONST TCHAR* fileName) {
    assert(D3DXCreateTextureFromFile(DirectX::direct3DDevice9, fileName, &this->data) == S_OK);
}

auto& Viewer::Texture::operator()() { return data; }


///////////////////////////////////////////////////// Button /////////////////////////////////////////////////////

std::unordered_map<std::string, bool> Viewer::Button::mainMenuHover, Viewer::Button::saveSlotHover;

Viewer::Button::Button() {}

Viewer::Button::Button(const char* id, Texture img, Texture img2, Type type) {
    if (type == Type::MAINMENU) {
        buttonType = Type::MAINMENU;
        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 10);
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ ImColor{139, 129, 119, 0} });
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ ImColor{255, 231, 0, 0} });
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ ImColor{255, 255, 255, 0} });
        isClicked = ImGui::ImageButton(mainMenuHover[id] ? img2() : img(), ImVec2(200, 50));
        mainMenuHover[id] = ImGui::IsItemHovered();
    }
    if (type == Type::CIRCLE) {
        buttonType = Type::CIRCLE;
        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 25);
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ ImColor{0,0,0,0} });
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ ImColor{0,0,0,0} });
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ ImColor{0,0,0,0} });
        isClicked = ImGui::ImageButton(img(), ImVec2(40, 40));
    }
    if (type == Type::SAVESLOT) {
        buttonType = Type::SAVESLOT;
        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 100);
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ ImColor{0,0,0,0} });
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ ImColor{0,0,0,0} });
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ ImColor{0,0,0,0} });
        isClicked = ImGui::ImageButton(saveSlotHover[id] ? img2() : img(), ImVec2(200, 100));
        saveSlotHover[id] = ImGui::IsItemHovered();
    }
}

// Destructor
Viewer::Button::~Button() {
    ImGui::PopStyleVar();
    ImGui::PopStyleColor(3);
}

Viewer::Button::operator bool()const { return isClicked; }

///////////////////////////////////////////////////// DirectX9 /////////////////////////////////////////////////////

// Initialize static variable
LPDIRECT3DDEVICE9 Viewer::DirectX::direct3DDevice9 = NULL;

Viewer::DirectX::DirectX(Viewer& viewer) : imgs(viewer) {}

BOOL Viewer::DirectX::CreateDeviceD3D(HWND hWnd) {

    static const auto once = [&]() noexcept -> BOOL {

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
    }();

    return once;
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

    InitImgs();

    // Initialize font
    auto& io = ImGui::GetIO();
    io.Fonts->AddFontFromFileTTF("../assets\\tahoma.ttf", 20);

    return TRUE;
}

void Viewer::DirectX::InitImgs() {
    /////////////// Main Menu ///////////////
    // Initialize background textures
    imgs.backgroundMenu.create(TEXT("../assets\\mainmenu.png"));
    imgs.backgroundLoadGame.create(TEXT("../assets\\background loadgame.png"));

    // Initialize button textures
    imgs.buttonStartGameImg.create(TEXT("../assets\\button startgame.png"));
    imgs.buttonExitGameImg.create(TEXT("../assets\\button exitgame.png"));
    imgs.buttonReadFileImg.create(TEXT("../assets\\button readfile.png"));
    imgs.buttonStartGameHoverImg.create(TEXT("../assets\\button startgame hover.png"));
    imgs.buttonExitGameHoverImg.create(TEXT("../assets\\button exitgame hover.png"));
    imgs.buttonReadFileHoverImg.create(TEXT("../assets\\button readfile hover.png"));
    imgs.buttonLoadGameImg.create(TEXT("../assets\\button loadgame.png"));
    imgs.buttonLoadGameHoverImg.create(TEXT("../assets\\button loadgame hover.png"));
    imgs.buttonLogReplayImg.create(TEXT("../assets\\button logreplay.png"));
    imgs.buttonLogReplayHoverImg.create(TEXT("../assets\\button logreplay hover.png"));
    

    /////////////// Gameplay ///////////////
    // Initialize background texture
    imgs.backgroundGame.create(TEXT("../assets\\gameboard.png"));
    imgs.backgroundSaveGame.create(TEXT("../assets\\background savegame.png"));
    imgs.backgroundRedWin.create(TEXT("../assets\\background red win.png"));
    imgs.backgroundBlackWin.create(TEXT("../assets\\background black win.png"));
    imgs.backgroundCheck.create(TEXT("../assets\\background check.png"));
    imgs.backgroundCheckmate.create(TEXT("../assets\\background checkmate.png"));
    imgs.backgroundStalemate.create(TEXT("../assets\\background stalemate.png"));

    // Initialize button textures
    imgs.buttonBackToMenuImg.create(TEXT("../assets\\button backtomenu.png"));
    imgs.buttonBackToMenuHoverImg.create(TEXT("../assets\\button backtomenu hover.png"));
    imgs.buttonPlayAgainImg.create(TEXT("../assets\\button playagain.png"));
    imgs.buttonPlayAgainHoverImg.create(TEXT("../assets\\button playagain hover.png"));
    imgs.buttonSurrenderImg.create(TEXT("../assets\\button surrender.png"));
    imgs.buttonSurrenderHoverImg.create(TEXT("../assets\\button surrender hover.png"));
    imgs.buttonExitBoardImg.create(TEXT("../assets\\button exitboard.png"));
    imgs.buttonExitBoardHoverImg.create(TEXT("../assets\\button exitboard hover.png"));
    imgs.buttonSaveGameImg.create(TEXT("../assets\\button savegame.png"));
    imgs.buttonSaveGameHoverImg.create(TEXT("../assets\\button savegame hover.png"));
    imgs.buttonSave1Img.create(TEXT("../assets\\button save1.png"));
    imgs.buttonSave2Img.create(TEXT("../assets\\button save2.png"));
    imgs.buttonSave3Img.create(TEXT("../assets\\button save3.png"));
    imgs.buttonSave1HoverImg.create(TEXT("../assets\\button save1 hover.png"));
    imgs.buttonSave2HoverImg.create(TEXT("../assets\\button save2 hover.png"));
    imgs.buttonSave3HoverImg.create(TEXT("../assets\\button save3 hover.png"));

    /////////////// Chess Pieces ///////////////
    // Initialize red chess piece textures
    imgs.chessRedGeneral.create(TEXT("../assets\\pion\\chess red general.png"));
    imgs.chessRedElephant.create(TEXT("../assets\\pion\\chess red elephant.png"));
    imgs.chessRedAdvisor.create(TEXT("../assets\\pion\\chess red advisor.png"));
    imgs.chessRedCannon.create(TEXT("../assets\\pion\\chess red cannon.png"));
    imgs.chessRedChariot.create(TEXT("../assets\\pion\\chess red chariot.png"));
    imgs.chessRedHorse.create(TEXT("../assets\\pion\\chess red horse.png"));
    imgs.chessRedSoldier.create(TEXT("../assets\\pion\\chess red soldier.png"));

    // Initialize black chess piece textures
    imgs.chessBlackGeneral.create(TEXT("../assets\\pion\\chess black general.png"));
    imgs.chessBlackElephant.create(TEXT("../assets\\pion\\chess black elephant.png"));
    imgs.chessBlackAdvisor.create(TEXT("../assets\\pion\\chess black advisor.png"));
    imgs.chessBlackCannon.create(TEXT("../assets\\pion\\chess black cannon.png"));
    imgs.chessBlackChariot.create(TEXT("../assets\\pion\\chess black chariot.png"));
    imgs.chessBlackHorse.create(TEXT("../assets\\pion\\chess black horse.png"));
    imgs.chessBlackSoldier.create(TEXT("../assets\\pion\\chess black soldier.png"));

    // Initialize possible move textures
    imgs.possibleRed.create(TEXT("../assets\\pion\\possible red.png"));
    imgs.possibleBlack.create(TEXT("../assets\\pion\\possible black.png"));
}

void Viewer::DirectX::onResize(WPARAM wParam, LPARAM lParam)noexcept {
    if (!direct3DDevice9 || wParam == SIZE_MINIMIZED) return;

    // Handle render buffer size to window size
    direct3DParams.BackBufferWidth = LOWORD(lParam);
    direct3DParams.BackBufferHeight = HIWORD(lParam);
    ResetDevice();
}


///////////////////////////////////////////////////// ID /////////////////////////////////////////////////////

Viewer::ID::ID(int id) {
    ImGui::PushID(id);
}

Viewer::ID::~ID() {
    ImGui::PopID();
}


///////////////////////////////////////////////////// Viewer Functions /////////////////////////////////////////////////////

Viewer::Viewer() : directx(*this) {}

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
    directx.direct3DDevice9->SetRenderState(D3DRS_ZENABLE, FALSE);
    directx.direct3DDevice9->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
    directx.direct3DDevice9->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);
    directx.direct3DDevice9->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR(), 1.f, 0);

    if (directx.direct3DDevice9->BeginScene() >= 0) {
        ImGui::Render();
        ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
        directx.direct3DDevice9->EndScene();
    }

    HRESULT result = directx.direct3DDevice9->Present(NULL, NULL, NULL, NULL);
    // Handle loss of D3D9 device
    if (result == D3DERR_DEVICELOST && directx.direct3DDevice9->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
        directx.ResetDevice();
}

void Viewer::endAll() {
    ImGui_ImplDX9_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    directx.CleanupDeviceD3D();
}

ImVec2 Viewer::createWindow(bool& appRunning, Texture background) {
    // Main Menu's window settings
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{});
    ImGui::Begin("##Window", &appRunning, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);

    // Set background
    ImVec2 screenSize = ImGui::GetContentRegionAvail();
    float middle_x = (screenSize.x / 2) - 100;
    float middle_y = (screenSize.y / 2) + 90;
    auto position = ImGui::GetCursorPos();
    ImGui::Image(background(), screenSize);
    ImGui::SetCursorPos(position);

    return screenSize;
}

void Viewer::endWindow() {
    ImGui::End();
    ImGui::PopStyleVar();
}

void Viewer::setButtonPos(float x, float y) {
    ImGui::SetCursorPos(ImVec2(x, y));
}

ImVec2 Viewer::getCursorPos()
{
    auto position = ImGui::GetCursorPos();
    return position;
}

void Viewer::makeExtraWindow() {
    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0, 0, 0, 0.2));
    ImGui::BeginChild("##extra window", ImGui::GetContentRegionAvail(), false, ImGuiWindowFlags_NoScrollbar);
}

void Viewer::endExtraWindow() {
    ImGui::EndChild();
    ImGui::PopStyleColor();
}

void Viewer::addWindowImage(Texture img) {
    ImGui::Image(img(), ImGui::GetContentRegionAvail());
}

void Viewer::addText(const char* text) {
    ImGui::Text(text);
}

// get ImGui's global data
ImGuiIO& Viewer::getData() {
    return ImGui::GetIO();
}