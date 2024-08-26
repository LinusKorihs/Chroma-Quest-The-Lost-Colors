#pragma once
#include "raylib.h"
#include "Enemy.h"
#include "PixelGame.h"
#include "EnemyManager.h"
#include "Projectile.h"
#include "MiniBoss.h"

enum lastDirection {
    LASTUP,
    LASTDOWN,
    LASTLEFT,
    LASTRIGHT
};

enum punchDir {
    left,
    right,
    down,
    up,
    none
};
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
    static bool animationFinished;

    static void drawMainCharacter(Texture texture, MainCharacter& character);
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
    static void setPosition(Vector2 pos);

    static Rectangle playerRec;
    static Rectangle HitRec;
    static float playerCharacterHitBoxScale;
    static float playerCharacterTextureScale;

    void drawHitboxes() const;
    Rectangle getRectangle() const;
    static Vector2 getPosition();
    static void updateRec();

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

    static bool isPushing;

    static punchDir punch;

    static lastDirection lastDir;

};
