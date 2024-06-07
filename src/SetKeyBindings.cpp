#include "Configuration.h"
#include "InGameHud.h"
#include "raylib.h"
#include "SetKeyBindings.h"
#include "Utils.h"

Texture2D SetKeyBindings::upKeyButtonTexture;
Texture2D SetKeyBindings::downKeyButtonTexture;
Texture2D SetKeyBindings::leftKeyButtonTexture;
Texture2D SetKeyBindings::rightKeyButtonTexture;
HudImageButton upKeySettingsButton, downKeySettingsButton, leftKeySettingsButton, rightKeySettingsButton;

void SetKeyBindings::settingTheKeyButtons(GameState &gameState)
{
    upKeySettingsButton.texture = upKeyButtonTexture;
    upKeySettingsButton.rec = {(float)Button::buttonScreenWidth, (float)PixelGameConfig::ScreenHeight / 2 - 100, Button::buttonWidth, Button::buttonHeight};
    upKeySettingsButton.buttonText = TextFormat("Up: %c", gameState.playerKeyBindings[Direction::UP]),
            TextFormat("Hoch: %c", gameState.playerKeyBindings[Direction::UP]);

    downKeySettingsButton.texture = downKeyButtonTexture;
    downKeySettingsButton.rec = {(float)Button::buttonScreenWidth, (float)PixelGameConfig::ScreenHeight / 2 - 50, Button::buttonWidth, Button::buttonHeight};
    downKeySettingsButton.buttonText = TextFormat("Down: %c", gameState.playerKeyBindings[Direction::DOWN]),
            TextFormat("Runter: %c", gameState.playerKeyBindings[Direction::DOWN]);

    leftKeySettingsButton.texture = leftKeyButtonTexture;
    leftKeySettingsButton.rec = {(float)Button::buttonScreenWidth, (float)PixelGameConfig::ScreenHeight / 2, Button::buttonWidth, Button::buttonHeight};
    leftKeySettingsButton.buttonText = TextFormat("Left: %c", gameState.playerKeyBindings[Direction::LEFT]),
            TextFormat("Links: %c", gameState.playerKeyBindings[Direction::LEFT]);

    rightKeySettingsButton.texture = rightKeyButtonTexture;
    rightKeySettingsButton.rec = {(float)Button::buttonScreenWidth, (float)PixelGameConfig::ScreenHeight / 2 + 50, Button::buttonWidth, Button::buttonHeight};
    rightKeySettingsButton.buttonText = TextFormat("Right: %c", gameState.playerKeyBindings[Direction::RIGHT]),
            TextFormat("Rechts: %c", gameState.playerKeyBindings[Direction::RIGHT]);
}

