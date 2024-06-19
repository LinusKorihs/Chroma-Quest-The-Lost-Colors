#pragma once
#include <map>
#include "raylib.h"
#include <string>

class TextureManager
{
public:
    static void init();
    static Texture2D getTexture(const std::string &name);

    static std::map<std::string, Texture2D> m_textures;
private:
    static bool m_texturesLoaded;
};

class TextureManage
{
public:
    static void loadAudio();
};