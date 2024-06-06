#include "PixelGame.h"

ApplicationState gameState;

std::shared_ptr<Pixelgame::Projectile> PixelGame::proj_p;
std::shared_ptr<Pixelgame::Projectile> PixelGame::proj_p_enemy;
std::shared_ptr<Pixelgame::Enemy> PixelGame::en_p;

std::vector<Stone> PixelGame::stones;

Texture2D PixelGame::lavaTexture;
Texture2D PixelGame::meatTexture;
Texture2D PixelGame::fruitTexture;
Texture2D PixelGame::slimeTexture;
Texture2D PixelGame::tilesetTexture;

Camera2D PixelGame::camera;

float PixelGame::mcX = 80;
float PixelGame::mcY = 368;
int PixelGame::projDest;

bool PixelGame::lastDirectionLeft = false;
bool PixelGame::lastDirectionUp = false;
bool PixelGame::lastDirectionRight = false;
bool PixelGame::lastDirectionDown = false;
bool PixelGame::isKnocked = false;

Rectangle PixelGame::characterRec;
Rectangle PixelGame::lavaRec;
Rectangle PixelGame::meatRec;
Rectangle PixelGame::fruitRec;
Rectangle PixelGame::characterHitRec;


void PixelGame::DrawTiles(tson::Map &Map, Texture2D &myTexture)
{
    auto layer1 = Map.getLayer("Kachelebene 2")->getData();
    DrawLayer(layer1, Map, myTexture);

    auto layer2 = Map.getLayer("animation")->getData();
    DrawLayer(layer2, Map, myTexture);
}

void PixelGame::DrawLayer(const std::vector<unsigned int> &layer, tson::Map &Map, Texture2D &myTexture)
{
    const int currentFrame = int(GetTime() * 6) % 4;

    float tileWidth = 16;
    int tileSetColumns = 16;

    for (int y = 0; y < Map.getSize().y; y++)
    {
        for (int x = 0; x < Map.getSize().x; x++)
        {
            int data = layer[y * Map.getSize().x + x];

            // Get the tile from the tileset
            tson::Tileset* tileset = Map.getTilesetByGid(data);
            if (tileset != nullptr)
            {
                tson::Tile* tile = tileset->getTile(data);

                // Check if the tile is a wall
                if (tile != nullptr && tile->get<bool>("Wall"))
                {
                    // Create a Rectangle for the tile and add it to the list of wall rectangles
                    Rectangle wallRec = {(float) x * tileWidth * 2, (float) y * tileWidth * 2, tileWidth * 2, tileWidth * 2};
                    gameState.wallRecs.push_back(wallRec);
                }
            }

            data--;
            if (data < 0) continue;

            Rectangle source = {(float) (data % tileSetColumns) * tileWidth, (float) (data / tileSetColumns) * tileWidth, tileWidth, tileWidth};
            Rectangle dest = {(float) x * tileWidth * 2, (float) y * tileWidth * 2, tileWidth * 2, tileWidth * 2};

            //animation layer
            if (data >= 0xE0)
            {
                source.x += (float) (currentFrame * tileWidth);
            }

            DrawTexturePro(myTexture, source, dest, {0, 0}, 0, WHITE);

        }
    }
}

void PixelGame::DrawSprite(Texture2D &myTexture)
{
    Rectangle source = {0.0f, 0.0f, (float) myTexture.width, (float) myTexture.height};
    Rectangle dest = {mcX, mcY, myTexture.width * 0.15f, myTexture.height * 0.15f};

    DrawTexturePro(myTexture, source, dest, {0, 0}, 0.0f, WHITE);
}

