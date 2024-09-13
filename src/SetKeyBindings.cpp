#include "Configuration.h"
#include "InGameHud.h"
#include "TextureManage.h"
#include "raylib.h"
#include "SetKeyBindings.h"
#include "Utils.h"

HudImageButton upKeySettingsButton, downKeySettingsButton, leftKeySettingsButton, rightKeySettingsButton;

void SetKeyBindings::settingTheKeyButtons(GameState &currentGameState)
{
    upKeySettingsButton.texture = TextureManager::getTexture("upKeyButtonTexture");
    upKeySettingsButton.rec = {(float)Button::buttonScreenWidth, (float)PixelGameConfig::ScreenHeight / 2 - 100, Button::buttonWidthSmall, Button::buttonHeightSmall};
    upKeySettingsButton.buttonText = TextFormat("Up: %c", currentGameState.playerKeyBindings[Direction::UP]),
            TextFormat("Hoch: %c", currentGameState.playerKeyBindings[Direction::UP]);

    downKeySettingsButton.texture = TextureManager::getTexture("downKeyButtonTexture");
    downKeySettingsButton.rec = {(float)Button::buttonScreenWidth, (float)PixelGameConfig::ScreenHeight / 2 - 50, Button::buttonWidthSmall, Button::buttonHeightSmall};
    downKeySettingsButton.buttonText = TextFormat("Down: %c", currentGameState.playerKeyBindings[Direction::DOWN]),
            TextFormat("Runter: %c", currentGameState.playerKeyBindings[Direction::DOWN]);

    leftKeySettingsButton.texture = TextureManager::getTexture("leftKeyButtonTexture");
    leftKeySettingsButton.rec = {(float)Button::buttonScreenWidth, (float)PixelGameConfig::ScreenHeight / 2, Button::buttonWidthSmall, Button::buttonHeightSmall};
    leftKeySettingsButton.buttonText = TextFormat("Left: %c", currentGameState.playerKeyBindings[Direction::LEFT]),
            TextFormat("Links: %c", currentGameState.playerKeyBindings[Direction::LEFT]);

    rightKeySettingsButton.texture = TextureManager::getTexture("rightKeyButtonTexture");
    rightKeySettingsButton.rec = {(float)Button::buttonScreenWidth, (float)PixelGameConfig::ScreenHeight / 2 + 50, Button::buttonWidthSmall, Button::buttonHeightSmall};
    rightKeySettingsButton.buttonText = TextFormat("Right: %c", currentGameState.playerKeyBindings[Direction::RIGHT]),
            TextFormat("Rechts: %c", currentGameState.playerKeyBindings[Direction::RIGHT]);
}

void SetKeyBindings::drawKeyBindingsMenu(GameState &currentGameState)
{
    //InGameHud::drawSmallButton(upKeySettingsButton);
    //InGameHud::drawSmallButton(downKeySettingsButton);
    //InGameHud::drawSmallButton(leftKeySettingsButton);
    //InGameHud::drawSmallButton(rightKeySettingsButton);

    if (Button::checkButtonClick(upKeySettingsButton.rec,
                                 TextFormat("Up: %c", currentGameState.playerKeyBindings[Direction::UP]),
                                 TextFormat("Hoch: %c", currentGameState.playerKeyBindings[Direction::UP])))
    {
        ConfigNotConst::selectedPlayerKey = Direction::UP;
        ConfigNotConst::isWaitingForKeyInput = true;
    }
    else if (Button::checkButtonClick(downKeySettingsButton.rec,
                                      TextFormat("Down: %c", currentGameState.playerKeyBindings[Direction::DOWN]),
                                      TextFormat("Runter: %c", currentGameState.playerKeyBindings[Direction::DOWN])))
    {
        ConfigNotConst::selectedPlayerKey = Direction::DOWN;
        ConfigNotConst::isWaitingForKeyInput = true;
    }
    else if (Button::checkButtonClick(leftKeySettingsButton.rec,
                                      TextFormat("Left: %c", currentGameState.playerKeyBindings[Direction::LEFT]),
                                      TextFormat("Links: %c", currentGameState.playerKeyBindings[Direction::LEFT])))
    {
        ConfigNotConst::selectedPlayerKey = Direction::LEFT;
        ConfigNotConst::isWaitingForKeyInput = true;
    }
    else if (Button::checkButtonClick(rightKeySettingsButton.rec,
                                      TextFormat("Right: %c", currentGameState.playerKeyBindings[Direction::RIGHT]),
                                      TextFormat("Rechts: %c", currentGameState.playerKeyBindings[Direction::RIGHT])))
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
                for (const auto& binding : currentGameState.playerKeyBindings)
                {
                    if (binding.second == key)
                    {
                        isKeyAlreadyBound = true;
                        break;
                    }
                }
                if (!isKeyAlreadyBound)
                {
                    currentGameState.playerKeyBindings[ConfigNotConst::selectedPlayerKey] = key;
                    ConfigNotConst::isWaitingForKeyInput = false;
                    currentGameState.lastChangedPlayerKey = {ConfigNotConst::selectedPlayerKey, key};
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

    if (currentGameState.lastChangedPlayerKey.first != Direction::NONE)
    {
        const char *englishDirection;
        const char *germanDirection;
        switch (currentGameState.lastChangedPlayerKey.first)
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
                         LanguageManager::getLocalizedGameText(englishDirection, germanDirection), currentGameState.lastChangedPlayerKey.second),
                 PixelGameConfig::ScreenWidth / 2 - MeasureText(TextFormat(
                         LanguageManager::getLocalizedGameText("You have remapped %s to %c!", "Du hast %s nach %c umgelegt!"),
                         LanguageManager::getLocalizedGameText(englishDirection,
                                                               germanDirection), currentGameState.lastChangedPlayerKey.second), 20) / 2,
                 PixelGameConfig::ScreenHeight / 2 - 150, 20, BLACK);
        Button::countDrawText++;
    }

    if (IsKeyPressed(KEY_ESCAPE))
    {
        ConfigNotConst::selectedPlayerKey = Direction::NONE;
        ConfigNotConst::isWaitingForKeyInput = false;
        currentGameState.currentGameMenu = MenuState::Control;
        currentGameState.lastChangedPlayerKey = {Direction::NONE, -1};

        Button::setKeyBindText = 0;
        Button::countDrawText = 0;
    }
}

void SetKeyBindings::resetPlayerKeyBindingState()
{
    ConfigNotConst::isWaitingForKeyInput = false;
    ConfigNotConst::selectedPlayerKey = Direction::NONE;
}