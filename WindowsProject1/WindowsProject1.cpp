#include "GameManager.h"

//struct Texture {
//    void create ( CONST TCHAR* fileName );
//    auto& operator()() { return data; }
//private:
//    LPDIRECT3DTEXTURE9 data;
//};
//
//Texture background;

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

    auto render = [] () {

    };

    return window->run ( *viewer, render );
}

//BOOL InitInstance ( HINSTANCE hInstance, INT nCmdShow ) {
//
//    background.create ( TEXT ( "C:\\Users\\Wyxather\\OneDrive\\Pictures\\Wallpapers\\Cloud City.jpg" ) );
//
//    return TRUE;
//}  return 0;
//
//VOID Texture::create ( CONST TCHAR* fileName ) {
//
//    D3DXCreateTextureFromFile ( direct3DDevice9, fileName, &background () );
//}