#pragma once

#include "GameState.h"
#include <memory>
#include "raylib.h"
#include "Enemy.h"

class Enemy;

class Projectile
{
public:
Projectile();
    static int getProjectileDestination();
    static int projectileDestination;
    static std::shared_ptr<Projectile> projectilePointer;
    static std::shared_ptr<Enemy> enemyPointer;

    void load();
    void init(Vector2 startPosition, Vector2 speed);
    void collision();
    void update(float deltaTime);
    void draw();

    bool getActive();
    void setActive(bool isActive);
    Rectangle getRectangle();
    void unload();

private:
    bool isProjectileActive = false;
    Vector2 projectilePosition;
    Vector2 projectileSpeed;
    Texture2D projectileTexture;
    Rectangle projectileRectangle;
};
