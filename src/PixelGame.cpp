#include "Camera.h"
#include "Configuration.h"
#include "DrawMap.h"
#include "Item.h"
#include "PixelGame.h"
#include "TextureManage.h"
#include "MainCharacter.h"
#include "UnloadResources.h"
#include "RoomChanger.h"

GameState currentGameState;

std::shared_ptr<Projectile> PixelGame::projectile_p;
std::shared_ptr<Projectile> PixelGame::projectileEnemy_p;
std::shared_ptr<MiniBoss> PixelGame::miniBoss_p;
EnemyManager PixelGame::enemyManager;
Texture2D PixelGame::slimeEnemyTexture;
Texture2D PixelGame::BossRed;
Vector2 PixelGame::BossRedPosition = {1120, 252};

std::vector<PressurePlate> pressurePlates;
//std::vector<Door> openDoors;
RoomChanger roomChanger;

bool PixelGame::isPlayerKnocked = false;
bool PixelGame::doorsErased1 = false;
bool PixelGame::doorsErased2 = false;
Rectangle MainCharacter::playerRec;
Rectangle MainCharacter::HitRec;

void PixelGame::gameInit()
{
    slimeEnemyTexture = TextureManager::getTexture("SlimeRed");
    BossRed = TextureManager::getTexture("BossRed");
    MainCharacter::setEnemyManager(&enemyManager);
    enemyManager.addEnemy({40*32, 75*32}, slimeEnemyTexture, SLIMERED, STAND, NONEEN,0,0,0,0);
    //enemyManager.addEnemy({1218, 1622}, slimeEnemyTexture, SLIMERED, STAND, NONEEN,0,0,0,0);
    //enemyManager.addEnemy({1028, 1658}, slimeEnemyTexture, SLIMERED, WALKVERTICL, UPEN,0,0,1610,1665);
   // enemyManager.addEnemy({32*35+80, 32*65-80}, slimeEnemyTexture, SLIMERED, WALKVERTICL, UPEN);

    projectile_p = std::make_shared<Projectile>();
    MainCharacter::setProjectile(projectile_p);

    Texture2D doorTexture1 = TextureManager::getTexture("DoorRed2");
    Texture2D doorTexture2 = TextureManager::getTexture("StoneDoorR");
    Texture2D plateTexture = TextureManager::getTexture("PlateNormal");
    pressurePlates.emplace_back(32 * 42, 32 * 62, 32, plateTexture);
   // pressurePlates.emplace_back(32 * 35, 32 * 63, 32, plateTexture);
    pressurePlates.emplace_back(32 * 35, 32 * 71, 32, plateTexture);
    pressurePlates.emplace_back(800, 2400, 32, plateTexture);
    Door::initDoors(doorTexture1, doorTexture2, doorTexture1, doorTexture2);

    TextureManage::loadAudio();
    MainCharacter::playerHealth = 100;

    projectile_p->load();
    MainCharacter::initPlayer(TextureManager::getTexture("MainCharacter"));

    tson::Tileson tileson; // tileson parse
   // auto MapPtr = tileson.parse("assets/graphics/TileSet & TileMap/tilemap.tmj");
    auto MapPtr = tileson.parse("assets/graphics/newTileset&Tilemap/newTilemap.tmj");
    tson::Map &Map = *MapPtr;

    if (Map.getStatus() != tson::ParseStatus::OK)
    {
        std::cout
                << LanguageManager::getLocalizedGameText("Failed to parse map, error: ",
                                                         "Fehler beim Parsen der Karte, Fehler: ")
                << Map.getStatusMessage() << std::endl;
    }


    playerCamera();

    Texture2D stoneTexture = TextureManager::getTexture("Stone");
    Rectangle stoneSourceRect = {0, 0, (float)stoneTexture.width, (float)stoneTexture.height};

    if (!IsTextureReady(stoneTexture))
    {
        std::cerr << "Error: Stone texture not loaded" << std::endl;
        return;
    }

    Stone::initializeStones(stoneTexture, stoneSourceRect);
}

