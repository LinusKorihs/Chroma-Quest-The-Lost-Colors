#include "config.h"
#include "raylib.h"
#include "tileson.h"
#include "Menu.h"
#include "Utils.h"
#include "PixelGame.h"
#include "ApplicationState.h"

int main()
{
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
                applicationState.changeState(MenuState::MainMenu);
                Menu::drawMainMenu(gameState);
                Menu::unloadTextures();
                break;
            case MenuState::GameRunning:
                Menu::loadTextures();
                applicationState.changeState(MenuState::GameRunning);
                PixelGame::gameInit();
                PixelGame::gameLoop(Map);
                Menu::unloadTextures();
                break;
            case MenuState::SettingsMenu:
                Menu::loadTextures();
                applicationState.changeState(MenuState::SettingsMenu);
                Menu::drawSettingsMenu(gameState);
                Menu::unloadTextures();
                break;
            case MenuState::KeyBindingsMenu:
                Menu::loadTextures();
                applicationState.changeState(MenuState::KeyBindingsMenu);
                Menu::drawKeyBindingsMenu(gameState);
                Menu::unloadTextures();
                break;
            case MenuState::PauseMenu:
                Menu::loadTextures();
                applicationState.changeState(MenuState::PauseMenu);
                applicationState.togglePause();
                Menu::drawPauseMenu(gameState);
                Menu::unloadTextures();
                break;
            case MenuState::ResumeGame:
                Menu::loadTextures();
                applicationState.changeState(MenuState::ResumeGame);
                applicationState.togglePause();
                Menu::unloadTextures();
                break;
            case MenuState::VolumeSliders:
                Menu::loadTextures();
                applicationState.changeState(MenuState::VolumeSliders);
                Menu::drawVolumeSlidersMenu(gameState);
                Menu::unloadTextures();
                break;
            case MenuState::Control:
                Menu::loadTextures();
                applicationState.changeState(MenuState::Control);
                Menu::drawControlMenu(gameState);
                Menu::unloadTextures();
                break;
            case MenuState::Language:
                Menu::loadTextures();
                applicationState.changeState(MenuState::Language);
                Menu::drawLanguageMenu(gameState);
                Menu::unloadTextures();
                break;
            case MenuState::ControllerMenu:
                Menu::loadTextures();
                applicationState.changeState(MenuState::ControllerMenu);
                Menu::drawControllerMenu(gameState);
                Menu::unloadTextures();
                break;
            case MenuState::None:
                applicationState.changeState(MenuState::None);
                Menu::unloadTextures();
                gameState.gameIsRunning = false;
                break;
        }
    }
    CloseWindow();

    return EXIT_SUCCESS;
}