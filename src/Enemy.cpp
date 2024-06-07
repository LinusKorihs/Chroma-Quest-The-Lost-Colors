#include "Enemy.h"
#include "Projectile.h"
#include "MainCharacter.h"

std::shared_ptr<Projectile> Enemy::projectilePointer;

Enemy::Enemy()
{
    projectilePointer = std::make_shared<Projectile>();
}

Enemy::Enemy(Vector2 position, Texture2D &enemyTexture, int hits, float knockbackStrength, EnemyType type)
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
    projectilePointer = std::make_shared<Projectile>();
}

void Enemy::updateEnemy(float deltaTime, Texture2D &enemyTexture)
{
    framesCounter++; // Update counter

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

void Enemy::drawEnemy(Texture2D &enemyTexture)
{
    if (!enemyDeath && !unload)
    {
        if (currentFrame < 7)
        {
            DrawTextureRec(enemyTexture, frameRec1, positionEnemy, WHITE);
        }
        else
        {
            DrawTextureRec(enemyTexture, frameRec2, positionEnemy, WHITE);
        }
    }
    else
    {
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
    return positionEnemy;
}

void Enemy::enemyAttack()
{
    //std::cout << "In Enemy::enemyAttack()" << std::endl;
    if (!projectilePointer)
    {
        std::cout << "projectilePointer is null" << std::endl;
        return; // Exit the function if projectilePointer is null
    }

    if (!projectilePointer->getActive() && !Projectile::enemyPointer->getEnemyDeath())
    {
        Vector2 startPosition = Projectile::enemyPointer->getPosition();
        startPosition.y += 10;

        Vector2 enemyProjectileSpeed = {100.0f, 0.0f}; // example speed to the right
        projectilePointer->init(startPosition, enemyProjectileSpeed);
        Projectile::projectilePointer->projectileDestination = 1; // Assuming 1 is the right direction
    }

    if (projectilePointer->getActive() && CheckCollisionRecs(projectilePointer->getRectangle(), MainCharacter::playerCharacterRectangle))
    {
        MainCharacter::playerHealth -= 10;
        projectilePointer->setActive(false);
    }

    if (CheckCollisionRecs(Projectile::enemyPointer->getEnemyRec(), MainCharacter::playerCharacterRectangle))
    {
        MainCharacter::playerHealth -= 10;
    }
}
