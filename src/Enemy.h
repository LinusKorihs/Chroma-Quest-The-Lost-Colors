#ifndef RAYLIBSTARTER_ENEMY_H
#define RAYLIBSTARTER_ENEMY_H
#include "raylib.h"

namespace Pixelgame {

    class Enemy {
    public:
        Enemy(Vector2 position, Texture2D &enemyTexture, int hits, float knockbackStrength);
        void DrawEnemies(Texture2D &enemyTexture);
        void EnemyUpdate(float deltaTime, Texture2D &enemyTexture);
        Rectangle GetEnemyRec();
        bool GetEnemyHit();
        void SetEnemyHit(bool hit);

    private:
        Texture2D slimeTexture;
        bool enemyHit;
        int enemyHits;
        bool turnAround;
        bool unload;
        Vector2 positionEnemy;
        Rectangle frameRec1;
        Rectangle frameRec2;
        Rectangle frameRec3;
        Rectangle enemyRec;
        int currentFrame;
        int framesCounter;
        int framesSpeed;
        int frames;
        float knockbackStrength;
        Vector2 knockbackDirection;

    };
}

#endif //RAYLIBSTARTER_ENEMY_H
