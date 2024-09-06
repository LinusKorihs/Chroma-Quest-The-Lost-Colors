#include "DrawMap.h"
#include "GameState.h"

int DrawMap::sizeDoorVec = 0;
int DrawMap::sizeWallVec = 0;
int DrawMap::sizeStoneWallVec = 0;
int DrawMap::sizeOpenDoorVec = 0;
int DrawMap::sizeOverworldWallVec = 0;
bool DrawMap::dungeon1 = false;
bool DrawMap::overworld = true;

bool DrawMap::isOpenDoor(float x, float y)
{
    return
    (x == 1120 && y == 2624) || (x == 1120 && y == 2048) || (x == 1312 && y == 1792) || (x == 928 && y == 1792) || (x == 800 && y == 1792) ||
    (x == 448 && y == 1632) || (x == 448 && y == 1504) || (x == 1088 && y == 896) || (x == 1216 && y == 896) || (x == 1536 && y == 1152) ||
    (x == 1440 && y == 1792) || (x == 1952 && y == 1632) || (x == 1952 && y == 1504) || (x== 1664 && y == 1152) || (x== 1120 && y == 672) || (x == 256 && y == 1216);
}

bool DrawMap::isDoor(float x, float y)
{
    return
    (x == 1120 && y == 2176)  || (x == 1312 && y == 2400) || (x == 1440 && y == 2400) ||
    (x == 384 && y == 1216) || (x == 2112 && y == 1312) || (x == 2240 && y == 1312) || (x == 1120 && y == 1536);
}

bool rectangleExists(const std::vector<Rectangle>& rectangles, const Rectangle& rect)
{
    return std::find_if(rectangles.begin(), rectangles.end(), [&rect](const Rectangle& r)
    {
        return r.x == rect.x && r.y == rect.y && r.width == rect.width && r.height == rect.height;
    }) != rectangles.end();
}

void DrawMap::drawTiles(tson::Map &gameMap, Texture2D &tileTexture)
{
    if(dungeon1)
    {
        auto layer1 = gameMap.getLayer("Barrier Boss")->getData();
        drawLayer(layer1, gameMap, tileTexture);

        auto layer2 = gameMap.getLayer("Floor & Walls")->getData();
        drawLayer(layer2, gameMap, tileTexture);

        auto layer3 = gameMap.getLayer("Wall with energy")->getData();
        drawLayer(layer3, gameMap, tileTexture);

        auto layer4 = gameMap.getLayer("Blocks Grey")->getData();
        drawLayer(layer4, gameMap, tileTexture);

        auto layer5 = gameMap.getLayer("Objects")->getData();
        drawLayer(layer5, gameMap, tileTexture);

        auto layer6 = gameMap.getLayer("Torches")->getData();
        drawLayer(layer6, gameMap, tileTexture);

    }
    else if(overworld)
    {
        /*auto layer1 = gameMap.getLayer("NPCs")->getData();
        drawLayer(layer1, gameMap, tileTexture);*/

        auto layer2 = gameMap.getLayer("Kachelebene 1")->getData();
        drawLayer(layer2, gameMap, tileTexture);

        auto layer3 = gameMap.getLayer("objekte")->getData();
        drawLayer(layer3, gameMap, tileTexture);


    }
}

