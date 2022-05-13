#include "GameManager.h"

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

    viewer->textures["background"].load ( *viewer, "../assets/mainmenu.png" );

    viewer->textures["start"].load ( *viewer, "../assets/button startgame.png" );
    viewer->textures["start-hover"].load ( *viewer, "../assets/button startgame hover.png" );

    viewer->textures["exit"].load ( *viewer, "../assets/button exitgame.png" );
    viewer->textures["exit-hover"].load ( *viewer, "../assets/button exitgame hover.png" );

    viewer->textures["read"].load ( *viewer, "../assets/button readfile.png" );
    viewer->textures["read-hover"].load ( *viewer, "../assets/button readfile hover.png" );

    auto render = [] ( GameManager& gameManager ) {

        auto& viewer{ gameManager.viewer };

        Viewer::Frame menu{ "##menu", viewer->textures["background"] };
        
        if ( menu ) {
            const ImVec2 buttonSize{ 270, 70 };

            Viewer::Position pos{ Viewer::Position::Type::CENTER };
            pos.data ().y *= 1.75f;

            ImVec2 btnPos = pos.data ();
            btnPos -= buttonSize * .5f;
            Viewer::Button start{ "##start", viewer->textures["start"], viewer->textures["start-hover"], btnPos, buttonSize };

            btnPos = pos.data ();
            btnPos.x *= 1.5f;
            btnPos -= buttonSize * .5f;
            Viewer::Button exit{ "##exit", viewer->textures["exit"], viewer->textures["exit-hover"], btnPos, buttonSize };

            btnPos = pos.data ();
            btnPos.x *= .5f;
            btnPos -= buttonSize * .5f;
            Viewer::Button read{ "##read", viewer->textures["read"], viewer->textures["read-hover"], btnPos, buttonSize };

            if ( exit.data ().isClicked )
                gameManager.window->running = false;
        }
    };

    return window->run ( *viewer, render );
}