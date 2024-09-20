
#include "MiniBoss.h"

MiniBoss::MiniBoss(Vector2 position, Texture2D &enemTexture, MiniBossType type, Pathfinder &pathfinder) : posEnemy(position), enemyTexture(enemTexture), enemyType(type), pathfinder(pathfinder), pathIndex(0) {
    std::srand(std::time(nullptr)); // Initialisiere Zufallsgenerator
    //direction = getRandomDirection();
    enemyDeath = false;
    unload = false;
    posEnemy = position;
    enemyHits = 0;
    enemyType = type;
    enemyTexture = enemTexture;
    direction = 1;
    speed = 100.0f;
    leftLimit = 31*32;
    rightLimit = 38*32;
    upLimit = 74*32;
    downLimit = 76*32;
    moveDelay = 2.0f;
    hasShield = true;
    shieldHits = 0;
    proj_p = std::make_shared<Projectile>();
    canMove = true;
    state = BossState::Idle;
    frameRec = {0, 0, (float)enemyTexture.width / 48, (float)enemyTexture.height};
    currentFrame = 0;
    framesCounter = 0;
    framesSpeed = 8;
    plate1Pressed = false;
    plate2Pressed = false;
    barHits = 0;

}
float Vector2Distance(Vector2 v1, Vector2 v2)
{
    return sqrt(pow(v2.x - v1.x, 2) + pow(v2.y - v1.y, 2));
}


