#include "GameManager.h"

GameManager::GameManager()
{
}

void GameManager::createTextures () {

    viewer.textures["background"].create ( "../../assets\\gameboard.png" );
}

void GameManager::createGameBoard (bool& appRunning) {

    // Game Board's window settings
    ImGui::PushStyleVar ( ImGuiStyleVar_WindowPadding, ImVec2{} );
    ImGui::Begin ( "##MainMenu", &appRunning, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize );

    // Set background
    ImVec2 screenSize = ImGui::GetContentRegionAvail ();
    float middle_x = ( screenSize.x / 2 ) - 100;
    float middle_y = ( screenSize.y / 2 ) + 90;
    ImGui::Image ( viewer.textures["background"](), screenSize);
}