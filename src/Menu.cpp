#include <iostream>
#include <cmath>
#include "GameState.h"
#include "Audio.h"
#include "config.h"
#include "Configuration.h"
#include "InGameHud.h"
#include "TextureManage.h"
#include "Menu.h"
#include "raylib.h"
#include "SetKeyBindings.h"
#include "UnloadResources.h"
#include "Utils.h"

std::vector<float> Menu::buttonPos;

RenderTexture Menu::canvas = {0};

HudImageButton startGameButton, settingsMenuButton, exitGameButton, resumeGameButton, quitGameButton, volumeSettingsButton, controlSettingsButton, languageSettingsButton, keyBoardSettingsButton, controllerSettingsButton, englishLanguageButton, germanLanguageButton;

HudImageButton startButtonFull, settingsButtonFull, exitButtonFull;
HudImageButton startButtonHoverFull, settingsButtonHoverFull, exitButtonHoverFull;

HudImageButton playButtonNormal, playButtonHover, playButtonFull, playButtonHoverFull;

float smallSpacing = 50.0f; // Adjust this value to increase or decrease the space between buttons
float bigSpacing = 150.0f; // Adjust this value to increase or decrease the space between buttons

float Menu::sliderSpacing = 75.0f; // Adjust this value to increase or decrease the space between sliders
bool Menu::showButtonRectangles = false;
Image Menu::backgroundPic;
Texture2D Menu::backgroundTex;
int Menu::animFrames = 0;
int Menu::currentAnimFrame = 0;
int Menu::frameDelay = 8;
int Menu::frameCounter = 0;

void Menu::initBackgroundGif()
{
    unloadBackgroundGif();

    backgroundPic = LoadImageAnim("assets/background.gif", &animFrames);
    backgroundTex = LoadTextureFromImage(backgroundPic);

    // Update the background GIF
    updateBackgroundAnimation();
}

void Menu::initBackgroundGifLarge()
{
    unloadBackgroundGif();

    backgroundPic = LoadImageAnim("assets/backgroundBig.gif", &animFrames);
    backgroundTex = LoadTextureFromImage(backgroundPic);

    // Update the background GIF
    updateBackgroundAnimation();
}

void Menu::unloadBackgroundGif()
{
    UnloadTexture(backgroundTex);
    UnloadImage(backgroundPic);
}

void Menu::updateBackgroundAnimation()
{
    frameCounter++;
    if (frameCounter >= frameDelay)
    {
        currentAnimFrame++;
        if (currentAnimFrame >= animFrames) currentAnimFrame = 0;

        unsigned int nextFrameDataOffset = backgroundPic.width * backgroundPic.height * 4 * currentAnimFrame;
        UpdateTexture(backgroundTex, ((unsigned char *)backgroundPic.data) + nextFrameDataOffset);

        frameCounter = 0;
    }
}

void Menu::initButtonsFull()
{
    startButtonFull.texture = LoadTexture("assets/graphics/Buttons/bigButtons/play.png");
    settingsButtonFull.texture = LoadTexture("assets/graphics/Buttons/bigButtons/settings.png");
    exitButtonFull.texture = LoadTexture("assets/graphics/Buttons/bigButtons/exit.png");

    startButtonHoverFull.texture = LoadTexture("assets/graphics/Buttons/bigButtons/playRGB.png");
    settingsButtonHoverFull.texture = LoadTexture("assets/graphics/Buttons/bigButtons/settingsRGB.png");
    exitButtonHoverFull.texture = LoadTexture("assets/graphics/Buttons/bigButtons/exitRGB.png");
}

void Menu::updateButtonPositions(Vector2 windowSize)
{
    float buttonWidth = 200.0f; // Adjust the button width
    float buttonHeight = 100.0f; // Adjust the button height
    float spacing = 20.0f; // Adjust the spacing between buttons

    float startX = (windowSize.x - buttonWidth) / 2.0f;
    float startY = (windowSize.y - (buttonHeight + spacing) * 3) / 2.0f;

    startButtonFull.rec = {startX, startY, buttonWidth, buttonHeight};
    settingsButtonFull.rec = {startX, startY + buttonHeight + spacing, buttonWidth, buttonHeight};
    exitButtonFull.rec = {startX, startY + 2 * (buttonHeight + spacing), buttonWidth, buttonHeight};
}

