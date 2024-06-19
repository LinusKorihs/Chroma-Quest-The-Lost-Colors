#pragma once

#include "GameState.h"
#include "Audio.h"
#include "Enemy.h"
#include "InGameHud.h"
#include "Menu.h"
#include "Projectile.h"
#include "raylib.h"
#include "Stone.h"
#include "tileson.h"

class PixelGame
{
public:
    static void gameInit();
    static void gameLoop(tson::Map& tileMap);

    static Enemy enemy;
    static Vector2 position;
    static Texture2D slimeEnemyTexture;

    static bool isPlayerKnocked;

    static std::shared_ptr<Projectile> projectileEnemyPointer;
    static std::shared_ptr<Projectile> projectilePlayerPointer;
    static std::shared_ptr<Enemy> enemyPointer;

    static void runGameOnce(tson::Map &Map);

private:
    static void drawObjects();
    static void drawHud();
    static void unloadAll();

};

