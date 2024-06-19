#include "Configuration.h"
#include "TextureManage.h"
#include "MainCharacter.h"
#include "Projectile.h"
#include "Objects.h"
#include "PixelGame.h"
#include "Enemy.h"

int MainCharacter::playerHealth = 100;
int MainCharacter::damagePerFrame = 2;
bool MainCharacter::isPlayerDead = false;
int MainCharacter::playerScore = 0;
int MainCharacter::playerMana = 5;
float MainCharacter::playerSpawnPositionX = 32*35; //32*35 in new, 80 in old
float MainCharacter::playerSpawnPositionY = 32*65; //32*65 in new, 368 in old
float MainCharacter::playerCharacterTextureScale = 0.1425f;
float MainCharacter::playerCharacterHitBoxScale = 0.1425f;
float MainCharacter::playerPositionX = MainCharacter::playerSpawnPositionX;
float MainCharacter::playerPositionY = MainCharacter::playerSpawnPositionY;

void MainCharacter::drawMainCharacter(Texture myTexture)
{
    Rectangle source = {0.0f, 0.0f, (float) myTexture.width, (float) myTexture.height};
    Rectangle destination = {playerPositionX, playerPositionY, myTexture.width * playerCharacterTextureScale, myTexture.height * playerCharacterTextureScale};
    DrawTexturePro(myTexture, source, destination, {0, 0}, 0.0f, WHITE);
}

float calculateSquaredDistance(float x1, float y1, float x2, float y2)
{
    return (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);
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
    Stone *nearestStone = nullptr;
    float nearestDistanceSquared = std::numeric_limits<float>::max();
    Rectangle newRec = {newPositionX, newPositionY, TextureManager::getTexture("MainCharacter").width * playerCharacterHitBoxScale, TextureManager::m_textures["MainCharacter"].height * playerCharacterHitBoxScale};

    for (const Rectangle &wallRec: currentGameState.wallRectangles)
    {
        if (CheckCollisionRecs(newRec, wallRec))
        {
            return;
        }
    }

    for (Stone &stone : Stone::stoneObjects)
    {
        float stoneCenterX = stone.getRectangle().x + stone.getRectangle().width / 2.0f;
        float stoneCenterY = stone.getRectangle().y + stone.getRectangle().height / 2.0f;
        float playerCenterX = newPositionX + (TextureManager::getTexture("MainCharacter").width * playerCharacterHitBoxScale) / 2.0f;
        float playerCenterY = newPositionY + (TextureManager::getTexture("MainCharacter").height * playerCharacterHitBoxScale) / 2.0f;

        float distanceSquared = calculateSquaredDistance(playerCenterX, playerCenterY, stoneCenterX, stoneCenterY);

        if (distanceSquared < nearestDistanceSquared)
        {
            nearestDistanceSquared = distanceSquared;
            nearestStone = &stone;
        }
    }

    // Attempt to move the nearest stone if one was found within a reasonable distance
    if (nearestStone && nearestDistanceSquared < 1000.0f) // Adjust threshold as needed
    {
        nearestStone->move(moveDirection, currentGameState.wallRectangles);
    }
    else
    {
        // If no stone is close enough, update player position
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
