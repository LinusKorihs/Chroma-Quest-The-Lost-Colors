#pragma once
#include "GameState.h"

class SetKeyBindings
{
public:
    static void drawKeyBindingsMenu(GameState &gameState);
    static void settingTheKeyButtons(GameState &gameState);
    static void resetPlayerKeyBindingState();

    static Texture2D upKeyButtonTexture;
    static Texture2D downKeyButtonTexture;
    static Texture2D leftKeyButtonTexture;
    static Texture2D rightKeyButtonTexture;
};