#include "Viewer.h"

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_win32.h"
#include "ImGui/imgui_impl_dx9.h"

#include "tahoma.h"

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
    style.WindowRounding    = 6;
    style.FrameRounding     = 6;
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