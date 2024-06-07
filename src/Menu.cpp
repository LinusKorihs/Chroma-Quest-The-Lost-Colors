#include "GameState.h"
#include "Audio.h"
#include "config.h"
#include "Configuration.h"
#include "InGameHud.h"
#include "LoadResources.h"
#include "Menu.h"
#include "raylib.h"
#include "SetKeyBindings.h"
#include "UnloadResources.h"
#include "Utils.h"

HudImageButton startGameButton, settingsMenuButton, exitGameButton, resumeGameButton, quitGameButton, volumeSettingsButton, controlSettingsButton, languageSettingsButton, keyBoardSettingsButton, controllerSettingsButton, englishLanguageButton, germanLanguageButton;

int Menu::drawMainMenu(GameState &gameState)
{
    int menuScreenWidth = PixelGameConfig::ScreenWidth;
    int menuScreenHeight = PixelGameConfig::ScreenHeight;

    startGameButton.texture = ConfigButton::startGameButtonTexture;
    startGameButton.rec = {(float)menuScreenWidth / 2 - startGameButton.texture.width / 2, (float)menuScreenHeight / 2 - 75, (float)startGameButton.texture.width, (float)startGameButton.texture.height};
    startGameButton.buttonText = LanguageManager::getLocalizedGameText("Start Game", "Spiel starten");

    settingsMenuButton.texture = ConfigButton::settingsMenuButtonTexture;
    settingsMenuButton.rec = {(float)menuScreenWidth / 2 - settingsMenuButton.texture.width / 2, (float)menuScreenHeight / 2, (float)settingsMenuButton.texture.width, (float)settingsMenuButton.texture.height};
    settingsMenuButton.buttonText = LanguageManager::getLocalizedGameText("Settings", "Einstellungen");

    exitGameButton.texture = ConfigButton::exitGameButtonTexture;
    exitGameButton.rec = {(float)menuScreenWidth / 2 - exitGameButton.texture.width / 2, (float)menuScreenHeight / 2 + 75, (float)exitGameButton.texture.width, (float)exitGameButton.texture.height};
    exitGameButton.buttonText = LanguageManager::getLocalizedGameText("Quit Game", "Spiel beenden");

    BeginDrawing();
    ClearBackground(DARKGRAY);

    DrawText(LanguageManager::getLocalizedGameText("Chroma Quest: The Lost Colors", "Chroma Quest: Die verlorenen Farben"),
             PixelGameConfig::ScreenWidth/2 - MeasureText(
                     LanguageManager::getLocalizedGameText("Chroma Quest: The Lost Colors",
                                                    "Chroma Quest: Die verlorenen Farben"), 20) / 2, 50, 20, BLACK);

    InGameHud::drawImageButton(startGameButton);
    InGameHud::drawImageButton(settingsMenuButton);
    InGameHud::drawImageButton(exitGameButton);

    if (Button::checkButtonClick(startGameButton.rec, "Start Game", "Spiel starten"))
    {
        gameState.gameMenuStack.push(MenuState::GameRunning);
        gameState.currentGameMenu = MenuState::GameRunning;
        ConfigNotConst::isGameRunning = 1;
    }

    if (Button::checkButtonClick(settingsMenuButton.rec, "Settings", "Einstellungen"))
    {
        gameState.gameMenuStack.push(MenuState::SettingsMenu);
        gameState.currentGameMenu = MenuState::SettingsMenu;
    }

    if (Button::checkButtonClick(exitGameButton.rec, "Quit Game", "Spiel beenden"))
    {
        ConfigNotConst::isGameRunning = false;
        TraceLog(LOG_INFO, "Quit button clicked");
        gameState.gameMenuStack.push(MenuState::None);
        gameState.currentGameMenu = MenuState::None;

    }

    if (IsKeyPressed(KEY_ESCAPE) && !gameState.gameMenuStack.empty())
    {
        gameState.gameMenuStack.pop();
        if (!gameState.gameMenuStack.empty())
        {
            gameState.currentGameMenu = gameState.gameMenuStack.top();
        }
        else
        {
            gameState.currentGameMenu = MenuState::MainMenu;
        }
    }

    EndDrawing();

    return ConfigNotConst::isProgramRunning ? 1 : 0;
}

