#include <iostream>
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

float buttonSpacing = 50.0f; // Adjust this value to increase or decrease the space between buttons
float Menu::sliderSpacing = 75.0f; // Adjust this value to increase or decrease the space between sliders

Image Menu::backgroundPic;
Texture2D Menu::backgroundTex;
int Menu::animFrames = 0;
int Menu::currentAnimFrame = 0;
int Menu::frameDelay = 8;
int Menu::frameCounter = 0;

void Menu::initBackgroundGif()
{
    backgroundPic = LoadImageAnim("assets/background.gif", &animFrames);
    backgroundTex = LoadTextureFromImage(backgroundPic);

    // Update the background GIF
    updateBackgroundAnimation();

    // Draw the background GIF
    int currentScreenWidth = GetScreenWidth();
    float scaleX = (float)currentScreenWidth / backgroundTex.width;
    DrawTextureEx(backgroundTex, (Vector2){0, 0}, 0.0f, scaleX, WHITE);
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

int Menu::drawMainMenu(GameState &currentGameState)
{
    // Load button textures
    startGameButton.texture = TextureManager::getTexture("playButton");
    settingsMenuButton.texture = TextureManager::getTexture("settingsButton");
    exitGameButton.texture = TextureManager::getTexture("exitButton");

    updateButtonPositions({(float) GetScreenWidth(), (float) GetScreenHeight()});

    // Draw buttons with scaling
    DrawTextureEx(startGameButton.texture, (Vector2){startGameButton.x, startGameButton.y / 2 - buttonSpacing / 2}, 0.0f, 0.5f, WHITE);
    //std::cout << "startGameButton.texture.width: " << startGameButton.texture.width << " startGameButton.texture.height: " << startGameButton.texture.height << " startGameButton.x: " << startGameButton.x << " startGameButton.y: " << startGameButton.y << std::endl;
    DrawTextureEx(settingsMenuButton.texture, (Vector2){settingsMenuButton.x, settingsMenuButton.y / 2}, 0.0f, 0.5f, WHITE);
    DrawTextureEx(exitGameButton.texture, (Vector2){exitGameButton.x, exitGameButton.y / 2 + buttonSpacing / 2}, 0.0f, 0.5f, WHITE);

    // Define button rectangles with new dimensions
    startGameButton.rec = {startGameButton.x, startGameButton.y / 2 - buttonSpacing / 2, startGameButton.width, startGameButton.height};
    //std::cout << "startGameButton.rec: " << startGameButton.rec.x << " " << startGameButton.rec.y << " " << startGameButton.rec.width << " " << startGameButton.rec.height << std::endl;
    settingsMenuButton.rec = {settingsMenuButton.x, settingsMenuButton.y / 2 , settingsMenuButton.width, settingsMenuButton.height};
    exitGameButton.rec = {exitGameButton.x, exitGameButton.y / 2 + buttonSpacing / 2, exitGameButton.width, exitGameButton.height};

    updateBackgroundAnimation();

    // Check button clicks
    if (CheckCollisionPointRec(GetMousePosition(), startGameButton.rec) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        currentGameState.changeGameState(MenuState::GameRunning);
        ConfigNotConst::isGameRunning = true;

        unloadBackgroundGif();
    }

    if (CheckCollisionPointRec(GetMousePosition(), settingsMenuButton.rec) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        currentGameState.changeGameState(MenuState::SettingsMenu);
    }

    if (CheckCollisionPointRec(GetMousePosition(), exitGameButton.rec) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        TraceLog(LOG_INFO, "Quit button clicked");
        ConfigNotConst::isGameRunning = false;
        currentGameState.changeGameState(MenuState::None);
    }

    if (IsKeyPressed(KEY_ESCAPE))
    {
        currentGameState.gameMenuStack.pop();
        if (!currentGameState.gameMenuStack.empty())
        {
            currentGameState.currentGameMenu = currentGameState.gameMenuStack.top();
        }
        else
        {
            currentGameState.currentGameMenu = MenuState::MainMenu;
        }
    }

    return ConfigNotConst::isProgramRunning ? 1 : 0;
}

void Menu::updateButtonPositions(Vector2 windowSize)
{
    float newButtonWidth = windowSize.x / 4.0f;  // Example calculation
    float newButtonHeight = windowSize.y / 10.0f;  // Example calculation

    // Calculate the center position for the buttons
    float centerX = windowSize.x / 2.0f;
    float centerY = windowSize.y / 2.0f;

    // Assuming the logo is centered at the top and has a height of logoHeight
    float logoHeight = windowSize.y / 5.0f;  // Example calculation for logo height

    // Update positions and dimensions of buttons
    Button::updateButtonDimensions(
            startGameButton, centerX - newButtonWidth / 2.0f, centerY - newButtonHeight / 2.0f + logoHeight + buttonSpacing, newButtonWidth, newButtonHeight);
    Button::updateButtonDimensions(
            settingsMenuButton, centerX - newButtonWidth / 2.0f, centerY + logoHeight / 2.0f + newButtonHeight + buttonSpacing * 2, newButtonWidth, newButtonHeight);
    Button::updateButtonDimensions(
            exitGameButton, centerX - newButtonWidth / 2.0f, centerY + logoHeight / 2.0f + newButtonHeight * 2 + buttonSpacing * 3, newButtonWidth, newButtonHeight);
}

void Menu::drawSettingsMenu(GameState &currentGameState)
{
    updateButtonPositions({(float) GetScreenWidth(), (float) GetScreenHeight()});
    float newButtonWidth = Menu::buttonPos[0];
    float newButtonHeight = Menu::buttonPos[1];

    volumeSettingsButton.texture = TextureManager::getTexture("VolumeButtonTexture");
    Button::updateButtonDimensions(volumeSettingsButton, newButtonWidth, newButtonHeight + buttonSpacing * 0, Button::buttonWidth, Button::buttonHeight);
    volumeSettingsButton.buttonText = LanguageManager::getLocalizedGameText("Sound", "Ton");

    controlSettingsButton.texture = TextureManager::getTexture("ControlButtonTexture");
    Button::updateButtonDimensions(controlSettingsButton, newButtonWidth, newButtonHeight + buttonSpacing * 1, Button::buttonWidth, Button::buttonHeight);
    controlSettingsButton.buttonText = LanguageManager::getLocalizedGameText("Controls", "Steuerung");

    languageSettingsButton.texture = TextureManager::getTexture("LanguageButtonTexture");
    Button::updateButtonDimensions(languageSettingsButton, newButtonWidth, newButtonHeight + buttonSpacing * 2, Button::buttonWidth, Button::buttonHeight);
    languageSettingsButton.buttonText = LanguageManager::getLocalizedGameText("Language", "Sprache");

    ClearBackground(DARKGRAY);

    InGameHud::drawImageButton(volumeSettingsButton);
    InGameHud::drawImageButton(controlSettingsButton);
    InGameHud::drawImageButton(languageSettingsButton);

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
    Button::updateButtonDimensions(keyBoardSettingsButton, newButtonWidth, newButtonHeight + buttonSpacing * 1, Button::buttonWidth, Button::buttonHeight);
    keyBoardSettingsButton.buttonText = LanguageManager::getLocalizedGameText("Keyboard/Mouse", "Tastatur/Maus");

    controllerSettingsButton.texture = TextureManager::getTexture("ControllerButtonTexture");
    Button::updateButtonDimensions(controllerSettingsButton, newButtonWidth, newButtonHeight + buttonSpacing * 2, Button::buttonWidth, Button::buttonHeight);
    controllerSettingsButton.buttonText = LanguageManager::getLocalizedGameText("Controller", "Kontroller");

    ClearBackground(DARKGRAY);

    InGameHud::drawImageButton(keyBoardSettingsButton);
    InGameHud::drawImageButton(controllerSettingsButton);

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
    Button::updateButtonDimensions(englishLanguageButton, newButtonWidth, newButtonHeight + buttonSpacing * 1, Button::buttonWidth, Button::buttonHeight);
    englishLanguageButton.buttonText = LanguageManager::getLocalizedGameText("English", "Englisch");

    germanLanguageButton.texture = TextureManager::getTexture("LanguageDEButtonTexture");
    Button::updateButtonDimensions(germanLanguageButton, newButtonWidth, newButtonHeight + buttonSpacing * 2, Button::buttonWidth, Button::buttonHeight);
    germanLanguageButton.buttonText = LanguageManager::getLocalizedGameText("German", "Deutsch");

    ClearBackground(DARKGRAY);

    InGameHud::drawImageButton(englishLanguageButton);
    InGameHud::drawImageButton(germanLanguageButton);

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
    Button::updateButtonDimensions(resumeGameButton, newButtonWidth, newButtonHeight + buttonSpacing * 1, Button::buttonWidth, Button::buttonHeight);
    resumeGameButton.buttonText = LanguageManager::getLocalizedGameText("Resume PixelGame", "Spiel fortsetzen");

    quitGameButton.texture = TextureManager::getTexture("QuitButtonTexture");
    Button::updateButtonDimensions(quitGameButton, newButtonWidth, newButtonHeight + buttonSpacing * 2, Button::buttonWidth, Button::buttonHeight);
    quitGameButton.buttonText = LanguageManager::getLocalizedGameText("Back to Menu", "Zurück zum Menü");

    ClearBackground(DARKGRAY);

    InGameHud::drawImageButton(resumeGameButton);
    InGameHud::drawImageButton(quitGameButton);

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