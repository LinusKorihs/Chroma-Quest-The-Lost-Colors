#include "Camera.h"
#include "Configuration.h"
#include "DrawMap.h"
#include "Item.h"
#include "PixelGame.h"
#include "TextureManage.h"
#include "MainCharacter.h"
#include "UnloadResources.h"
#include "RoomChanger.h"
#include "MiniBoss.h"
#include "Pathfinder.h"
#include "tileson.h"

GameState currentGameState;

Music PixelGame::music;
bool PixelGame::firstLoopOverworld = true;
bool PixelGame::firstLoopDungeon1 = true;
bool PixelGame::track1Played = false;
Music PixelGame::dungeonMusic2;
std::shared_ptr<Projectile> PixelGame::projectile_p;
std::shared_ptr<Projectile> PixelGame::projectileEnemy_p;
//std::shared_ptr<MiniBoss> PixelGame::miniBoss_p;
EnemyManager PixelGame::enemyManager;
Texture2D PixelGame::slimeEnemyTexture;
Texture2D PixelGame::BossRed;
Vector2 PixelGame::BossRedPosition = {35*32, 11*32};

//std::vector<PressurePlate> pressurePlates;
std::vector<Machine> machines;
//std::vector<Door> openDoors;
RoomChanger roomChanger;

bool PixelGame::isPlayerKnocked = false;
Rectangle MainCharacter::playerRec;
Rectangle MainCharacter::HitRec;
MiniBoss* PixelGame::miniboss;
Pathfinder* PixelGame::pathfinder;
bool PixelGame::hasAnimated[3] = {false, false, false};

tson::Map PixelGame::currentMap;

tson::Map& PixelGame::getMap()
{
    return currentMap;
}

void PixelGame::createEnemies()
{
    enemyManager.addEnemy({40*32, 75*32}, slimeEnemyTexture, SLIMERED, STAND, NONEEN,0,0,0,0);
    enemyManager.addEnemy({1060, 2395}, slimeEnemyTexture, SLIMERED, WALKVERTICL, DOWNEN,0,0,2358,2440);
    enemyManager.addEnemy({19*32, 56*32}, slimeEnemyTexture, SLIMERED, STAND, NONEEN,0,0,0,0);
    enemyManager.addEnemy({34*32, 53*32}, slimeEnemyTexture, SLIMERED, STAND, NONEEN,0,0,0,0);
    enemyManager.addEnemy({35*32, 51*32}, slimeEnemyTexture, SLIMERED, STAND, NONEEN,0,0,0,0);
    enemyManager.addEnemy({56*32, 56*32}, slimeEnemyTexture, SLIMERED, STAND, NONEEN,0,0,0,0);
    enemyManager.addEnemy({29*32, 28*32}, slimeEnemyTexture, SLIMERED, STAND, NONEEN,0,0,0,0);
    enemyManager.addEnemy({36*32, 53*32}, slimeEnemyTexture, SLIMERED, STAND, NONEEN,0,0,0,0);
}

