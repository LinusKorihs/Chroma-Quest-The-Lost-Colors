
#ifndef RAYLIBSTARTER_MINIBOSS_H
#define RAYLIBSTARTER_MINIBOSS_H
#include "raylib.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include "Projectile.h"
#include "Objects.h"
#include "MainCharacter.h"
#include "Pathfinder.h"

// Diese KLasse wird am Ende Kindklasse von enemy, die jetzige Enemy Klasse wird bsp "normalEnemy" und auch Kindklasse von enemy

enum MiniBossType {
    BOSSRED,
    BOSSBLUE,
    BOSSYELLOW
};

enum class BossState {
    Idle,
    Attacking,
    RandomMovement,
    Returning
};


class MiniBoss {
public:
    MiniBoss(Vector2 position, Texture2D &enemTexture, MiniBossType type, Pathfinder &pathfinder);

    void updateBoss(float deltaTime, Vector2 playerPosition);
    void findPath(Vector2 playerPosition);

    void drawBoss();
    void bossGetsHit();
    void setBossDead(bool dead);
    void findPath(int playerX, int playerY);
    void updateShield();
    void drawShieldBar();
    Rectangle getBossRec();
    bool getBossDeath();
    bool getUnload();
    int getBossHits();
    Vector2 getPosition();
    int enemyHits;
    bool enemyHit;
    int getShieldHits();
    bool isCollisionInDirection(Vector2 newPosition);

    Vector2 Vector2Subtract(Vector2 v1, Vector2 v2);

private:
    bool enemyDeath;
    bool unload;
    bool hasShield;
    MiniBossType enemyType;
    Vector2 posEnemy;
    Rectangle enemyRec;
    int frames;
    Texture2D enemyTexture;
    int direction;
    float speed;
    int barHits;
    int shieldHits;

    float leftLimit;
    float rightLimit;
    float upLimit;
    float downLimit;

    Rectangle frameRec;

    int currentFrame;
    int framesCounter;
    int framesSpeed;
    int animationDeath;

    float moveDelay; // Zeit in Sekunden, die der Boss stehen bleibt
    float moveTimer; // Timer, um die verstrichene Zeit zu überwachen
    bool canMove;    // Flag, ob der Boss sich bewegen kann

    std::shared_ptr<Projectile> proj_p;
    bool isPlayerInRange(Vector2 playerPosition, float range);
    Pathfinder &pathfinder; // Referenz auf Pathfinder
    std::vector<Vector2> path; // Aktueller Pfad zum Spieler
    int pathIndex; // Aktueller Index im Pfa

    bool pathFound = false;

    BossState state; // Aktueller Zustand des Bosses
    float stateTimer; // Timer für den aktuellen Zustand

    const float idleTime = 2.0f; // Zeit in Sekunden, die der Boss im Idle-Zustand bleibt
    const float attackDuration = 1.0f; // Dauer des Angriffs in Sekunden
    const float randomMovementDuration = 3.0f;
    int currentDirection;
    bool plate1Pressed;
    bool plate2Pressed;
};


#endif //RAYLIBSTARTER_MINIBOSS_H