void Menu::unloadButtonsFull()
{
    if (startButtonFull.texture.id != 0)
    {
        HudImageButton::unloadImageButton(startButtonFull);
    }

    if (settingsButtonFull.texture.id != 0)
    {
        HudImageButton::unloadImageButton(settingsButtonFull);
    }

    if (exitButtonFull.texture.id != 0)
    {
        HudImageButton::unloadImageButton(exitButtonFull);
    }

    if (startButtonHoverFull.texture.id != 0)
    {
        HudImageButton::unloadImageButton(startButtonHoverFull);
    }

    if (settingsButtonHoverFull.texture.id != 0)
    {
        HudImageButton::unloadImageButton(settingsButtonHoverFull);
    }

    if (exitButtonHoverFull.texture.id != 0)
    {
        HudImageButton::unloadImageButton(exitButtonHoverFull);
    }
}

int Menu::drawMainMenu(GameState &currentGameState)
{
    initButtonsFull();

    Vector2 windowSize = {(float) GetScreenWidth(), (float) GetScreenHeight()};

    updateButtonPositions(windowSize);

    // Draw buttons
    //DrawTextureRec(startButtonFull.texture, {0, 0, (float)startButtonFull.texture.width, (float)startButtonFull.texture.height}, {startButtonFull.rec.x, startButtonFull.rec.y}, WHITE);
    //DrawTextureRec(settingsButtonFull.texture, {0, 0, (float)settingsButtonFull.texture.width, (float)settingsButtonFull.texture.height}, {settingsButtonFull.rec.x, settingsButtonFull.rec.y}, WHITE);
    //DrawTextureRec(exitButtonFull.texture, {0, 0, (float)exitButtonFull.texture.width, (float)exitButtonFull.texture.height}, {exitButtonFull.rec.x, exitButtonFull.rec.y}, WHITE);

    InGameHud::drawBigButton(startButtonFull);
    InGameHud::drawBigButton(settingsButtonFull);
    InGameHud::drawBigButton(exitButtonFull);

    // Draw hover states if necessary
    if (CheckCollisionPointRec(GetMousePosition(), startButtonFull.rec))
    {
        DrawTextureRec(startButtonHoverFull.texture, {0, 0, (float)startButtonHoverFull.texture.width, (float)startButtonHoverFull.texture.height}, {startButtonFull.rec.x, startButtonFull.rec.y}, WHITE);
    }
    if (CheckCollisionPointRec(GetMousePosition(), settingsButtonFull.rec))
    {
        DrawTextureRec(settingsButtonHoverFull.texture, {0, 0, (float)settingsButtonHoverFull.texture.width, (float)settingsButtonHoverFull.texture.height}, {settingsButtonFull.rec.x, settingsButtonFull.rec.y}, WHITE);
    }
    if (CheckCollisionPointRec(GetMousePosition(), exitButtonFull.rec))
    {
        DrawTextureRec(exitButtonHoverFull.texture, {0, 0, (float)exitButtonHoverFull.texture.width, (float)exitButtonHoverFull.texture.height}, {exitButtonFull.rec.x, exitButtonFull.rec.y}, WHITE);
    }

    // Check button clicks
    if (CheckCollisionPointRec(GetMousePosition(), startButtonFull.rec) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        currentGameState.changeGameState(MenuState::GameRunning);
        ConfigNotConst::isGameRunning = true;
        unloadBackgroundGif();
    }
    if (CheckCollisionPointRec(GetMousePosition(), settingsButtonFull.rec) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        currentGameState.changeGameState(MenuState::SettingsMenu);
    }
    if (CheckCollisionPointRec(GetMousePosition(), exitButtonFull.rec) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        ConfigNotConst::isGameRunning = false;
    }

    if (IsKeyPressed(KEY_ESCAPE))
    {
        ConfigNotConst::isGameRunning = false;
    }

    if (IsKeyPressed(KEY_H))
    {
        showButtonRectangles = !showButtonRectangles;
    }

    if (showButtonRectangles)
    {
        DrawRectangleLinesEx(startButtonFull.rec, 3, BLUE);
        std::cout << "Start button rectangle: " << startButtonFull.rec.x << ", " << startButtonFull.rec.y << ", " << startButtonFull.rec.width << ", " << startButtonFull.rec.height << std::endl;
        DrawRectangleLinesEx(settingsButtonFull.rec, 4, BLUE);
        std::cout << "Settings button rectangle: " << settingsButtonFull.rec.x << ", " << settingsButtonFull.rec.y << ", " << settingsButtonFull.rec.width << ", " << settingsButtonFull.rec.height << std::endl;
        DrawRectangleLinesEx(exitButtonFull.rec, 5, BLUE);
        std::cout << "Exit button rectangle: " << exitButtonFull.rec.x << ", " << exitButtonFull.rec.y << ", " << exitButtonFull.rec.width << ", " << exitButtonFull.rec.height << std::endl;
    }

    updateBackgroundAnimation();

    return ConfigNotConst::isProgramRunning ? 1 : 0;
}

