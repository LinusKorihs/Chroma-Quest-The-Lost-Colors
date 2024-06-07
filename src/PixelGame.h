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
    static void gameLoop(tson::Map& map);
    static void loadTexture(Texture2D& loadTexture, const char* textureFilePath);
    static void drawTexture(Texture2D& texture, Rectangle destination);
    static void unloadTexture(Texture2D& unloadTexture);
    static void drawObjects();
    static void unloadAll();
    static void drawHud();

    static Rectangle lavaTileRectangle;

    static Enemy enemy;
    static Vector2 position;

    static Texture2D lavaTileTexture;
    static Texture2D slimeEnemyTexture;
    static Texture2D gameTilesetTexture;

    static bool isPlayerKnocked;

    static std::shared_ptr<Projectile> projectileEnemyPointer;
    static std::shared_ptr<Projectile> projectilePlayerPointer;
    static std::shared_ptr<Enemy> enemyPointer;
};

