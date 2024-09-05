#include "Configuration.h"
#include "MainCharacter.h"
#include "Projectile.h"
#include "Objects.h"
#include "PixelGame.h"
#include "Enemy.h"

int MainCharacter::playerHealth = 100;
//int MainCharacter::damagePerFrame = 2;
bool MainCharacter::isPlayerDead = false;
bool MainCharacter::canReceiveDamage = true;
int MainCharacter::playerScore = 0;
int MainCharacter::playerMana = 5;
float MainCharacter::playerSpawnPositionX = 43*32; //1120
float MainCharacter::playerSpawnPositionY = 37*32; //2590
float MainCharacter::playerCharacterTextureScale = 0.425f;
float MainCharacter::playerCharacterHitBoxScale = 0.425f;
float MainCharacter::playerPosX = MainCharacter::playerSpawnPositionX;
float MainCharacter::playerPosY = MainCharacter::playerSpawnPositionY;
std::shared_ptr<Projectile> MainCharacter::projectile_p = std::make_shared<Projectile>();
EnemyManager* MainCharacter::enemyManager = nullptr;
int MainCharacter::currentFrame;
float MainCharacter::framesCounter = 0;
int MainCharacter::framesSpeed;
Rectangle MainCharacter::frameRec;
std::shared_ptr<Enemy> MainCharacter::enemy_p;
std::shared_ptr<EnemyManager> MainCharacter::enemyManager_p = std::make_shared<EnemyManager>();
lastDirection MainCharacter::lastDir;
punchDir MainCharacter::punch = none;
bool MainCharacter::animationFinished = false;
bool MainCharacter::canGiveDamage = true;
Rectangle MainCharacter::playerEnemyRec;

void MainCharacter::setEnemy(const std::shared_ptr<Enemy>& enemy)
{
    enemy_p = enemy;
}

void MainCharacter::setEnemyManager(EnemyManager* manager)
{
    enemyManager = manager;
}

void MainCharacter::setProjectile(const std::shared_ptr<Projectile>& projectile)
{
    projectile_p = projectile;
}

void MainCharacter::initPlayer(Texture myTexture)
{
    frameRec = {32, 0.0f, 32, 32};
    framesCounter = 0;
    currentFrame = 0;
    framesSpeed = 8;
    lastDir = LASTRIGHT;
}

void MainCharacter::updateRec()
{
    float xPos = playerPosX + 5; // Adjusted X Position
    float yPos = playerPosY + 4; // Adjusted Y Position
    float width = 20; // Hitbox Width
    float height = 28; // Hitbox Height

    //Rec für kollision des chars
    playerRec = {
            xPos,
            yPos,
            width,
            height
    };
    //Rec zum hitten von enemies
    if(lastDir == LASTRIGHT || lastDir == LASTLEFT) {
        HitRec = {
                playerPosX - 4,
                playerPosY + 12,
                40,
                18
        };
    }
    if(lastDir == LASTUP || lastDir == LASTDOWN){
        HitRec = {
                playerPosX+4,
                playerPosY-4,
                25,
                40
        };
    }
    playerEnemyRec = {
            playerPosX,
            playerPosY,
            32,
            32
    };
}

void MainCharacter::updatePlayer(Texture myTexture, float deltaTime)
{
    bool moving;

    if(IsKeyDown(KEY_W) || IsKeyDown(KEY_A) || IsKeyDown(KEY_S) || IsKeyDown(KEY_D))
    {
        moving = true;
    }else if(!IsKeyDown(KEY_W) && !IsKeyDown(KEY_A) && !IsKeyDown(KEY_S) && !IsKeyDown(KEY_D))
    {
        moving = false;
    }

    if (punch == none && moving)
    {
        if (IsKeyDown(KEY_D)) {
            UniversalMethods::updateAnimation(deltaTime, framesCounter, currentFrame, 4, 7, frameRec.x, player);
        }
        else if (IsKeyDown(KEY_A)) {
            UniversalMethods::updateAnimation(deltaTime, framesCounter, currentFrame, 12, 15, frameRec.x, player);
        }
        else if (IsKeyDown(KEY_W)) {
            UniversalMethods::updateAnimation(deltaTime, framesCounter, currentFrame, 8, 11, frameRec.x, player);
        }
        else if (IsKeyDown(KEY_S)) {
            UniversalMethods::updateAnimation(deltaTime, framesCounter, currentFrame, 0, 3, frameRec.x, player);
        }

    }
    else if (punch != none)
    {
        int startFrame, endFrame;

        switch (punch)
        {
            case down:  startFrame = 16; endFrame = 19; break;
            case right: startFrame = 20; endFrame = 23; break;
            case up:    startFrame = 24; endFrame = 27; break;
            case left:  startFrame = 28; endFrame = 31; break;
            default:    startFrame = 0;  endFrame = 0;  break;
        }

        UniversalMethods::updateAnimation(deltaTime, framesCounter, currentFrame, startFrame, endFrame, frameRec.x, player);

        if (currentFrame == endFrame) {
            animationFinished = true;
            punch = none;
        }
    }
    else if (!moving && punch == none)
    {
        switch (lastDir) {
            case LASTRIGHT: UniversalMethods::updateAnimation(deltaTime, framesCounter, currentFrame, 36, 39, frameRec.x, player); break;
            case LASTLEFT:  UniversalMethods::updateAnimation(deltaTime, framesCounter, currentFrame, 44, 47, frameRec.x, player); break;
            case LASTUP:    UniversalMethods::updateAnimation(deltaTime, framesCounter, currentFrame, 40, 43, frameRec.x, player); break;
            case LASTDOWN:  UniversalMethods::updateAnimation(deltaTime, framesCounter, currentFrame, 32, 35, frameRec.x, player); break;
        }
    }

    checkCollisions();
}

