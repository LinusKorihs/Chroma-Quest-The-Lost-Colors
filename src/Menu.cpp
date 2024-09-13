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

void Menu::reloadBackgroundGif()
{
    unloadBackgroundGif();
    initBackgroundGif();
}

void Menu::updateButtonPositions(Vector2 windowSize)
{
    // Example button positions update logic
    float buttonWidth = 100.0f;
    float buttonHeight = 50.0f;
    float spacing = 10.0f;

    // Update button positions based on window size
    float startX = (windowSize.x - buttonWidth) / 2.0f;
    float startY = (windowSize.y - (buttonHeight + spacing) * 3) / 2.0f;

    // Assuming you have buttons like playButton, settingsButton, etc.
    startButtonFull.rec = {startX, startY, buttonWidth, buttonHeight};
    settingsButtonFull.rec = {startX, startY + buttonHeight + spacing, buttonWidth, buttonHeight};
    exitButtonFull.rec = {startX, startY + 2 * (buttonHeight + spacing), buttonWidth, buttonHeight};
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

void Menu::butRec()
{
    if (IsKeyPressed(KEY_H))
    {
        showButtonRectangles = !showButtonRectangles;
    }
}

void Menu::initButtonsFull()
{
    // Initialize full sized buttons
    startButtonFull.texture = TextureManager::getTexture("playBig");
    settingsButtonFull.texture = TextureManager::getTexture("settingsBig");
    exitButtonFull.texture = TextureManager::getTexture("exitBig");

    startButtonHoverFull.texture = TextureManager::getTexture("playBigPressed");
    settingsButtonHoverFull.texture = TextureManager::getTexture("settingsBigPressed");
    exitButtonHoverFull.texture = TextureManager::getTexture("exitBigPressed");
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
    Vector2 windowSize = {(float) GetScreenWidth(), (float) GetScreenHeight()};
    
    initButtonsFull();

    // Use full-size mode buttons
    startButtonFull.rec = {(windowSize.x - Button::buttonWidthBig) / 2,
                           static_cast<float>((windowSize.y - Button::buttonHeightBig) / 1.5), Button::buttonWidthBig,
                           Button::buttonHeightBig};
    settingsButtonFull.rec = {(windowSize.x - Button::buttonWidthBig) / 2,
                              static_cast<float>((windowSize.y - Button::buttonHeightBig) / 1.5 + bigSpacing),
                              Button::buttonWidthBig, Button::buttonHeightBig};
    exitButtonFull.rec = {(windowSize.x - Button::buttonWidthBig) / 2,
                          static_cast<float>((windowSize.y - Button::buttonHeightBig) / 1.5 + bigSpacing * 2),
                          Button::buttonWidthBig, Button::buttonHeightBig};

    InGameHud::drawBigButton(startButtonFull);
    InGameHud::drawBigButton(settingsButtonFull);
    InGameHud::drawBigButton(exitButtonFull);

    if (CheckCollisionPointRec(GetMousePosition(), startButtonFull.rec))
    {
        startButtonHoverFull.rec = {(windowSize.x - Button::buttonWidthBig) / 2,
                                    static_cast<float>((windowSize.y - Button::buttonHeightBig) / 1.5),
                                    Button::buttonWidthBig, Button::buttonHeightBig};
        InGameHud::drawBigButton(startButtonHoverFull);
    }

    if (CheckCollisionPointRec(GetMousePosition(), settingsButtonFull.rec))
    {
        settingsButtonHoverFull.rec = {(windowSize.x - Button::buttonWidthBig) / 2,
                                       static_cast<float>((windowSize.y - Button::buttonHeightBig) / 1.5 + bigSpacing),
                                       Button::buttonWidthBig, Button::buttonHeightBig};
        InGameHud::drawBigButton(settingsButtonHoverFull);
    }

    if (CheckCollisionPointRec(GetMousePosition(), exitButtonFull.rec))
    {
        exitButtonHoverFull.rec = {(windowSize.x - Button::buttonWidthBig) / 2,
                                   static_cast<float>((windowSize.y - Button::buttonHeightBig) / 1.5 + bigSpacing * 2),
                                   Button::buttonWidthBig, Button::buttonHeightBig};
        InGameHud::drawBigButton(exitButtonHoverFull);
    }

    // Check button clicks for the full-size button
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

    if (showButtonRectangles)
    {
        DrawRectangleLinesEx(startButtonFull.rec, 1, BLUE);
        DrawRectangleLinesEx(settingsButtonFull.rec, 1, BLUE);
        DrawRectangleLinesEx(exitButtonFull.rec, 1, BLUE);
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
    else
    {
        if(playButtonFull.texture.id + playButtonHoverFull.texture.id > 0)
        {
            // Unload full-size buttons if they are loaded
            unloadButtonsFull();
            ClearBackground(DARKGRAY);
            float currentWidth = GetScreenWidth();
            float currentHeight = GetScreenHeight();
            DrawTexturePro(Menu::backgroundTex,
                           {0, 0, (float)Menu::backgroundTex.width, (float)Menu::backgroundTex.height},
                           {0, 0, currentWidth, currentHeight},
                           {0, 0}, 0.0f, WHITE);
            // Initialize small-size button
            playButtonNormal.texture = TextureManager::getTexture("playSmall");
            playButtonHover.texture = TextureManager::getTexture("playSmallPressed");
        }

        // Use normal mode button
        playButtonNormal.rec = {(windowSize.x - Button::buttonWidthSmall) / 2, static_cast<float>((windowSize.y - Button::buttonHeightSmall) / 1.5), Button::buttonWidthSmall, Button::buttonHeightSmall};
        InGameHud::drawSmallButton(playButtonNormal);

        if (CheckCollisionPointRec(GetMousePosition(), playButtonNormal.rec))
        {
            playButtonHover.rec = {(windowSize.x - Button::buttonWidthSmall) / 2, static_cast<float>((windowSize.y - Button::buttonHeightSmall) / 1.5), Button::buttonWidthSmall, Button::buttonHeightSmall};
            InGameHud::drawSmallButton(playButtonHover);
        }

        // Check button clicks for the normal mode button
        if (CheckCollisionPointRec(GetMousePosition(), playButtonNormal.rec) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
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
            DrawRectangleLinesEx(playButtonNormal.rec, 1, RED);
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

void Menu::drawControlMenu(GameState &currentGameState)
{
    //Menu::buttonPos = updateButtonPositions();
    float newButtonWidth = Menu::buttonPos[0];
    float newButtonHeight = Menu::buttonPos[1];

    keyBoardSettingsButton.texture = TextureManager::getTexture("KeyboardButtonTexture");
    Button::updateButtonDimensions(keyBoardSettingsButton, newButtonWidth, newButtonHeight + smallSpacing * 1, Button::buttonWidthSmall, Button::buttonHeightSmall);
    keyBoardSettingsButton.buttonText = LanguageManager::getLocalizedGameText("Keyboard/Mouse", "Tastatur/Maus");

    controllerSettingsButton.texture = TextureManager::getTexture("ControllerButtonTexture");
    Button::updateButtonDimensions(controllerSettingsButton, newButtonWidth, newButtonHeight + smallSpacing * 2, Button::buttonWidthSmall, Button::buttonHeightSmall);
    controllerSettingsButton.buttonText = LanguageManager::getLocalizedGameText("Controller", "Kontroller");

    ClearBackground(DARKGRAY);

    InGameHud::drawSmallButton(keyBoardSettingsButton);
    InGameHud::drawSmallButton(controllerSettingsButton);

    if (Button::checkButtonClick(keyBoardSettingsButton.rec, "Keyboard/Mouse", "Tastatur/Maus"))
    {
        currentGameState.currentGameMenu = MenuState::KeyBindingsMenu;
        drawKeyBindingsMenu(currentGameState);
    }
    if (Button::checkButtonClick(controllerSettingsButton.rec, "Controller", "Controller"))
    {
        currentGameState.currentGameMenu = MenuState::ControllerMenu;
        drawControllerMenu(currentGameState);
    }

    if (IsKeyPressed(KEY_ESCAPE))
    {
        currentGameState.currentGameMenu = MenuState::SettingsMenu;
    }
}

void Menu::drawKeyBindingsMenu(GameState &currentGameState)
{
    SetKeyBindings::settingTheKeyButtons(currentGameState);

    ClearBackground(DARKGRAY);

    SetKeyBindings::drawKeyBindingsMenu(currentGameState);
}

void Menu::drawControllerMenu(GameState &currentGameState)
{
    ClearBackground(DARKGRAY);

    const char* text = LanguageManager::getLocalizedGameText("No Controller Implementation yet.",
                                                          "Keine Controller Implementierung bisher.");
    int menuTextWidth = MeasureText(text, 20);
    DrawText(text, GetScreenWidth() / 2 - menuTextWidth / 2, GetScreenHeight() / 2, 20, BLACK);

    if (IsKeyPressed(KEY_ESCAPE))
    {
        currentGameState.currentGameMenu = MenuState::Control;
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

    InGameHud::drawSmallButton(englishLanguageButton);
    InGameHud::drawSmallButton(germanLanguageButton);

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

    InGameHud::drawSmallButton(resumeGameButton);
    InGameHud::drawSmallButton(quitGameButton);

    drawVolumeSlidersPauseMenu();
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

void Menu::drawVolumeSlidersPauseMenu()
{
    ClearBackground(DARKGRAY);

    Rectangle sliderPos1 = Audio::updateSliderPositions(Audio::index = 0);
    Audio::drawVolumeSlider(VolumeType::Global, &ConfigNotConst::globalVolumeLevel, "Global Volume", "Globale Lautstärke", sliderPos1.y);

    Rectangle sliderPos2 = Audio::updateSliderPositions(Audio::index = 1);
    Audio::drawVolumeSlider(VolumeType::BGMusic, &ConfigNotConst::backgroundMusicVolumeLevel, "Music Volume", "Musiklautstärke", sliderPos2.y);

    Rectangle sliderPos3 = Audio::updateSliderPositions(Audio::index = 2);
    Audio::drawVolumeSlider(VolumeType::SFX, &ConfigNotConst::soundEffectsVolumeLevel, "Sound Effect Volume", "Soundeffektlautstärke", sliderPos3.y);
}