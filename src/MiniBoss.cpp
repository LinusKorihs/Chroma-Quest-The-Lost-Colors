
#include "MiniBoss.h"

MiniBoss::MiniBoss(Vector2 position, Texture2D &enemTexture, MiniBossType type) {
    std::srand(std::time(nullptr)); // Initialisiere Zufallsgenerator
    direction = getRandomDirection();
    enemyDeath = false;
    unload = false;
    posEnemy = position;
    enemyHits = 0;
    enemyType = type;
    enemyTexture = enemTexture;
    direction = 1;
    speed = 100.0f;
    leftLimit = 1050.0f;
    rightLimit = 1180.0f;
    upLimit = 1920.0f;
    downLimit = 2100.0f;
    moveDelay = 2.0f;
}

MiniBossDirection MiniBoss::getRandomDirection() {
    return static_cast<MiniBossDirection>(std::rand() % 4);
}


void MiniBoss::updateBoss(float deltaTime)
{
    enemyRec = {posEnemy.x, posEnemy.y, (float)enemyTexture.width, (float)enemyTexture.height};

    if (canMove) {
        switch (direction) {
            case LEFT:
                posEnemy.x -= speed * deltaTime;
                break;
            case RIGHT:
                posEnemy.x += speed * deltaTime;
                break;
            case UP:
                posEnemy.y -= speed * deltaTime;
                break;
            case DOWN:
                posEnemy.y += speed * deltaTime;
                break;
                case DIAGONALUPLEFT:
                posEnemy.x -= speed * deltaTime;
                posEnemy.y -= speed * deltaTime;
                break;
                case DIAGONALUPRIGHT:
                posEnemy.x += speed * deltaTime;
                posEnemy.y -= speed * deltaTime;
                break;
                case DIAGONALDOWNLEFT:
                posEnemy.x -= speed * deltaTime;
                posEnemy.y += speed * deltaTime;
                break;
                case DIAGONALDOWNRIGHT:
                posEnemy.x += speed * deltaTime;
                posEnemy.y += speed * deltaTime;
                break;
        }

        if (posEnemy.x <= leftLimit) {
            posEnemy.x = leftLimit;
            direction = getRandomDirection();
        } else if (posEnemy.x >= rightLimit) {
            posEnemy.x = rightLimit;
            direction = getRandomDirection();
        } else if (posEnemy.y <= upLimit) {
            posEnemy.y = upLimit;
            direction = getRandomDirection();
        } else if (posEnemy.y >= downLimit) {
            posEnemy.y = downLimit;
            direction = getRandomDirection();
        }else if (posEnemy.x <= leftLimit && posEnemy.y <= upLimit) {
            posEnemy.x = leftLimit;
            posEnemy.y = upLimit;
            direction = getRandomDirection();
        }else if (posEnemy.x >= rightLimit && posEnemy.y <= upLimit) {
            posEnemy.x = rightLimit;
            posEnemy.y = upLimit;
            direction = getRandomDirection();
        }else if (posEnemy.x <= leftLimit && posEnemy.y >= downLimit) {
            posEnemy.x = leftLimit;
            posEnemy.y = downLimit;
            direction = getRandomDirection();
        }else if (posEnemy.x >= rightLimit && posEnemy.y >= downLimit) {
            posEnemy.x = rightLimit;
            posEnemy.y = downLimit;
            direction = getRandomDirection();
        }
        moveTimer += deltaTime;
        if (moveTimer >= moveDelay) {
            canMove = false;
            moveTimer = 0.0f; // Zurücksetzen des Timers für die nächste Bewegung
        }
    } else {
        // Boss bleibt stehen
        moveTimer += deltaTime;
        if (moveTimer >= moveDelay) {
            canMove = true;
            moveTimer = 0.0f; // Zurücksetzen des Timers für die nächste Bewegung
            direction = getRandomDirection(); // Neue Richtung nach der Pause wählen
        }
    }

    if(getBossHits() == 15 && enemyType == BOSSRED) //wie viele hits ein enemy aushält
    {
        enemyDeath = true;
    }
    if(getBossHits() == 20 && enemyType == BOSSBLUE)
    {
        enemyDeath = true;
    }
    if(enemyHits == 25 && enemyType == BOSSYELLOW)
    {
        enemyDeath = true;
    }


}

void MiniBoss::drawBoss()
{
    DrawTextureV(enemyTexture, posEnemy, WHITE);
    DrawRectangleLines(posEnemy.x, posEnemy.y, enemyTexture.width, enemyTexture.height, RED);
}

Rectangle MiniBoss::getBossRec()
{
    return enemyRec;
}

bool MiniBoss::getBossDeath()
{
    return enemyDeath;
}
void MiniBoss::setBossDead(bool dead)
{
    enemyDeath = dead;
}

bool MiniBoss::getUnload()
{
    return unload;
}

void MiniBoss::bossGetsHit()
{
    enemyHits++;
}
int MiniBoss::getBossHits()
{
    return enemyHits;
}

Vector2 MiniBoss::getPosition()
{
    return posEnemy;
}