void Menu::drawSettingsMenu(GameState &currentGameState)
{
    Vector2 windowSize = {(float) GetScreenWidth(), (float) GetScreenHeight()};
    if (GetScreenWidth() == 1920 && GetScreenHeight() == 1057)
    {
        if(playButtonNormal.texture.id + playButtonHover.texture.id > 0)
        {
            // Unload small buttons if they are loaded
            DrawTexturePro(Menu::backgroundTex,
                           {0, 0, (float)Menu::backgroundTex.width, (float)Menu::backgroundTex.height},
                           {0, 0, 1920, 1080},
                           {0, 0}, 0.0f, WHITE);
            // Initialize full-size button
            playButtonFull.texture = TextureManager::getTexture("playBig");
            playButtonHoverFull.texture = TextureManager::getTexture("playBigPressed");
        }

        // Use full-size mode button
        playButtonFull.rec = {(windowSize.x - Button::buttonWidthBig) / 2, static_cast<float>((windowSize.y - Button::buttonHeightBig) / 1.5), Button::buttonWidthBig, Button::buttonHeightBig};
        InGameHud::drawBigButton(playButtonFull);

        if (CheckCollisionPointRec(GetMousePosition(), playButtonFull.rec))
        {
            playButtonHoverFull.rec = {(windowSize.x - Button::buttonWidthBig) / 2, static_cast<float>((windowSize.y - Button::buttonHeightBig) / 1.5), Button::buttonWidthBig, Button::buttonHeightBig};
            InGameHud::drawBigButton(playButtonHoverFull);
        }

        // Check button clicks for the full-size button
        if (CheckCollisionPointRec(GetMousePosition(), playButtonFull.rec) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            currentGameState.changeGameState(MenuState::GameRunning);
            ConfigNotConst::isGameRunning = true;
            unloadBackgroundGif();
        }

        if (IsKeyPressed(KEY_ESCAPE))
        {
            currentGameState.currentGameMenu = MenuState::MainMenu;
        }

        if (showButtonRectangles)
        {
            DrawRectangleLinesEx(playButtonFull.rec, 1, BLUE);
        }
    }

    updateBackgroundAnimation();
}

void Menu::drawVolumeSlidersMenu(GameState &currentGameState)
{
    ClearBackground(DARKGRAY);

    Rectangle sliderPos1 = Audio::updateSliderPositions(Audio::index = 0);
    Audio::drawVolumeSlider(VolumeType::Global, &ConfigNotConst::globalVolumeLevel, "Global Volume", "Globale Lautstärke", sliderPos1.y);

    Rectangle sliderPos2 = Audio::updateSliderPositions(Audio::index = 1);
    Audio::drawVolumeSlider(VolumeType::BGMusic, &ConfigNotConst::backgroundMusicVolumeLevel, "Music Volume", "Musiklautstärke", sliderPos2.y);

    Rectangle sliderPos3 = Audio::updateSliderPositions(Audio::index = 2);
    Audio::drawVolumeSlider(VolumeType::SFX, &ConfigNotConst::soundEffectsVolumeLevel, "Sound Effect Volume", "Soundeffektlautstärke", sliderPos3.y);

    if (IsKeyPressed(KEY_ESCAPE))
    {
        currentGameState.currentGameMenu = MenuState::SettingsMenu;
    }
}

