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

Texture2D logoTexBig;
Texture2D playButton;
Texture2D settingsButton;
Texture2D exitButton;

void loadAssetsBasedOnWindowSize()
{
    // Load large versions of assets
    Menu::initBackgroundGifLarge();

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

    playButton = LoadTexture("assets/graphics/Buttons/bigButtons/play.png");
    settingsButton = LoadTexture("assets/graphics/Buttons/bigButtons/settings.png");
    exitButton = LoadTexture("assets/graphics/Buttons/bigButtons/exit.png");
}

void unloadAssetsBasedOnWindowSize()
{
    // Unload large versions of assets
    Menu::unloadBackgroundGif();

    UnloadTexture(logoTexBig);
    UnloadTexture(playButton);
    UnloadTexture(settingsButton);
    UnloadTexture(exitButton);
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
    //ToggleFullscreen();

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

        if (applicationState.currentGameMenu == MenuState::MainMenu)
        {
            // Draw the background GIF scaled to the small canvas size
            DrawTexturePro(Menu::backgroundTex,
                           {0, 0, (float)Menu::backgroundTex.width, (float)Menu::backgroundTex.height},
                           {0, 0, 1920, 1057},
                           {0, 0}, 0.0f, WHITE);
            // Update and draw the logo
            Texture2D logoTex = logoTexBig;
            logoTex.width = logoTexBig.width;
            logoTex.height = logoTexBig.height;
            float logoWidth = logoTexBig.width;
            float logoX = (1920 - logoWidth) / 2.0f;
            float logoY = 1057 / 13.0f;
            DrawTextureEx(logoTex, {logoX, logoY}, 0.0f, 1.0f, WHITE);

            // Update button positions and hitboxes
            //Menu::updateButtonPositions({1920, 1057});

            //std::cout << "Current window size: " << currentWindowSize.x << "x" << currentWindowSize.y << std::endl;

            Texture2D playButton = LoadTexture("assets/graphics/Buttons/bigButtons/play.png");
            playButton.width = playButton.width / 2;
            playButton.height = playButton.height / 2;
            DrawTexture(playButton, (1920 - playButton.width) / 2, (1080 - playButton.height) / 2 - 150, WHITE);

            Texture2D settingsButton = LoadTexture("assets/graphics/Buttons/bigButtons/settings.png");
            settingsButton.width = settingsButton.width / 2;
            settingsButton.height = settingsButton.height / 2;
            DrawTexture(settingsButton, (1920 - settingsButton.width) / 2, (1080 - settingsButton.height) / 2, WHITE);

            Texture2D exitButton = LoadTexture("assets/graphics/Buttons/bigButtons/exit.png");
            exitButton.width = exitButton.width / 2;
            exitButton.height = exitButton.height / 2;
            DrawTexture(exitButton, (1920 - exitButton.width) / 2, (1080 - exitButton.height) / 2 + 150, WHITE);

            Rectangle playButtonRec = {static_cast<float>((1920 - playButton.width) / 2),
                                       static_cast<float>((1080 - playButton.height) / 2 - 150),
                                       static_cast<float>(playButton.width), static_cast<float>(playButton.height)};
            Rectangle settingsButtonRec = {static_cast<float>((1920 - settingsButton.width) / 2),
                                           static_cast<float>((1080 - settingsButton.height) / 2),
                                           static_cast<float>(settingsButton.width),
                                           static_cast<float>(settingsButton.height)};
            Rectangle exitButtonRec = {static_cast<float>((1920 - exitButton.width) / 2),
                                       static_cast<float>((1080 - exitButton.height) / 2 + 150),
                                       static_cast<float>(exitButton.width), static_cast<float>(exitButton.height)};

            //DrawRectangleLines(playButtonRec.x, playButtonRec.y, playButtonRec.width, playButtonRec.height, PURPLE);
            //DrawRectangleLines(settingsButtonRec.x, settingsButtonRec.y, settingsButtonRec.width, settingsButtonRec.height, GREEN);
            //DrawRectangleLines(exitButtonRec.x, exitButtonRec.y, exitButtonRec.width, exitButtonRec.height, BLUE);

            if (CheckCollisionPointRec(GetMousePosition(), playButtonRec))
            {
                Texture2D playButtonHover = LoadTexture("assets/graphics/Buttons/bigButtons/playRGB.png");
                playButtonHover.width = playButtonHover.width / 2;
                playButtonHover.height = playButtonHover.height / 2;
                DrawTexture(playButtonHover, (1920 - playButtonHover.width) / 2,
                            (1080 - playButtonHover.height) / 2 - 150, WHITE);
            }

            if (CheckCollisionPointRec(GetMousePosition(), settingsButtonRec))
            {
                Texture2D settingsButtonHover = LoadTexture("assets/graphics/Buttons/bigButtons/settingsRGB.png");
                settingsButtonHover.width = settingsButtonHover.width / 2;
                settingsButtonHover.height = settingsButtonHover.height / 2;
                DrawTexture(settingsButtonHover, (1920 - settingsButtonHover.width) / 2,
                            (1080 - settingsButtonHover.height) / 2, WHITE);
            }

            if (CheckCollisionPointRec(GetMousePosition(), exitButtonRec))
            {
                Texture2D exitButtonHover = LoadTexture("assets/graphics/Buttons/bigButtons/exitRGB.png");
                exitButtonHover.width = exitButtonHover.width / 2;
                exitButtonHover.height = exitButtonHover.height / 2;
                DrawTexture(exitButtonHover, (1920 - exitButtonHover.width) / 2,
                            (1080 - exitButtonHover.height) / 2 + 150, WHITE);
            }

            if (CheckCollisionPointRec(GetMousePosition(), playButtonRec) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                applicationState.currentGameMenu = MenuState::GameRunning;
                ConfigNotConst::isGameRunning = true;
                Menu::unloadBackgroundGif();
            }

            if (CheckCollisionPointRec(GetMousePosition(), settingsButtonRec) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                applicationState.currentGameMenu = MenuState::MainMenu;
            }

            if (CheckCollisionPointRec(GetMousePosition(), exitButtonRec) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                applicationState.currentGameMenu = MenuState::None;
            }
        }
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
            case MenuState::Language:
                Menu::drawLanguageMenu(applicationState);
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

    unloadAssetsBasedOnWindowSize();
    CloseWindow();
    return EXIT_SUCCESS;
}