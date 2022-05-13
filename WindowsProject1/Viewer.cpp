#include "Viewer.h"

#include "tahoma.h"

std::unordered_map<std::string, Viewer::Button::Data> Viewer::Button::buttons;

Viewer::Viewer (
    HWND windowHandle ) noexcept {

    Direct3DParams.BackBufferWidth              = 0;
    Direct3DParams.BackBufferHeight             = 0;
    Direct3DParams.BackBufferFormat             = D3DFMT_UNKNOWN;
    Direct3DParams.BackBufferCount              = 0;
    Direct3DParams.MultiSampleType              = D3DMULTISAMPLE_TYPE::D3DMULTISAMPLE_NONE;
    Direct3DParams.MultiSampleQuality           = 0;
    Direct3DParams.SwapEffect                   = D3DSWAPEFFECT_DISCARD;
    Direct3DParams.hDeviceWindow                = windowHandle;
    Direct3DParams.Windowed                     = TRUE;
    Direct3DParams.EnableAutoDepthStencil       = TRUE;
    Direct3DParams.AutoDepthStencilFormat       = D3DFMT_D16;
    Direct3DParams.Flags                        = NULL;
    Direct3DParams.FullScreen_RefreshRateInHz   = NULL;
    Direct3DParams.PresentationInterval         = D3DPRESENT_INTERVAL_IMMEDIATE;

    assert ( Direct3D9 = Direct3DCreate9 ( D3D_SDK_VERSION ) );
    assert ( Direct3D9->CreateDevice ( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, windowHandle, D3DCREATE_HARDWARE_VERTEXPROCESSING, &Direct3DParams, &Direct3DDevice9 ) == D3D_OK );

    ImGui::CreateContext ();
    ImGui::StyleColorsDark ();

    ImGui_ImplWin32_Init ( windowHandle );
    ImGui_ImplDX9_Init ( Direct3DDevice9 );

    auto& io{ ImGui::GetIO () };
    io.IniFilename = nullptr;
    io.LogFilename = nullptr;

    auto& fonts{ *io.Fonts };
    fonts.AddFontFromMemoryCompressedTTF ( tahoma_compressed_data, tahoma_compressed_size, 15 );

    auto& style{ ImGui::GetStyle () };
    style.WindowRounding    = 10;
    style.FrameRounding     = 10;
}

Viewer::~Viewer () noexcept {

    ImGui_ImplDX9_Shutdown ();
    ImGui_ImplWin32_Shutdown ();
    ImGui::DestroyContext ();

    if ( Direct3DDevice9 ) { Direct3DDevice9->Release (); Direct3DDevice9 = NULL; }
    if ( Direct3D9 ) { Direct3D9->Release (); Direct3D9 = NULL; }
}

void Viewer::reset () noexcept {

    ImGui_ImplDX9_InvalidateDeviceObjects ();
    assert ( Direct3DDevice9->Reset ( &Direct3DParams ) != D3DERR_INVALIDCALL );
    ImGui_ImplDX9_CreateDeviceObjects ();
}

void Viewer::resize (
    WPARAM wParam,
    LPARAM lParam ) noexcept {

    if ( wParam == SIZE_MINIMIZED )
        return;

    Direct3DParams.BackBufferWidth  = LOWORD ( lParam );
    Direct3DParams.BackBufferHeight = HIWORD ( lParam );

    reset ();
}

void Viewer::Texture::load ( const Viewer& viewer, const char* path ) noexcept {

    assert ( D3DXCreateTextureFromFileA ( viewer.Direct3DDevice9, path, &data ) == S_OK );

    D3DSURFACE_DESC desc;
    assert ( data->GetLevelDesc ( 0, &desc ) == D3D_OK );

    size.x = static_cast< float >( desc.Width );
    size.y = static_cast< float >( desc.Height );
}

void Viewer::Texture::load ( const Viewer& viewer, const wchar_t* path ) noexcept {

    assert ( D3DXCreateTextureFromFileW ( viewer.Direct3DDevice9, path, &data ) == S_OK );
}

Viewer::Position::Position ( Type type ) noexcept {

    switch ( type ) {

    case Type::CURSOR:
        position = {};
        break;

    case Type::CENTER:
        position = ImGui::GetContentRegionAvail () * .5f;
        break;
    }
}

Viewer::Frame::Frame ( const char* id, const Texture& texture ) noexcept {

    draw = ImGui::BeginChild ( id, ImGui::GetContentRegionAvail (), false, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoScrollbar );

    if ( !draw )
        return;

    if ( texture.data ) {

        const auto cursorPos{ ImGui::GetCursorPos () };
        const auto framePos{ ImGui::GetWindowPos () + cursorPos };

        ImGui::GetWindowDrawList ()->AddImageRounded (
            texture.data,
            framePos,
            framePos + ImGui::GetContentRegionAvail (),
            ImVec2{ 0, 0 },
            ImVec2{ 1, 1 },
            IM_COL32 ( 255, 255, 255, 255 ),
            ImGui::GetStyle ().FrameRounding,
            ImDrawFlags_RoundCornersAll );

        ImGui::SetCursorPos ( cursorPos );
    }
}

Viewer::Frame::~Frame () noexcept {

    ImGui::EndChild ();
}

Viewer::Button::Button ( const char* id, const Texture& texture, const Texture& textureHovered, const ImVec2& position, const ImVec2& size ) noexcept {

    button = &buttons[id] ;

    ImGui::PushStyleColor ( ImGuiCol_Button, IM_COL32 ( 0, 0, 0, 0 ) );
    ImGui::PushStyleColor ( ImGuiCol_ButtonActive, IM_COL32 ( 0, 0, 0, 0 ) );
    ImGui::PushStyleColor ( ImGuiCol_ButtonHovered, IM_COL32 ( 0, 0, 0, 0 ) );

    ImGui::SetCursorPos ( position );

    button->isClicked = ImGui::ImageButton ( button->isHovered ? textureHovered.data : texture.data, size );
    button->isHovered = ImGui::IsItemHovered ();
}

Viewer::Button::~Button () noexcept {

    ImGui::PopStyleColor ( 3 );
}

const Viewer::Button::Data& Viewer::Button::data () const noexcept {

    return *button;
}