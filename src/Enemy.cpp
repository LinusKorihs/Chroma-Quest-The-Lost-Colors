#include "Enemy.h"


Enemy::Enemy(Vector2 position, Texture2D &enemyTexture, EnemyType type)
{
    enemyDeath = false;
    unload = false;
    posEnemy = position;
    frameRec1 = { 0.0f, 0.0f, (float)enemyTexture.width / 8, (float)enemyTexture.height / 3 };
    frameRec2 = { 0.0f, (float)enemyTexture.height / 3, (float)enemyTexture.width / 8, (float)enemyTexture.height / 3 };
    frameRec3 = { 0.0f, ((float)enemyTexture.height / 3) * 2, (float)enemyTexture.width / 8, (float)enemyTexture.height / 3 };
    currentFrame = 0;
    framesCounter = 0;
    framesSpeed = 8;
    animationDeath = 0;
    //enemyRec = {posEnemy.x, posEnemy.y, (float)enemyTexture.width / 8, (float)enemyTexture.height / 3};
    enemyHits = 0;
    enemyType = type;
    projectile_p = std::make_shared<Projectile>();
    enTexture = enemyTexture;
}

void Enemy::updateEnemy(float deltaTime)
{
    enemyRec = {posEnemy.x, posEnemy.y, (float)enTexture.width / 8, (float)enTexture.height / 3};
    framesCounter++; // Update counter

    if (framesCounter >= (60 / framesSpeed))
    {
        framesCounter = 0;
        currentFrame++;

        if (currentFrame > 20) // Reset bei 20 weil danach death animation
        {
            currentFrame = 0;
        }

        frameRec1.x = (float)currentFrame * (float)enTexture.width / 8; //weil 8 pro zeile
        frameRec2.x = (float)currentFrame * (float)enTexture.width / 8;
        frameRec3.x = (float)currentFrame * (float)enTexture.width / 8;
    }

    if(getEnemyHits() == 3 && enemyType == ENEMYBLUE) //wie viele hits ein enemy aushält
    {
        enemyDeath = true;
    }
    if(getEnemyHits() == 2 && enemyType == SLIMERED)
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

void Enemy::drawEnemy()
{
    unload = false;
    if (!enemyDeath && !unload)
    {
        if (currentFrame < 7)
        {
            DrawTextureRec(enTexture, frameRec1, posEnemy, WHITE);
        }
        else
        {
            DrawTextureRec(enTexture, frameRec2, posEnemy, WHITE);
        }
    }
    else
    {
        if (!unload)
        {
            DrawTextureRec(enTexture, frameRec3, posEnemy, WHITE);
        }
        if (currentFrame == 20)
        {
            unload = true;
        }
    }
}

Rectangle Enemy::getEnemyRec()
{
    return enemyRec;
}

bool Enemy::getEnemyDeath()
{
    return enemyDeath;
}
void Enemy::setEnemyDead(bool dead)
{
    enemyDeath = dead;
}

bool Enemy::getUnload()
{
    return unload;
}

void Enemy::enemyGetsHit()
{
    enemyHits++;
}
int Enemy::getEnemyHits()
{
    return enemyHits;
}

Vector2 Enemy::getPosition()
{
    return posEnemy;
}
