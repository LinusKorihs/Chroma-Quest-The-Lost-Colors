#include "ApplicationState.h"
#include "Audio.h"
#include "config.h"
#include "InGameHud.h"
#include "Menu.h"
#include "raylib.h"
#include "Utils.h"


Texture2D Menu::gameStartButtonTexture;
Texture2D Menu::settingsButtonTexture;
Texture2D Menu::exitButtonTexture;
Texture2D Menu::resumeButtonTexture;
Texture2D Menu::quitButtonTexture;
Texture2D Menu::keyBindingsButtonTexture;
Texture2D Menu::volumeButtonTexture;
Texture2D Menu::controlButtonTexture;
Texture2D Menu::languageButtonTexture;
Texture2D Menu::controllerButtonTexture;
Texture2D Menu::pauseButtonTexture;
Texture2D Menu::keyboardButtonTexture;
Texture2D Menu::languageENButtonTexture;
Texture2D Menu::languageDEButtonTexture;
Texture2D Menu::upKeyButtonTexture;
Texture2D Menu::downKeyButtonTexture;
Texture2D Menu::leftKeyButtonTexture;
Texture2D Menu::rightKeyButtonTexture;
ImageButton gameStartButton, settingsButton, exitButton, resumeButton, quitButton, volumeButton, controlButton, languageButton, keyBoardButton, controllerButton, languageEN, languageDE, upKeyButton, downKeyButton, leftKeyButton, rightKeyButton;

void Menu::loadTextures()
{
    gameStartButtonTexture = LoadTexture("assets/graphics/ButtonColors/ButtonBlue.png");
    settingsButtonTexture = LoadTexture("assets/graphics/ButtonColors/ButtonYellow.png");
    exitButtonTexture = LoadTexture("assets/graphics/ButtonColors/ButtonRed.png");
    resumeButtonTexture = LoadTexture("assets/graphics/ButtonColors/ButtonGreen.png");
    quitButtonTexture = LoadTexture("assets/graphics/ButtonColors/ButtonYellow.png");
    keyBindingsButtonTexture = LoadTexture("assets/graphics/ButtonColors/ButtonWhite.png");
    volumeButtonTexture = LoadTexture("assets/graphics/ButtonColors/ButtonGreen.png");
    controlButtonTexture = LoadTexture("assets/graphics/ButtonColors/ButtonOrange.png");
    languageButtonTexture = LoadTexture("assets/graphics/ButtonColors/ButtonPurple.png");
    controllerButtonTexture = LoadTexture("assets/graphics/ButtonColors/ButtonGrey.png");
    pauseButtonTexture = LoadTexture("assets/graphics/ButtonColors/ButtonGrey.png");
    keyboardButtonTexture = LoadTexture("assets/graphics/ButtonColors/ButtonWhite.png");
    languageENButtonTexture = LoadTexture("assets/graphics/ButtonColors/ButtonOrange.png");
    languageDEButtonTexture = LoadTexture("assets/graphics/ButtonColors/ButtonPurple.png");
    upKeyButtonTexture = LoadTexture("assets/graphics/ButtonColors/ButtonBlue.png");
    downKeyButtonTexture = LoadTexture("assets/graphics/ButtonColors/ButtonYellow.png");
    leftKeyButtonTexture = LoadTexture("assets/graphics/ButtonColors/ButtonGreen.png");
    rightKeyButtonTexture = LoadTexture("assets/graphics/ButtonColors/ButtonRed.png");
}

void Menu::unloadTextures()
{
    UnloadTexture(gameStartButtonTexture);
    UnloadTexture(settingsButtonTexture);
    UnloadTexture(exitButtonTexture);
    UnloadTexture(resumeButtonTexture);
    UnloadTexture(quitButtonTexture);
    UnloadTexture(keyBindingsButtonTexture);
    UnloadTexture(volumeButtonTexture);
    UnloadTexture(controlButtonTexture);
    UnloadTexture(languageButtonTexture);
    UnloadTexture(controllerButtonTexture);
    UnloadTexture(pauseButtonTexture);
    UnloadTexture(keyboardButtonTexture);
    UnloadTexture(languageENButtonTexture);
    UnloadTexture(languageDEButtonTexture);
    UnloadTexture(upKeyButtonTexture);
    UnloadTexture(downKeyButtonTexture);
    UnloadTexture(leftKeyButtonTexture);
    UnloadTexture(rightKeyButtonTexture);
}