void PixelGame::gameInit()
{
    music = LoadMusicStream("assets/audio/tracks/dungeon1-1new.wav");
    dungeonMusic2 = LoadMusicStream("assets/audio/tracks/dungeon1-2.wav");
    SetMusicVolume(music, 0.5f);
    SetMusicVolume(dungeonMusic2, 0.5f);

    slimeEnemyTexture = TextureManager::getTexture("SlimeRed");
    BossRed = TextureManager::getTexture("BossRed");
    MainCharacter::setEnemyManager(&enemyManager);
    //createEnemies();

    projectile_p = std::make_shared<Projectile>();
    MainCharacter::setProjectile(projectile_p);
    Texture2D doorTexture1 = TextureManager::getTexture("DoorRed2");
    Texture2D doorTexture2 = TextureManager::getTexture("StoneDoorR");
    Texture2D plateTexture = TextureManager::getTexture("PlateNormal");
    Texture2D machineTexture = TextureManager::getTexture("Machine");
    Texture2D chestTexture = TextureManager::getTexture("Chest");
    //pressurePlates.emplace_back(32 * 35, 32 * 63, 32, plateTexture);
    //pressurePlates.emplace_back(32 * 35, 32 * 71, 32, plateTexture);
    machines.emplace_back(32 * 36, 32 * 69, 32 * 47, 32 * 75, machineTexture, 0);
    machines.emplace_back(34*32,49*32,6*32,38*32,machineTexture,0);
    machines.emplace_back(36*32, 49*32, 72*32, 41*32, machineTexture, 0);

    TextureManage::loadAudio();
    MainCharacter::playerHealth = 100;
    InGameHud::init();

    projectile_p->load();
    MainCharacter::initPlayer(TextureManager::getTexture("MainCharacter"));

    if (currentMap.getStatus() != tson::ParseStatus::OK)
    {
        std::cout
                << LanguageManager::getLocalizedGameText("Failed to parse map, error: ",
                                                         "Fehler beim Parsen der Karte, Fehler: ")
                << currentMap.getStatusMessage() << std::endl;
    }


    pathfinder = new Pathfinder();
    miniboss = new MiniBoss(BossRedPosition, BossRed, BOSSRED, *pathfinder);


    playerCamera();

    //Texture2D stoneTexture = TextureManager::getTexture("Stone");
   // Rectangle stoneSourceRect = {0, 0, (float)stoneTexture.width, (float)stoneTexture.height};
    Texture2D doorTexture3 = TextureManager::getTexture("StoneDoorL");
    Door::initDoors(doorTexture1, doorTexture2, doorTexture3, doorTexture2);

   /* if (!IsTextureReady(stoneTexture))
    {
        std::cerr << "Error: Stone texture not loaded" << std::endl;
        return;
    }*/

    //Stone::initializeStones(stoneTexture, stoneSourceRect); // kommt als 1x if in die loop dungeon1
    PressurePlate::initPlates(plateTexture);
    Chest::init(chestTexture);

    Texture2D npcTexture = TextureManager::getTexture("mouse");
    Texture2D npcTexture2 = TextureManager::getTexture("frog");
    Texture2D npcTexture4 = TextureManager::getTexture("gekko");
    Texture2D npcTexture3 = TextureManager::getTexture("owl");
    Texture2D dialogTexture = TextureManager::getTexture("speechBubble");
    NPC::init(npcTexture,npcTexture2,npcTexture3, npcTexture4);
    DialogBox::init(dialogTexture);
}

void PixelGame::rectangle()
{
    float x = MainCharacter::playerPosX + 5;
    float y = MainCharacter::playerPosY + 2.5;
    float width = TextureManager::getTexture("MainCharacter").width - 875;
    float height = TextureManager::getTexture("MainCharacter").height + 170;
    float playerScale = 0.15f;
    float hitScale = 0.18f;

    MainCharacter::playerRec = {x, y, width * playerScale, height * playerScale};

    MainCharacter::HitRec = {x, y, width * hitScale, height * hitScale};
}

void PixelGame::checkPressurePlates()
{
    Vector2 doorPositions[3] = {
            {41*32, 75*32},
            {12*32,38*32},
            {66*32,41*32}
    };

    for (int i = 0; i < 3; i++)
    {
        if (PressurePlate::pressurePlates[i].isPressed() && !hasAnimated[i])
        {
            playerCamera::animationCam(doorPositions[i]);
            PlaySound(ConfigNotConst::doorOpenSound);
            if(!IsSoundPlaying(ConfigNotConst::doorOpenSound))
            {
                StopSound(ConfigNotConst::doorOpenSound);
            }
            hasAnimated[i] = true; // Animation wurde für diese Platte gestartet

            // Aktionen für die spezifische Tür
            //Door::openDoors[i].draw();
            eraseDoor(doorPositions[i].x, doorPositions[i].y);
        }
    }
}