void PixelGame::MoveCharacter(int direction, float deltaTime) {
    float newPositionX = mcX;
    float newPositionY = mcY;

        switch (direction) {
            case KEY_RIGHT:
            case KEY_D:
                newPositionX += gameState.moveSpeed;
                lastDirectionLeft = false;
                lastDirectionUp = false;
                lastDirectionDown = false;
                lastDirectionRight = true;
                break;
            case KEY_LEFT:
            case KEY_A:
                newPositionX -= gameState.moveSpeed;
                lastDirectionLeft = true;
                lastDirectionUp = false;
                lastDirectionDown = false;
                lastDirectionRight = false;
                break;
            case KEY_UP:
            case KEY_W:
                newPositionY -= gameState.moveSpeed;
                lastDirectionUp = true;
                lastDirectionDown = false;
                lastDirectionRight = false;
                lastDirectionLeft = false;
                break;
            case KEY_DOWN:
            case KEY_S:
                newPositionY += gameState.moveSpeed;
                lastDirectionUp = false;
                lastDirectionDown = true;
                lastDirectionRight = false;
                lastDirectionLeft = false;
                break;
            default:
                break;
        }


        Rectangle newRec = {newPositionX, newPositionY, gameState.myMC.width * 0.15f, gameState.myMC.height * 0.15f};

        for (const Rectangle &wallRec: gameState.wallRecs) {
            if (CheckCollisionRecs(newRec, wallRec)) {
                return;
            }
        }
        bool stoneCollision = false;
        for (Stone &stone: stones) {
            if (CheckCollisionRecs(newRec, stone.getRectangle())) {
                stone.move(direction, gameState.wallRecs);
                stoneCollision = true;
            }
        }
        if (!stoneCollision) {
            mcX = newPositionX;
            mcY = newPositionY;
        }
    if(!proj_p->GetActive()) //Richtung der Projektile basierend auf Player movement (wird in Projectile.h übergeben)
    {
        if (lastDirectionLeft)
        {
            projDest = 2;
        }
        if (lastDirectionRight)
        {
            projDest = 1;
        }
        if (lastDirectionUp)
        {
            projDest = 3;
        }
        if (lastDirectionDown)
        {
            projDest = 4;
        }
    }
}


