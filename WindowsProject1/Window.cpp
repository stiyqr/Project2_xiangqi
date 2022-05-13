#include "Window.h"
#include "GameManager.h"
#include "Viewer.h"

Window::Window (
    HINSTANCE   hInstance,
    INT         nCmdShow ) noexcept :
    instance{ hInstance } {

    GetModuleFileName ( hInstance, path, ( sizeof path / sizeof path[0] ) );

    assert ( LoadStringW ( hInstance, IDS_APP_TITLE, text, ( sizeof text / sizeof text[0] ) ) != NULL );
    assert ( LoadStringW ( hInstance, IDC_WINDOWSPROJECT1, className, ( sizeof text / sizeof text[0] ) ) != NULL );

    classEx.cbSize          = sizeof classEx;
    classEx.style           = CS_HREDRAW | CS_VREDRAW | CS_CLASSDC;
    classEx.lpfnWndProc     = &Proc;
    classEx.cbClsExtra      = 0;
    classEx.cbWndExtra      = 0;
    classEx.hInstance       = hInstance;
    classEx.hIcon           = LoadIcon ( hInstance, MAKEINTRESOURCE ( IDI_WINDOWSPROJECT1 ) );
    classEx.hCursor         = LoadCursor ( nullptr, IDC_ARROW );
    classEx.hbrBackground   = ( HBRUSH ) ( COLOR_WINDOW + 1 );
    classEx.lpszMenuName    = NULL;
    classEx.lpszClassName   = className;
    classEx.hIconSm         = LoadIcon ( classEx.hInstance, MAKEINTRESOURCE ( IDI_SMALL ) );

    assert ( RegisterClassEx ( &classEx ) != NULL );

    RECT rect;
    rect.left       = 0;
    rect.top        = 0;
    rect.right      = GetSystemMetrics ( SM_CXMAXTRACK ); //If you have more than one monitor, you will get the total width
    rect.bottom     = GetSystemMetrics ( SM_CYMAXTRACK );

    handle = CreateWindowEx ( WS_EX_LAYERED, className, text, WS_POPUP,
                              0, 0, rect.right - rect.left, rect.bottom - rect.top, nullptr, nullptr, hInstance, nullptr );
    assert ( handle != NULL );

    SetLayeredWindowAttributes ( handle, RGB ( 0, 0, 0 ), 1, LWA_COLORKEY );
    ShowWindow ( handle, nCmdShow );
    UpdateWindow ( handle );

    running = true;
}

Window::~Window () noexcept {
    
    DestroyWindow ( handle );
    UnregisterClass ( classEx.lpszClassName, classEx.hInstance );
}

LRESULT Window::Proc (
    HWND    hWnd,
    UINT    message,
    WPARAM  wParam,
    LPARAM  lParam ) noexcept {

    const auto& gameManager{ GameManager::instance () };

    if ( gameManager.window ) {

        if ( !gameManager.window->running )
            message = WM_DESTROY;
        else if ( gameManager.viewer ) {

            LRESULT ImGui_ImplWin32_WndProcHandler ( HWND, UINT, WPARAM, LPARAM );
            if ( ImGui_ImplWin32_WndProcHandler ( hWnd, message, wParam, lParam ) )
                return true;

            switch ( message ) {
            case WM_SIZE: if ( gameManager.viewer ) gameManager.viewer->resize ( wParam, lParam );
                return EXIT_SUCCESS;
            }
        }
    }

    switch ( message ) {
    case WM_DESTROY: PostQuitMessage ( 0 );
        return EXIT_SUCCESS;
    }

    return DefWindowProc ( hWnd, message, wParam, lParam );
}

INT Window::run (
    Viewer& viewer,
    void    ( *callback )( GameManager& ) ) noexcept {

    while ( GetMessage ( &message, nullptr, 0, 0 ) ) {

        TranslateMessage ( &message );
        DispatchMessage ( &message );

        ImGui_ImplDX9_NewFrame ();
        ImGui_ImplWin32_NewFrame ();
        ImGui::NewFrame ();

        if ( running ) {

            ImGui::SetNextWindowSize ( ImVec2{ 1364, 764 }, ImGuiCond_Once );

            ImGui::PushStyleVar ( ImGuiStyleVar_WindowPadding, ImVec2{} );

            if ( ImGui::Begin ( "Xiangqi", &running, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar ) && callback )
                callback ( GameManager::instance () );

            ImGui::End ();

            ImGui::PopStyleVar ();
        }

        ImGui::EndFrame ();

        viewer.Direct3DDevice9->SetRenderState ( D3DRS_ZENABLE, FALSE );
        viewer.Direct3DDevice9->SetRenderState ( D3DRS_ALPHABLENDENABLE, FALSE );
        viewer.Direct3DDevice9->SetRenderState ( D3DRS_SCISSORTESTENABLE, FALSE );
        viewer.Direct3DDevice9->Clear ( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR (), 1.f, 0 );

        if ( viewer.Direct3DDevice9->BeginScene () == D3D_OK ) {
            ImGui::Render ();
            ImGui_ImplDX9_RenderDrawData ( ImGui::GetDrawData () );
            viewer.Direct3DDevice9->EndScene ();
        }

        if ( viewer.Direct3DDevice9->Present ( nullptr, nullptr, nullptr, nullptr ) == D3DERR_DEVICELOST &&
             viewer.Direct3DDevice9->TestCooperativeLevel () == D3DERR_DEVICENOTRESET )
            viewer.reset ();
    }

    return static_cast< INT >( message.wParam );
}