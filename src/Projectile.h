
#ifndef RAYLIBSTARTER_PROJECTILE_H
#define RAYLIBSTARTER_PROJECTILE_H
#include "ApplicationState.h"
#include "raylib.h"


namespace Pixelgame {
    class Projectile {
    public:
        Projectile();
        void Load();
        void Init(Vector2 startPosition, Vector2 speed);
        void Update(float deltaTime, int direction);
        void Draw();
        void Collision();
        Rectangle GetRec();
        void SetActive(bool active);
        bool GetActive();
        void Unload();

    private:
        Vector2 position{};
        Vector2 projSpeed{};
        bool isActive;
        Rectangle projectileRec{};
        Texture2D projectileTexture{};
    };
}

#endif //RAYLIBSTARTER_PROJECTILE_H
