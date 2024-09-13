#include "GameState.h"
#include "config.h"
#include "Configuration.h"
#include "TextureManage.h"
#include <math.h>
#include "Menu.h"
#include "PixelGame.h"
#include "raylib.h"
#include "tileson.h"
#include "Utils.h"
#include "VMouse.h"
#include "WindowSizeScale.h"

Texture2D logoTexSmall;
Texture2D logoTexBig;

void loadAssetsBasedOnWindowSize()
{
    // Load large versions of assets
    Menu::initBackgroundGifLarge();
    Menu::initButtonsFull();

    Image logoBig = LoadImage("assets/graphics/Buttons/LogoBig.png");
    if (logoBig.data == nullptr)
    {
        // Handle error
        return;
    }

    logoTexBig = LoadTextureFromImage(logoBig);
    if (logoTexBig.id == 0)
    {
        // Handle error
        UnloadImage(logoBig);
        return;
    }
    logoTexBig.width = logoBig.width / 3;
    logoTexBig.height = logoBig.height / 3;
    UnloadImage(logoBig);
}

int main()
{
    GameState applicationState;
    InitWindow(1920, 1057, PixelGameConfig::PROJECT_NAME); // Start with small window size
    SetTargetFPS(ConfigConst::targetFPS);
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    InitAudioDevice();

    PixelGame::loadMap("assets/graphics/newTileset&Tilemap/Overworld.tmj");
    SetExitKey(KEY_F4);
    ToggleFullscreen();

    RenderTexture canvasSmall = LoadRenderTexture(480, 270);
    if (canvasSmall.id == 0)
    {
        // Handle error
        return EXIT_FAILURE;
    }

    float renderScale = 1.0f;
    TextureManager::init();
    PixelGame::gameInit();
    Vector2 previousWindowSize = {(float) GetScreenWidth(), (float) GetScreenHeight()};

    loadAssetsBasedOnWindowSize();

    while (ConfigNotConst::isGameRunning && !WindowShouldClose())
    {
        Vector2 currentWindowSize = {(float) GetScreenWidth(), (float) GetScreenHeight()};

        if (currentWindowSize.x != previousWindowSize.x || currentWindowSize.y != previousWindowSize.y)
        {
            loadAssetsBasedOnWindowSize();
            previousWindowSize = currentWindowSize;
        }

        renderScale = fminf(currentWindowSize.x / 480.0f, currentWindowSize.y / 270.0f);

        Rectangle renderRectangle = WindowSizeScale::calculateRenderRectangle(renderScale);
        VMouse::calcVMouse(renderRectangle, renderScale);

        BeginDrawing();
        ClearBackground(BLACK);

        // Draw the background GIF scaled to the small canvas size
        DrawTexturePro(Menu::backgroundTex,
                       {0, 0, (float)Menu::backgroundTex.width, (float)Menu::backgroundTex.height},
                       {0, 0, 1920, 1057},
                       {0, 0}, 0.0f, WHITE);
        // Update and draw the logo
        Texture2D logoTex = logoTexBig;
        float logoWidth = logoTexBig.width;
        float logoX = (1920 - logoWidth) / 2.0f;
        float logoY = 1057 / 13.0f;
        DrawTextureEx(logoTex, {logoX, logoY}, 0.0f, 1.0f, WHITE);

        // Update button positions and hitboxes
        Menu::updateButtonPositions({1920, 1057});

        std::cout << "Current window size: " << currentWindowSize.x << "x" << currentWindowSize.y << std::endl;
        BeginTextureMode(canvasSmall);
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

        // Draw the small canvas scaled to the current window size
        DrawTexturePro(canvasSmall.texture, {0, 0, (float)canvasSmall.texture.width, (float)-canvasSmall.texture.height},
                       {0, 0, currentWindowSize.x, currentWindowSize.y}, {0, 0}, 0.0f, WHITE);

        EndDrawing();
    }

    UnloadTexture(logoTexSmall);
    UnloadTexture(logoTexBig);
    Menu::unloadBackgroundGif();
    CloseWindow();
    return EXIT_SUCCESS;
}