void MainCharacter::drawMainCharacter(Texture myTexture, MainCharacter& character)
{
    // Draw the player sprite
    DrawTextureRec(myTexture, character.frameRec, {character.playerPosX, character.playerPosY}, WHITE);

    /*DrawRectangleLines(
            playerRec.x,
            playerRec.y,
            playerRec.width,
            playerRec.height,
            PURPLE
    );*/
}

float calculateSquaredDistance(float x1, float y1, float x2, float y2)
{
    return (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);
}

void MainCharacter::moveMainCharacter(int moveDirection, float deltaTime)
{
    float newPositionX = MainCharacter::playerPosX;
    float newPositionY = MainCharacter::playerPosY;
    float moveSpeedX = 0.0f;
    float moveSpeedY = 0.0f;

    switch (moveDirection)
    {
        case KEY_RIGHT:
        case KEY_D:
            newPositionX += ConfigConst::playerMoveSpeed;
            lastDir = LASTRIGHT;
            break;
        case KEY_LEFT:
        case KEY_A:
            newPositionX -= ConfigConst::playerMoveSpeed;
            lastDir = LASTLEFT;
            break;
        case KEY_UP:
        case KEY_W:
            newPositionY -= ConfigConst::playerMoveSpeed;
            lastDir = LASTUP;
            break;
        case KEY_DOWN:
        case KEY_S:
            newPositionY += ConfigConst::playerMoveSpeed;
            lastDir = LASTDOWN;
            break;

        default:
            break; //hier cases einfügen für schräg laufen mit hälfte speed?
    }
    /*if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
    {
        moveSpeedX = ConfigConst::playerMoveSpeed;
        lastDir = LASTRIGHT;
    }
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
    {
        moveSpeedX = -ConfigConst::playerMoveSpeed;
        lastDir = LASTLEFT;
    }
    if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W))
    {
        moveSpeedY = -ConfigConst::playerMoveSpeed;
        lastDir = LASTUP;
    }
    if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S))
    {
        moveSpeedY = ConfigConst::playerMoveSpeed;
        lastDir = LASTDOWN;
    }*/
    if (IsKeyDown(KEY_S) && IsKeyDown(KEY_D) && IsKeyDown(KEY_A) || IsKeyDown(KEY_S) && IsKeyDown(KEY_D) && IsKeyDown(KEY_W) || IsKeyDown(KEY_S) && IsKeyDown(KEY_A) && IsKeyDown(KEY_W) || IsKeyDown(KEY_D) && IsKeyDown(KEY_A) && IsKeyDown(KEY_W))
    {
        return;
    }

   /* if (moveSpeedX != 0.0f && moveSpeedY != 0.0f)
    {
        moveSpeedX *= 0.5f;
        moveSpeedY *= 0.5;
    }*/

    newPositionX += moveSpeedX;
    newPositionY += moveSpeedY;

    Rectangle newRec = {newPositionX + 4, newPositionY+16, playerRec.width, playerRec.height-12}; //hier hab ich y und height geändert - falls was buggt wieder rückgängig machen
    Rectangle enemyNewRec = {newPositionX + 4, newPositionY, playerRec.width, playerRec.height}; // für enemy kollision, weil der player sonst komplett den enemy verdecken kann /schaden kein sinn macht


    for (const Rectangle &doorRec : currentGameState.doorRectangles)
    {
        if (CheckCollisionRecs(enemyNewRec, doorRec))
        {
            return;
        }
    }

    for (const Rectangle &wallRec : currentGameState.wallRectangles)
    {
        if (CheckCollisionRecs(newRec, wallRec))
        {
            return;
        }
    }

    for (const Rectangle &wallRec : currentGameState.overworldWallRecs)
    {
        if (CheckCollisionRecs(newRec, wallRec))
        {
            return;
        }
    }

    for (const auto &enemy: enemyManager->enemies)
    {
        if (CheckCollisionRecs(enemyNewRec, {enemy->getHitRec().x + 4, enemy->getHitRec().y, enemy->getHitRec().width - 8,enemy->getHitRec().height - 10}))
        {
            return;
        }
    }

    Stone* nearestStone = nullptr;
    float nearestDistanceSquared = std::numeric_limits<float>::max();

    for (Stone &stone : Stone::stoneObjects)
    {
        if (CheckCollisionRecs(enemyNewRec, stone.getRectangle()))  //test
        {
            nearestStone = &stone;
            break;
        }
    }

    checkCollisions();

    if (nearestStone)
    {
        nearestStone->moveOneTile(moveDirection, currentGameState.wallRectangles);
    }
    else
    {
        // If no stone is to be moved, update player position
        playerPosX = newPositionX;
        playerPosY = newPositionY;
    }

    // Update all stones
    for (Stone &stone : Stone::stoneObjects)
    {
        stone.update(deltaTime);
    }

    if (!projectile_p->getActive())
    {
        if (lastDir == LASTLEFT)
        {
            projectile_p->setProjectileDestination(Direction::LEFT);
        }

        if (lastDir == LASTRIGHT)
        {
            projectile_p->setProjectileDestination(Direction::RIGHT);
        }

        if (lastDir == LASTUP)
        {
            projectile_p->setProjectileDestination(Direction::UP);
        }

        if (lastDir == LASTDOWN)
        {
            projectile_p->setProjectileDestination(Direction::DOWN);
        }
    }
}

