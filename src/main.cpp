﻿#include <synchapi.h>
#include "GameState.h"
#include "config.h"
#include "Configuration.h"
#include "LoadResources.h"
#include "Menu.h"
#include "PixelGame.h"
#include "raylib.h"
#include "tileson.h"
#include "Utils.h"
#include "VMouse.h"
#include "WindowSizeScale.h"

int main()
{
    GameState applicationState;
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(PixelGameConfig::ScreenWidth, PixelGameConfig::ScreenHeight, PixelGameConfig::PROJECT_NAME);

    SetTargetFPS(ConfigConst::targetFPS);
    InitAudioDevice();

#ifdef GAME_START_FULLSCREEN
    ToggleFullscreen();
#endif

    tson::Tileson tileson;
    auto MapPtr = tileson.parse("assets/graphics/TileSet & TileMap/tilemap.tmj");
    tson::Map& tileMap = *MapPtr;

    SetExitKey(KEY_F4);

    RenderTexture canvas = LoadRenderTexture(PixelGameConfig::ScreenWidth, PixelGameConfig::ScreenHeight);

    float renderScale = 1.0f;
    TextureManager::init();
    PixelGame::gameInit();

    Vector2 previousWindowSize = { (float)GetScreenWidth(), (float)GetScreenHeight() };

    while (ConfigNotConst::isGameRunning && !WindowShouldClose())
    {
        Vector2 currentWindowSize = { (float)GetScreenWidth(), (float)GetScreenHeight() };

        if (currentWindowSize.x != previousWindowSize.x || currentWindowSize.y != previousWindowSize.y)
        {
            previousWindowSize = currentWindowSize; // Update previous window size
        }

        WindowSizeScale::calculateRenderRectangle(renderScale);
        Rectangle renderRectangle = WindowSizeScale::calculateRenderRectangle(renderScale); // Calculate render rectangle for letterbox

        VMouse::calcVMouse(renderRectangle, renderScale); // Update virtual mouse position

        BeginDrawing();
        ClearBackground(BLACK);
        BeginTextureMode(canvas);

        switch (applicationState.currentGameMenu)
        {
            case MenuState::MainMenu:
                Menu::drawMainMenu(applicationState);
                break;
            case MenuState::GameRunning:
                PixelGame::gameLoop(tileMap);
                if (IsKeyPressed(KEY_ESCAPE))
                {
                    applicationState.currentGameMenu = MenuState::PauseMenu;
                }
                break;
            case MenuState::SettingsMenu:
                Menu::drawSettingsMenu(applicationState);
                break;
            case MenuState::KeyBindingsMenu:
                Menu::drawKeyBindingsMenu(applicationState);
                break;
            case MenuState::PauseMenu:
                Menu::drawPauseMenu(applicationState);
                break;
            case MenuState::ResumeGame:
                ConfigFunction::toggleGamePause();
                applicationState.currentGameMenu = MenuState::GameRunning;
                break;
            case MenuState::VolumeSliders:
                Menu::drawVolumeSlidersMenu(applicationState);
                break;
            case MenuState::Control:
                Menu::drawControlMenu(applicationState);
                break;
            case MenuState::Language:
                Menu::drawLanguageMenu(applicationState);
                break;
            case MenuState::ControllerMenu:
                Menu::drawControllerMenu(applicationState);
                break;
            case MenuState::None:
                ConfigNotConst::isGameRunning = false;
                break;
        }

        EndTextureMode();
        DrawTexturePro(canvas.texture, {0, 0, (float)canvas.texture.width, (float)-canvas.texture.height}, renderRectangle, {0, 0}, 0.0f, WHITE);
        EndDrawing();
    }

    CloseWindow();
    return EXIT_SUCCESS;
}