void Menu::drawLanguageMenu(GameState &currentGameState)
{
    //Menu::buttonPos = updateButtonPositions();
    float newButtonWidth = Menu::buttonPos[0];
    float newButtonHeight = Menu::buttonPos[1];

    englishLanguageButton.texture = TextureManager::getTexture("LanguageENButtonTexture");
    Button::updateButtonDimensions(englishLanguageButton, newButtonWidth, newButtonHeight + smallSpacing * 1, Button::buttonWidthSmall, Button::buttonHeightSmall);
    englishLanguageButton.buttonText = LanguageManager::getLocalizedGameText("English", "Englisch");

    germanLanguageButton.texture = TextureManager::getTexture("LanguageDEButtonTexture");
    Button::updateButtonDimensions(germanLanguageButton, newButtonWidth, newButtonHeight + smallSpacing * 2, Button::buttonWidthSmall, Button::buttonHeightSmall);
    germanLanguageButton.buttonText = LanguageManager::getLocalizedGameText("German", "Deutsch");

    ClearBackground(DARKGRAY);

    //InGameHud::drawSmallButton(englishLanguageButton);
    //InGameHud::drawSmallButton(germanLanguageButton);

    if (Button::checkButtonClick(englishLanguageButton.rec, "English", "Englisch"))
    {
        if (LanguageManager::currentLanguage == LanguageManager::Language::German)
        {
            LanguageManager::toggleLanguage();
        }
    }

    if (Button::checkButtonClick(germanLanguageButton.rec, "German", "Deutsch"))
    {
        if (LanguageManager::currentLanguage == LanguageManager::Language::English)
        {
            LanguageManager::toggleLanguage();
        }
    }

    if (IsKeyPressed(KEY_ESCAPE))
    {
        currentGameState.currentGameMenu = MenuState::SettingsMenu;
    }
}

void Menu::drawPauseMenu(GameState &currentGameState)
{
    //Menu::buttonPos = updateButtonPositions();
    float newButtonWidth = Menu::buttonPos[0];
    float newButtonHeight = Menu::buttonPos[1];

    resumeGameButton.texture = TextureManager::getTexture("ResumeButtonTexture");
    Button::updateButtonDimensions(resumeGameButton, newButtonWidth, newButtonHeight + smallSpacing * 1, Button::buttonWidthSmall, Button::buttonHeightSmall);
    resumeGameButton.buttonText = LanguageManager::getLocalizedGameText("Resume PixelGame", "Spiel fortsetzen");

    quitGameButton.texture = TextureManager::getTexture("QuitButtonTexture");
    Button::updateButtonDimensions(quitGameButton, newButtonWidth, newButtonHeight + smallSpacing * 2, Button::buttonWidthSmall, Button::buttonHeightSmall);
    quitGameButton.buttonText = LanguageManager::getLocalizedGameText("Back to Menu", "Zurück zum Menü");

    ClearBackground(DARKGRAY);

    //InGameHud::drawSmallButton(resumeGameButton);
    //InGameHud::drawSmallButton(quitGameButton);

    Audio::updateAudioVolumes();

    if (Button::checkButtonClick(resumeGameButton.rec, "Resume PixelGame", "Spiel fortsetzen"))
    {
        currentGameState.changeGameState(MenuState::ResumeGame);  // Update state to ResumeGame
        ConfigNotConst::isGamePaused = false;
    }
    if (Button::checkButtonClick(quitGameButton.rec, "Back to Menu", "Zurück zum Menü"))
    {
        currentGameState.currentGameMenu = MenuState::MainMenu;  // Update state to MainMenu
        ConfigNotConst::isGameRunning = false;  // Optionally stop the game
    }
    DrawText(LanguageManager::getLocalizedGameText("Pause Menu", "Pause Menü"), 10, 10, 20, BLACK);
}