#ifndef RAYLIBSTARTER_ENEMY_H
#define RAYLIBSTARTER_ENEMY_H
#include "raylib.h"
#include "cmath"

enum EnemyType {
    SLIMERED,
    ENEMYBLUE,
    ENEMYYELLOW,
    MINIBOSS
};

namespace Pixelgame {

    class Enemy {
    public:
        Enemy(Vector2 position, Texture2D &enemyTexture, int hits, float knockbackStrength, EnemyType type);

        void DrawEnemies(Texture2D &enemyTexture);
        void EnemyUpdate(float deltaTime, Texture2D &enemyTexture);
        void EnemyGetsHit();
        void SetEnemyDeath(bool dead);

        Rectangle GetEnemyRec();
        bool GetEnemyDeath();
        bool GetUnload();
        int GetEnemyHits();
        Vector2 GetPosition();

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
}

#endif //RAYLIBSTARTER_ENEMY_H
