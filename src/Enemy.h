#pragma once

#include "raylib.h"
#include "cmath"
#include "Projectile.h"
#include <memory>

enum EnemyType {
    SLIMERED,
    ENEMYBLUE,
    ENEMYYELLOW,
    MINIBOSS
};

enum EnemyBehaviour {
    WALKHORIZONTAL,
    WALKVERTICL,
    STAND,
    SHOOT
};

enum EnemyDirection {
    LEFTEN,
    RIGHTEN,
    UPEN,
    DOWNEN,
    NONEEN
};


class Enemy
{
public:

    Enemy(Vector2 position, Texture2D &enemTexture, EnemyType type, EnemyBehaviour behaviour, EnemyDirection enDirection);

    void drawEnemy();
    void updateEnemy(float deltaTime);
    void enemyGetsHit();
    void setEnemyDead(bool dead);
    void projectileCollision();
    void punchCollision();

    Rectangle getEnemyRec();
    bool getEnemyDeath();
    bool getUnload();
    int getEnemyHits();
    Vector2 getPosition();

    int enemyHits;
    bool enemyHit;

private:
    bool enemyDeath;
    bool turnAround;
    bool unload;
    bool isKnockedBack;


    EnemyType enemyType;
    EnemyBehaviour enemyBehaviour;
    EnemyDirection direction;

    Vector2 posEnemy;

    Rectangle frameRec1;
    Rectangle frameRec2;
    Rectangle frameRec3;
    Rectangle enemyRec;
    Rectangle frameRec;

    int currentFrame;
    int framesCounter;
    int framesSpeed;
    int animationDeath;
    int frames;


    Texture2D enTexture;

    std::shared_ptr<Projectile> projectile_p;
};