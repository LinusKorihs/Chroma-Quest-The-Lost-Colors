#include "Audio.h"
#include "Configuration.h"
#include <iostream>
#include "TextureManage.h"
#include "raylib.h"
#include "SetKeyBindings.h"
#include "tileson.h"
#include <map>
#include <string>

bool TextureManager::m_texturesLoaded = false;
std::map<std::string, Texture2D> TextureManager::m_textures;

void TextureManager::init()
{
    if (m_texturesLoaded)
    {
        TraceLog(LOG_ERROR, "The TextureManager has already been initialized!");
        return;
    }
    m_texturesLoaded = true;
    m_textures["ERROR"] = LoadTexture("assets/graphics/Tiles/MissingTexture.png");
    //m_textures["MainCharacter"] = LoadTexture("assets/graphics/MainCharacter/MainCharacter.png");
    m_textures["MainCharacter"] = LoadTexture("assets/graphics/MainCharacter/MC_animation_sheet.png");
    m_textures["DoorRed2"] = LoadTexture("assets/graphics/Tiles/DoorRed2.png");
    m_textures["StoneDoorR"] = LoadTexture("assets/graphics/Tiles/StoneDoorR.png");
    m_textures["StoneDoorL"] = LoadTexture("assets/graphics/Tiles/StoneDoorL.png");
    m_textures["SlimeRed"] = LoadTexture("assets/graphics/Enemies/slimeRedAnim.png");
    m_textures["OpenWoodDoor2"] = LoadTexture("assets/graphics/Tiles/OpenWoodDoorDown.png");
    m_textures["SlimeEnemy"] = LoadTexture("assets/graphics/Enemies/TestSlime.png");
    m_textures["BossRed"] = LoadTexture("assets/graphics/Enemies/redBoss.png");
    m_textures["speechBubble"] = LoadTexture("assets/graphics/HUD/speechBubble.png");
    //m_textures["TileSet"] = LoadTexture("assets/graphics/TileSet & TileMap/TileSet.png");
    m_textures["TileSet"] = LoadTexture("assets/graphics/newTileset&Tilemap/newTileSet.png");
    m_textures["StartGameButtonTexture"] = LoadTexture("assets/graphics/ButtonColors/ButtonBlue.png");
    m_textures["SettingsMenuButtonTexture"] = LoadTexture("assets/graphics/ButtonColors/ButtonYellow.png");
    m_textures["ExitGameButtonTexture"] = LoadTexture("assets/graphics/ButtonColors/ButtonRed.png");
    m_textures["ResumeButtonTexture"] = LoadTexture("assets/graphics/ButtonColors/ButtonGreen.png");
    m_textures["QuitButtonTexture"] = LoadTexture("assets/graphics/ButtonColors/ButtonYellow.png");
    m_textures["KeyBindingsButtonTexture"] = LoadTexture("assets/graphics/ButtonColors/ButtonWhite.png");
    m_textures["VolumeButtonTexture"] = LoadTexture("assets/graphics/ButtonColors/ButtonGreen.png");
    m_textures["ControlButtonTexture"] = LoadTexture("assets/graphics/ButtonColors/ButtonOrange.png");
    m_textures["LanguageButtonTexture"] = LoadTexture("assets/graphics/ButtonColors/ButtonPurple.png");
    m_textures["ControllerButtonTexture"] = LoadTexture("assets/graphics/ButtonColors/ButtonGrey.png");
    m_textures["PauseButtonTexture"] = LoadTexture("assets/graphics/ButtonColors/ButtonGrey.png");
    m_textures["KeyboardButtonTexture"] = LoadTexture("assets/graphics/ButtonColors/ButtonWhite.png");
    m_textures["LanguageENButtonTexture"] = LoadTexture("assets/graphics/ButtonColors/ButtonOrange.png");
    m_textures["LanguageDEButtonTexture"] = LoadTexture("assets/graphics/ButtonColors/ButtonPurple.png");
    m_textures["upKeyButtonTexture"] = LoadTexture("assets/graphics/ButtonColors/ButtonBlue.png");
    m_textures["downKeyButtonTexture"] = LoadTexture("assets/graphics/ButtonColors/ButtonYellow.png");
    m_textures["leftKeyButtonTexture"] = LoadTexture("assets/graphics/ButtonColors/ButtonGreen.png");
    m_textures["rightKeyButtonTexture"] = LoadTexture("assets/graphics/ButtonColors/ButtonRed.png");
    m_textures["Machine"] = LoadTexture("assets/graphics/Tiles/machine.png");
   // m_textures["Stone"] = LoadTexture("assets/graphics/Tiles/Stone.png");
    m_textures["Stone"] = LoadTexture("assets/graphics/Tiles/newStone.png");
    m_textures["Orb"] = LoadTexture("assets/graphics/Tiles/orb.png");
    m_textures["PlateNormal"] = LoadTexture("assets/graphics/Tiles/druckN.png");
    m_textures["PlatePressed"] = LoadTexture("assets/graphics/Tiles/druck.png");
    m_textures["Heart"] = LoadTexture("assets/graphics/HUD/HeartFull.png");
    m_textures["HeartEmpty"] = LoadTexture("assets/graphics/HUD/HeartEmpty.png");
    m_textures["HeartHalf"] = LoadTexture("assets/graphics/HUD/HeartHalf.png");
    m_textures["RedButton"] = LoadTexture("assets/graphics/Tiles/RedButton.png");
    m_textures["Chest"] = LoadTexture("assets/graphics/Tiles/chest.png");
    m_textures["Frucht"] = LoadTexture("assets/graphics/Items/Frucht.png");

    for (auto &texture : m_textures)
    {
        if (!IsTextureReady(texture.second))
        {
            TraceLog(LOG_WARNING, "TextureManager::init() failed to load texture: %s", texture.first.c_str());
        }
    }
}

Texture2D TextureManager::getTexture(const std::string &name) // call this texture on construction of a new object, not every frame
{
    if (m_textures.find(name) != m_textures.end()) // check if the texture exists in map
    {
        return m_textures[name];
    }
    TraceLog(LOG_WARNING, "TextureManager::getTexture() called with unknown texture name: %s", name.c_str());
    return m_textures["ERROR"];
}

void TextureManage::loadAudio()
{
    //InitAudioDevice(); // Initialize audio device

    ConfigNotConst::playerWalkingSound = LoadSound("assets/audio/sfx/FootSteps.wav");
    ConfigNotConst::gameBackgroundMusic = LoadMusicStream("assets/audio/tracks/TestSong.wav");

    Audio::updateAudioVolumes();
    PlayMusicStream(ConfigNotConst::gameBackgroundMusic);
}