void SetKeyBindings::drawKeyBindingsMenu(GameState &gameState)
{
    InGameHud::drawImageButton(upKeySettingsButton);
    InGameHud::drawImageButton(downKeySettingsButton);
    InGameHud::drawImageButton(leftKeySettingsButton);
    InGameHud::drawImageButton(rightKeySettingsButton);

    if (Button::checkButtonClick(upKeySettingsButton.rec,
                                 TextFormat("Up: %c", gameState.playerKeyBindings[Direction::UP]),
                                 TextFormat("Hoch: %c", gameState.playerKeyBindings[Direction::UP])))
    {
        ConfigNotConst::selectedPlayerKey = Direction::UP;
        ConfigNotConst::isWaitingForKeyInput = true;
    }
    else if (Button::checkButtonClick(downKeySettingsButton.rec,
                                      TextFormat("Down: %c", gameState.playerKeyBindings[Direction::DOWN]),
                                      TextFormat("Runter: %c", gameState.playerKeyBindings[Direction::DOWN])))
    {
        ConfigNotConst::selectedPlayerKey = Direction::DOWN;
        ConfigNotConst::isWaitingForKeyInput = true;
    }
    else if (Button::checkButtonClick(leftKeySettingsButton.rec,
                                      TextFormat("Left: %c", gameState.playerKeyBindings[Direction::LEFT]),
                                      TextFormat("Links: %c", gameState.playerKeyBindings[Direction::LEFT])))
    {
        ConfigNotConst::selectedPlayerKey = Direction::LEFT;
        ConfigNotConst::isWaitingForKeyInput = true;
    }
    else if (Button::checkButtonClick(rightKeySettingsButton.rec,
                                      TextFormat("Right: %c", gameState.playerKeyBindings[Direction::RIGHT]),
                                      TextFormat("Rechts: %c", gameState.playerKeyBindings[Direction::RIGHT])))
    {
        ConfigNotConst::selectedPlayerKey = Direction::RIGHT;
        ConfigNotConst::isWaitingForKeyInput = true;
    }

    if (Button::setKeyBindText == 0)
    {
        SetKeyBindings::resetPlayerKeyBindingState();
        Button::setKeyBindText++;
    }

    if (ConfigNotConst::isWaitingForKeyInput &&  ConfigNotConst::selectedPlayerKey != Direction::NONE)
    {
        for (int key = KEY_A; key <= KEY_Z; key++)
        {
            if (IsKeyPressed(key))
            {
                bool isKeyAlreadyBound = false;
                for (const auto& binding : gameState.playerKeyBindings)
                {
                    if (binding.second == key)
                    {
                        isKeyAlreadyBound = true;
                        break;
                    }
                }
                if (!isKeyAlreadyBound)
                {
                    gameState.playerKeyBindings[ConfigNotConst::selectedPlayerKey] = key;
                    ConfigNotConst::isWaitingForKeyInput = false;
                    gameState.lastChangedPlayerKey = {ConfigNotConst::selectedPlayerKey, key};
                }
                break;
            }
        }
        const char *englishDirection;
        const char *germanDirection;
        switch (ConfigNotConst::selectedPlayerKey)
        {
            case Direction::UP:
                englishDirection = "Up";
                germanDirection = "Hoch";
                break;
            case Direction::DOWN:
                englishDirection = "Down";
                germanDirection = "Runter";
                break;
            case Direction::LEFT:
                englishDirection = "Left";
                germanDirection = "Links";
                break;
            case Direction::RIGHT:
                englishDirection = "Right";
                germanDirection = "Rechts";
                break;
            case Direction::NONE:
                break;
        }
        if (ConfigNotConst::isWaitingForKeyInput)
        {
            Button::drawPromptText(englishDirection, germanDirection);
        }
    }

    if (gameState.lastChangedPlayerKey.first != Direction::NONE)
    {
        const char *englishDirection;
        const char *germanDirection;
        switch (gameState.lastChangedPlayerKey.first)
        {
            case Direction::UP:
                englishDirection = "move forward";
                germanDirection = "vorne gehen";
                break;
            case Direction::DOWN:
                englishDirection = "move backward";
                germanDirection = "zurück gehen";
                break;
            case Direction::LEFT:
                englishDirection = "move left";
                germanDirection = "links gehen";
                break;
            case Direction::RIGHT:
                englishDirection = "move right";
                germanDirection = "rechts gehen";
                break;
        }

        DrawText(TextFormat(
                         LanguageManager::getLocalizedGameText("You have remapped %s to %c!", "Du hast %s nach %c umgelegt!"),
                         LanguageManager::getLocalizedGameText(englishDirection, germanDirection), gameState.lastChangedPlayerKey.second),
                 PixelGameConfig::ScreenWidth / 2 - MeasureText(TextFormat(
                         LanguageManager::getLocalizedGameText("You have remapped %s to %c!", "Du hast %s nach %c umgelegt!"),
                         LanguageManager::getLocalizedGameText(englishDirection,
                                                               germanDirection), gameState.lastChangedPlayerKey.second), 20) / 2,
                 PixelGameConfig::ScreenHeight / 2 - 150, 20, BLACK);
        Button::countDrawText++;
    }

    if (IsKeyPressed(KEY_ESCAPE))
    {
        ConfigNotConst::selectedPlayerKey = Direction::NONE;
        ConfigNotConst::isWaitingForKeyInput = false;
        gameState.gameMenuStack.pop();
        gameState.currentGameMenu = MenuState::Control;
        gameState.lastChangedPlayerKey = {Direction::NONE, -1};

        Button::setKeyBindText = 0;
        Button::countDrawText = 0;
    }
}

void SetKeyBindings::resetPlayerKeyBindingState()
{
    ConfigNotConst::isWaitingForKeyInput = false;
    ConfigNotConst::selectedPlayerKey = Direction::NONE;
}