void PixelGame::openDoors()
{
    for (PressurePlate& plate : PressurePlate::pressurePlates) // Draw pressure plates
    {
        plate.update();
        plate.draw();

        if(PressurePlate::pressurePlates[0].isPressed())
        {
            if(playerCamera::getIsHolding() || playerCamera::getIsGoingBack() ){
                Door::openDoors[2].draw(); //wenn zeit ist animation + sound einfügen
                Door::openDoors[3].draw();
            }
            if(!playerCamera::getIsHolding() && !playerCamera::getIsAnimating()) {
                Door::openDoors[2].drawNormal(96);
                Door::openDoors[3].drawNormal(96);
            }
            eraseDoor(45*32,75*32);
        }
        if(PressurePlate::pressurePlates[1].isPressed())
        {
            if(playerCamera::getIsHolding() || playerCamera::getIsGoingBack()) {
                Door::openDoors[8].draw(); //wenn zeit ist animation + sound einfügen
                Door::openDoors[9].draw();
            }
            if(!playerCamera::getIsHolding() && !playerCamera::getIsAnimating()) {
                Door::openDoors[8].drawNormal(96);
                Door::openDoors[9].drawNormal(96);
            }
            eraseDoor(12*32,38*32);
        }
        if(PressurePlate::pressurePlates[2].isPressed())
        {
            if(playerCamera::getIsHolding() || playerCamera::getIsGoingBack()) {
                Door::openDoors[6].draw(); //wenn zeit ist animation + sound einfügen
                Door::openDoors[7].draw();
            }
            if(!playerCamera::getIsHolding() && !playerCamera::getIsAnimating()) {
                Door::openDoors[6].drawNormal(96);
                Door::openDoors[7].drawNormal(96);
            }
            // eraseDoor(66*32,41*32);
            eraseDoor(70*32,41*32);
        }
    }
    for (Machine& machine : machines)
    {
        machine.draw();
        machine.update();
        machine.drawOrb();

        if(machines[0].isFilled())
        {
            Door::openDoors[0].draw();
            eraseDoor(35*32,68*32);
        }

        if(machines[1].isFilled() && machines[2].isFilled())
        {
            Door::openDoors[1].draw();
            eraseDoor(35*32,48*32);
        }
    }
}

void PixelGame::drawObjects()
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
        }

        for (const PressurePlate& plate : PressurePlate::pressurePlates) // Draw pressure plates - warum steht das hier drinnen? also in dem drawStone ding und nicht separat?
        {
            plate.draw();
        }

        Stone::drawStone = 1;
    }
    if(PressurePlate::pressurePlates[5].isPressed()){
        Stone::roomOne = true;
        Stone::resetStones();
        Stone::roomOne = false;
        PressurePlate::pressurePlates[5].setPressed(false);
    }
    if(PressurePlate::pressurePlates[6].isPressed()){
        Stone::roomTwo = true;
        Stone::resetStones();
        Stone::roomTwo = false;
        PressurePlate::pressurePlates[6].setPressed(false);
    }
    if(PressurePlate::pressurePlates[7].isPressed() || PressurePlate::pressurePlates[8].isPressed()){
        Stone::roomThree = true;
        Stone::resetStones();
        Stone::roomThree = false;
        PressurePlate::pressurePlates[7].setPressed(false);
        PressurePlate::pressurePlates[8].setPressed(false);
    }
    if(PressurePlate::pressurePlates[9].isPressed() || PressurePlate::pressurePlates[10].isPressed()){
        Stone::roomFour = true;
        Stone::resetStones();
        Stone::roomFour = false;
        PressurePlate::pressurePlates[9].setPressed(false);
        PressurePlate::pressurePlates[10].setPressed(false);
    }
    for(Chest& chest : Chest::chests)
    {
        chest.draw();
    }
}

void PixelGame::eraseDoor(int targetX, int targetY)
{
    auto it = std::remove_if(currentGameState.doorRectangles.begin(), currentGameState.doorRectangles.end(),
                             [targetX, targetY](const Rectangle& rect) {
                                 return rect.x == targetX && rect.y == targetY;
                             });
    currentGameState.doorRectangles.erase(it, currentGameState.doorRectangles.end());
}

