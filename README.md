# Xiangqi 象棋

A game of Chinese Chess or also known as Xiangqi（象棋）

## Main Menu

![main_menu](https://github.com/stiyqr/Project2_xiangqi/assets/88047576/bd5f6c79-6807-4627-9e4b-881dc8d81da4)

### Main Menu Buttons
* \[讀取游戲\] **Read Game**: read a game file and replay the steps taken by each player
* \[游戲開始\] **Start Game**: start a new game
* \[離開游戲\] **Exit Game**: exit the game
* \[重播\] **Replay**: replay the previously played game step by step
* \[加載游戲\] **Load Game**: load a saved game file and continue playing

## Gameplay

![gameplay_1](https://github.com/stiyqr/Project2_xiangqi/assets/88047576/21e1d44c-29be-4a15-844c-0b4b29938942)

![gameplay_2](https://github.com/stiyqr/Project2_xiangqi/assets/88047576/94b3f4d1-6700-4c2a-9c06-43e8dc61412c)

### Gameplay Buttons
* \[存檔\] **Save Game**: save the current game
* \[認輸\] **Surrender**: the current player surrender
* \[離開\] **Leave**: leave the current game

## Save Screen

![save_screen](https://github.com/stiyqr/Project2_xiangqi/assets/88047576/6e5517e5-718d-429c-9c58-4b406196e3ca)

## Game Over Screen

![game_over_screen](https://github.com/stiyqr/Project2_xiangqi/assets/88047576/3ca9a96e-22e6-42ad-8fd4-d6177acc01d0)

***

### Running the game in Visual Studio

* If you run into problems when running in Visual Studio Debugger:
  * Install DirectX SDK (DXSDK_Jun10)
    * (should run fine without installing this, but if cannot run please install)

* If still cannot run program in Visual Studio:
  * Change configuration settings:
    * right click "WindowsProject1" project
    * open Properties
    * make sure Configuration is "Active(Debug)" and Platform is "Active(Win32)"
    * open Configuration Properties -> VC++ Directories
    * click Include Directories, click the arrow and <Edit...>
    * in the uppermost textbox type "$(IncludePath)" and "$(DXSDK_DIR)Include"
    * click OK
    * click Library Directories, click the arrow and <Edit...>
    * in the uppermost textbox type "$(DXSDK_DIR)Lib\x86" (or "$(DXSDK_DIR)Lib\x64")
    * click OK
    * Apply and close
