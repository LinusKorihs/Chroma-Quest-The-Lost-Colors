#include "Projectile.h"
#include "GameState.h"
#include "Enemy.h"
#include "PixelGame.h"

std::shared_ptr<Projectile> Projectile::projectilePointer;
std::shared_ptr<Enemy> Projectile::enemyPointer;

Projectile::Projectile()
{
    enemyPointer = std::make_shared<Enemy>(PixelGame::enemy);
}

int Projectile::projectileDestination;

void Projectile::load()
{
    projectileTexture = LoadTexture("assets/graphics/Projectiles/TestProjectile.png");
}

void Projectile::init(Vector2 startPosition, Vector2 speed)
{
    projectilePosition = startPosition;
    projectileSpeed = speed;
    isProjectileActive = true;
}

void Projectile::collision()
{
    for (const Rectangle& wallRec : currentGameState.wallRectangles)
    {
        if (CheckCollisionRecs(projectileRectangle, wallRec) || projectilePosition.x > projectilePosition.x + 200)
        {
            isProjectileActive = false;
        }
    }
}

void Projectile::update(float deltaTime)
{
    if (!isProjectileActive)
        return;

    projectileRectangle = {projectilePosition.x, projectilePosition.y, static_cast<float>(projectileTexture.width), static_cast<float>(projectileTexture.height)};

    switch (projectileDestination)
    {
        case 1:
            projectilePosition.x += projectileSpeed.x * deltaTime;
            break;
        case 2:
            projectilePosition.x -= projectileSpeed.x * deltaTime;
            break;
        case 3:
            projectilePosition.y -= projectileSpeed.y * deltaTime;
            break;
        case 4:
            projectilePosition.y += projectileSpeed.y * deltaTime;
            break;
    }

    collision();
}

void Projectile::draw()
{
    if (isProjectileActive)
    {
        DrawTextureEx(projectileTexture, projectilePosition, 0, 1.0f, WHITE);
    }
}

bool Projectile::getActive()
{
    return isProjectileActive;
}

void Projectile::setActive(bool isActive)
{
    isProjectileActive = isActive;
}

Rectangle Projectile::getRectangle()
{
    return projectileRectangle;
}

void Projectile::unload()
{
    UnloadTexture(projectileTexture);
}

int Projectile::getProjectileDestination()
{
    return projectileDestination;
}
