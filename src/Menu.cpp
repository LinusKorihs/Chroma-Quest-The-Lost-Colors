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

HudImageButton startGameButton, settingsMenuButton, exitGameButton, resumeGameButton, quitGameButton, volumeSettingsButton, controlSettingsButton, languageSettingsButton, keyBoardSettingsButton, controllerSettingsButton, englishLanguageButton, germanLanguageButton;

HudImageButton startButtonNormal, settingsButtonNormal, exitButtonNormal;
HudImageButton startButtonHover, settingsButtonHover, exitButtonHover;

HudImageButton startButtonFull, settingsButtonFull, exitButtonFull;
HudImageButton startButtonHoverFull, settingsButtonHoverFull, exitButtonHoverFull;

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
    if (GetScreenWidth() > 960 && GetScreenHeight() > 540)
    {
        backgroundPic = LoadImageAnim("assets/backgroundBig.gif", &animFrames);
    }
    else
    {
        backgroundPic = LoadImageAnim("assets/background.gif", &animFrames);
    }
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

void Menu::initButtonsSmall()
{
    // Initialize small sized buttons
    startButtonNormal.texture = TextureManager::getTexture("playSmall");
    settingsButtonNormal.texture = TextureManager::getTexture("settingsSmall");
    exitButtonNormal.texture = TextureManager::getTexture("exitSmall");

    startButtonHover.texture = TextureManager::getTexture("playSmallPressed");
    settingsButtonHover.texture = TextureManager::getTexture("settingsSmallPressed");
    exitButtonHover.texture = TextureManager::getTexture("exitSmallPressed");
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

void Menu::unloadButtonsSmall()
{
    if (startButtonNormal.texture.id != 0)
    {
        HudImageButton::unloadImageButton(startButtonNormal);
    }

    if (settingsButtonNormal.texture.id != 0)
    {
        HudImageButton::unloadImageButton(settingsButtonNormal);
    }

    if (exitButtonNormal.texture.id != 0)
    {
        HudImageButton::unloadImageButton(exitButtonNormal);
    }

    if (startButtonHover.texture.id != 0)
    {
        HudImageButton::unloadImageButton(startButtonHover);
    }

    if (settingsButtonHover.texture.id != 0)
    {
        HudImageButton::unloadImageButton(settingsButtonHover);
    }

    if (exitButtonHover.texture.id != 0)
    {
        HudImageButton::unloadImageButton(exitButtonHover);
    }
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
    if (GetScreenWidth() == 1920 && GetScreenHeight() == 1057)
    {
        if(startButtonNormal.texture.id + settingsButtonNormal.texture.id + exitButtonNormal.texture.id + startButtonHover.texture.id + settingsButtonHover.texture.id + exitButtonHover.texture.id > 0)
        {
            unloadButtonsSmall();
            DrawTexturePro(Menu::backgroundTex,
                           {0, 0, (float)Menu::backgroundTex.width, (float)Menu::backgroundTex.height},
                           {0, 0, 1920, 1080},
                           {0, 0}, 0.0f, WHITE);
            initButtonsFull();
        }

        // Use full-size mode buttons
        startButtonFull.rec = {(windowSize.x - Button::buttonWidthBig) / 2, static_cast<float>((windowSize.y - Button::buttonHeightBig) / 1.5), Button::buttonWidthBig, Button::buttonHeightBig};
        settingsButtonFull.rec = {(windowSize.x - Button::buttonWidthBig) / 2, static_cast<float>((windowSize.y - Button::buttonHeightBig) / 1.5 + bigSpacing), Button::buttonWidthBig, Button::buttonHeightBig};
        exitButtonFull.rec = {(windowSize.x - Button::buttonWidthBig) / 2, static_cast<float>((windowSize.y - Button::buttonHeightBig) / 1.5 + bigSpacing * 2), Button::buttonWidthBig, Button::buttonHeightBig};

        InGameHud::drawBigButton(startButtonFull);
        InGameHud::drawBigButton(settingsButtonFull);
        InGameHud::drawBigButton(exitButtonFull);

        if (CheckCollisionPointRec(GetMousePosition(), startButtonFull.rec))
        {
            startButtonHoverFull.rec = {(windowSize.x - Button::buttonWidthBig) / 2, static_cast<float>((windowSize.y - Button::buttonHeightBig) / 1.5), Button::buttonWidthBig, Button::buttonHeightBig};
            InGameHud::drawBigButton(startButtonHoverFull);
        }

        if (CheckCollisionPointRec(GetMousePosition(), settingsButtonFull.rec))
        {
            settingsButtonHoverFull.rec = {(windowSize.x - Button::buttonWidthBig) / 2, static_cast<float>((windowSize.y - Button::buttonHeightBig) / 1.5 + bigSpacing), Button::buttonWidthBig, Button::buttonHeightBig};
            InGameHud::drawBigButton(settingsButtonHoverFull);
        }

        if (CheckCollisionPointRec(GetMousePosition(), exitButtonFull.rec))
        {
            exitButtonHoverFull.rec = {(windowSize.x - Button::buttonWidthBig) / 2, static_cast<float>((windowSize.y - Button::buttonHeightBig) / 1.5 + bigSpacing * 2), Button::buttonWidthBig, Button::buttonHeightBig};
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
    }
    else
    {
        if(startButtonFull.texture.id + settingsButtonFull.texture.id + exitButtonFull.texture.id + startButtonHoverFull.texture.id + settingsButtonHoverFull.texture.id + exitButtonHoverFull.texture.id > 0)
        {
            unloadButtonsFull();
            ClearBackground(DARKGRAY);
            float currentWidth = GetScreenWidth();
            float currentHeight = GetScreenHeight();
            DrawTexturePro(Menu::backgroundTex,
                           {0, 0, (float)Menu::backgroundTex.width, (float)Menu::backgroundTex.height},
                           {0, 0, currentWidth, currentHeight},
                           {0, 0}, 0.0f, WHITE);
            initButtonsSmall();
        }

        // Use normal mode buttons
        startButtonNormal.rec = {(windowSize.x - Button::buttonWidthSmall) / 2, static_cast<float>((windowSize.y - Button::buttonHeightSmall) / 1.5 - smallSpacing), Button::buttonWidthSmall, Button::buttonHeightSmall};
        settingsButtonNormal.rec = {(windowSize.x - Button::buttonWidthSmall) / 2, static_cast<float>((windowSize.y - Button::buttonHeightSmall) / 1.5), Button::buttonWidthSmall, Button::buttonHeightSmall};
        exitButtonNormal.rec = {(windowSize.x - Button::buttonWidthSmall) / 2, static_cast<float>((windowSize.y - Button::buttonHeightSmall) / 1.5 + smallSpacing), Button::buttonWidthSmall, Button::buttonHeightSmall};

        InGameHud::drawSmallButton(startButtonNormal);
        InGameHud::drawSmallButton(settingsButtonNormal);
        InGameHud::drawSmallButton(exitButtonNormal);

        if (CheckCollisionPointRec(GetMousePosition(), startButtonNormal.rec))
        {
            startButtonHover.rec = {(windowSize.x - Button::buttonWidthSmall) / 2, static_cast<float>((windowSize.y - Button::buttonHeightSmall) / 1.5 - smallSpacing), Button::buttonWidthSmall, Button::buttonHeightSmall};
            InGameHud::drawSmallButton(startButtonHover);
        }

        if (CheckCollisionPointRec(GetMousePosition(), settingsButtonNormal.rec))
        {
            settingsButtonHover.rec = {(windowSize.x - Button::buttonWidthSmall) / 2, static_cast<float>((windowSize.y - Button::buttonHeightSmall) / 1.5), Button::buttonWidthSmall, Button::buttonHeightSmall};
            InGameHud::drawSmallButton(settingsButtonHover);
        }

        if (CheckCollisionPointRec(GetMousePosition(), exitButtonNormal.rec))
        {
            exitButtonHover.rec = {(windowSize.x - Button::buttonWidthSmall) / 2, static_cast<float>((windowSize.y - Button::buttonHeightSmall) / 1.5 + smallSpacing), Button::buttonWidthSmall, Button::buttonHeightSmall};
            InGameHud::drawSmallButton(exitButtonHover);
        }

        // Check button clicks for the normal mode buttons
        if (CheckCollisionPointRec(GetMousePosition(), startButtonNormal.rec) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            currentGameState.changeGameState(MenuState::GameRunning);
            ConfigNotConst::isGameRunning = true;
            unloadBackgroundGif();
        }

        if (CheckCollisionPointRec(GetMousePosition(), settingsButtonNormal.rec) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            currentGameState.changeGameState(MenuState::SettingsMenu);
        }

        if (CheckCollisionPointRec(GetMousePosition(), exitButtonNormal.rec) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            ConfigNotConst::isGameRunning = false;
        }

        if (IsKeyPressed(KEY_ESCAPE))
        {
            ConfigNotConst::isGameRunning = false;
        }

        if (showButtonRectangles)
        {
            DrawRectangleLinesEx(startButtonNormal.rec, 1, RED);
            DrawRectangleLinesEx(settingsButtonNormal.rec, 1, RED);
            DrawRectangleLinesEx(exitButtonNormal.rec, 1, RED);
        }
    }

    updateBackgroundAnimation();

    return ConfigNotConst::isProgramRunning ? 1 : 0;
}

void Menu::updateButtonPositions(Vector2 windowSize)
{

}

void Menu::drawSettingsMenu(GameState &currentGameState)
{
    updateButtonPositions({(float) GetScreenWidth(), (float) GetScreenHeight()});
    float newButtonWidth = Menu::buttonPos[0];
    float newButtonHeight = Menu::buttonPos[1];

    volumeSettingsButton.texture = TextureManager::getTexture("VolumeButtonTexture");
    Button::updateButtonDimensions(volumeSettingsButton, newButtonWidth, newButtonHeight + smallSpacing * 0, Button::buttonWidthSmall, Button::buttonHeightSmall);
    volumeSettingsButton.buttonText = LanguageManager::getLocalizedGameText("Sound", "Ton");

    controlSettingsButton.texture = TextureManager::getTexture("ControlButtonTexture");
    Button::updateButtonDimensions(controlSettingsButton, newButtonWidth, newButtonHeight + smallSpacing * 1, Button::buttonWidthSmall, Button::buttonHeightSmall);
    controlSettingsButton.buttonText = LanguageManager::getLocalizedGameText("Controls", "Steuerung");

    languageSettingsButton.texture = TextureManager::getTexture("LanguageButtonTexture");
    Button::updateButtonDimensions(languageSettingsButton, newButtonWidth, newButtonHeight + smallSpacing * 2, Button::buttonWidthSmall, Button::buttonHeightSmall);
    languageSettingsButton.buttonText = LanguageManager::getLocalizedGameText("Language", "Sprache");

    ClearBackground(DARKGRAY);

    InGameHud::drawSmallButton(volumeSettingsButton);
    InGameHud::drawSmallButton(controlSettingsButton);
    InGameHud::drawSmallButton(languageSettingsButton);

    if (Button::checkButtonClick(volumeSettingsButton.rec, "Sound", "Ton"))
    {
        currentGameState.currentGameMenu = MenuState::VolumeSliders;
    }

    if (Button::checkButtonClick(controlSettingsButton.rec, "Controls", "Steuerung"))
    {
        currentGameState.currentGameMenu = MenuState::Control;
    }

    if (Button::checkButtonClick(languageSettingsButton.rec, "Language", "Sprache"))
    {
        currentGameState.currentGameMenu = MenuState::Language;
    }

    if (IsKeyPressed(KEY_ESCAPE))
    {
        currentGameState.currentGameMenu = MenuState::MainMenu;
    }
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