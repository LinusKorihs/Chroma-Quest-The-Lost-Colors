#pragma once
#include "raylib.h"
#include "TextureManage.h"


class Comments {
public:

    Comments();
    static void drawComment();
    static void checkIfShowedAlready();
    static void initComment();

private:
    static bool showedAlready;
    static Texture2D commentTexture;

};


