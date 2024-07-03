#include "DrawMap.h"
#include "GameState.h"

int DrawMap::sizeDoorVec = 0;
int DrawMap::sizeWallVec = 0;

bool DrawMap::isWall(float x, float y) {
    return (x == 992 && y == 1632) || (x == 704 && y == 1600) || (x == 1024 && y == 992) ||
           (x == 864 && y == 1632) || (x == 704 && y == 1472) || (x == 1024 && y == 1120) ||
           (x == 1344 && y == 1184) || (x == 1472 && y == 1184) || (x == 1632 && y == 1344) ||
           (x == 1632 && y == 1472) || (x == 1440 && y == 1600) || (x == 1248 && y == 1632) ||
           (x == 928 && y == 1376) || (x == 1056 && y == 1376) || (x == 1184 && y == 1376) ||
           (x == 1280 && y == 1376) || (x == 1792 && y == 1184) || (x == 1920 && y == 1184) ||
           (x == 448 && y == 1184) || (x == 320 && y == 1184) || (x == 1120 && y == 672) || (x == 1376 && y == 1632);
}

bool DrawMap::isDoor(float x, float y) {
    return (x == 1120 && y == 1888) || (x == 1120 && y == 1760)  ||
           (x == 1152 && y == 1216) || (x == 576 && y == 992) || (x == 544 && y == 992) ||
           (x == 1120 && y == 1536) || (x == 1152 && y == 1248) || (x == 1440 && y == 1568);
}

bool rectangleExists(const std::vector<Rectangle>& rectangles, const Rectangle& rect) {
    return std::find_if(rectangles.begin(), rectangles.end(), [&rect](const Rectangle& r) {
        return r.x == rect.x && r.y == rect.y && r.width == rect.width && r.height == rect.height;
    }) != rectangles.end();
}

void DrawMap::drawTiles(tson::Map &gameMap, Texture2D &tileTexture)
{
    auto layer1 = gameMap.getLayer("Black")->getData();
    drawLayer(layer1, gameMap, tileTexture);

    auto layer2 = gameMap.getLayer("Kachelebene 1")->getData();
    drawLayer(layer2, gameMap, tileTexture);

    auto layer3 = gameMap.getLayer("Kachelebene 2")->getData();
    drawLayer(layer3, gameMap, tileTexture);

    auto layer4 = gameMap.getLayer("Schatten")->getData();
    //drawLayer(layer4, gameMap, tileTexture);

/*
    auto layer1 = gameMap.getLayer("Kachelebene 2")->getData();
    drawLayer(layer1, gameMap, tileTexture);

    auto layer2 = gameMap.getLayer("animation")->getData();
    drawLayer(layer2, gameMap, tileTexture); */
}

void DrawMap::drawLayer(const std::vector<unsigned int> &layer, tson::Map &Map, Texture2D &tileTexture)
{

    const int currentFrame = int(GetTime() * 6) % 4;
    int multiplier = 1;

    float tileWidth = 32; // Old 16x16
    int tileSetColumns = 8; // Old 16;

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

                    if (!isWall(wallRec.x,wallRec.y) && !rectangleExists(currentGameState.doorRectangles, wallRec) && isDoor(wallRec.x, wallRec.y) && sizeDoorVec <= 7)
                    {
                        currentGameState.doorRectangles.push_back(wallRec); // Add to door rectangles
                        sizeDoorVec++;

                    } else {

                        if(!isWall(wallRec.x,wallRec.y) && !rectangleExists(currentGameState.wallRectangles, wallRec) && sizeWallVec <= 465 && !isDoor(wallRec.x, wallRec.y))
                        {
                            currentGameState.wallRectangles.push_back(wallRec); // Add to wall rectangles
                            sizeWallVec++;
                        }
                    }
                }
            }

            data--;
            if (data < 0) continue;
            Rectangle source = {(float) (data % tileSetColumns) * tileWidth, (float) (data / tileSetColumns) * tileWidth, tileWidth, tileWidth};
            Rectangle destination = {(float) x * tileWidth * multiplier, (float) y * tileWidth * multiplier, tileWidth * multiplier, tileWidth * multiplier};

            if (data >= 0xE0) //animation layer
            {
                source.x += (float) (currentFrame * tileWidth);
            }
            DrawTexturePro(tileTexture, source, destination, {0, 0}, 0, WHITE);
            //std::cout << currentGameState.wallRectangles.size() << std::endl;
        }
    }
}