void DrawMap::drawLayer(const std::vector<unsigned int> &layer, tson::Map &Map, Texture2D &tileTexture)
{
    const int currentFrame = int(GetTime() * 6) % 4;
    int multiplier = 1;
    float tileWidth;
    int tileSetColumns;

    if(dungeon1)
    {
       tileWidth = 32; // Old 16x16
       tileSetColumns = 31; // Old 16; rn 8, new 31
    }
    if(overworld)
    {
        tileWidth = 32; // Old 16x16
        tileSetColumns = 31; // Old 16; rn 8, new 31
    }

    for (int y = 0; y < Map.getSize().y; y++)
    {
        for (int x = 0; x < Map.getSize().x; x++)
        {
            int data = layer[y * Map.getSize().x + x];

            tson::Tileset* tileset = Map.getTilesetByGid(data); // Get the tile from the tileset
            if (tileset != nullptr) //TODO this has to be moved to happen ONCE on map load
            {
                tson::Tile* tile = tileset->getTile(data);

                if (tile != nullptr && tile->get<bool>("Wall")) // Check if the tile is a wall
                {
                    Rectangle wallRec = {(float) x * tileWidth * multiplier, (float) y * tileWidth * multiplier, tileWidth * multiplier, tileWidth * multiplier}; // Create a Rectangle for the tile and add it to the list of wall rectangles
                    if(overworld)
                    {
                       /* if(!rectangleExists(currentGameState.overworldWallRecs, wallRec))
                        {*/
                            //currentGameState.overworldWallRecs.push_back(wallRec);
                            if(sizeOverworldWallVec <= 1189){
                                currentGameState.overworldWallRecs.push_back(wallRec);
                                sizeOverworldWallVec++;
                                //std::cout << "sizeOverworldWallVec: " << sizeOverworldWallVec << std::endl;
                        }
                    }
                    else if(dungeon1)
                    {
                        sizeOverworldWallVec = 0;
                        if (isOpenDoor(wallRec.x, wallRec.y) &&
                            !rectangleExists(currentGameState.openDoorRectangles, wallRec) && sizeOpenDoorVec <= 22 ||
                            isDoor(wallRec.x, wallRec.y) &&
                            !rectangleExists(currentGameState.openDoorRectangles, wallRec) /*&& sizeOpenDoorVec <=
                                                                                              23*/) //für projectile kollisionserkennung - damit es nicht durch offene türen fliegt
                        {
                            currentGameState.openDoorRectangles.push_back(wallRec);
                            sizeOpenDoorVec++;
                        }
                        else if (!isOpenDoor(wallRec.x, wallRec.y) &&
                                   !rectangleExists(currentGameState.doorRectangles, wallRec) &&
                                   isDoor(wallRec.x, wallRec.y) && sizeDoorVec <= 6)
                        {
                            currentGameState.doorRectangles.push_back(wallRec);
                            sizeDoorVec++;

                        }
                        else
                        {
                            if (!isOpenDoor(wallRec.x, wallRec.y) &&
                                !rectangleExists(currentGameState.wallRectangles, wallRec) &&
                                !isDoor(wallRec.x, wallRec.y))
                            {
                                currentGameState.wallRectangles.push_back(wallRec);
                                sizeWallVec++;
                            }
                        }
                    }
                }

                if (tile != nullptr && tile->get<bool>("StoneWall")) // Check if the tile is a Stonewall
                {
                    Rectangle stoneWallRec = {(float) x * tileWidth * multiplier, (float) y * tileWidth * multiplier, tileWidth * multiplier, tileWidth * multiplier}; // Create a Rectangle for the tile and add it to the list of wall rectangles
                     if(dungeon1)
                    {
                        sizeOverworldWallVec = 0;
                        if (!isOpenDoor(stoneWallRec.x, stoneWallRec.y) &&
                        !rectangleExists(currentGameState.stoneWallRectangles, stoneWallRec) &&
                        !isDoor(stoneWallRec.x, stoneWallRec.y))
                        {
                            currentGameState.stoneWallRectangles.push_back(stoneWallRec);
                            sizeStoneWallVec++;
                        }
                    }
                }
            }

            data--;
            if (data < 0) continue;
            Rectangle source = {(float) (data % tileSetColumns) * tileWidth, (float) (data / tileSetColumns) * tileWidth, tileWidth, tileWidth};
            Rectangle destination = {(float) x * tileWidth * multiplier, (float) y * tileWidth * multiplier, tileWidth * multiplier, tileWidth * multiplier};

            if (dungeon1 && data >= 448) //animation layer
            {
                source.x += (float) (currentFrame * tileWidth);
            }
            if(overworld && data >= 496) //animation layer
            {
                source.x += (float) (currentFrame * tileWidth);
            }
            DrawTexturePro(tileTexture, source, destination, {0, 0}, 0, WHITE);
        }
    }
}