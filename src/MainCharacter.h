#pragma once
#include "raylib.h"
#include "Enemy.h"
#include "PixelGame.h"

class MainCharacter
{
public:
    static int playerHealth;
    static int damagePerFrame;
    static int playerScore;
    static int playerMana;

    static float playerPositionX;
    static float playerPositionY;
    static float playerSpawnPositionX;
    static float playerSpawnPositionY;

    static bool isPlayerDead;

    static void drawMainCharacter(Texture texture);
    static void moveMainCharacter(int moveDirection, float deltaTime);
    static void playerDeath();
    static void receiveDamage();
    static void attack();
    static void setSpawnPosition();

    static Rectangle playerCharacterRectangle;
    static Rectangle playerCharacterHitRectangle;
};
