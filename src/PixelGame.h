#include "ApplicationState.h"
#include "Audio.h"
#include "cmath"
#include "Enemy.h"
#include "InGameHud.h"
#include <memory>
#include "Menu.h"
#include "Projectile.h"
#include "raylib.h"
#include "stone.h"
#include "tileson.h"

class PixelGame {
public:

    static void DrawTiles(tson::Map &Map, Texture2D &myTexture);
    static void DrawLayer(const std::vector<unsigned int> &layer, tson::Map &Map, Texture2D &myTexture);
    static void DrawSprite(Texture2D &myTexture);
    static void MoveCharacter(int direction, float deltaTime);
    static void GameInit();
    static void GameLoop(tson::Map &Map);
    static void LoadTextureX(Texture2D &texture, const char* path);
    static void DrawTexture(Texture2D &texture, Rectangle dest);
    static void UnloadTextureX(Texture2D &texture);
    static void DrawObjects();
    static void UnloadAll();
    static void DrawHud();
    static void PlayerDeath();
    static void ReceiveDmg();
    static void Attack();
    static void EnemyAttack();
    static int GetProjDest();


private:

    static Vector2 position;
    static Camera2D camera;

    static Texture2D lavaTexture;
    static Texture2D meatTexture;
    static Texture2D fruitTexture;
    static Texture2D slimeTexture;
    static Texture2D tilesetTexture;


    static float mcX;
    static float mcY;
    static int projDest;

    static bool lastDirectionLeft;
    static bool lastDirectionUp;
    static bool lastDirectionRight;
    static bool lastDirectionDown;
    static bool isKnocked;

    static Rectangle characterRec;
    static Rectangle characterHitRec;
    static Rectangle lavaRec;
    static Rectangle meatRec;
    static Rectangle fruitRec;

    static std::vector <Stone> stones;

    static std::shared_ptr<Pixelgame::Projectile> proj_p;
    static std::shared_ptr<Pixelgame::Projectile> proj_p_enemy;
    static std::shared_ptr<Pixelgame::Enemy> en_p;

};