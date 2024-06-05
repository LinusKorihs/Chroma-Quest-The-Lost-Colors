#ifndef APPLICATIONSTATE_H
#define APPLICATIONSTATE_H

#include <map>
#include "raylib.h"
#include <stack>
#include "thread"
#include <vector>


enum VolumeType { Global, BGMusic, SFX };
enum Direction { NONE = -1, UP, DOWN, LEFT, RIGHT };
enum MenuType { None, Control, Language };

enum class MenuState {
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

class ApplicationState {
public:
    int globalVolume = 50, globalMusicVolume = 0, globalSFXVolume = 50, gameIsRunning = 1;
    int health = 100, damage_per_frame = 2, playerDeath = 0, score = 0, mana = 5;
    bool isPaused = false, isWaitingForKey = false, programIsRunning = true, meatUnload = false, fruitUnload = false;

    Sound walkingSound;
    Music backgroundMusic;
    Texture2D myTexture, myMC;

    const float moveSpeed = 2.0f;
    const int targettedFps = 60;

    std::map<Direction, int> keyBindings = { {UP, KEY_W}, {DOWN, KEY_S}, {LEFT, KEY_A}, {RIGHT, KEY_D} };
    std::pair<Direction, int> lastChangedKey = { NONE, -1 };
    std::vector<Rectangle> wallRecs;
    std::stack<MenuState> menuStack;

    Direction selectedKey;
    MenuState currentMenu = MenuState::MainMenu;

    enum Language { English, German };
    static Language currentLanguage;

    void ResetKeyBindingState();
    void ChangeState(MenuState newState);
    void TogglePause();
    void ToggleLanguage();

    static const char* GetLocalizedText(const char* englishText, const char* germanText);

};

extern ApplicationState gameState;

#endif // APPLICATIONSTATE_H