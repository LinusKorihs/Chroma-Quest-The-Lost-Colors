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

int menuScreenWidth = GetScreenWidth();
int menuScreenHeight = GetScreenHeight();
float buttonSpacing = 50.0f; // Adjust this value to increase or decrease the space between buttons
float Menu::sliderSpacing = 75.0f; // Adjust this value to increase or decrease the space between sliders

std::vector<float> Menu::UpdateButtonPositions()
{
    float upMenuScreenWidth = GetScreenWidth();
    float upMenuScreenHeight = GetScreenHeight();

    float newButtonWidth = Button::buttonScreenWidth;
    float newButtonHeight = (float)PixelGameConfig::ScreenHeight / 2 - 50;
    Menu::buttonPos = {newButtonWidth, newButtonHeight, upMenuScreenWidth};

    float startY = (upMenuScreenHeight - (3 * newButtonHeight + 2 * buttonSpacing)) / 2; // Calculate initial y position for the first button (centered vertically)
    Rectangle buttonRec1 = {(upMenuScreenWidth - newButtonWidth) / 2, startY + buttonSpacing * 0, newButtonWidth, newButtonHeight};
    Rectangle buttonRec2 = {(upMenuScreenWidth - newButtonWidth) / 2, startY + newButtonHeight + buttonSpacing * 1, newButtonWidth, newButtonHeight};
    Rectangle buttonRec3 = {(upMenuScreenWidth - newButtonWidth) / 2, startY + 2 * newButtonHeight + buttonSpacing * 2, newButtonWidth, newButtonHeight};
    Rectangle buttonRec4 = {(upMenuScreenWidth - newButtonWidth) / 2, startY + newButtonHeight + buttonSpacing * 1, newButtonWidth, newButtonHeight};
    Rectangle buttonRec5 = {(upMenuScreenWidth - newButtonWidth) / 2, startY + 2 * newButtonHeight + buttonSpacing * 2, newButtonWidth, newButtonHeight};

    startGameButton.rec = buttonRec1;
    settingsMenuButton.rec = buttonRec2;
    exitGameButton.rec = buttonRec3;

    volumeSettingsButton.rec = buttonRec1;
    controlSettingsButton.rec = buttonRec2;
    languageSettingsButton.rec = buttonRec3;

    englishLanguageButton.rec = buttonRec4;
    germanLanguageButton.rec = buttonRec5;

    keyBoardSettingsButton.rec = buttonRec4;
    controllerSettingsButton.rec = buttonRec5;

    resumeGameButton.rec = buttonRec4;
    quitGameButton.rec = buttonRec5;

    return Menu::buttonPos;
}

int Menu::drawMainMenu(GameState &currentGameState)
{
    Menu::buttonPos = UpdateButtonPositions();
    float newButtonWidth = Menu::buttonPos[0];
    float newButtonHeight = Menu::buttonPos[1];
    int upMenuScreenWidth = static_cast<int>(Menu::buttonPos[2]);

    startGameButton.texture = TextureManager::getTexture("StartGameButtonTexture");
    Button::updateButtonDimensions(startGameButton, newButtonWidth, newButtonHeight + buttonSpacing * 0, Button::buttonWidth, Button::buttonHeight);
    startGameButton.buttonText = LanguageManager::getLocalizedGameText("Start Game", "Spiel starten");

    settingsMenuButton.texture = TextureManager::getTexture("SettingsMenuButtonTexture");
    Button::updateButtonDimensions(settingsMenuButton, newButtonWidth, newButtonHeight + buttonSpacing * 1, Button::buttonWidth, Button::buttonHeight);
    settingsMenuButton.buttonText = LanguageManager::getLocalizedGameText("Settings", "Einstellungen");

    exitGameButton.texture = TextureManager::getTexture("ExitGameButtonTexture");
    Button::updateButtonDimensions(exitGameButton, newButtonWidth, newButtonHeight + buttonSpacing * 2, Button::buttonWidth, Button::buttonHeight);
    exitGameButton.buttonText = LanguageManager::getLocalizedGameText("Quit Game", "Spiel beenden");

    ClearBackground(DARKGRAY);

    DrawText(LanguageManager::getLocalizedGameText("Chroma Quest: The Lost Colors", "Chroma Quest: Die verlorenen Farben"),
             upMenuScreenWidth / 2 - MeasureText(LanguageManager::getLocalizedGameText("Chroma Quest: The Lost Colors", "Chroma Quest: Die verlorenen Farben"), 20) / 2,
             50, 20, BLACK);

    InGameHud::drawImageButton(startGameButton);
    InGameHud::drawImageButton(settingsMenuButton);
    InGameHud::drawImageButton(exitGameButton);

    if (Button::checkButtonClick(startGameButton.rec, "Start Game", "Spiel starten"))
    {
        currentGameState.changeGameState(MenuState::GameRunning);
        ConfigNotConst::isGameRunning = true;
    }

    if (Button::checkButtonClick(settingsMenuButton.rec, "Settings", "Einstellungen"))
    {
        currentGameState.changeGameState(MenuState::SettingsMenu);
    }

    if (Button::checkButtonClick(exitGameButton.rec, "Quit Game", "Spiel beenden"))
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

void Menu::drawSettingsMenu(GameState &currentGameState)
{
    Menu::buttonPos = UpdateButtonPositions();
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
    Menu::buttonPos = UpdateButtonPositions();
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
    DrawText(text, menuScreenWidth / 2 - menuTextWidth / 2, menuScreenHeight / 2, 20, BLACK);

    if (IsKeyPressed(KEY_ESCAPE))
    {
        currentGameState.currentGameMenu = MenuState::Control;
    }
}

void Menu::drawLanguageMenu(GameState &currentGameState)
{
    Menu::buttonPos = UpdateButtonPositions();
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
    Menu::buttonPos = UpdateButtonPositions();
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