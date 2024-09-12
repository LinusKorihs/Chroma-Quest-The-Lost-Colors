#pragma once

#include "raylib.h"
#include "GameState.h"

enum type {
    npc,
    enemy,
    player,
    object,
    chest
};

class UniversalMethods {
public:
    UniversalMethods() = default;

    static void updateAnimation(float deltaTime, float &frameCounter, int &currentFrame, int startFrame, int endFrame, float &frameRecX, type type);
    static void moveObj(Vector2& position, Vector2 speed, Direction direction, float deltaTime);

};

