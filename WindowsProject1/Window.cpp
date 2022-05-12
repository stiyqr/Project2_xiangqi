#include "Window.h"

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

    handle = CreateWindowEx ( WS_EX_TOPMOST | WS_EX_LAYERED, className, text, WS_POPUP,
                              0, 0, rect.right - rect.left, rect.bottom - rect.top, nullptr, nullptr, hInstance, nullptr );
    assert ( handle != NULL );

    SetLayeredWindowAttributes ( handle, RGB ( 0, 0, 0 ), 1, LWA_COLORKEY );
    ShowWindow ( handle, nCmdShow );
    UpdateWindow ( handle );
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

    switch ( message ) {
    case WM_SIZE:
        return EXIT_SUCCESS;
    case WM_DESTROY: PostQuitMessage ( 0 );
        return EXIT_SUCCESS;
    }

    return DefWindowProc ( hWnd, message, wParam, lParam );
}

bool Window::run () noexcept {

    if ( GetMessage ( &message, nullptr, 0, 0 ) == NULL )
        return false;

    TranslateMessage ( &message );
    DispatchMessage ( &message );

    return true;
}