void MiniBoss::updateBoss(float deltaTime, Vector2 playerPosition)
{
    if(currentDirection == UP_RIGHT || currentDirection == UP_LEFT || currentDirection == DOWN_RIGHT || currentDirection == DOWN_LEFT || currentDirection == LEFTEN || currentDirection == RIGHTEN)
    {
        enemyRec = {posEnemy.x+16, posEnemy.y + 10, 32,54};
    }
    else if(currentDirection == UPEN || currentDirection == DOWNEN || state == BossState::Idle) {
        enemyRec = {posEnemy.x, posEnemy.y + 10, 64,54};
    }
    if(state == BossState::Idle){
        enemyRec = {posEnemy.x, posEnemy.y + 10, 64,54};
    }
    float newPosX = posEnemy.x;
    float newPosY = posEnemy.y;

    static int diagonalSteps = 0; // Zähler für Schritte in diagonalen Richtungen
    Vector2 direction; // Bewegungsrichtung

    switch (state)
    {
        case BossState::Idle:
            if (isPlayerInRange(playerPosition, 400))
            {
                std::cout << "Idle" << std::endl;
                stateTimer += deltaTime;
                if (stateTimer >= idleTime)
                {
                    state = BossState::Attacking;
                    stateTimer = 0;
                }
            }
            break;

        case BossState::Attacking:
            if (isPlayerInRange(playerPosition, 400))
            {
                if (Vector2Distance(posEnemy, playerPosition) > 1.0f)
                {
                    direction = { playerPosition.x - posEnemy.x, playerPosition.y - posEnemy.y };

                    // Normalisiere die Richtung
                    float length = sqrt(direction.x * direction.x + direction.y * direction.y);
                    if (length > 0.0f)
                    {
                        direction.x /= length;
                        direction.y /= length;
                    }

                    // Bewege den Boss in beide Achsen
                    newPosX += direction.x * speed * deltaTime;
                    newPosY += direction.y * speed * deltaTime;

                    // Berechne den Winkel in Grad
                    float angle = atan2(direction.y, direction.x) * (180.0f / PI); // PI ist die Konstante für π

                    // Setze die Richtung basierend auf der Bewegungsrichtung
                    if (fabs(direction.x) > fabs(direction.y))
                    {
                        currentDirection = (direction.x > 0) ? RIGHTEN : LEFTEN;
                    } else if (fabs(direction.y) > fabs(direction.x))
                    {
                        currentDirection = (direction.y > 0) ? DOWNEN : UPEN;
                    } else {
                        // Bei diagonaler Bewegung, überprüfe den Winkel
                        if (angle >= 30.0f && angle <= 60.0f)
                        {
                            currentDirection = UP_RIGHT;
                        } else if (angle <= -30.0f && angle >= -60.0f)
                        {
                            currentDirection = DOWN_LEFT;
                        } else if (angle < 30.0f && angle > 0)
                        {
                            currentDirection = UP_RIGHT;
                        } else if (angle > -30.0f && angle < 0)
                        {
                            currentDirection = DOWN_LEFT;
                        }
                    }
                } else {
                    state = BossState::Idle;
                    stateTimer = 0;
                }
            }
            break;

        case BossState::Returning:
            if (isPlayerInRange(playerPosition, 400)) {
                if (Vector2Distance(posEnemy, {35 * 32, 11 * 32}) > 1.0f) {
                    direction = { 35 * 32 - posEnemy.x, 11 * 32 - posEnemy.y };

                    // Normalisiere die Richtung
                    float length = sqrt(direction.x * direction.x + direction.y * direction.y);
                    if (length > 0.0f) {
                        direction.x /= length;
                        direction.y /= length;
                    }

                    // Bewege den Boss in beide Achsen
                    newPosX += direction.x * speed * deltaTime;
                    newPosY += direction.y * speed * deltaTime;

                    // Berechne den Winkel in Grad
                    float angle = atan2(direction.y, direction.x) * (180.0f / PI);

                    // Setze die Richtung basierend auf der Bewegungsrichtung
                    if (fabs(direction.x) > fabs(direction.y)) {
                        currentDirection = (direction.x > 0) ? RIGHTEN : LEFTEN;
                    } else if (fabs(direction.y) > fabs(direction.x)) {
                        currentDirection = (direction.y > 0) ? DOWNEN : UPEN;
                    } else {
                        // Bei diagonaler Bewegung, überprüfe den Winkel
                        if (angle >= 30.0f && angle <= 60.0f) {
                            currentDirection = UP_RIGHT; // Animation für oben rechts
                        } else if (angle <= -30.0f && angle >= -60.0f) {
                            currentDirection = DOWN_LEFT; // Animation für unten links
                        } else if (angle < 30.0f && angle > 0) {
                            currentDirection = UP_RIGHT; // Animation für oben rechts
                        } else if (angle > -30.0f && angle < 0) {
                            currentDirection = DOWN_LEFT; // Animation für unten links
                        }
                    }
                } else {
                    state = BossState::Idle;
                    stateTimer = 0;
                }
            }
            break;
    }

            Rectangle newRec = {newPosX, newPosY, static_cast<float>(enemyTexture.width / 48),
                                static_cast<float>(enemyTexture.height)};
            for (const Rectangle &wallRec: currentGameState.wallRectangles) {
                if (CheckCollisionRecs(newRec, wallRec)) {
                    state = BossState::Returning; // Bei Kollision mit einer Wand zurückkehren
                    break;
                }
            }
            for (const Rectangle &doorRec: currentGameState.doorRectangles)
            {
                if (CheckCollisionRecs(newRec, doorRec))
                {
                    state = BossState::Returning;
                    break;
                }
            }
            for (Stone &stone: Stone::stoneObjects)
            {
                if (CheckCollisionRecs(newRec, stone.getRectangle()))
                {
                    state = BossState::Returning;
                    break;
                }
            }

            if (!enemyDeath)
            {
                posEnemy.x = newPosX;
                posEnemy.y = newPosY;
            }

            // Animation update
            framesCounter++; // Update counter

            if (framesCounter >= (60 / framesSpeed))
            {
                framesCounter = 0;

                if (enemyDeath) {
                    if (currentFrame < 32)
                    {
                        currentFrame = 32;
                    }
                    currentFrame++;

                    if (currentFrame > 34)
                    {
                        unload = true; // Ende der Death-Animation
                    }
                } else {
                    currentFrame++;
                    if (state == BossState::Idle)
                    {
                        if (currentFrame > 3)
                        {
                            currentFrame = 0;
                        }
                    }
                    if (state == BossState::Attacking || state == BossState::Returning)
                    {
                        if (currentDirection == RIGHTEN)
                        {
                            if (currentFrame > 27 || currentFrame < 24)
                            {
                                currentFrame = 24;
                            }
                        }
                        if (currentDirection == LEFTEN)
                        {
                            if (currentFrame > 31 || currentFrame < 28)
                            {
                                currentFrame = 28;
                            }
                        }
                        if (currentDirection == DOWNEN || currentDirection == DOWN_LEFT || currentDirection == DOWN_RIGHT)
                        {
                            if (currentFrame > 19 || currentFrame < 16)
                            {
                                currentFrame = 16;
                            }
                        }
                        if (currentDirection == UPEN || currentDirection == UP_LEFT || currentDirection == UP_RIGHT)
                        {
                            if (currentFrame > 23 || currentFrame < 20)
                            {
                                currentFrame = 20;
                            }
                        }
                    }
                }
            }

            frameRec.x = (float) currentFrame * 64; // Update frame rectangle

            if (getBossHits() == 7 && enemyType == BOSSRED) //wie viele hits ein enemy aushält
            {
                enemyDeath = true;
            }
            if (getBossHits() == 20 && enemyType == BOSSBLUE)
            {
                enemyDeath = true;
            }
            if (enemyHits == 25 && enemyType == BOSSYELLOW)
            {
                enemyDeath = true;
            }



    double currentTimer = GetTime();
    if(currentTimer - lastDamageTimer >= 0.3)
    {
        canGiveDamage1 = true;
    }

            if (CheckCollisionRecs(MainCharacter::HitRec, {enemyRec.x-4,enemyRec.y-4,enemyRec.width+8,enemyRec.height+4}) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                if(canGiveDamage1)
                {
                    bossGetsHit();
                }
                canGiveDamage1 = false;
                lastDamageTimer = currentTimer;
            }
            giveDamage();

            updateShield();

    }


