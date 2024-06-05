
#include "Enemy.h"

Pixelgame::Enemy::Enemy(Vector2 position, Texture2D &enemyTexture, int hits, float knockbackStrength)
{
    enemyHit = false;
    unload = false;
    positionEnemy = position;
    frameRec1 = { 0.0f, 0.0f, (float)enemyTexture.width / 8, (float)enemyTexture.height / 3 };
    frameRec2 = { 0.0f, (float)enemyTexture.height / 3, (float)enemyTexture.width / 8, (float)enemyTexture.height / 3 };
    frameRec3 = { 0.0f, ((float)enemyTexture.height / 3) * 2, (float)enemyTexture.width / 8, (float)enemyTexture.height / 3 };
    currentFrame = 0;
    framesCounter = 0;
    framesSpeed = 8;
    enemyHits = 0;
    enemyRec = {positionEnemy.x, positionEnemy.y, (float)enemyTexture.width / 8, (float)enemyTexture.height / 3};
}


void Pixelgame::Enemy::EnemyUpdate(float deltaTime, Texture2D &enemyTexture)
{
    framesCounter++;

    if (framesCounter >= (60 / framesSpeed))
    {
        framesCounter = 0;
        currentFrame++;

        if (currentFrame > 20)
        {
            currentFrame = 0;
        }

        frameRec1.x = (float)currentFrame * (float)enemyTexture.width / 8;
        frameRec2.x = (float)currentFrame * (float)enemyTexture.width / 8;
        frameRec3.x = (float)currentFrame * (float)enemyTexture.width / 8;
    }

    if(IsKeyPressed(KEY_SPACE))
    {
        enemyHit = true;
    }

    if(enemyHit && !enemyHits)
    {
        currentFrame = 16;
        enemyHits = true;
    }
}

void Pixelgame::Enemy::DrawEnemies(Texture2D &enemyTexture) {

    if (!enemyHit && !unload)
    {
        if (currentFrame < 7)
        {
            DrawTextureRec(enemyTexture, frameRec1, positionEnemy, WHITE);
        } else {
            DrawTextureRec(enemyTexture, frameRec2, positionEnemy, WHITE);
        }
    } else {
        if (!unload)
        {
            DrawTextureRec(enemyTexture, frameRec3, positionEnemy, WHITE);
        }
        if (currentFrame == 20)
        {
            UnloadTexture(enemyTexture);
            unload = true;
        }
    }
}

Rectangle Pixelgame::Enemy::GetEnemyRec() {
    return enemyRec;
}

bool Pixelgame::Enemy::GetEnemyHit() {
    return enemyHit;
}
void Pixelgame::Enemy::SetEnemyHit(bool hit) {
    enemyHit = hit;
}