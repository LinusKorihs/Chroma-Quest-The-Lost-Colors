#include "Projectile.h"

Pixelgame::Projectile::Projectile()
{
}
void Pixelgame::Projectile::Load(){
    projectileTexture = LoadTexture("assets/graphics/necrobolt1_strip.png");
}
void Pixelgame::Projectile::Init(Vector2 startPosition, Vector2 speed)
{
    position = startPosition;
    projSpeed = speed;
    isActive = true;
}

void Pixelgame::Projectile::Collision()
{

    for (const Rectangle& wallRec : gameState.wallRecs)
    {
        if (CheckCollisionRecs(projectileRec, wallRec) or position.x > position.x + 200) //mcX darf nicht mehr geupdated werden - andere variable benutzen
        {
            isActive = false;
        }
    }
}

void Pixelgame::Projectile::Update( float deltaTime, int projDest)
{
    projectileRec = {position.x, position.y, static_cast<float>(projectileTexture.width) , static_cast<float>(projectileTexture.height)};

        switch (static_cast<int>(projDest)) //switch nicht für float, deshalb cast
        {
            case 1:
                position.x += projSpeed.x * deltaTime;
                break;
            case 2:
                position.x -= projSpeed.x * deltaTime;
                break;
            case 3:
                position.y -= projSpeed.y * deltaTime;
                break;
            case 4:
                position.y += projSpeed.y * deltaTime;
                break;
        }

    Collision(); //kollisionen mit wänden
}

void Pixelgame::Projectile::Draw()
{
    if (isActive)
    {
        DrawTextureEx(projectileTexture, position, 0, 1.0f, WHITE);
    }
}

bool Pixelgame::Projectile::GetActive() {
    return isActive;
}

void Pixelgame::Projectile::SetActive(bool active) {
    isActive = active;
}

Rectangle Pixelgame::Projectile::GetRec() {
    return projectileRec;
}

void Pixelgame::Projectile::Unload() {
    UnloadTexture(projectileTexture);
}