void MiniBoss::findPath(Vector2 playerPosition)
{
    int playerX = static_cast<int>(playerPosition.x);
    int playerY = static_cast<int>(playerPosition.y);
    int bossX = static_cast<int>(posEnemy.x);
    int bossY = static_cast<int>(posEnemy.y);
    path = pathfinder.findPath(bossX, bossY, playerX, playerY);
    pathIndex = 0;
}

bool MiniBoss::isPlayerInRange(Vector2 playerPosition, float range)
{
    return Vector2Distance(posEnemy, playerPosition) <= range;
}

void MiniBoss::drawBoss()
{
    DrawTextureRec(enemyTexture, frameRec, posEnemy, WHITE);
   // DrawRectangleLines(enemyRec.x, enemyRec.y, enemyRec.width, enemyRec.height, RED);

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
    if(!hasShield)
    {
        enemyHits++;
        barHits++;
        PlaySound(ConfigNotConst::miniBossHit);
        if(!IsSoundPlaying(ConfigNotConst::miniBossHit))
        {
            StopSound(ConfigNotConst::miniBossHit);
        }
        std::cout << "Enemy hits: " << enemyHits << std::endl;
    }
}
int MiniBoss::getBossHits()
{
    return enemyHits;
}

Vector2 MiniBoss::getPosition()
{
    return posEnemy;
}

void MiniBoss::updateShield()
{
    if(hasShield && PressurePlate::pressurePlates[3].isPressed() && !plate1Pressed)
    {
        shieldHits += 1;
        plate1Pressed = true;
        std::cout << "Shield hits: " << shieldHits << std::endl;
    }
    if(hasShield && PressurePlate::pressurePlates[4].isPressed() && !plate2Pressed)
    {
        shieldHits += 1;
        plate2Pressed = true;
        std::cout << "Shield hits: " << shieldHits << std::endl;
    }
    if(shieldHits >= 2)
    {
        hasShield = false;
    }
}

int MiniBoss::getShieldHits()
{
    return shieldHits;
}

void MiniBoss::drawShieldBar()
{
    /*if (isPlayerInRange({MainCharacter::playerPosX, MainCharacter::playerPosY}, 400))
    {
        if(shieldHits == 1)
        {
            DrawRectangle(150, 20, 100, 10, DARKGRAY);
        }
        if(shieldHits == 0)
        {
            DrawRectangle(260, 20, 100, 10, DARKGRAY);
            DrawRectangle(150, 20, 100, 10, DARKGRAY);
        }

        DrawRectangle(173, 40, 165, 10, DARKGRAY);
        DrawRectangle(173, 40, barHits * 11, 10, RED);
    }*/
    if (isPlayerInRange({MainCharacter::playerPosX, MainCharacter::playerPosY}, 400) && !MainCharacter::isPlayerDead)
    {
        if(shieldHits == 0){
            DrawTexture(TextureManager::getTexture("BossFull"),115, 190, WHITE);
        }
        if(shieldHits == 1){
            DrawTexture(TextureManager::getTexture("Boss1Shield"),115, 190, WHITE);
        }
        if(!hasShield && barHits == 0){
            DrawTexture(TextureManager::getTexture("BossNoShield"),115, 190, WHITE);
        }
        if(barHits == 1){
            DrawTexture(TextureManager::getTexture("Boss-1"),115, 190, WHITE);
        }
        if(barHits == 2){
            DrawTexture(TextureManager::getTexture("Boss-2"),115, 190, WHITE);
        }
        if(barHits == 3){
            DrawTexture(TextureManager::getTexture("Boss-3"),115, 190, WHITE);
        }
        if(barHits == 4){
            DrawTexture(TextureManager::getTexture("Boss-4"),115, 190, WHITE);
        }
        if(barHits == 5){
            DrawTexture(TextureManager::getTexture("Boss-5"),115, 190, WHITE);
        }
        if(barHits == 6){
            DrawTexture(TextureManager::getTexture("Boss-6"),115, 190, WHITE);
        }
        if(barHits >= 7){
            DrawTexture(TextureManager::getTexture("BossEmpty"),115, 190, WHITE);
        }

    }
}

void MiniBoss::giveDamage()
{
    static double lastDamageTime = 0.0;
    double currentTime = GetTime();

    if (currentTime - lastDamageTime >= 0.5)
    {
        canGiveDamage = true;
    }

    if (CheckCollisionRecs(MainCharacter::playerRec, enemyRec))
    {
        if (canGiveDamage) {
            InGameHud::health -= 0.5;
            MainCharacter::damageAnim = true;
            canGiveDamage = false;
            lastDamageTime = currentTime;
        }
    }
}


