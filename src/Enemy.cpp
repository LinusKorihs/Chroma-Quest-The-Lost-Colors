#include "Enemy.h"
#include "iostream"


Enemy::Enemy(Vector2 position, Texture2D &enemyTexture, EnemyType type, EnemyBehaviour behaviour, EnemyDirection enDirection, float rLimit, float lLimit, float uLimit, float dLimit)
{
    enemyDeath = false;
    unload = false;
    posEnemy = position;
    currentFrame = 0;
    framesCounter = 0;
    framesSpeed = 8;
    animationDeath = 0;
    enemyHits = 0;
    enemyType = type;
    direction = enDirection;
    enemyBehaviour = behaviour;
    projectile_p = std::make_shared<Projectile>();
    enTexture = enemyTexture;
    rightLimit = rLimit;
    leftLimit = lLimit;
    upLimit = uLimit;
    downLimit = dLimit;
    frameRec = {0, 0, (float)enTexture.width / 24, (float)enTexture.height};
}

void Enemy::updateEnemy(float deltaTime)
{

    if(enemyType == SLIMERED)
    {
        enemyRec = {posEnemy.x + 8, posEnemy.y +12, 16, 12};
    }
    if(enemyType == ENEMYBLUE)
    {
        enemyRec = {posEnemy.x +4, posEnemy.y +4, 24, 24};
    }
    if(enemyType == ENEMYYELLOW)
    {
        enemyRec = {posEnemy.x, posEnemy.y, 32, 32};
    }
    framesCounter++; // Update counter

    if (framesCounter >= (60 / framesSpeed)) {
        framesCounter = 0;

        if (enemyDeath) {
            if (currentFrame < 19) {
                currentFrame = 19;
            }
            currentFrame++;

            if (currentFrame > 23) // Ende der Death-Animation
            {
                unload = true;
            }
        } else {
            if (enemyBehaviour == STAND) {
                currentFrame++;
                if (currentFrame > 3) { // Reset bei 4, weil normale Animation 0-3
                    currentFrame = 0;
                }
            } else if (enemyBehaviour == WALKHORIZONTAL) {
                currentFrame++;
                if (direction == RIGHTEN) {
                    if (currentFrame > 11) {
                        currentFrame = 8; // Reset bei 8-11, weil Lauf-Animation
                    }
                } else if (direction == LEFTEN) {
                    if (currentFrame > 19 || currentFrame < 16) {
                        currentFrame = 16; // Reset bei 16-19, weil Lauf-Animation
                    }
                }
            } else if (enemyBehaviour == WALKVERTICL) {
                currentFrame++;
                if (direction == UPEN) {
                    if (currentFrame > 15 || currentFrame < 12) {
                        currentFrame = 12; // Reset bei 12-15, weil Lauf-Animation
                    }
                } else if (direction == DOWNEN) {
                    if (currentFrame > 7) {
                        currentFrame = 4; // Reset bei 4-7, weil Lauf-Animation
                    }
                }
            }
        }

        frameRec.x = (float) currentFrame * (float) enTexture.width / 24; //weil 8 pro Zeile
    }

    switch (direction) {
        case LEFTEN:
            posEnemy.x -= 20 * deltaTime;
            break;
        case RIGHTEN:
            posEnemy.x += 20 * deltaTime;
            break;
        case UPEN:
            posEnemy.y -= 20 * deltaTime;
            break;
        case DOWNEN:
            posEnemy.y += 20 * deltaTime;
            break;
        case NONEEN:
            break;
    }
    if(enemyBehaviour == WALKHORIZONTAL) {
        if (posEnemy.x >= leftLimit) {
            posEnemy.x = leftLimit;
            direction = RIGHTEN;
        } else if (posEnemy.x >= rightLimit) {
            posEnemy.x = rightLimit;
            direction = LEFTEN;
        }
    }
    if(enemyBehaviour == WALKVERTICL) {
        if (posEnemy.y <= upLimit) {
            posEnemy.y = upLimit;
            direction = DOWNEN;
        } else if (posEnemy.y >= downLimit) {
            posEnemy.y = downLimit;
            direction = UPEN;
        }
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
}

void Enemy::drawEnemy()
{
   if(!unload)
   {
       DrawTextureRec(enTexture, frameRec, posEnemy, WHITE);
       DrawRectangleLines(enemyRec.x, enemyRec.y, enemyRec.width, enemyRec.height, RED);
   }
}

Rectangle Enemy::getRec()
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
