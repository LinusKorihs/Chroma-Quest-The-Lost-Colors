#pragma once

#include <map>
#include "raylib.h"
#include <stack>
#include "thread"
#include <vector>

enum class VolumeType { Global, BGMusic, SFX }; // Enums are capitalized
enum class Direction { NONE = -1, UP, DOWN, LEFT, RIGHT };

enum class MenuState
{
    MainMenu,
    GameRunning,
    SettingsMenu,
    KeyBindingsMenu,
    PauseMenu,
    ResumeGame,
    VolumeSliders,
    Control,
    Language,
    ControllerMenu,
    None
};

class GameState
{
public:
    std::map<Direction, int> playerKeyBindings = {{Direction::UP, KEY_W}, {Direction::DOWN, KEY_S}, {Direction::LEFT, KEY_A}, {Direction::RIGHT, KEY_D} };
    std::pair<Direction, int> lastChangedPlayerKey = {Direction::NONE, -1 };
    std::vector<Rectangle> wallRectangles;
    std::stack<MenuState> gameMenuStack;

    MenuState currentGameMenu = MenuState::MainMenu;

    void changeGameState(MenuState newState);
};

class LanguageManager
{
public:
    enum class Language { English, German };
    static Language currentLanguage;

    static const char* getLocalizedGameText(const char* englishText, const char* germanText);

    static void toggleLanguage();
};

extern GameState currentGameState;