
#include "Enemy.h"

Pixelgame::Enemy::Enemy(Vector2 position, Texture2D &enemyTexture, int hits, float knockbackStrength, EnemyType type)
{
    enemyDeath = false;
    unload = false;
    positionEnemy = position;
    frameRec1 = { 0.0f, 0.0f, (float)enemyTexture.width / 8, (float)enemyTexture.height / 3 };
    frameRec2 = { 0.0f, (float)enemyTexture.height / 3, (float)enemyTexture.width / 8, (float)enemyTexture.height / 3 };
    frameRec3 = { 0.0f, ((float)enemyTexture.height / 3) * 2, (float)enemyTexture.width / 8, (float)enemyTexture.height / 3 };
    currentFrame = 0;
    framesCounter = 0;
    framesSpeed = 8;
    animationDeath = 0;
    enemyRec = {positionEnemy.x, positionEnemy.y, (float)enemyTexture.width / 8, (float)enemyTexture.height / 3};
    enemyHits = 0;
    enemyType = type;
}


void Pixelgame::Enemy::EnemyUpdate(float deltaTime, Texture2D &enemyTexture)
{
    framesCounter++;    // Update counter

    if (framesCounter >= (60 / framesSpeed)) // wechsel frame jede 12 frames
    {
        framesCounter = 0;
        currentFrame++; // Update animation frame

        if (currentFrame > 20) // Reset bei 20 weil danach death animation
        {
            currentFrame = 0;
        }

        frameRec1.x = (float)currentFrame * (float)enemyTexture.width / 8; //weil 8 pro zeile
        frameRec2.x = (float)currentFrame * (float)enemyTexture.width / 8;
        frameRec3.x = (float)currentFrame * (float)enemyTexture.width / 8;
    }

    if(GetEnemyHits() == 3 && enemyType == ENEMYBLUE) //wie viele hits ein enemy aushält
    {
        enemyDeath = true;
    }
    if(GetEnemyHits() == 2 && enemyType == SLIMERED)
    {
        enemyDeath = true;
    }
    if(enemyHits == 4 && enemyType == ENEMYYELLOW)
    {
        enemyDeath = true;
    }
    if(enemyHits == 20 && enemyType == MINIBOSS)
    {
        enemyDeath = true;
    }

    if(enemyDeath && !animationDeath)
    {
        currentFrame = 16;
        animationDeath = true;
    }
}

void Pixelgame::Enemy::DrawEnemies(Texture2D &enemyTexture) {

    if (!enemyDeath && !unload)
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

bool Pixelgame::Enemy::GetEnemyDeath() {
    return enemyDeath;
}
void Pixelgame::Enemy::SetEnemyDeath(bool dead) {
    enemyDeath = dead;
}

bool Pixelgame::Enemy::GetUnload() {
    return unload;
}

void Pixelgame::Enemy::EnemyGetsHit() {
    enemyHits++;
}
int Pixelgame::Enemy::GetEnemyHits() {
    return enemyHits;
}

Vector2 Pixelgame::Enemy::GetPosition() {
    return positionEnemy;
}

