#include "Configuration.h"
#include "LoadResources.h"
#include "MainCharacter.h"
#include "Projectile.h"
#include "Stone.h"
#include "PixelGame.h"
#include "Enemy.h"

int MainCharacter::playerHealth = 100;
int MainCharacter::damagePerFrame = 2;
bool MainCharacter::isPlayerDead = false;
int MainCharacter::playerScore = 0;
int MainCharacter::playerMana = 5;
float MainCharacter::playerSpawnPositionX = 32*35; //32*35 in new, 80 in old
float MainCharacter::playerSpawnPositionY = 32*65; //32*65 in new, 368 in old
float MainCharacter::playerPositionX = MainCharacter::playerSpawnPositionX;
float MainCharacter::playerPositionY = MainCharacter::playerSpawnPositionY;

void MainCharacter::drawMainCharacter(Texture myTexture)
{
    Rectangle source = {0.0f, 0.0f, (float) myTexture.width, (float) myTexture.height};
    Rectangle destination = {playerPositionX, playerPositionY, myTexture.width * 0.15f, myTexture.height * 0.15f};
    DrawTexturePro(myTexture, source, destination, {0, 0}, 0.0f, WHITE);
}

void MainCharacter::moveMainCharacter(int moveDirection, float deltaTime)
{
    float newPositionX = MainCharacter::playerPositionX;
    float newPositionY = MainCharacter::playerPositionY;

    switch (moveDirection)
    {
        case KEY_RIGHT:
        case KEY_D:
            newPositionX += ConfigConst::playerMoveSpeed;
            ConfigNotConst::lastDirectionLeft = false;
            ConfigNotConst::lastDirectionUp = false;
            ConfigNotConst::lastDirectionDown = false;
            ConfigNotConst::lastDirectionRight = true;
            break;
        case KEY_LEFT:
        case KEY_A:
            newPositionX -= ConfigConst::playerMoveSpeed;
            ConfigNotConst::lastDirectionLeft = true;
            ConfigNotConst::lastDirectionUp = false;
            ConfigNotConst::lastDirectionDown = false;
            ConfigNotConst::lastDirectionRight = false;
            break;
        case KEY_UP:
        case KEY_W:
            newPositionY -= ConfigConst::playerMoveSpeed;
            ConfigNotConst::lastDirectionUp = true;
            ConfigNotConst::lastDirectionDown = false;
            ConfigNotConst::lastDirectionRight = false;
            ConfigNotConst::lastDirectionLeft = false;
            break;
        case KEY_DOWN:
        case KEY_S:
            newPositionY += ConfigConst::playerMoveSpeed;
            ConfigNotConst::lastDirectionUp = false;
            ConfigNotConst::lastDirectionDown = true;
            ConfigNotConst::lastDirectionRight = false;
            ConfigNotConst::lastDirectionLeft = false;
            break;
        default:
            break;
    }

    Rectangle newRec = {newPositionX, newPositionY, TextureManager::getTexture("MainCharacter").width * 0.15f, TextureManager::m_textures["MainCharacter"].height * 0.15f};

    for (const Rectangle &wallRec: currentGameState.wallRectangles)
    {
        if (CheckCollisionRecs(newRec, wallRec))
        {
            return;
        }
    }

    Stone::stoneCollision = false;
    for (Stone &stone: Stone::stoneObjects)
    {
        if (CheckCollisionRecs(newRec, stone.getRectangle()))
        {
            stone.move(moveDirection, currentGameState.wallRectangles);
            Stone::stoneCollision = true;
        }
    }

    if (!Stone::stoneCollision)
    {
        playerPositionX = newPositionX;
        playerPositionY = newPositionY;
    }

    if(!Projectile::projectilePointer->getActive()) //Richtung der Projektile basierend auf Player movement (wird in Projectiles.h übergeben)
    {
        if (ConfigNotConst::lastDirectionLeft)
        {
            Projectile::projectileDestination = 2;
        }
        if (ConfigNotConst::lastDirectionRight)
        {
            Projectile::projectileDestination = 1;
        }
        if (ConfigNotConst::lastDirectionUp)
        {
            Projectile::projectileDestination = 3;
        }
        if (ConfigNotConst::lastDirectionDown)
        {
            Projectile::projectileDestination = 4;
        }
    }
}

void MainCharacter::playerDeath()
{
    if (MainCharacter::playerHealth <= 0)
    {
        MainCharacter::isPlayerDead = true;
        currentGameState.changeGameState(MenuState::MainMenu);
        MainCharacter::playerHealth = 100;
        MainCharacter::isPlayerDead = true;
        MainCharacter::setSpawnPosition();
    }
}

void MainCharacter::receiveDamage()
{
    /*if (CheckCollisionRecs(MainCharacter::playerCharacterRectangle, PixelGame::lavaTileRectangle))
    {
        MainCharacter::playerHealth -= MainCharacter::damagePerFrame;
        if (MainCharacter::playerHealth <= 0)
        {
            playerDeath();
        }
    }*/
}

void MainCharacter::attack()
{
    if (IsKeyPressed(KEY_ENTER) && MainCharacter::playerMana > 0 && !Projectile::projectilePointer->getActive())
    {
        Vector2 startPosition;
        MainCharacter::playerMana -= 1;

        if (ConfigNotConst::lastDirectionRight)
        {
            startPosition = {MainCharacter::playerPositionX + 20, MainCharacter::playerPositionY + 10};
            Projectile::projectilePointer->init(startPosition, {300.0f, 0.0f});
            Projectile::projectilePointer->projectileDestination = 1;
        }
        else if (ConfigNotConst::lastDirectionLeft)
        {
            startPosition = {MainCharacter::playerPositionX - 1, MainCharacter::playerPositionY + 10};
            Projectile::projectilePointer->init(startPosition, {-300.0f, 0.0f});
            Projectile::projectilePointer->projectileDestination = 2;
        }
        else if (ConfigNotConst::lastDirectionUp)
        {
            startPosition = {MainCharacter::playerPositionX + 10, MainCharacter::playerPositionY - 5};
            Projectile::projectilePointer->init(startPosition, {0.0f, -300.0f});
            Projectile::projectilePointer->projectileDestination = 3;
        }
        else if (ConfigNotConst::lastDirectionDown)
        {
            startPosition = {MainCharacter::playerPositionX + 10, MainCharacter::playerPositionY + 20};
            Projectile::projectilePointer->init(startPosition, {0.0f, 300.0f});
            Projectile::projectilePointer->projectileDestination = 4;
        }
    }

    if (CheckCollisionRecs(Projectile::projectilePointer->getRectangle(), PixelGame::enemy.getEnemyRec()) &&
        Projectile::projectilePointer->getActive() && !Projectile::enemyPointer->getUnload())
    {
        Projectile::enemyPointer->enemyGetsHit();
        MainCharacter::playerScore += 10;
        Projectile::projectilePointer->setActive(false);
    }
}

void MainCharacter::setSpawnPosition()
{
    playerPositionX = MainCharacter::playerSpawnPositionX;
    playerPositionY = MainCharacter::playerSpawnPositionY;
}