void PixelGame::gameLoop(tson::Map &Map) {
    if (roomChanger.getDungeon1() && !roomChanger.getOverworld()) {
        if(firstLoopDungeon1){
            currentGameState.overworldWallRecs.clear();
            DrawMap::dungeon1 = true;
            DrawMap::overworld = false;
            createEnemies();
            Texture2D stoneTexture = TextureManager::getTexture("Stone");
            Rectangle stoneSourceRect = {0, 0, (float)stoneTexture.width, (float)stoneTexture.height};
            Stone::initializeStones(stoneTexture, stoneSourceRect);
            firstLoopOverworld = true;
            firstLoopDungeon1 = false;
        }

        BeginMode2D(playerCamera::camera); //BeginDrawing();
        checkPressurePlates();
        playerCamera::updateCamera({MainCharacter::playerPosX, MainCharacter::playerPosY}, GetFrameTime());
        ClearBackground(DARKGRAY);

        DrawMap::drawTiles(Map, TextureManager::m_textures["TileSet"]);

        openDoors();
        openBottomDoorRoom1();

        for (Stone stone: Stone::stoneObjects) {
            stone.draw();
            //stone.drawHitboxes();
        }

        drawObjects();
        InGameHud::drawHealthBarTexture();


        if (!roomChanger.isTransitioning() && !playerCamera::getIsAnimating()) {
            MainCharacter::updatePlayer(TextureManager::getTexture("MainCharacter"), GetFrameTime());
        }
        MainCharacter::updateRec();
        MainCharacter character;
        Texture texture = TextureManager::getTexture("MainCharacter");
        MainCharacter::drawMainCharacter(texture, character);
        MainCharacter::isPlayerDead = false;

        enemyManager.updateEnemies(GetFrameTime());
        enemyManager.drawEnemies();
        projectile_p->update(GetFrameTime(), projectile_p->getProjectileDestination());
        projectile_p->draw();

        if (!miniboss->getUnload()) {
            miniboss->updateBoss(GetFrameTime(), MainCharacter::getPosition());
            miniboss->drawBoss();
        }

        NPC::npcs[0].update();
        NPC::npcs[0].draw();

        for (DialogBox &dialogBox: DialogBox::dialogBoxes) {
            dialogBox.update({MainCharacter::playerPosX, MainCharacter::playerPosY});
          //  dialogBox.draw();
        }

        MainCharacter::attack();
        MainCharacter::receiveDamage();

        closedDoorTransition();
        for (Chest &chest: Chest::chests) {
            chest.update();
        }

        for (Door &doors: Door::openDoors) {
            if (doors.isOpen()) {
                if (!roomChanger.isTransitioning() &&
                    CheckCollisionRecs(MainCharacter::playerRec, doors.getRectangle())) {
                    roomChanger.setTargetPos();
                    Vector2 newPos = roomChanger.getTargetPos();
                    roomChanger.startTransition(newPos); // neue Position und Raum anpassen
                    roomChanger.update();
                }
            }
        }

        EndMode2D();
        drawHud();
        if (!miniboss->getUnload()) {
            miniboss->drawShieldBar();
        }
        //EndDrawing();
    }
    else if(roomChanger.getOverworld() && !roomChanger.getDungeon1()){
        if(firstLoopOverworld) {
            currentGameState.wallRectangles.clear();
            currentGameState.doorRectangles.clear();
            currentGameState.openDoorRectangles.clear(); //das muss dann wieder bei dungeon1 gefüllt werden
            DrawMap::overworld = true;
            DrawMap::dungeon1 = false;
            enemyManager.deleteEnemies(); // muss wieder gefüllt werden

            Stone::deleteStones(); // muss gefüllt werden
            MainCharacter::setPosition({1 * 32, 39 * 32});
            firstLoopDungeon1 = true;
            firstLoopOverworld = false;
           // std::cout << "First Position set" << std::endl;
        }

        ClearBackground(DARKGRAY);
        MainCharacter::playerRec = {MainCharacter::playerPosX, MainCharacter::playerPosY,
                                    TextureManager::getTexture("MainCharacter").width * 0.15f,
                                    TextureManager::getTexture("MainCharacter").height * 0.15f};
        MainCharacter::HitRec = {MainCharacter::playerPosX, MainCharacter::playerPosY,
                                 TextureManager::getTexture("MainCharacter").width * 0.18f,
                                 TextureManager::getTexture("MainCharacter").height * 0.18f};

        BeginMode2D(playerCamera::camera);
        playerCamera::updateCamera({MainCharacter::playerPosX, MainCharacter::playerPosY}, GetFrameTime());
        DrawMap::drawTiles(Map, TextureManager::m_textures["Overworld"]);

        MainCharacter::updatePlayer(TextureManager::getTexture("MainCharacter"), GetFrameTime());
        for(auto &npc : NPC::npcs)
        {
            npc.update();
        }
        NPC::npcs[1].draw();
        NPC::npcs[2].draw();
        NPC::npcs[3].draw();
        NPC::npcs[4].draw();
        NPC::npcs[5].draw();
        NPC::npcs[6].draw();
        NPC::npcs[7].draw();
        NPC::npcs[8].draw();


        MainCharacter::updateRec();
        MainCharacter character1;
        Texture texture = TextureManager::getTexture("MainCharacter");
        MainCharacter::drawMainCharacter(texture, character1);

        Rectangle dungeonRec = {0, 39*32, 32, 32};
        DrawRectangle(dungeonRec.x, dungeonRec.y, dungeonRec.width, dungeonRec.height, RED);
        if (
            CheckCollisionRecs(MainCharacter::playerRec, dungeonRec)) {
            std::cout << "Collision with dungeon" << std::endl;
            roomChanger.setTargetPosOverworld();
            Vector2 newPos = roomChanger.getTargetPos();
            roomChanger.startTransition(newPos); // neue Position und Raum anpassen
            roomChanger.update();
        }

        EndMode2D();
        drawHud();
    }
    if (Map.getLayers().empty() || Map.getTilesets().empty()) {
        std::cerr << "Invalid map data" << std::endl;
        return;
    }

    if (IsKeyPressed(KEY_ESCAPE)) {
        ConfigNotConst::isGamePaused = true;
    }

    if (ConfigNotConst::isGamePaused) {
        currentGameState.changeGameState(MenuState::PauseMenu);
        currentGameState.currentGameMenu = MenuState::PauseMenu;
        Menu::drawPauseMenu(currentGameState);
    }

    if (IsKeyPressed(KEY_ESCAPE)) {
        currentGameState.changeGameState(MenuState::PauseMenu);
        return;
    }

    bool isMoving = false; //movement sollte noch separiert werden

    for (auto &dialogBox: DialogBox::dialogBoxes) {
        if (!dialogBox.isActive()) {

           // if (!roomChanger.isTransitioning() && !playerCamera::getIsAnimating()) {
                if (IsKeyDown(currentGameState.playerKeyBindings[Direction::UP])) {
                    MainCharacter::moveMainCharacter(KEY_UP, GetFrameTime());
                    isMoving = true;
                    std::cout << "UP" << std::endl;
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
        //}
    }
    updateAudio();
    playerCamera::camera.target = (Vector2) {MainCharacter::playerPosX, MainCharacter::playerPosY};

    if (WindowShouldClose()) {
        CloseWindow();
        unloadAll();
        exit(0);
    }
}

void PixelGame::unloadAll()
{
    UnloadResources::unloadAudio();
    projectile_p->unload(); //Projectile Textur
    //projectileEnemy_p->unload(); //Projectile Enemy Textur
    delete miniboss;
    delete pathfinder;
}

void PixelGame::drawHud()
{
    for(auto &dialogBox: DialogBox::dialogBoxes)
    {
        dialogBox.draw();
    }
    InGameHud::drawHealthBarTexture();
    InGameHud::drawRGBBarTexture();

}

void PixelGame::openBottomDoorRoom1()
{
    if (CheckCollisionRecs(MainCharacter::playerRec, Door::openDoors[1].getRectangle()) &&
        !roomChanger.isTransitioning())
    {
        roomChanger.startTransition({0, 0}); // Set new position and room
    }

    roomChanger.update();
    Door::openDoors[20].setOpened();
}

void PixelGame::closedDoorTransition()
{
    if(machines[0].isFilled())
    {

        if (CheckCollisionRecs(MainCharacter::playerRec, Door::openDoors[0].getRectangle()) &&
            !roomChanger.isTransitioning())
        {
            roomChanger.startTransition({1120, 2028}); // neue Position und Raum anpassen
        }

        roomChanger.update();
        Door::openDoors[0].setOpened();
    }
    if(machines[1].isFilled() && machines[2].isFilled())
    {
        if (CheckCollisionRecs(MainCharacter::playerRec, Door::openDoors[1].getRectangle()) &&
            !roomChanger.isTransitioning())
        {
            roomChanger.startTransition({35*32, 21*32-18}); // neue Position und Raum anpassen
        }

        roomChanger.update();
        Door::openDoors[1].setOpened();
    }
    if(PressurePlate::pressurePlates[0].isPressed())
    {
        if (CheckCollisionRecs(MainCharacter::playerRec, Door::openDoors[2].getRectangle()) &&
            !roomChanger.isTransitioning())
        {
            roomChanger.startTransition({45*32+18, 75*32}); // neue Position und Raum anpassen
        }

        roomChanger.update();
        Door::openDoors[2].setOpened();
        Door::openDoors[3].setOpened();
    }
    if(PressurePlate::pressurePlates[1].isPressed())
    {
        if (CheckCollisionRecs(MainCharacter::playerRec, Door::openDoors[8].getRectangle()) &&
            !roomChanger.isTransitioning())
        {
            roomChanger.startTransition({8*32-20, 38*32}); // neue Position und Raum anpassen

        }

        roomChanger.update();
        Door::openDoors[8].setOpened();
        Door::openDoors[9].setOpened();
    }
    if(PressurePlate::pressurePlates[2].isPressed())
    {
        if (CheckCollisionRecs(MainCharacter::playerRec, Door::openDoors[6].getRectangle()) &&
            !roomChanger.isTransitioning())
        {
            roomChanger.startTransition({70*32+18, 41*32}); // neue Position und Raum anpassen

        }

        roomChanger.update();
        Door::openDoors[6].setOpened();
        //Door::openDoors[7].setOpened();
    }
}

void PixelGame::loadMap(const std::string &mapPath) {
    // Entlade die aktuelle Karte, bevor eine neue geladen wird
    if (!currentMap.getLayers().empty() || !currentMap.getTilesets().empty()) {
        std::cout << "Entlade aktuelle Karte und Tilesets" << std::endl;
        unloadMap();
    }

    // Parsen der neuen Karte
    tson::Tileson tileson;
    auto mapPtr = tileson.parse(mapPath);

    if (mapPtr && mapPtr->getStatus() == tson::ParseStatus::OK) {
        currentMap = std::move(*mapPtr);
        std::cout << "Karte erfolgreich geladen: " << mapPath << std::endl;

        // Tilesets laden
        for (auto& tileset : currentMap.getTilesets()) {
            std::cout << "Tileset geladen: " << tileset.getName() << std::endl;
        }
    } else {
        std::cerr << "Fehler beim Parsen der Karte: " << mapPtr->getStatusMessage() << std::endl;
    }
}

void PixelGame::unloadMap()
{
    if (!currentMap.getLayers().empty() || !currentMap.getTilesets().empty()) {
        // Alle Layers entladen
        currentMap.getLayers().clear();

        // Alle Tilesets entladen
        currentMap.getTilesets().clear();

        // Entlade den Rest der Karte (falls benötigt)
        currentMap = tson::Map();  // Setzt das currentMap-Objekt zurück

        std::cout << "Karte und Tilesets entladen" << std::endl;
    }
}

void PixelGame::updateAudio()
{
    if (!track1Played)
    {
        // Nur einmal den Track starten, nicht in jedem Frame
        if (GetMusicTimePlayed(music) == 0)
        {
            PlayMusicStream(music);
        }
        UpdateMusicStream(music);

        if (GetMusicTimePlayed(music) >= 104.34)
        {
            StopMusicStream(music);
            track1Played = true;  // Mark that Track 1 has finished
            std::cout << "Music stopped, switching to track 2" << std::endl;
            PlayMusicStream(dungeonMusic2);
        }
    }
    else
    {
        UpdateMusicStream(dungeonMusic2);
    }
}

