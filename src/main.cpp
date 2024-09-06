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

    //ToggleFullscreen();

    PixelGame::loadMap("assets/graphics/newTileset&Tilemap/Overworld.tmj");
    SetExitKey(KEY_F4);

    RenderTexture canvas = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
    float renderScale = 1.0f;
    TextureManager::init();
    PixelGame::gameInit();
    Vector2 previousWindowSize = {(float) GetScreenWidth(), (float) GetScreenHeight()};

    Menu::initBackgroundGif();

    Image logo = LoadImage("assets/graphics/Buttons/Logo_official.png");
    Texture2D logoTex = LoadTextureFromImage(logo);
    logoTex.width = logo.width / 6;
    logoTex.height = logo.height / 6;
    UnloadImage(logo);

    while (ConfigNotConst::isGameRunning && !WindowShouldClose())
    {
        Vector2 currentWindowSize = {(float) GetScreenWidth(), (float) GetScreenHeight()};

        if (currentWindowSize.x != previousWindowSize.x || currentWindowSize.y != previousWindowSize.y)
        {
            previousWindowSize = currentWindowSize;
        }

        renderScale = fminf(currentWindowSize.x / GetScreenWidth(),
                            currentWindowSize.y / GetScreenHeight());

        Rectangle renderRectangle = WindowSizeScale::calculateRenderRectangle(renderScale);
        VMouse::calcVMouse(renderRectangle, renderScale);

        BeginDrawing();
        ClearBackground(BLACK);
        BeginTextureMode(canvas);

        // Draw the background GIF scaled to the current window size
        DrawTexturePro(Menu::backgroundTex,
                       {0, 0, (float) Menu::backgroundTex.width, (float) Menu::backgroundTex.height},
                       {0, 0, currentWindowSize.x, currentWindowSize.y},
                       {0, 0}, 0.0f, WHITE);

        float logoX = GetScreenWidth() / 2.5;
        float logoY = GetScreenHeight() / 13;
        DrawTexture(logoTex, logoX, logoY, WHITE);

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
    UnloadTexture(logoTex);
    Menu::unloadBackgroundGif();
    CloseWindow();
    return EXIT_SUCCESS;
}