void PixelGame::GameInit()
{
    proj_p = std::make_shared<Pixelgame::Projectile>();
    proj_p_enemy = std::make_shared<Pixelgame::Projectile>();

    Audio::LoadResourcesAndInitAudio();
    LoadTextureX(lavaTexture, "assets/graphics/backgrounds/Lava.png");
    LoadTextureX(meatTexture, "assets/graphics/Fleisch.png");
    LoadTextureX(fruitTexture, "assets/graphics/Frucht.png");
    LoadTextureX(slimeTexture, "assets/graphics/slime-Sheet.png");
    LoadTextureX(tilesetTexture, "assets/graphics/testimage.png");
    proj_p->Load(); //Projectile Textur
    proj_p_enemy->Load(); //Projectile Enemy Textur

    gameState.health = 100;

    // tileson parse
    tson::Tileson tileson;
    auto MapPtr = tileson.parse("assets/data/tilemap.tmj");
    tson::Map &Map = *MapPtr;

    if (Map.getStatus() != tson::ParseStatus::OK)
    {
        std::cout
                << gameState.GetLocalizedText("Failed to parse map, error: ", "Fehler beim Parsen der Karte, Fehler: ")
                << Map.getStatusMessage() << std::endl;
    }
    //camera init
    camera = { 0 };
    camera.target = (Vector2){ 80,368 };
    camera.offset = (Vector2){ GetScreenWidth()/2.0f, GetScreenHeight()/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 4.0f;

    Rectangle stoneSourceRect = {144,96,16,16};
    int x = 16 * 6;
    int y = 20 * 16;

    stones.push_back(Stone(x,y,32,tilesetTexture,stoneSourceRect));
}
void PixelGame::EnemyAttack()
{
    if (!proj_p_enemy->GetActive() && !en_p->GetEnemyDeath()){
        Vector2 startPosition = en_p->GetPosition();
        startPosition.y += 10;
        proj_p_enemy->Init(startPosition, {100.0f, 100.0f});
    }
    if (CheckCollisionRecs(proj_p_enemy->GetRec(), characterRec) && proj_p_enemy->GetActive()) {
        gameState.health -= 10;
        proj_p_enemy->SetActive(false);
    }
    if(CheckCollisionRecs(en_p->GetEnemyRec(), characterRec))
    {
        gameState.health -= 10;
    }
}
void PixelGame::Attack()
{
    if (IsKeyPressed(KEY_ENTER) && gameState.mana > 0 && !proj_p->GetActive()) //Projectile wird aktiviert
    {
        Vector2 startPosition;
        gameState.mana -= 1;
        if(lastDirectionRight)
        {
            startPosition = {mcX + 20, mcY + 10};
        }
        if(lastDirectionLeft)
        {
            startPosition = {mcX - 1, mcY + 10};
        }
        if(lastDirectionUp)
        {
            startPosition = {mcX + 10, mcY - 5};
        }
        if(lastDirectionDown)
        {
            startPosition = {mcX + 10, mcY + 20};
        }

        proj_p->Init(startPosition, {300.0f, 300.0f});

    }
    if(CheckCollisionRecs(proj_p->GetRec(), en_p->GetEnemyRec()) && proj_p->GetActive() && !en_p->GetUnload())
    {
        en_p->EnemyGetsHit();
        gameState.score += 10;
        proj_p->SetActive(false);
    }
    if(CheckCollisionRecs(characterHitRec, en_p->GetEnemyRec()) && !en_p->GetUnload())
    {
        if(IsKeyPressed(KEY_SPACE))
        {
            en_p->EnemyGetsHit();
            gameState.score += 100;
        }
    }
}


void PixelGame::DrawObjects() //unload sieht noch bisschen weird aus
{

    characterRec = {mcX, mcY, gameState.myMC.width * 0.15f, gameState.myMC.height * 0.15f};
    characterHitRec = {mcX, mcY, gameState.myMC.width * 0.18f, gameState.myMC.height * 0.18f};
    lavaRec = {300.0f, 275.0f, lavaTexture.width / 25.0f, lavaTexture.height / 25.0f};
    meatRec = {450.0f, 275.0f, meatTexture.width / 1.5f, meatTexture.height / 1.5f};
    fruitRec = {150.0f, 100.0f, fruitTexture.width / 1.5f, fruitTexture.height / 1.5f};

    if(!gameState.meatUnload)
    {
        DrawTexture(meatTexture, {450.0f, 275.0f, meatTexture.width / 1.5f, meatTexture.height / 1.5f});
    }
    if(!gameState.fruitUnload)
    {
        DrawTexture(fruitTexture, {150.0f, 100.0f, fruitTexture.width / 1.5f, fruitTexture.height / 1.5f});
    }

    DrawTexture(lavaTexture, {300.0f, 275.0f, lavaTexture.width / 25.0f, lavaTexture.height / 25.0f});

    if (CheckCollisionRecs(characterRec, fruitRec))
    {
        if(!gameState.fruitUnload)
        {
            gameState.fruitUnload = true;
            gameState.health += 25;
            if (gameState.health >= 100)
            {
                gameState.health = 100;
            }

            UnloadTexture(fruitTexture);
            gameState.score += 50;
        }
    }

    if (CheckCollisionRecs(characterRec, meatRec))
    {
        if(!gameState.meatUnload)
        {
            gameState.meatUnload = true;
            gameState.health += 50;
            gameState.mana += 1;
            if(gameState.mana >= 5)
            {
                gameState.mana = 5;
            }
            if (gameState.health >= 100)
            {
                gameState.health = 100;
            }

            UnloadTexture(meatTexture);
            gameState.score += 100;
        }
    }
}

void PixelGame::GameLoop(tson::Map &Map)
{

    en_p = std::make_shared<Pixelgame::Enemy>(Vector2{250, 280}, slimeTexture, 2, 5.0f, SLIMERED);

    while (!WindowShouldClose() && gameState.gameIsRunning)
    {

        if (IsKeyPressed(KEY_ESCAPE))
        {
            gameState.isPaused = true;
        }

        if (gameState.isPaused)
        {
            gameState.ChangeState(MenuState::PauseMenu);
            gameState.currentMenu = MenuState::PauseMenu;
            Menu::drawPauseMenu(gameState);
        }

        if (gameState.currentMenu == MenuState::MainMenu || !gameState.gameIsRunning)
        {
            break;
        }

        BeginDrawing();
        BeginMode2D(camera);
        ClearBackground(DARKGRAY);

        DrawTiles(Map, gameState.myTexture);

        for (const Stone& stone : stones)
        {
            stone.draw();
        }

        DrawObjects();

        DrawSprite(gameState.myMC);
        gameState.playerDeath = 0;

        en_p->EnemyUpdate( GetFrameTime(), slimeTexture);
        en_p->DrawEnemies(slimeTexture);

        Attack();
        EnemyAttack();
        proj_p_enemy->Update(GetFrameTime(), 2);
        proj_p_enemy->Draw();
        proj_p->Update(GetFrameTime(), GetProjDest());
        proj_p->Draw();


        if (IsKeyPressed(KEY_ESCAPE))
        {
            Audio::UnloadResourcesAndCloseAudio();
            gameState.ChangeState(MenuState::PauseMenu);
            return;
        }

        bool isMoving = false; //movement sollte noch separiert werden

        if (IsKeyDown(gameState.keyBindings[UP]))
        {
            MoveCharacter(KEY_UP, GetFrameTime());
            isMoving = true;
        }
        if (IsKeyDown(gameState.keyBindings[DOWN]))
        {
            MoveCharacter(KEY_DOWN, GetFrameTime());
            isMoving = true;
        }
        if (IsKeyDown(gameState.keyBindings[LEFT]))
        {
            MoveCharacter(KEY_LEFT, GetFrameTime());
            isMoving = true;
        }
        if (IsKeyDown(gameState.keyBindings[RIGHT]))
        {
            MoveCharacter(KEY_RIGHT, GetFrameTime());
            isMoving = true;
        }
        if (isMoving && !IsSoundPlaying(gameState.walkingSound))
        {
            PlaySound(gameState.walkingSound);
        } else if (!isMoving && IsSoundPlaying(gameState.walkingSound))
        {
            StopSound(gameState.walkingSound);
        }
        UpdateMusicStream(gameState.backgroundMusic);
        camera.target = (Vector2){ mcX,mcY };

        if (CheckCollisionRecs(characterRec, lavaRec)) //muss noch separiert werden
        {
            gameState.health -= gameState.damage_per_frame;
            if (gameState.health <= 0) {
                gameState.health = 0;
                UnloadAll();
                gameState.ChangeState(MenuState::MainMenu);
                gameState.health = 100;
                gameState.playerDeath = 1;
                return;
            }
        }

        if (WindowShouldClose())
        {
            CloseWindow();
            UnloadAll();
            exit(0);
        }
        EndMode2D();
        DrawHud();
        EndDrawing();
    }

    CloseWindow();
    UnloadAll();
}

void PixelGame::LoadTextureX(Texture2D &texture, const char* path)
{
    texture = LoadTexture(path);
}

void PixelGame::DrawTexture(Texture2D &texture, Rectangle dest)
{
    Rectangle source = {0.0f, 0.0f, (float)texture.width, (float)texture.height};
    Vector2 origin = {0.0f, 0.0f};
    DrawTexturePro(texture, source, dest, origin, 0.0f, WHITE);
}

void PixelGame::UnloadTextureX(Texture2D &texture)
{
    UnloadTexture(texture);
}

void PixelGame::UnloadAll()
{
    Audio::UnloadResourcesAndCloseAudio();
    UnloadTextureX(lavaTexture);
    UnloadTextureX(meatTexture);
    UnloadTextureX(fruitTexture);
    proj_p->Unload(); //Projectile Textur
    proj_p_enemy->Unload(); //Projectile Enemy Textur
    UnloadTextureX(slimeTexture);
    UnloadTextureX(tilesetTexture);
}

void PixelGame::DrawHud()
{
    InGameHud::DrawHealthBarTexture();
    InGameHud::DrawRGBBarTexture();
    DrawText(TextFormat("%s: %i", gameState.GetLocalizedText("Score", "Punkte"), gameState.score), 1700, 140, 20, BLACK);
}

void PixelGame::PlayerDeath() //muss noch richtig implementiert werden
{
    if (gameState.health <= 0)
    {
        gameState.playerDeath = 1;
        gameState.ChangeState(MenuState::MainMenu);
    }
}

void PixelGame::ReceiveDmg() //muss noch richtig implementiert werden
{
    if (CheckCollisionRecs(characterRec, lavaRec))
    {
        gameState.health -= gameState.damage_per_frame;
        if (gameState.health <= 0) {
           PlayerDeath();
        }
    }
}

int PixelGame::GetProjDest() { //funktion um movement des players in projectile zu übergeben
    return projDest;
}
