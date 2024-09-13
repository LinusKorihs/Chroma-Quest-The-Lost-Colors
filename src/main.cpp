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

RenderTexture Menu::canvas = {0};

int main()
{
    GameState applicationState;
    InitWindow(PixelGameConfig::ScreenWidth, PixelGameConfig::ScreenHeight, PixelGameConfig::PROJECT_NAME);
    SetTargetFPS(ConfigConst::targetFPS);
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    InitAudioDevice();

    PixelGame::loadMap("assets/graphics/newTileset&Tilemap/Overworld.tmj");
    SetExitKey(KEY_F4);

    Menu::canvas = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
    if (Menu::canvas.id == 0)
    {
        // Handle error
        return EXIT_FAILURE;
    }

    float renderScale = 1.0f;
    TextureManager::init();
    PixelGame::gameInit();
    Vector2 previousWindowSize = {(float) GetScreenWidth(), (float) GetScreenHeight()};

    Menu::initBackgroundGif();
    Menu::initButtonsSmall();

    Image logoSmall = LoadImage("assets/graphics/Buttons/LogoSmall.png");
    if (logoSmall.data == nullptr)
    {
        // Handle error
        return EXIT_FAILURE;
    }

    Texture2D logoTexSmall = LoadTextureFromImage(logoSmall);
    if (logoTexSmall.id == 0)
    {
        // Handle error
        UnloadImage(logoSmall);
        return EXIT_FAILURE;
    }

    logoTexSmall.width = logoSmall.width / 6;
    logoTexSmall.height = logoSmall.height / 6;
    UnloadImage(logoSmall);

    Image logoBig = LoadImage("assets/graphics/Buttons/LogoBig.png");
    if (logoBig.data == nullptr)
    {
        // Handle error
        return EXIT_FAILURE;
    }
    Texture2D logoTexBig = LoadTextureFromImage(logoBig);
    if (logoTexBig.id == 0)
    {
        // Handle error
        UnloadImage(logoBig);
        return EXIT_FAILURE;
    }
    logoTexBig.width = logoBig.width / 6;
    logoTexBig.height = logoBig.height / 6;
    UnloadImage(logoBig);

    while (ConfigNotConst::isGameRunning && !WindowShouldClose())
    {
        Vector2 currentWindowSize = {(float) GetScreenWidth(), (float) GetScreenHeight()};

        if (currentWindowSize.x != previousWindowSize.x || currentWindowSize.y != previousWindowSize.y)
        {
            // Handle window resize
            if (currentGameState.currentGameMenu != MenuState::MainMenu)
            {
                PixelGame::ReloadAssets(logoTexSmall);
            }
            else
            {
                Menu::reloadBackgroundGif();
            }

            previousWindowSize = currentWindowSize;
        }

        renderScale = fminf(currentWindowSize.x / PixelGameConfig::ScreenWidth,
                            currentWindowSize.y / PixelGameConfig::ScreenHeight);

        Rectangle renderRectangle = WindowSizeScale::calculateRenderRectangle(renderScale);
        VMouse::calcVMouse(renderRectangle, renderScale);

        BeginDrawing();
        ClearBackground(BLACK);

        // Draw the background GIF scaled to the current window size
        if (GetScreenWidth() == 1920 && GetScreenHeight() == 1057)
        {
            DrawTexturePro(Menu::backgroundTex,
                           {0, 0, (float)Menu::backgroundTex.width, (float)Menu::backgroundTex.height},
                           {0, 0, 1920, 1080},
                           {0, 0}, 0.0f, WHITE);
        }
        else
        {
            DrawTexturePro(Menu::backgroundTex,
                           {0, 0, (float)Menu::backgroundTex.width, (float)Menu::backgroundTex.height},
                           {0, 0, currentWindowSize.x, currentWindowSize.y},
                           {0, 0}, 0.0f, WHITE);
        }

        // Update and draw the logoSmall
        Texture2D logoTex = (GetScreenWidth() == 1920 && GetScreenHeight() == 1057) ? logoTexBig : logoTexSmall;
        float logoWidth = (GetScreenWidth() == 1920 && GetScreenHeight() == 1057) ? logoTexBig.width : logoTexSmall.width;
        float logoX = (currentWindowSize.x - logoWidth * renderScale) / 2.0f;
        float logoY = currentWindowSize.y / 13.0f;
        DrawTextureEx(logoTex, {logoX, logoY}, 0.0f, renderScale, WHITE);

        switch (applicationState.currentGameMenu)
        {
            case MenuState::MainMenu:
                Menu::drawMainMenu(applicationState);
                Menu::butRec();
                break;
            case MenuState::GameRunning:
                BeginTextureMode(Menu::canvas);
                PixelGame::startSequence();
                if(PixelGame::state == gameLoopState)
                {
                    PixelGame::gameLoop(PixelGame::getMap());
                }
                if (IsKeyPressed(KEY_ESCAPE))
                {
                    applicationState.currentGameMenu = MenuState::PauseMenu;
                }
                EndTextureMode();
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

        DrawTexturePro(Menu::canvas.texture, {0, 0, (float)Menu::canvas.texture.width, (float)-Menu::canvas.texture.height},
                       {0, 0, currentWindowSize.x, currentWindowSize.y}, {0, 0}, 0.0f, WHITE);
        EndDrawing();
    }

    UnloadTexture(logoTexSmall);
    Menu::unloadBackgroundGif();
    CloseWindow();
    return EXIT_SUCCESS;
}