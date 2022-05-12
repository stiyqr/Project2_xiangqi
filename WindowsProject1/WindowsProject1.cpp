#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_win32.h"
#include "ImGui/imgui_impl_dx9.h"

#pragma push_macro("#define IMGUI_DEFINE_MATH_OPERATORS")
#define IMGUI_DEFINE_MATH_OPERATORS
#include "ImGui/imgui_internal.h"
#pragma pop_macro("#define IMGUI_DEFINE_MATH_OPERATORS")

#include "tahoma.h"

#include "GameManager.h"

LRESULT CALLBACK    WndProc ( HWND, UINT, WPARAM, LPARAM );

struct Texture {
    void create ( CONST TCHAR* fileName );
    auto& operator()() { return data; }
private:
    LPDIRECT3DTEXTURE9 data;
};

Texture background;

// Forward declarations of functions for directx 9:
BOOL CreateDeviceD3D ( HWND hWnd );
VOID CleanupDeviceD3D ();
VOID ResetDevice ();

// Global Variables for imgui:
bool ImGuiWindow = true;

INT APIENTRY wWinMain (
    _In_ HINSTANCE      hInstance,
    _In_opt_ HINSTANCE  hPrevInstance,
    _In_ LPWSTR         lpCmdLine,
    _In_ INT            nCmdShow ) {

    auto& gameManager{ GameManager::instance () };

    auto& window{ gameManager.window };
    window = std::make_unique<std::remove_reference_t<decltype( window )>::element_type> ( hInstance, nCmdShow );

    auto& viewer{ gameManager.viewer };
    viewer = std::make_unique<std::remove_reference_t<decltype( viewer )>::element_type> ( window->handle );

    //// Main message loop:
    //while ( GetMessage ( &msg, nullptr, 0, 0 ) ) {

    //    TranslateMessage ( &msg );
    //    DispatchMessage ( &msg );

    //    // Start the Dear ImGui frame
    //    ImGui_ImplDX9_NewFrame ();
    //    ImGui_ImplWin32_NewFrame ();
    //    ImGui::NewFrame ();
    //    {
    //        // Start rendering the menu through imgui functions
    //        if ( ImGuiWindow ) {

    //            ImGui::SetNextWindowSize ( ImGui::GetIO ().DisplaySize / 2, ImGuiCond_Once );

    //            ImGui::PushStyleVar ( ImGuiStyleVar_WindowPadding, ImVec2{} );
    //            if ( ImGui::Begin ( "Xiangqi", &ImGuiWindow, ImGuiWindowFlags_NoCollapse ) ) {

    //                ImGui::Image ( background (), ImGui::GetContentRegionAvail() );
    //            }
    //            ImGui::End ();
    //            ImGui::PopStyleVar ();
    //        }
    //    }
    //    ImGui::EndFrame ();

    //    // Start clearing previous buffer and render next one through directx9
    //    direct3DDevice9->SetRenderState ( D3DRS_ZENABLE, FALSE );
    //    direct3DDevice9->SetRenderState ( D3DRS_ALPHABLENDENABLE, FALSE );
    //    direct3DDevice9->SetRenderState ( D3DRS_SCISSORTESTENABLE, FALSE );
    //    direct3DDevice9->Clear ( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR (), 1.f, 0 );

    //    if ( direct3DDevice9->BeginScene () >= 0 ) {
    //        ImGui::Render ();
    //        ImGui_ImplDX9_RenderDrawData ( ImGui::GetDrawData () );
    //        direct3DDevice9->EndScene ();
    //    }

    //    HRESULT result = direct3DDevice9->Present ( NULL, NULL, NULL, NULL );

    //    // Handle loss of D3D9 device
    //    if ( result == D3DERR_DEVICELOST && direct3DDevice9->TestCooperativeLevel () == D3DERR_DEVICENOTRESET )
    //        ResetDevice ();
    //}

    //// Cleanup ImGui
    //ImGui_ImplDX9_Shutdown ();
    //ImGui_ImplWin32_Shutdown ();
    //ImGui::DestroyContext ();

    //// Cleanup directx 9
    //CleanupDeviceD3D ();

    while ( window->run () ) {

        viewer->run ();
    }

    return window->message.wParam;
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
////        create and display the main program window.
////
//BOOL InitInstance ( HINSTANCE hInstance, INT nCmdShow ) {
//
//    // Initialize ImGui
//    ImGui::CreateContext ();
//    ImGui::StyleColorsDark ();
//
//    // Initialize ImGui Implementation
//    ImGui_ImplWin32_Init ( hWnd );
//    ImGui_ImplDX9_Init ( direct3DDevice9 );
//
//    auto& io{ ImGui::GetIO () };
//    io.IniFilename = nullptr;
//    io.LogFilename = nullptr;
//
//    auto& fonts{ *io.Fonts };
//    fonts.AddFontFromMemoryCompressedTTF ( tahoma_compressed_data, tahoma_compressed_size, 15 );
//
//    auto& style{ ImGui::GetStyle () };
//    style.WindowRounding = 6;
//    style.FrameRounding = 6;
//
//    background.create ( TEXT ( "C:\\Users\\Wyxather\\OneDrive\\Pictures\\Wallpapers\\Cloud City.jpg" ) );
//
//    return TRUE;
//}
//
////
////  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
////
////  PURPOSE: Processes messages for the main window.
////
////  WM_DESTROY  - post a quit message and return
////  WM_SIZE     - resize directx9 render buffer size(width,height) with window size.
////
////
//LRESULT CALLBACK WndProc ( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam ) {
//
//    // Handle imgui menu input
//    if ( !ImGuiWindow )
//        message = WM_DESTROY;
//    else {
//        extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler ( HWND, UINT, WPARAM, LPARAM );
//        if ( ImGui_ImplWin32_WndProcHandler ( hWnd, message, wParam, lParam ) )
//            return true;
//    }
//
//    switch ( message ) {
//
//    case WM_SIZE: // Handle render buffer size to window size
//    {
//        if ( direct3DDevice9 != NULL && wParam != SIZE_MINIMIZED ) {
//            direct3DParams.BackBufferWidth = LOWORD ( lParam );
//            direct3DParams.BackBufferHeight = HIWORD ( lParam );
//            ResetDevice ();
//        }
//    }
//    break;
//    }
//
//    return 0;
//}
//
//BOOL CreateDeviceD3D ( HWND hWnd ) {
//
//    if ( ( direct3D9 = Direct3DCreate9 ( D3D_SDK_VERSION ) ) == NULL )
//        return FALSE;
//
//    // Create the D3DDevice
//    ZeroMemory ( &direct3DParams, sizeof ( direct3DParams ) );
//    direct3DParams.Windowed = TRUE;
//    direct3DParams.SwapEffect = D3DSWAPEFFECT_DISCARD;
//    direct3DParams.BackBufferFormat = D3DFMT_UNKNOWN; // Need to use an explicit format with alpha if needing per-pixel alpha composition.
//    direct3DParams.EnableAutoDepthStencil = TRUE;
//    direct3DParams.AutoDepthStencilFormat = D3DFMT_D16;
//    direct3DParams.PresentationInterval = D3DPRESENT_INTERVAL_ONE;           // Present with vsync
//    direct3DParams.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;   // Present without vsync, maximum unthrottled framerate
//    if ( direct3D9->CreateDevice ( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &direct3DParams, &direct3DDevice9 ) < 0 )
//        return FALSE;
//
//    return TRUE;
//}
//
//VOID CleanupDeviceD3D () {
//
//    if ( background () ) { background ()->Release (); background () = NULL; }
//    if ( direct3DDevice9 ) { direct3DDevice9->Release (); direct3DDevice9 = NULL; }
//    if ( direct3D9 ) { direct3D9->Release (); direct3D9 = NULL; }
//}
//
//VOID ResetDevice () {
//
//    ImGui_ImplDX9_InvalidateDeviceObjects ();
//
//    const auto hr = direct3DDevice9->Reset ( &direct3DParams );
//    if ( hr == D3DERR_INVALIDCALL )
//        IM_ASSERT ( 0 );
//
//    ImGui_ImplDX9_CreateDeviceObjects ();
//}
//
//VOID Texture::create ( CONST TCHAR* fileName ) {
//
//    D3DXCreateTextureFromFile ( direct3DDevice9, fileName, &background () );
//}