#pragma once
#include "GameState.h"
#include <memory>
#include "raylib.h"
#include "UniversalMethods.h"


class Projectile
{
public:
    Projectile();
    Direction getProjectileDestination();

    void load();
    void init(Vector2 startPosition, Vector2 speed);
    void collision();
    void update(float deltaTime, Direction direction);
    void draw();
    void unload();
    void setActive(bool isActive);
    void setProjectileDestination(Direction destination);

    bool getActive();

    Rectangle getRec();


private:
    bool isProjActive = false;
    Vector2 projectilePos;
    Vector2 projectileSpeed;
    Texture2D projectileTexture;
    Rectangle projectileRec;
    Direction projectileDestination;
};