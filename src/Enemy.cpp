#include "Enemy.h"
#include "iostream"


Enemy::Enemy(Vector2 position, Texture2D &enemyTexture, EnemyType type, EnemyBehaviour behaviour, Direction enDirection, float rLimit, float lLimit, float uLimit, float dLimit)
{
    enemyDeath = false;
    unload = false;
    posEnemy = position;
    currentFrame = 0;
    framesCounter = 0;
    framesSpeed = 6;
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
        hitRec = {posEnemy.x + 9, posEnemy.y + 14, 14, 12};
    }
    if(enemyType == ENEMYBLUE)
    {
        enemyRec = {posEnemy.x +4, posEnemy.y +4, 24, 24};
    }
    if(enemyType == ENEMYYELLOW)
    {
        enemyRec = {posEnemy.x, posEnemy.y, 32, 32};
    }

    if (enemyDeath)
    {
        UniversalMethods::updateAnimation(deltaTime, framesCounter, currentFrame,
                        19, 23, frameRec.x, enemy);

        if (currentFrame == 23)
        {
            unload = true;
        }
    } else {
        if (enemyBehaviour == STAND)
        {
            UniversalMethods::updateAnimation(deltaTime, framesCounter, currentFrame,
                            0, 3, frameRec.x, enemy);
        } else if (enemyBehaviour == WALKHORIZONTAL)
        {
            if (direction == Direction::RIGHT)
            {
                UniversalMethods::updateAnimation(deltaTime, framesCounter, currentFrame,
                                8, 11, frameRec.x, enemy);
            } else if (direction == Direction::LEFT)
            {
                UniversalMethods::updateAnimation(deltaTime, framesCounter, currentFrame,
                                16, 19, frameRec.x, enemy);
            }
        } else if (enemyBehaviour == WALKVERTICAL)
        {
            if (direction == Direction::UP) {
                UniversalMethods::updateAnimation(deltaTime, framesCounter, currentFrame,
                                12, 15, frameRec.x, enemy);
            } else if (direction == Direction::DOWN)
            {
                UniversalMethods::updateAnimation(deltaTime, framesCounter, currentFrame,
                                4, 7, frameRec.x, enemy);
            }
        }
    }

    Vector2 enemySpeed = {20, 20};
    UniversalMethods::moveObj(posEnemy, enemySpeed, direction, deltaTime);

    if(enemyBehaviour == WALKHORIZONTAL)
    {
        if (posEnemy.x >= leftLimit)
        {
            posEnemy.x = leftLimit;
            direction = Direction::RIGHT;
        } else if (posEnemy.x >= rightLimit)
        {
            posEnemy.x = rightLimit;
            direction = Direction::LEFT;
        }
    }
    if(enemyBehaviour == WALKVERTICAL)
    {
        if (posEnemy.y <= upLimit)
        {
            posEnemy.y = upLimit;
            direction = Direction::DOWN;
        } else if (posEnemy.y >= downLimit)
        {
            posEnemy.y = downLimit;
            direction = Direction::UP;
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
       //DrawRectangleLines(hitRec.x, hitRec.y, hitRec.width, hitRec.height, GREEN);
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

Rectangle Enemy::getHitRec()
{
    return hitRec;
}

bool Enemy::setMcCollision(bool collision)
{
    MCCollision = collision;
}

void Enemy::setPos(Vector2 pos)
{
    posEnemy = pos;
}

Direction Enemy::getDirection()
{
    return direction;
}

void Enemy::setDirection(Direction dir)
{
    direction = dir;
}