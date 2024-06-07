#include "GameState.h"
#include "config.h"
#include "Configuration.h"
#include "Menu.h"
#include "PixelGame.h"
#include "raylib.h"
#include "tileson.h"
#include "Utils.h"

int main()
{
    SetTraceLogLevel(LOG_WARNING);
    GameState applicationState;

    InitWindow(PixelGameConfig::ScreenWidth, PixelGameConfig::ScreenHeight, PixelGameConfig::PROJECT_NAME);
    SetTargetFPS(ConfigConst::targetFPS);

#ifdef GAME_START_FULLSCREEN
    ToggleFullscreen();
#endif

    tson::Tileson tileson;
    auto tileMapPointer = tileson.parse("assets/graphics/Old TileSet & TileMap/tilemap.tmj");
    tson::Map& tileMap = *tileMapPointer;

    SetExitKey(KEY_F4);

    while (ConfigNotConst::isGameRunning == true)
    {
        switch (currentGameState.currentGameMenu)
        {
            case MenuState::MainMenu:
                Menu::loadButtonAndKeyButtonTextures();
                applicationState.changeGameState(MenuState::MainMenu);
                Menu::drawMainMenu(currentGameState);
                Menu::unloadButtonAndKeyButtonTextures();
                break;

            case MenuState::GameRunning:
                Menu::loadButtonAndKeyButtonTextures();
                applicationState.changeGameState(MenuState::GameRunning);
                PixelGame::gameInit();
                PixelGame::gameLoop(tileMap);
                Menu::unloadButtonAndKeyButtonTextures();
                break;

            case MenuState::SettingsMenu:
                Menu::loadButtonAndKeyButtonTextures();
                applicationState.changeGameState(MenuState::SettingsMenu);
                Menu::drawSettingsMenu(currentGameState);
                Menu::unloadButtonAndKeyButtonTextures();
                break;

            case MenuState::KeyBindingsMenu:
                Menu::loadButtonAndKeyButtonTextures();
                applicationState.changeGameState(MenuState::KeyBindingsMenu);
                Menu::drawKeyBindingsMenu(currentGameState);
                Menu::unloadButtonAndKeyButtonTextures();
                break;

            case MenuState::PauseMenu:
                Menu::loadButtonAndKeyButtonTextures();
                applicationState.changeGameState(MenuState::PauseMenu);
                ConfigFunction::toggleGamePause();
                Menu::drawPauseMenu(currentGameState);
                Menu::unloadButtonAndKeyButtonTextures();
                break;

            case MenuState::ResumeGame:
                Menu::loadButtonAndKeyButtonTextures();
                applicationState.changeGameState(MenuState::ResumeGame);
                ConfigFunction::toggleGamePause();
                Menu::unloadButtonAndKeyButtonTextures();
                break;

            case MenuState::VolumeSliders:
                Menu::loadButtonAndKeyButtonTextures();
                applicationState.changeGameState(MenuState::VolumeSliders);
                Menu::drawVolumeSlidersMenu(currentGameState);
                Menu::unloadButtonAndKeyButtonTextures();
                break;

            case MenuState::Control:
                Menu::loadButtonAndKeyButtonTextures();
                applicationState.changeGameState(MenuState::Control);
                Menu::drawControlMenu(currentGameState);
                Menu::unloadButtonAndKeyButtonTextures();
                break;

            case MenuState::Language:
                Menu::loadButtonAndKeyButtonTextures();
                applicationState.changeGameState(MenuState::Language);
                Menu::drawLanguageMenu(currentGameState);
                Menu::unloadButtonAndKeyButtonTextures();
                break;

            case MenuState::ControllerMenu:
                Menu::loadButtonAndKeyButtonTextures();
                applicationState.changeGameState(MenuState::ControllerMenu);
                Menu::drawControllerMenu(currentGameState);
                Menu::unloadButtonAndKeyButtonTextures();
                break;

            case MenuState::None:
                applicationState.changeGameState(MenuState::None);
                Menu::unloadButtonAndKeyButtonTextures();
                ConfigNotConst::isGameRunning = false;
                break;
        }
    }
    CloseWindow();

    return EXIT_SUCCESS;
}