void PixelGame::drawObjects() //unload sieht noch bisschen weird aus
{
    MainCharacter::playerRec = {MainCharacter::playerPosX, MainCharacter::playerPosY,
                                               TextureManager::getTexture("MainCharacter").width * 0.15f,
                                               TextureManager::getTexture("MainCharacter").height * 0.15f};
    MainCharacter::HitRec = {MainCharacter::playerPosX, MainCharacter::playerPosY,
                                                  TextureManager::getTexture("MainCharacter").width * 0.18f,
                                                  TextureManager::getTexture("MainCharacter").height * 0.18f};

    if (Stone::drawStone == 0)
    {
        for (Stone &stone : Stone::stoneObjects)
        {
            stone.draw();
            stone.drawHitboxes();
        }

        for (const PressurePlate& plate : pressurePlates) // Draw pressure plates
        {
            plate.draw();
            plate.drawHitboxes();
        }

        Stone::drawStone = 1;
    }
}

void PixelGame::gameLoop(tson::Map &Map)
{
    static bool isBossInitialized = false;
    if (!isBossInitialized)
    {
        miniBoss_p = std::make_shared<MiniBoss>(BossRedPosition, BossRed, BOSSRED);
        isBossInitialized = true;
    }
    //enemy_p = std::make_shared<Enemy>(Vector2{250, 280}, slimeEnemyTexture, 2, 5.0f, SLIMERED);

    if (IsKeyPressed(KEY_ESCAPE))
    {
        ConfigNotConst::isGamePaused = true;
    }

    if (ConfigNotConst::isGamePaused)
    {
        currentGameState.changeGameState(MenuState::PauseMenu);
        currentGameState.currentGameMenu = MenuState::PauseMenu;
        Menu::drawPauseMenu(currentGameState);
    }

    BeginMode2D(playerCamera::camera); //BeginDrawing();
    ClearBackground(DARKGRAY);

    DrawMap::drawTiles(Map, TextureManager::m_textures["TileSet"]);

    for (const Stone &stone: Stone::stoneObjects)
    {
        stone.draw();
        stone.drawHitboxes();
    }
    bool shouldEraseDoors = false;
    bool shouldEraseDoors2 = false;

    for (PressurePlate& plate : pressurePlates) // Draw pressure plates
    {
        plate.update();
        plate.draw();
        plate.drawHitboxes();

        if(pressurePlates[0].isPressed())
        {
            Door::openDoors[0].draw();
            shouldEraseDoors = true;
        }
        if(pressurePlates[1].isPressed())
        {
            Door::openDoors[2].drawNormal(96); //wenn zeit ist animation + sound einfügen
            shouldEraseDoors2 = true;
        }
    }

    if (shouldEraseDoors && !currentGameState.doorRectangles.empty())
    {
        if(!doorsErased1)
        {
            currentGameState.doorRectangles.pop_back();
            if (!doorsErased1 && currentGameState.doorRectangles.size() > 4)
            {
                auto it = currentGameState.doorRectangles.begin() + 5;
                std::swap(*it, currentGameState.doorRectangles.back());
                currentGameState.doorRectangles.pop_back();
                doorsErased1 = true;
            }
        }
    }

    if (shouldEraseDoors2 && !currentGameState.doorRectangles.empty())
    {
        if (!doorsErased1)
        {
            auto it = currentGameState.doorRectangles.begin() + 6;
            std::swap(*it, currentGameState.doorRectangles.back());
            currentGameState.doorRectangles.pop_back();
            doorsErased2 = true;
        }
    }

    drawObjects();

    if(!roomChanger.isTransitioning())
    {
        MainCharacter::updatePlayer(TextureManager::getTexture("MainCharacter"), GetFrameTime());
    }
    MainCharacter::updateRec();
    MainCharacter character;
    Texture texture = TextureManager::getTexture("MainCharacter");
    MainCharacter::drawMainCharacter(texture, character);
    MainCharacter::isPlayerDead = false;

    enemyManager.updateEnemies(GetFrameTime());
    enemyManager.drawEnemies();
    miniBoss_p->updateBoss(GetFrameTime());
    miniBoss_p->drawBoss();

    //projectileEnemy_p->update(GetFrameTime(), 2);
    //projectileEnemy_p->draw();
    projectile_p->update(GetFrameTime(), projectile_p->getProjectileDestination());
    projectile_p->draw();

    MainCharacter::attack();

    if(pressurePlates[0].isPressed())
    {
        if (CheckCollisionRecs(MainCharacter::playerRec, Door::openDoors[0].getRectangle()) &&
            !roomChanger.isTransitioning())
        {
            roomChanger.startTransition(1, {1120, 2028}); // neue Position und Raum anpassen
        }

        roomChanger.update();
        Door::openDoors[0].setOpened();
    }

    for (Door& doors : Door::openDoors)
    {

        if(doors.isOpen())
        {
           if (!roomChanger.isTransitioning() &&
                CheckCollisionRecs(MainCharacter::playerRec, doors.getRectangle())) {
                roomChanger.setTargetPos();
                Vector2 newPos = roomChanger.getTargetPos();
                roomChanger.startTransition(0, newPos); // neue Position und Raum anpassen
                roomChanger.update();
            }
        }
    }


    if (IsKeyPressed(KEY_ESCAPE))
    {
        currentGameState.changeGameState(MenuState::PauseMenu);
        return;
    }

    bool isMoving = false; //movement sollte noch separiert werden

    if(!roomChanger.isTransitioning()) {
        if (IsKeyDown(currentGameState.playerKeyBindings[Direction::UP])) {
            MainCharacter::moveMainCharacter(KEY_UP, GetFrameTime());
            isMoving = true;
        }
        if (IsKeyDown(currentGameState.playerKeyBindings[Direction::DOWN])) {
            MainCharacter::moveMainCharacter(KEY_DOWN, GetFrameTime());
            isMoving = true;
        }
        if (IsKeyDown(currentGameState.playerKeyBindings[Direction::LEFT])) {
            MainCharacter::moveMainCharacter(KEY_LEFT, GetFrameTime());
            isMoving = true;
        }
        if (IsKeyDown(currentGameState.playerKeyBindings[Direction::RIGHT])) {
            MainCharacter::moveMainCharacter(KEY_RIGHT, GetFrameTime());
            isMoving = true;
        }
        if (isMoving && !IsSoundPlaying(ConfigNotConst::playerWalkingSound)) {
            PlaySound(ConfigNotConst::playerWalkingSound);
        } else if (!isMoving && IsSoundPlaying(ConfigNotConst::playerWalkingSound)) {
            StopSound(ConfigNotConst::playerWalkingSound);
        }
    }
        UpdateMusicStream(ConfigNotConst::gameBackgroundMusic);
        playerCamera::camera.target = (Vector2) {MainCharacter::playerPosX, MainCharacter::playerPosY};


    if (WindowShouldClose())
    {
        CloseWindow();
        unloadAll();
        exit(0);
    }
    EndMode2D();
    drawHud();
    //EndDrawing();
}

void PixelGame::unloadAll()
{
    UnloadResources::unloadAudio();
    projectile_p->unload(); //Projectile Textur
    //projectileEnemy_p->unload(); //Projectile Enemy Textur
}

void PixelGame::drawHud()
{
    InGameHud::drawHealthBarTexture();
    InGameHud::drawRGBBarTexture();
    DrawText(TextFormat("%s: %i", LanguageManager::getLocalizedGameText("Score", "Punkte"), MainCharacter::playerScore),
             1700, 140, 20, BLACK);
}


