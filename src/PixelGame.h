#include "raylib.h"
#include "ApplicationState.h"
#include "tileson.h"

class PixelGame {
public:
    static void drawTiles(tson::Map &Map, Texture2D &myTexture);
    static void drawLayer(const std::vector<unsigned int> &layer, tson::Map &Map, Texture2D &myTexture);
    static void drawSprite(Texture2D &myTexture, float mcX, float mcY);
    static void moveCharacter(float& mcX, float& mcY, int direction);
    static void gameInit();
    static void gameLoop(tson::Map &Map);
    static void loadTexture(Texture2D &texture, const char* path);
    static void drawTexture(Texture2D &texture, Rectangle dest);
    static void unloadTexture(Texture2D &texture);

    static Texture2D lavaTexture;
    static Texture2D meatTexture;
    static Texture2D fruitTexture;
};