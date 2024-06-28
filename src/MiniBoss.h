
#ifndef RAYLIBSTARTER_MINIBOSS_H
#define RAYLIBSTARTER_MINIBOSS_H
#include "raylib.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

// Diese KLasse wird am Ende Kindklasse von enemy, die jetzige Enemy Klasse wird bsp "normalEnemy" und auch Kindklasse von enemy

enum MiniBossType {
    BOSSRED,
    BOSSBLUE,
    BOSSYELLOW
};

enum MiniBossDirection {
    LEFT,
    RIGHT,
    UP,
    DOWN,
    DIAGONALUPLEFT,
    DIAGONALUPRIGHT,
    DIAGONALDOWNLEFT,
    DIAGONALDOWNRIGHT
};

class MiniBoss {
public:
    MiniBoss(Vector2 position, Texture2D &enemTexture, MiniBossType type);

    void drawBoss();
    void updateBoss(float deltaTime);
    void bossGetsHit();
    void setBossDead(bool dead);
    Rectangle getBossRec();
    bool getBossDeath();
    bool getUnload();
    int getBossHits();
    Vector2 getPosition();
    int enemyHits;
    bool enemyHit;

private:
    bool enemyDeath;
    bool unload;
    MiniBossType enemyType;
    Vector2 posEnemy;
    Rectangle enemyRec;
    int frames;
    Texture2D enemyTexture;
    int direction;
    float speed;

    float leftLimit;
    float rightLimit;
    float upLimit;
    float downLimit;

    MiniBossDirection getRandomDirection();

    float moveDelay; // Zeit in Sekunden, die der Boss stehen bleibt
    float moveTimer; // Timer, um die verstrichene Zeit zu überwachen
    bool canMove;    // Flag, ob der Boss sich bewegen kann

};


#endif //RAYLIBSTARTER_MINIBOSS_H
