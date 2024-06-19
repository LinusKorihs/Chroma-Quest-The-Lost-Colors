#pragma once
#include "raylib.h"
#include "Enemy.h"
#include "PixelGame.h"
#include "EnemyManager.h"
#include "Projectile.h"

class MainCharacter
{
public:
    static int playerHealth;
    static int damagePerFrame;
    static int playerScore;
    static int playerMana;

    static float playerPosX;
    static float playerPosY;
    static float playerSpawnPositionX;
    static float playerSpawnPositionY;

    static bool isPlayerDead;

    static void drawMainCharacter(Texture texture);
    static void moveMainCharacter(int moveDirection, float deltaTime);
    static void playerDeath();
    static void receiveDamage();
    static void attack();
    static void setSpawnPosition();

    static void setEnemy(const std::shared_ptr<Enemy>& enemy);
    static void setProjectile(const std::shared_ptr<Projectile>& projectile);
    static void setEnemyManager(EnemyManager* manager);
    static void updatePlayer(Texture myTexture, float deltaTime);
    static void initPlayer(Texture myTexture);


    static Rectangle playerCharacterRectangle;
    static Rectangle playerCharacterHitRectangle;
    static float playerCharacterHitBoxScale;
    static float playerCharacterTextureScale;

private:
    static std::shared_ptr<Projectile> projectile_p;
    static std::shared_ptr<Enemy> enemy_p;
    static std::shared_ptr<EnemyManager> enemyManager_p;
    static EnemyManager* enemyManager;
    static int currentFrame;
    static int framesCounter;
    static int framesSpeed;
    static bool forward;
    static Rectangle frameRec;
    static Texture2D PlayerTexture;

};
