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

    viewer->textures["menu"].load ( *viewer, "../assets/menu.png" );
    viewer->textures["board"].load ( *viewer, "../assets/board.png" );

    viewer->textures["btn-start"].load ( *viewer, "../assets/button_start.png" );
    viewer->textures["btn-start-hover"].load ( *viewer, "../assets/button_start_dark.png" );

    viewer->textures["btn-exit"].load ( *viewer, "../assets/button_exit.png" );
    viewer->textures["btn-exit-hover"].load ( *viewer, "../assets/button_exit_dark.png" );

    viewer->textures["btn-read"].load ( *viewer, "../assets/button_read.png" );
    viewer->textures["btn-read-hover"].load ( *viewer, "../assets/button_read_dark.png" );

    viewer->textures["btn-back"].load ( *viewer, "../assets/button_back.png" );
    viewer->textures["btn-back-hover"].load ( *viewer, "../assets/button_back_dark.png" );

    auto render = [] ( GameManager& gameManager ) {

        static bool startGame = false;

        auto& viewer{ gameManager.viewer };

        if ( !startGame ) {

            Viewer::Frame menu{ "##menu", viewer->textures["menu"] };

            if ( menu ) {

                const ImVec2 btnSize{ 270, 70 };

                Viewer::Position pos{ Viewer::Position::Type::CENTER };
                pos.data ().y *= 1.75f;

                ImVec2 btnPos = pos.data ();
                btnPos -= btnSize * .5f;
                Viewer::Button btnRead{ "##btn-read", viewer->textures["btn-read"], viewer->textures["btn-read-hover"], btnPos, btnSize };

                btnPos = pos.data ();
                btnPos.x *= 1.5f;
                btnPos -= btnSize * .5f;
                Viewer::Button btnExit{ "##btn-exit", viewer->textures["btn-exit"], viewer->textures["btn-exit-hover"], btnPos, btnSize };

                btnPos = pos.data ();
                btnPos.x *= .5f;
                btnPos -= btnSize * .5f;
                Viewer::Button btnStart{ "##btn-start", viewer->textures["btn-start"], viewer->textures["btn-start-hover"], btnPos, btnSize };

                if ( btnStart.data ().isClicked )
                    startGame = true;

                if ( btnExit.data ().isClicked )
                    gameManager.window->running = false;
            }
        }
        else {

            Viewer::Frame board ( "##board", viewer->textures["board"] );

            const ImVec2 buttonSize{ 315, 50 };

            if ( board ) {

                Viewer::Position pos{ Viewer::Position::Type::CENTER };
                pos.data ().x *= 1.55f;
                pos.data ().y *= 1.25f;

                ImVec2 btnPos = pos.data ();
                btnPos -= buttonSize * .5f;
                Viewer::Button btnBack{ "##btn-back", viewer->textures["btn-back"], viewer->textures["btn-back-hover"], btnPos, buttonSize };

                if ( btnBack.data ().isClicked )
                    startGame = false;
            }
        }
    };

    return window->run ( *viewer, render );
}