int Menu::drawMainMenu(ApplicationState &gameState)
{
    int screenWidth = PixelGameConfig::ScreenWidth;
    int screenHeight = PixelGameConfig::ScreenHeight;

    gameStartButton.texture = gameStartButtonTexture;
    gameStartButton.rec = {(float)screenWidth/2 - gameStartButton.texture.width / 2, (float)screenHeight/2 - 75, (float)gameStartButton.texture.width, (float)gameStartButton.texture.height};
    gameStartButton.text = gameState.GetLocalizedText("Start Game", "Spiel starten");

    settingsButton.texture = settingsButtonTexture;
    settingsButton.rec = {(float)screenWidth/2 - settingsButton.texture.width / 2, (float)screenHeight/2, (float)settingsButton.texture.width, (float)settingsButton.texture.height};
    settingsButton.text = gameState.GetLocalizedText("Settings", "Einstellungen");

    exitButton.texture = exitButtonTexture;
    exitButton.rec = {(float)screenWidth/2 - exitButton.texture.width / 2, (float)screenHeight/2 + 75, (float)exitButton.texture.width, (float)exitButton.texture.height};
    exitButton.text = gameState.GetLocalizedText("Quit Game", "Spiel beenden");

    BeginDrawing();
    ClearBackground(DARKGRAY);

    DrawText(gameState.GetLocalizedText("Chroma Quest: The Lost Colors", "Chroma Quest: Die verlorenen Farben"),
             PixelGameConfig::ScreenWidth/2 - MeasureText(
                     gameState.GetLocalizedText("Chroma Quest: The Lost Colors", "Chroma Quest: Die verlorenen Farben"), 20) / 2, 50, 20, BLACK);

    InGameHud::DrawImageButton(gameStartButton);
    InGameHud::DrawImageButton(settingsButton);
    InGameHud::DrawImageButton(exitButton);

    if (Button::CheckButtonClick(gameStartButton.rec, "Start Game", "Spiel starten"))
    {
        gameState.menuStack.push(MenuState::GameRunning);
        gameState.currentMenu = MenuState::GameRunning;
        gameState.gameIsRunning = 1;
    }

    if (Button::CheckButtonClick(settingsButton.rec, "Settings", "Einstellungen"))
    {
        gameState.menuStack.push(MenuState::SettingsMenu);
        gameState.currentMenu = MenuState::SettingsMenu;
    }

    if (Button::CheckButtonClick(exitButton.rec, "Quit Game", "Spiel beenden"))
    {
        gameState.gameIsRunning = false;
        TraceLog(LOG_INFO, "Quit button clicked");
        gameState.menuStack.push(MenuState::None);
        gameState.currentMenu = MenuState::None;

    }

    if (IsKeyPressed(KEY_ESCAPE) && !gameState.menuStack.empty())
    {
        gameState.menuStack.pop();
        if (!gameState.menuStack.empty())
        {
            gameState.currentMenu = gameState.menuStack.top();
        }
        else
        {
            gameState.currentMenu = MenuState::MainMenu;
        }
    }

    EndDrawing();

    return gameState.programIsRunning ? 1 : 0;
}

