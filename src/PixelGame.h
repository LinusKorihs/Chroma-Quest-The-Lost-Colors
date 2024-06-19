#pragma once

#include "GameState.h"
#include "Audio.h"
#include "Enemy.h"
#include "InGameHud.h"
#include "Menu.h"
#include "Projectile.h"
#include "raylib.h"
#include "Objects.h"
#include "tileson.h"
#include "EnemyManager.h"

class PixelGame
{
public:
    static void gameInit();
    static void gameLoop(tson::Map& tileMap);

    static Enemy enemy;
    static Vector2 position;
    static Texture2D slimeEnemyTexture;

    static bool isPlayerKnocked;

    static void runGameOnce(tson::Map &Map);

private:
    static void drawObjects();
    static void drawHud();
    static void unloadAll();

    static std::shared_ptr<Projectile> projectile_p;
    static std::shared_ptr<Projectile> projectileEnemy_p;
    static EnemyManager enemyManager;

};

