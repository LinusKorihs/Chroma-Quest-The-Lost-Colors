#include "Projectile.h"


Projectile::Projectile()
{
}

void Projectile::load()
{
    projectileTexture = LoadTexture("assets/graphics/Projectiles/TestProjectile.png");
}

void Projectile::init(Vector2 startPosition, Vector2 speed)
{
    projectilePos = startPosition;
    projectileSpeed = speed;
    isProjActive = true;
}

void Projectile::collision()
{
    for (const Rectangle& wallRec : currentGameState.wallRectangles)
    {
        if (CheckCollisionRecs(projectileRec, wallRec) || projectilePos.x > projectilePos.x + 200)
        {
            isProjActive = false;
        }
    }
}

void Projectile::update(float deltaTime, int direction)
{
    projectileRec = {projectilePos.x, projectilePos.y, static_cast<float>(projectileTexture.width) , static_cast<float>(projectileTexture.height)};

    switch (static_cast<int>(projectileDestination)) //switch nicht für float, deshalb cast
    {
        case 1:
            projectilePos.x += projectileSpeed.x * deltaTime;
            break;
        case 2:
            projectilePos.x -= projectileSpeed.x * deltaTime;
            break;
        case 3:
            projectilePos.y -= projectileSpeed.y * deltaTime;
            break;
        case 4:
            projectilePos.y += projectileSpeed.y * deltaTime;
            break;
    }

    collision(); //kollisionen mit wänden
}


void Projectile::draw()
{
    if (isProjActive)
    {
        DrawTextureEx(projectileTexture, projectilePos, 0, 1.0f, WHITE);
    }
}

bool Projectile::getActive()
{
    return isProjActive;
}

void Projectile::setActive(bool isActive)
{
    isProjActive = isActive;
}

Rectangle Projectile::getRec()
{
    return projectileRec;
}

void Projectile::unload()
{
    UnloadTexture(projectileTexture);
}

int Projectile::getProjectileDestination()
{
    return projectileDestination;
}

void Projectile::setProjectileDestination(int destination)
{
    projectileDestination = destination;
}