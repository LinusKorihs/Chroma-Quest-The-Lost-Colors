#include "GameState.h"
#include "config.h"
#include "Configuration.h"
#include "TextureManage.h"
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

    PixelGame::loadMap("assets/graphics/newTileset&Tilemap/Overworld.tmj");

    SetExitKey(KEY_F4);

    RenderTexture canvas = LoadRenderTexture(PixelGameConfig::ScreenWidth, PixelGameConfig::ScreenHeight);

    float renderScale = 1.0f;
    TextureManager::init();
    PixelGame::gameInit();

    Vector2 previousWindowSize = {(float) GetScreenWidth(), (float) GetScreenHeight()};

    // Initialize the background GIF
    Menu::initBackgroundGif();

    while (ConfigNotConst::isGameRunning && !WindowShouldClose())
    {
        Vector2 currentWindowSize = {(float) GetScreenWidth(), (float) GetScreenHeight()};

        if (currentWindowSize.x != previousWindowSize.x || currentWindowSize.y != previousWindowSize.y)
        {
            previousWindowSize = currentWindowSize; // Update previous window size
        }

        // Calculate the render scale based on the current window size
        renderScale = fminf(currentWindowSize.x / PixelGameConfig::ScreenWidth,
                            currentWindowSize.y / PixelGameConfig::ScreenHeight);

        // Calculate the render rectangle for letterboxing
        Rectangle renderRectangle = WindowSizeScale::calculateRenderRectangle(renderScale);

        // Update virtual mouse position
        VMouse::calcVMouse(renderRectangle, renderScale);

        BeginDrawing();
        ClearBackground(BLACK);
        BeginTextureMode(canvas);

        // Draw the background texture scaled to the current window size
        DrawTexturePro(canvas.texture,
                       {0, 0, (float) canvas.texture.width, (float) -canvas.texture.height},
                       {0, 0, currentWindowSize.x, currentWindowSize.y},
                       {0, 0},
                       0.0f,
                       WHITE);

        switch (applicationState.currentGameMenu)
        {
            case MenuState::MainMenu:
                Menu::drawMainMenu(applicationState);
                break;
            case MenuState::GameRunning:
                PixelGame::gameLoop(PixelGame::getMap());
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
        DrawTexturePro(canvas.texture, {0, 0, (float) canvas.texture.width, (float) -canvas.texture.height},
                       renderRectangle, {0, 0}, 0.0f, WHITE);
        EndDrawing();
    }

    // Unload the background GIF
    Menu::unloadBackgroundGif();

    CloseWindow();
    return EXIT_SUCCESS;
}