void Menu::drawKeyBindingsMenu(GameState &gameState)
{
    SetKeyBindings::settingTheKeyButtons(gameState);

    BeginDrawing();
    ClearBackground(DARKGRAY);

    SetKeyBindings::drawKeyBindingsMenu(gameState);

    EndDrawing();
}

int Menu::drawControllerMenu(GameState &gameState)
{
    while (!WindowShouldClose() && ConfigNotConst::isProgramRunning)
    {
        BeginDrawing();
        ClearBackground(DARKGRAY);

        const char* text = LanguageManager::getLocalizedGameText("No Controller Implementation yet.",
                                                          "Keine Controller Implementierung bisher.");
        int menuTextWidth = MeasureText(text, 20);

        DrawText(text, PixelGameConfig::ScreenWidth / 2 - menuTextWidth / 2, PixelGameConfig::ScreenHeight / 2, 20, BLACK);

        if (IsKeyPressed(KEY_ESCAPE))
        {
            gameState.gameMenuStack.pop();
            gameState.currentGameMenu = MenuState::Control;
            return 0;
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}

void Menu::drawLanguageMenu(GameState &gameState)
{
    int menuScreenWidth = PixelGameConfig::ScreenWidth;
    int menuScreenHeight = PixelGameConfig::ScreenHeight;

    englishLanguageButton.texture = ConfigButton::languageDEButtonTexture;
    englishLanguageButton.rec = {(float)menuScreenWidth / 2 - 50, (float)menuScreenHeight / 2 - 50, 150, 30};
    englishLanguageButton.buttonText = LanguageManager::getLocalizedGameText("English", "Englisch");

    germanLanguageButton.texture = ConfigButton::languageENButtonTexture;
    germanLanguageButton.rec = {(float)menuScreenWidth / 2 - 50, (float)menuScreenHeight / 2, 150, 30};
    germanLanguageButton.buttonText = LanguageManager::getLocalizedGameText("German", "Deutsch");

    BeginDrawing();
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
        gameState.gameMenuStack.pop();
        if (!gameState.gameMenuStack.empty())
        {
            gameState.currentGameMenu = gameState.gameMenuStack.top();
        }
        else
        {
            gameState.currentGameMenu = MenuState::SettingsMenu;
        }
    }
    EndDrawing();
}

bool Menu::drawSettingsMenu(GameState &gameState)
{
    int menuScreenWidth = PixelGameConfig::ScreenWidth;
    int menuScreenHeight = PixelGameConfig::ScreenHeight;

    volumeSettingsButton.texture = ConfigButton::volumeButtonTexture;
    volumeSettingsButton.rec = {(float)menuScreenWidth / 2 - 50, (float)menuScreenHeight / 2 - 50, 150, 30};
    volumeSettingsButton.buttonText = LanguageManager::getLocalizedGameText("Sound", "Ton");

    controlSettingsButton.texture = ConfigButton::controlButtonTexture;
    controlSettingsButton.rec = {(float)menuScreenWidth / 2 - 50, (float)menuScreenHeight / 2, 150, 30};
    controlSettingsButton.buttonText = LanguageManager::getLocalizedGameText("Controls", "Steuerung");

    languageSettingsButton.texture = ConfigButton::languageButtonTexture;
    languageSettingsButton.rec = {(float)menuScreenWidth / 2 - 50, (float)menuScreenHeight / 2 + 50, 150, 30};
    languageSettingsButton.buttonText = LanguageManager::getLocalizedGameText("Language", "Sprache");

    BeginDrawing();
    ClearBackground(DARKGRAY);

    InGameHud::drawImageButton(volumeSettingsButton);
    InGameHud::drawImageButton(controlSettingsButton);
    InGameHud::drawImageButton(languageSettingsButton);

    if (Button::checkButtonClick(volumeSettingsButton.rec, "Sound", "Ton"))
    {
        gameState.gameMenuStack.push(MenuState::VolumeSliders);
        gameState.currentGameMenu = MenuState::VolumeSliders;
    }

    if (Button::checkButtonClick(controlSettingsButton.rec, "Controls", "Steuerung"))
    {
        gameState.gameMenuStack.push(MenuState::Control);
        gameState.currentGameMenu = MenuState::Control;
    }

    if (Button::checkButtonClick(languageSettingsButton.rec, "Language", "Sprache"))
    {
        gameState.gameMenuStack.push(MenuState::Language);
        gameState.currentGameMenu = MenuState::Language;
    }

    if (IsKeyPressed(KEY_ESCAPE))
    {
        gameState.gameMenuStack.pop();
        if (!gameState.gameMenuStack.empty())
        {
            gameState.currentGameMenu = gameState.gameMenuStack.top();
        }
        else
        {
            gameState.currentGameMenu = MenuState::MainMenu;
        }
    }
    EndDrawing();

    return true;
}

void Menu::drawPauseMenu(GameState &gameState)
{
    int menuScreenWidth = PixelGameConfig::ScreenWidth;
    int menuScreenHeight = PixelGameConfig::ScreenHeight;

    resumeGameButton.texture = ConfigButton::resumeButtonTexture;
    resumeGameButton.rec = {(float)menuScreenWidth / 2 - 50, (float)menuScreenHeight / 2 - 175, 150, 30};
    resumeGameButton.buttonText = LanguageManager::getLocalizedGameText("Resume PixelGame", "Spiel fortsetzen");

    quitGameButton.texture = ConfigButton::quitButtonTexture;
    quitGameButton.rec = {(float)menuScreenWidth / 2 - 50, (float)menuScreenHeight / 2 + 150, 150, 30};
    quitGameButton.buttonText = LanguageManager::getLocalizedGameText("Back to Menu", "Zurück zum Menü");

    while (!WindowShouldClose() && ConfigNotConst::isGamePaused)
    {
        BeginDrawing();
        ClearBackground(DARKGRAY);

        InGameHud::drawImageButton(resumeGameButton);
        InGameHud::drawImageButton(quitGameButton);

        drawVolumeSlidersPauseMenu(gameState);
        Audio::updateAudioVolumes();

        if (Button::checkButtonClick(resumeGameButton.rec, "Resume PixelGame", "Spiel fortsetzen"))
        {
            ConfigNotConst::isGamePaused = false;
            gameState.gameMenuStack.pop();
            break;
        }
        else if (Button::checkButtonClick(quitGameButton.rec, "Back to Menu", "Zurück zum Menü"))
        {
            ConfigNotConst::isGamePaused = false;
            ConfigNotConst::isGameRunning = 0;
            gameState.gameMenuStack.pop();
            gameState.currentGameMenu = MenuState::MainMenu;
            break;
        }

        DrawText(LanguageManager::getLocalizedGameText("Pause Menu", "Pause Menü"), 10, 10, 20, BLACK);

        EndDrawing();
    }
}

bool Menu::drawControlMenu(GameState &gameState)
{
    keyBoardSettingsButton.texture = ConfigButton::keyboardButtonTexture;
    keyBoardSettingsButton.rec = {(float)Button::buttonScreenWidth - 25, (float)PixelGameConfig::ScreenHeight / 2 - 50, Button::buttonWidth + 50, Button::buttonHeight};
    keyBoardSettingsButton.buttonText = LanguageManager::getLocalizedGameText("Keyboard/Mouse", "Tastatur/Maus");

    controllerSettingsButton.texture = ConfigButton::controllerButtonTexture;
    controllerSettingsButton.rec = {(float)Button::buttonScreenWidth - 25, (float)PixelGameConfig::ScreenHeight / 2, Button::buttonWidth + 50, Button::buttonHeight};
    controllerSettingsButton.buttonText = LanguageManager::getLocalizedGameText("Controller", "Kontroller");

    BeginDrawing();
    ClearBackground(DARKGRAY);

    InGameHud::drawImageButton(keyBoardSettingsButton);
    InGameHud::drawImageButton(controllerSettingsButton);

    if (Button::checkButtonClick(keyBoardSettingsButton.rec, "Keyboard/Mouse", "Tastatur/Maus"))
    {
        gameState.gameMenuStack.push(MenuState::KeyBindingsMenu);
        gameState.currentGameMenu = MenuState::KeyBindingsMenu;
        drawKeyBindingsMenu(gameState);
    }
    if (Button::checkButtonClick(controllerSettingsButton.rec, "Controller", "Controller"))
    {
        gameState.gameMenuStack.push(MenuState::ControllerMenu);
        gameState.currentGameMenu = MenuState::ControllerMenu;
        drawControllerMenu(gameState);
    }

    if (IsKeyPressed(KEY_ESCAPE))
    {
        gameState.gameMenuStack.pop();
        if (!gameState.gameMenuStack.empty())
        {
            gameState.currentGameMenu = gameState.gameMenuStack.top();
        }
        else
        {
            gameState.currentGameMenu = MenuState::SettingsMenu;
        }
    }
    EndDrawing();

    return true;
}

void Menu::drawVolumeSlidersMenu(GameState &gameState)
{
    int screenHeight = PixelGameConfig::ScreenHeight;

    BeginDrawing();
    ClearBackground(DARKGRAY);

    Audio::drawVolumeSlider(VolumeType::Global, &ConfigNotConst::globalVolumeLevel, "Global Volume", "Globale Lautstärke",
                            (float) screenHeight / 2 - 75);
    Audio::drawVolumeSlider(VolumeType::BGMusic, &ConfigNotConst::backgroundMusicVolumeLevel, "Music Volume",
                            "Musiklautstärke",
                            (float) screenHeight / 2);
    Audio::drawVolumeSlider(VolumeType::SFX, &ConfigNotConst::soundEffectsVolumeLevel, "Sound Effect Volume",
                            "Soundeffektlautstärke",
                            (float) screenHeight / 2 + 75);

    if (IsKeyPressed(KEY_ESCAPE))
    {
        gameState.gameMenuStack.pop();
        if (!gameState.gameMenuStack.empty())
        {
            gameState.currentGameMenu = gameState.gameMenuStack.top();
        }
        else
        {
            gameState.currentGameMenu = MenuState::SettingsMenu;
        }
    }

    EndDrawing();
}

void Menu::drawVolumeSlidersPauseMenu(GameState &gameState)
{
    int screenHeight = PixelGameConfig::ScreenHeight;

    Audio::drawVolumeSlider(VolumeType::Global, &ConfigNotConst::globalVolumeLevel, "Global Volume", "Globale Lautstärke",
                            (float) screenHeight / 2 - 75);
    Audio::drawVolumeSlider(VolumeType::BGMusic, &ConfigNotConst::backgroundMusicVolumeLevel, "Music Volume",
                            "Musiklautstärke",
                            (float) screenHeight / 2);
    Audio::drawVolumeSlider(VolumeType::SFX, &ConfigNotConst::soundEffectsVolumeLevel, "Sound Effect Volume",
                            "Soundeffektlautstärke",
                            (float) screenHeight / 2 + 75);
}

void Menu::loadButtonAndKeyButtonTextures()
{
    LoadResources::loadButtonTextures();
    LoadResources::loadKeyButtonTextures();
}

void Menu::unloadButtonAndKeyButtonTextures()
{
    UnloadResources::unloadButtonTextures();
    UnloadResources::unloadKeyButtonTextures();
}


