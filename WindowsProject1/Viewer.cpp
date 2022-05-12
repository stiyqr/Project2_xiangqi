#include "Viewer.h"

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
}
Viewer::~Viewer () noexcept {

    if ( Direct3DDevice9 ) { Direct3DDevice9->Release (); Direct3DDevice9 = NULL; }
    if ( Direct3D9 ) { Direct3D9->Release (); Direct3D9 = NULL; }
}

void Viewer::run () noexcept {

    Direct3DDevice9->SetRenderState ( D3DRS_ZENABLE, FALSE );
    Direct3DDevice9->SetRenderState ( D3DRS_ALPHABLENDENABLE, FALSE );
    Direct3DDevice9->SetRenderState ( D3DRS_SCISSORTESTENABLE, FALSE );
    Direct3DDevice9->Clear ( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR (), 1.f, 0 );

    if ( Direct3DDevice9->BeginScene () == D3D_OK ) {
        //ImGui::Render ();
        //ImGui_ImplDX9_RenderDrawData ( ImGui::GetDrawData () );
        Direct3DDevice9->EndScene ();
    }

    if ( Direct3DDevice9->Present ( nullptr, nullptr, nullptr, nullptr )    == D3DERR_DEVICELOST &&
         Direct3DDevice9->TestCooperativeLevel ()                           == D3DERR_DEVICENOTRESET )
        reset ();
}

void Viewer::reset () noexcept {

    //ImGui_ImplDX9_InvalidateDeviceObjects ();
    assert ( Direct3DDevice9->Reset ( &Direct3DParams ) != D3DERR_INVALIDCALL );
    //ImGui_ImplDX9_CreateDeviceObjects ();
}