void Menu::drawKeyBindingsMenu(ApplicationState &gameState)
{
    upKeyButton.texture = upKeyButtonTexture;
    upKeyButton.rec = {(float)Button::buttonScreenWidth, (float)PixelGameConfig::ScreenHeight / 2 - 100, Button::buttonWidth, Button::buttonHeight};
    upKeyButton.text = TextFormat("Up: %c", gameState.keyBindings[UP]),
            TextFormat("Hoch: %c", gameState.keyBindings[UP]);

    downKeyButton.texture = downKeyButtonTexture;
    downKeyButton.rec = {(float)Button::buttonScreenWidth, (float)PixelGameConfig::ScreenHeight / 2 - 50, Button::buttonWidth, Button::buttonHeight};
    downKeyButton.text = TextFormat("Down: %c", gameState.keyBindings[DOWN]),
            TextFormat("Runter: %c", gameState.keyBindings[DOWN]);

    leftKeyButton.texture = leftKeyButtonTexture;
    leftKeyButton.rec = {(float)Button::buttonScreenWidth, (float)PixelGameConfig::ScreenHeight / 2, Button::buttonWidth, Button::buttonHeight};
    leftKeyButton.text = TextFormat("Left: %c", gameState.keyBindings[LEFT]),
            TextFormat("Links: %c", gameState.keyBindings[LEFT]);

    rightKeyButton.texture = rightKeyButtonTexture;
    rightKeyButton.rec = {(float)Button::buttonScreenWidth, (float)PixelGameConfig::ScreenHeight / 2 + 50, Button::buttonWidth, Button::buttonHeight};
    rightKeyButton.text = TextFormat("Right: %c", gameState.keyBindings[RIGHT]),
            TextFormat("Rechts: %c", gameState.keyBindings[RIGHT]);

    BeginDrawing();
    ClearBackground(DARKGRAY);

    InGameHud::DrawImageButton(upKeyButton);
    InGameHud::DrawImageButton(downKeyButton);
    InGameHud::DrawImageButton(leftKeyButton);
    InGameHud::DrawImageButton(rightKeyButton);

    if (Button::CheckButtonClick(upKeyButton.rec, TextFormat("Up: %c", gameState.keyBindings[UP]),
                                 TextFormat("Hoch: %c", gameState.keyBindings[UP])))
    {
        gameState.selectedKey = UP;
        gameState.isWaitingForKey = true;
    }
    else if (Button::CheckButtonClick(downKeyButton.rec, TextFormat("Down: %c", gameState.keyBindings[DOWN]),
                                      TextFormat("Runter: %c", gameState.keyBindings[DOWN])))
    {
        gameState.selectedKey = DOWN;
        gameState.isWaitingForKey = true;
    }
    else if (Button::CheckButtonClick(leftKeyButton.rec, TextFormat("Left: %c", gameState.keyBindings[LEFT]),
                                      TextFormat("Links: %c", gameState.keyBindings[LEFT])))
    {
        gameState.selectedKey = LEFT;
        gameState.isWaitingForKey = true;
    }
    else if (Button::CheckButtonClick(rightKeyButton.rec, TextFormat("Right: %c", gameState.keyBindings[RIGHT]),
                                      TextFormat("Rechts: %c", gameState.keyBindings[RIGHT])))
    {
        gameState.selectedKey = RIGHT;
        gameState.isWaitingForKey = true;
    }

    if (Button::setKeyBindText == 0)
    {
        gameState.ResetKeyBindingState();
        Button::setKeyBindText++;
    }

    if (gameState.isWaitingForKey && gameState.selectedKey != NONE)
    {
        for (int key = KEY_A; key <= KEY_Z; key++)
        {
            if (IsKeyPressed(key))
            {
                bool isKeyAlreadyBound = false;
                for (const auto& binding : gameState.keyBindings)
                {
                    if (binding.second == key)
                    {
                        isKeyAlreadyBound = true;
                        break;
                    }
                }
                if (!isKeyAlreadyBound)
                {
                    gameState.keyBindings[gameState.selectedKey] = key;
                    gameState.isWaitingForKey = false;
                    gameState.lastChangedKey = {gameState.selectedKey, key};
                }
                break;
            }
        }
        const char *englishDirection;
        const char *germanDirection;
        switch (gameState.selectedKey)
        {
            case UP:
                englishDirection = "Up";
                germanDirection = "Hoch";
                break;
            case DOWN:
                englishDirection = "Down";
                germanDirection = "Runter";
                break;
            case LEFT:
                englishDirection = "Left";
                germanDirection = "Links";
                break;
            case RIGHT:
                englishDirection = "Right";
                germanDirection = "Rechts";
                break;
        }
        if (gameState.isWaitingForKey)
        {
            Button::DrawPromptText(englishDirection, germanDirection);
        }
    }

    if (gameState.lastChangedKey.first != NONE)
    {
        const char *englishDirection;
        const char *germanDirection;
        switch (gameState.lastChangedKey.first)
        {
            case UP:
                englishDirection = "move forward";
                germanDirection = "vorne gehen";
                break;
            case DOWN:
                englishDirection = "move backward";
                germanDirection = "zurück gehen";
                break;
            case LEFT:
                englishDirection = "move left";
                germanDirection = "links gehen";
                break;
            case RIGHT:
                englishDirection = "move right";
                germanDirection = "rechts gehen";
                break;
        }

        DrawText(TextFormat(gameState.GetLocalizedText("You have remapped %s to %c!", "Du hast %s nach %c umgelegt!"),
                            gameState.GetLocalizedText(englishDirection, germanDirection), gameState.lastChangedKey.second),
                 PixelGameConfig::ScreenWidth / 2 - MeasureText(TextFormat(
                         gameState.GetLocalizedText("You have remapped %s to %c!", "Du hast %s nach %c umgelegt!"),
                                                                           gameState.GetLocalizedText(englishDirection,
                                                                                                      germanDirection), gameState.lastChangedKey.second), 20) / 2,
                 PixelGameConfig::ScreenHeight / 2 - 150, 20, BLACK);
        Button::countDrawText++;
    }

    if (IsKeyPressed(KEY_ESCAPE))
    {
        gameState.selectedKey = NONE;
        gameState.isWaitingForKey = false;
        gameState.menuStack.pop();
        gameState.currentMenu = MenuState::Control;
        gameState.lastChangedKey = {NONE, -1};

        Button::setKeyBindText = 0;
        Button::countDrawText = 0;

    }
    EndDrawing();
}