void MainCharacter::checkCollisions()
{
    for (const auto &enemy: enemyManager->enemies)
    {
        if (CheckCollisionRecs(playerEnemyRec, enemy->getRec()))
        {
            std::cout << "collision" << std::endl;
            if(playerPosY > enemy->getPosition().y +16 && enemy->getDirection() == Direction::DOWN && playerPosX >= enemy->getPosition().x -16  && playerPosX <= enemy->getPosition().x+14)
            {
                enemy->setPos({enemy->getPosition().x, playerPosY -32});
                enemy->setDirection(Direction::UP);
            }
            if(playerPosY < enemy->getPosition().y-16 && enemy->getDirection() == Direction::UP && playerPosX >= enemy->getPosition().x -16 && playerPosX < enemy->getPosition().x+14)
            {
                enemy->setPos({enemy->getPosition().x, playerPosY+22});
                enemy->setDirection(Direction::DOWN);
            }
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
    static double lastDamageTime = 0.0;
    double currentTime = GetTime();

    if (currentTime - lastDamageTime >= 0.5) {
        canReceiveDamage = true;
    }

    for (const auto &enemy : enemyManager->enemies)
    {
        if (CheckCollisionRecs(MainCharacter::playerRec, enemy->getRec()))
        {
            if (canReceiveDamage) {
                InGameHud::health -= 0.5;
                canReceiveDamage = false;
                lastDamageTime = currentTime;
            }
            break;
        }
    }
}


void MainCharacter::attack()
{

    static double lastDamageTime = 0.0;
    double currentTime = GetTime();
    if(currentTime - lastDamageTime >= 0.3){
        canGiveDamage = true;
    }

    if (IsKeyPressed(KEY_ENTER) && playerMana > 0 && !projectile_p->getActive()) //Projectile wird aktiviert
    {
        Vector2 startPosition;
        playerMana -= 1;
        if (lastDir == LASTRIGHT)
        {
            startPosition = {playerPosX + 20, playerPosY + 10};
        }
        if (lastDir == LASTLEFT)
        {
            startPosition = {playerPosX - 1, playerPosY + 10};
        }
        if (lastDir == LASTUP)
        {
            startPosition = {playerPosX + 10, playerPosY - 5};
        }
        if (lastDir == LASTDOWN)
        {
            startPosition = {playerPosX + 10, playerPosY + 20};
        }
        projectile_p->init(startPosition, {300.0f, 300.0f});
    }

    if (projectile_p->getActive())
    {
        enemyManager->checkProjectileEnemyCollision(projectile_p, enemy_p);
    }
    enemyManager->deleteEnemy();

    if(IsKeyPressed(KEY_SPACE) && punch == none)
    {
        if (lastDir == LASTRIGHT)
        {
            punch = right;
        }
        if (lastDir == LASTLEFT)
        {
            punch = left;
        }
        if (lastDir == LASTUP)
        {
            punch = up;
        }
        if (lastDir == LASTDOWN)
        {
            punch = down;
        }
    }

    for (const auto &enemy: enemyManager->enemies)  //es gibt noch einen bug dass man 2 mal spammen kann in dem moment wo das projektil den enemy trifft
    {

        if (CheckCollisionRecs(MainCharacter::HitRec, enemy->getRec()) && IsKeyPressed(KEY_SPACE))
        {
            if(canGiveDamage)
            {
                enemy->enemyGetsHit();
            }
            canGiveDamage = false;
            lastDamageTime = currentTime;
            break;
        }
    }
}

void MainCharacter::setSpawnPosition()
{
    playerPosX = MainCharacter::playerSpawnPositionX;
    playerPosY = MainCharacter::playerSpawnPositionY;
}

Rectangle MainCharacter::getRectangle() const
{
    Rectangle rect;
    rect.x = HitRec.x + 4.5;
    rect.y = HitRec.y + 2;
    rect.width = HitRec.width - 10;
    rect.height = HitRec.height - 4.5;
    return rect;
}

void MainCharacter::setPosition(Vector2 pos)
{
    playerPosX = pos.x;
    playerPosY = pos.y;
}

Vector2 MainCharacter::getPosition()
{
    return {playerPosX, playerPosY};
}