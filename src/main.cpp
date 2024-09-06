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
    InitWindow(PixelGameConfig::ScreenWidth, PixelGameConfig::ScreenHeight, PixelGameConfig::PROJECT_NAME);
    SetTargetFPS(ConfigConst::targetFPS);
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    InitAudioDevice();

    PixelGame::loadMap("assets/graphics/newTileset&Tilemap/Overworld.tmj");
    SetExitKey(KEY_F4);

    RenderTexture canvas = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
    if (canvas.id == 0)
    {
        // Handle error
        return EXIT_FAILURE;
    }

    float renderScale = 1.0f;
    TextureManager::init();
    PixelGame::gameInit();
    Vector2 previousWindowSize = {(float) GetScreenWidth(), (float) GetScreenHeight()};

    Menu::initBackgroundGif();

    Image logo = LoadImage("assets/graphics/Buttons/Logo_official.png");
    if (logo.data == nullptr)
    {
        // Handle error
        return EXIT_FAILURE;
    }

    Texture2D logoTex = LoadTextureFromImage(logo);
    if (logoTex.id == 0)
    {
        // Handle error
        UnloadImage(logo);
        return EXIT_FAILURE;
    }

    logoTex.width = logo.width / 6;
    logoTex.height = logo.height / 6;
    UnloadImage(logo);

    while (ConfigNotConst::isGameRunning && !WindowShouldClose())
    {
        Vector2 currentWindowSize = {(float) GetScreenWidth(), (float) GetScreenHeight()};

        if (currentWindowSize.x != previousWindowSize.x || currentWindowSize.y != previousWindowSize.y)
        {
            // Handle window resize
            if (currentGameState.currentGameMenu != MenuState::MainMenu)
            {
                PixelGame::ReloadAssets(logoTex, canvas);
            }

            previousWindowSize = currentWindowSize;
        }

        renderScale = fminf(currentWindowSize.x / PixelGameConfig::ScreenWidth,
                            currentWindowSize.y / PixelGameConfig::ScreenHeight);

        Rectangle renderRectangle = WindowSizeScale::calculateRenderRectangle(renderScale);
        VMouse::calcVMouse(renderRectangle, renderScale);

        BeginDrawing();
        ClearBackground(BLACK);
        BeginTextureMode(canvas);

        // Draw the background GIF scaled to the current window size
        DrawTexturePro(Menu::backgroundTex,
                       {0, 0, (float)Menu::backgroundTex.width, (float)Menu::backgroundTex.height},
                       {0, 0, currentWindowSize.x, currentWindowSize.y},
                       {0, 0}, 0.0f, WHITE);

        // Update and draw the logo
        float logoX = (currentWindowSize.x - logoTex.width * renderScale) / 2.0f;
        float logoY = currentWindowSize.y / 13.0f;
        DrawTextureEx(logoTex, {logoX, logoY}, 0.0f, renderScale, WHITE);

        // Update button positions and hitboxes
        Menu::updateButtonPositions(currentWindowSize);

        switch (applicationState.currentGameMenu)
        {
            case MenuState::MainMenu:
                Menu::drawMainMenu(applicationState);
                break;
            case MenuState::GameRunning:
                PixelGame::startSequence();
                if(PixelGame::state == gameLoopState)
                {
                    PixelGame::gameLoop(PixelGame::getMap());
                }
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
                InGameHud::health = 5;
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
        DrawTexturePro(canvas.texture, {0, 0, (float)canvas.texture.width, (float)-canvas.texture.height},
                       {0, 0, currentWindowSize.x, currentWindowSize.y}, {0, 0}, 0.0f, WHITE);
        EndDrawing();
    }

    UnloadTexture(logoTex);
    Menu::unloadBackgroundGif();
    CloseWindow();
    return EXIT_SUCCESS;
}