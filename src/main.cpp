#include "ApplicationState.h"
#include "config.h"
#include "Menu.h"
#include "PixelGame.h"
#include "raylib.h"
#include "tileson.h"
#include "Utils.h"




int main(){

    SetTraceLogLevel(LOG_WARNING);
    ApplicationState applicationState;

    InitWindow(PixelGameConfig::ScreenWidth, PixelGameConfig::ScreenHeight, PixelGameConfig::PROJECT_NAME);
    SetTargetFPS(gameState.targettedFps);
#ifdef GAME_START_FULLSCREEN
    ToggleFullscreen();
#endif

    tson::Tileson tileson;
    auto MapPtr = tileson.parse("assets/data/tilemap.tmj");
    tson::Map &Map = *MapPtr;

    SetExitKey(KEY_F4);

    while (gameState.gameIsRunning == true)
    {
        switch (gameState.currentMenu)
        {
            case MenuState::MainMenu:
                Menu::loadTextures();
                applicationState.ChangeState(MenuState::MainMenu);
                Menu::drawMainMenu(gameState);
                Menu::unloadTextures();
                break;
            case MenuState::GameRunning:
                Menu::loadTextures();
                applicationState.ChangeState(MenuState::GameRunning);
                PixelGame::GameInit();
                PixelGame::GameLoop(Map);
                Menu::unloadTextures();
                break;
            case MenuState::SettingsMenu:
                Menu::loadTextures();
                applicationState.ChangeState(MenuState::SettingsMenu);
                Menu::drawSettingsMenu(gameState);
                Menu::unloadTextures();
                break;
            case MenuState::KeyBindingsMenu:
                Menu::loadTextures();
                applicationState.ChangeState(MenuState::KeyBindingsMenu);
                Menu::drawKeyBindingsMenu(gameState);
                Menu::unloadTextures();
                break;
            case MenuState::PauseMenu:
                Menu::loadTextures();
                applicationState.ChangeState(MenuState::PauseMenu);
                applicationState.TogglePause();
                Menu::drawPauseMenu(gameState);
                Menu::unloadTextures();
                break;
            case MenuState::ResumeGame:
                Menu::loadTextures();
                applicationState.ChangeState(MenuState::ResumeGame);
                applicationState.TogglePause();
                Menu::unloadTextures();
                break;
            case MenuState::VolumeSliders:
                Menu::loadTextures();
                applicationState.ChangeState(MenuState::VolumeSliders);
                Menu::drawVolumeSlidersMenu(gameState);
                Menu::unloadTextures();
                break;
            case MenuState::Control:
                Menu::loadTextures();
                applicationState.ChangeState(MenuState::Control);
                Menu::drawControlMenu(gameState);
                Menu::unloadTextures();
                break;
            case MenuState::Language:
                Menu::loadTextures();
                applicationState.ChangeState(MenuState::Language);
                Menu::drawLanguageMenu(gameState);
                Menu::unloadTextures();
                break;
            case MenuState::ControllerMenu:
                Menu::loadTextures();
                applicationState.ChangeState(MenuState::ControllerMenu);
                Menu::drawControllerMenu(gameState);
                Menu::unloadTextures();
                break;
            case MenuState::None:
                applicationState.ChangeState(MenuState::None);
                Menu::unloadTextures();
                gameState.gameIsRunning = false;
                break;
        }
    }
    CloseWindow();

    return EXIT_SUCCESS;

}