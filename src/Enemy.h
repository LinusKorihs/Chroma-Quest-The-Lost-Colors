#pragma once

#include "raylib.h"
#include "cmath"
#include "Projectile.h"

enum EnemyType {
    SLIMERED,
    ENEMYBLUE,
    ENEMYYELLOW,
    MINIBOSS
};

class Projectile;

class Enemy
{
public:
        Enemy();
        Enemy(Vector2 position, Texture2D &enemyTexture, int hits, float knockbackStrength, EnemyType type);

        void drawEnemy(Texture2D &enemyTexture);
        void updateEnemy(float deltaTime, Texture2D &enemyTexture);
        void enemyGetsHit();
        void setEnemyDead(bool dead);

        Rectangle getEnemyRec();
        bool getEnemyDeath();
        bool getUnload();
        int getEnemyHits();
        Vector2 getPosition();
        static void enemyAttack();

        static std::shared_ptr<Projectile> projectilePointer;
        static std::shared_ptr<Enemy> projectileEnemyPointer;

private:
        bool enemyDeath;
        bool turnAround;
        bool unload;
        bool isKnockedBack;

        EnemyType enemyType;

        Vector2 positionEnemy;

        Rectangle frameRec1;
        Rectangle frameRec2;
        Rectangle frameRec3;
        Rectangle enemyRec;

        int currentFrame;
        int framesCounter;
        int framesSpeed;
        int animationDeath;
        int enemyHits;
        int frames;
    };