int Menu::drawControllerMenu(ApplicationState &gameState)
{
    while (!WindowShouldClose() && gameState.programIsRunning)
    {
        BeginDrawing();
        ClearBackground(DARKGRAY);

        const char* text = gameState.GetLocalizedText("No Controller Implementation yet.",
                                                      "Keine Kontroller Implementierung bisher.");
        int textWidth = MeasureText(text, 20);

        DrawText(text, PixelGameConfig::ScreenWidth / 2 - textWidth / 2, PixelGameConfig::ScreenHeight / 2, 20, BLACK);

        if (IsKeyPressed(KEY_ESCAPE))
        {
            gameState.menuStack.pop();
            gameState.currentMenu = MenuState::Control;
            return 0;
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}

bool Menu::drawControlMenu(ApplicationState &gameState)
{
    keyBoardButton.texture = keyboardButtonTexture;
    keyBoardButton.rec = {(float)Button::buttonScreenWidth - 25, (float)PixelGameConfig::ScreenHeight / 2 - 50, Button::buttonWidth + 50, Button::buttonHeight};
    keyBoardButton.text = gameState.GetLocalizedText("Keyboard/Mouse", "Tastatur/Maus");

    controllerButton.texture = controllerButtonTexture;
    controllerButton.rec = {(float)Button::buttonScreenWidth - 25, (float)PixelGameConfig::ScreenHeight / 2, Button::buttonWidth + 50, Button::buttonHeight};
    controllerButton.text = gameState.GetLocalizedText("Controller", "Kontroller");

    BeginDrawing();
    ClearBackground(DARKGRAY);

    InGameHud::DrawImageButton(keyBoardButton);
    InGameHud::DrawImageButton(controllerButton);

    if (Button::CheckButtonClick(keyBoardButton.rec, "Keyboard/Mouse", "Tastatur/Maus"))
    {
        gameState.menuStack.push(MenuState::KeyBindingsMenu);
        gameState.currentMenu = MenuState::KeyBindingsMenu;
        drawKeyBindingsMenu(gameState);
    }
    if (Button::CheckButtonClick(controllerButton.rec, "Controller", "Controller"))
    {
        gameState.menuStack.push(MenuState::ControllerMenu);
        gameState.currentMenu = MenuState::ControllerMenu;
        drawControllerMenu(gameState);
    }

    if (IsKeyPressed(KEY_ESCAPE))
    {
        gameState.menuStack.pop();
        if (!gameState.menuStack.empty())
        {
            gameState.currentMenu = gameState.menuStack.top();
        }
        else
        {
            gameState.currentMenu = MenuState::SettingsMenu;
        }
    }
    EndDrawing();

    return true;
}

void Menu::drawLanguageMenu(ApplicationState &gameState)
{
    int screenWidth = PixelGameConfig::ScreenWidth;
    int screenHeight = PixelGameConfig::ScreenHeight;

    languageEN.texture = languageDEButtonTexture;
    languageEN.rec = {(float)screenWidth/2 - 50, (float)screenHeight/2 - 50, 150, 30};
    languageEN.text = gameState.GetLocalizedText("English", "Englisch");

    languageDE.texture = languageENButtonTexture;
    languageDE.rec = {(float)screenWidth/2 - 50, (float)screenHeight/2, 150, 30};
    languageDE.text = gameState.GetLocalizedText("German", "Deutsch");

    BeginDrawing();
    ClearBackground(DARKGRAY);

    InGameHud::DrawImageButton(languageEN);
    InGameHud::DrawImageButton(languageDE);

    if (Button::CheckButtonClick(languageEN.rec, "English", "Englisch"))
    {
        gameState.ToggleLanguage();
    }

    if (Button::CheckButtonClick(languageDE.rec, "German", "Deutsch"))
    {
        gameState.ToggleLanguage();
    }

    if (IsKeyPressed(KEY_ESCAPE))
    {
        gameState.menuStack.pop();
        if (!gameState.menuStack.empty())
        {
            gameState.currentMenu = gameState.menuStack.top();
        }
        else
        {
            gameState.currentMenu = MenuState::SettingsMenu;
        }
    }
    EndDrawing();
}

bool Menu::drawSettingsMenu(ApplicationState &gameState)
{
    int screenWidth = PixelGameConfig::ScreenWidth;
    int screenHeight = PixelGameConfig::ScreenHeight;

    volumeButton.texture = volumeButtonTexture;
    volumeButton.rec = {(float)screenWidth/2 - 50, (float)screenHeight/2 - 50, 150, 30};
    volumeButton.text = gameState.GetLocalizedText("Sound", "Ton");

    controlButton.texture = controlButtonTexture;
    controlButton.rec = {(float)screenWidth/2 - 50, (float)screenHeight/2, 150, 30};
    controlButton.text = gameState.GetLocalizedText("Controls", "Steuerung");

    languageButton.texture = languageButtonTexture;
    languageButton.rec = {(float)screenWidth/2 - 50, (float)screenHeight/2 + 50, 150, 30};
    languageButton.text = gameState.GetLocalizedText("Language", "Sprache");

    BeginDrawing();
    ClearBackground(DARKGRAY);

    InGameHud::DrawImageButton(volumeButton);
    InGameHud::DrawImageButton(controlButton);
    InGameHud::DrawImageButton(languageButton);

    if (Button::CheckButtonClick(volumeButton.rec, "Sound", "Ton"))
    {
        gameState.menuStack.push(MenuState::VolumeSliders);
        gameState.currentMenu = MenuState::VolumeSliders;
    }

    if (Button::CheckButtonClick(controlButton.rec, "Controls", "Steuerung"))
    {
        gameState.menuStack.push(MenuState::Control);
        gameState.currentMenu = MenuState::Control;
    }

    if (Button::CheckButtonClick(languageButton.rec, "Language", "Sprache"))
    {
        gameState.menuStack.push(MenuState::Language);
        gameState.currentMenu = MenuState::Language;
    }

    if (IsKeyPressed(KEY_ESCAPE))
    {
        gameState.menuStack.pop();
        if (!gameState.menuStack.empty())
        {
            gameState.currentMenu = gameState.menuStack.top();
        }
        else
        {
            gameState.currentMenu = MenuState::MainMenu;
        }
    }
    EndDrawing();

    return true;
}

void Menu::drawVolumeSlidersMenu(ApplicationState &gameState)
{
    int screenHeight = PixelGameConfig::ScreenHeight;

    BeginDrawing();
    ClearBackground(DARKGRAY);

    Audio::DrawVolumeSlider(Global, &gameState.globalVolume, "Global Volume", "Globale Lautstärke",
                            (float) screenHeight / 2 - 75);
    Audio::DrawVolumeSlider(BGMusic, &gameState.globalMusicVolume, "Music Volume", "Musiklautstärke",
                            (float) screenHeight / 2);
    Audio::DrawVolumeSlider(SFX, &gameState.globalSFXVolume, "Sound Effect Volume", "Soundeffektlautstärke",
                            (float) screenHeight / 2 + 75);

    if (IsKeyPressed(KEY_ESCAPE))
    {
        gameState.menuStack.pop();
        if (!gameState.menuStack.empty())
        {
            gameState.currentMenu = gameState.menuStack.top();
        }
        else
        {
            gameState.currentMenu = MenuState::SettingsMenu;
        }
    }

    EndDrawing();
}

void Menu::drawVolumeSlidersPauseMenu(ApplicationState &gameState)
{
    int screenHeight = PixelGameConfig::ScreenHeight;

    Audio::DrawVolumeSlider(Global, &gameState.globalVolume, "Global Volume", "Globale Lautstärke",
                            (float) screenHeight / 2 - 75);
    Audio::DrawVolumeSlider(BGMusic, &gameState.globalMusicVolume, "Music Volume", "Musiklautstärke",
                            (float) screenHeight / 2);
    Audio::DrawVolumeSlider(SFX, &gameState.globalSFXVolume, "Sound Effect Volume", "Soundeffektlautstärke",
                            (float) screenHeight / 2 + 75);
}

void Menu::drawPauseMenu(ApplicationState &gameState)
{
    int screenWidth = PixelGameConfig::ScreenWidth;
    int screenHeight = PixelGameConfig::ScreenHeight;

    resumeButton.texture = resumeButtonTexture;
    resumeButton.rec = {(float)screenWidth/2 - 50, (float)screenHeight/2 - 175, 150, 30};
    resumeButton.text = gameState.GetLocalizedText("Resume PixelGame", "Spiel fortsetzen");

    quitButton.texture = quitButtonTexture;
    quitButton.rec = {(float)screenWidth/2 - 50, (float)screenHeight/2 + 150, 150, 30};
    quitButton.text = gameState.GetLocalizedText("Back to Menu", "Zurück zum Menü");

    while (!WindowShouldClose() && gameState.isPaused)
    {
        BeginDrawing();
        ClearBackground(DARKGRAY);

        InGameHud::DrawImageButton(resumeButton);
        InGameHud::DrawImageButton(quitButton);

        drawVolumeSlidersPauseMenu(gameState);
        Audio::UpdateVolumes();

        if (Button::CheckButtonClick(resumeButton.rec, "Resume PixelGame", "Spiel fortsetzen"))
        {
            gameState.isPaused = false;
            gameState.menuStack.pop();
            break;
        }
        else if (Button::CheckButtonClick(quitButton.rec, "Back to Menu", "Zurück zum Menü"))
        {
            gameState.isPaused = false;
            gameState.gameIsRunning = 0;
            gameState.menuStack.pop();
            gameState.currentMenu = MenuState::MainMenu;
            break;
        }

        DrawText(gameState.GetLocalizedText("Pause Menu", "Pause Menü"), 10, 10, 20, BLACK);

        EndDrawing();
    }
}

