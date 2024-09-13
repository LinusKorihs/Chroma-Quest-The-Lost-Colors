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
    m_textures["MainCharacter"] = LoadTexture("assets/graphics/MainCharacter/newMC.png");
    m_textures["DoorRed2"] = LoadTexture("assets/graphics/Tiles/DoorRed2.png");
    m_textures["StoneDoorR"] = LoadTexture("assets/graphics/Tiles/StoneDoorR.png");
    m_textures["StoneDoorL"] = LoadTexture("assets/graphics/Tiles/StoneDoorL.png");
    m_textures["SlimeRed"] = LoadTexture("assets/graphics/Enemies/slimeRedAnim.png");
    m_textures["OpenWoodDoor2"] = LoadTexture("assets/graphics/Tiles/OpenWoodDoorDown.png");
    m_textures["SlimeEnemy"] = LoadTexture("assets/graphics/Enemies/TestSlime.png");
    m_textures["BossRed"] = LoadTexture("assets/graphics/Enemies/redBoss.png");
    //m_textures["TileSet"] = LoadTexture("assets/graphics/TileSet & TileMap/TileSet.png");
    m_textures["TileSet"] = LoadTexture("assets/graphics/newTileset&Tilemap/newTileSet.png");
    m_textures["Overworld"] = LoadTexture("assets/graphics/newTileset&Tilemap/overworldTileset.png");
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
    m_textures["platePressedDark"] = LoadTexture("assets/graphics/Tiles/platePressedDark.png");
    m_textures["plateNormalDark"] = LoadTexture("assets/graphics/Tiles/plateNormalDark.png");
    m_textures["Heart"] = LoadTexture("assets/graphics/HUD/HeartFull.png");
    m_textures["HeartEmpty"] = LoadTexture("assets/graphics/HUD/HeartEmpty.png");
    m_textures["HeartHalf"] = LoadTexture("assets/graphics/HUD/HeartHalf.png");
    m_textures["RedButton"] = LoadTexture("assets/graphics/Tiles/RedButton.png");
    m_textures["Chest"] = LoadTexture("assets/graphics/Tiles/chest.png");
    m_textures["Frucht"] = LoadTexture("assets/graphics/Items/Frucht.png");
    m_textures["mouse"] = LoadTexture("assets/graphics/NPC/mouse.png");
    m_textures["frog"] = LoadTexture("assets/graphics/NPC/frog.png");
    m_textures["gekko"] = LoadTexture("assets/graphics/NPC/gekko.png");
    m_textures["owl"] = LoadTexture("assets/graphics/NPC/owl.png");
    m_textures["MouseBubble"] = LoadTexture("assets/graphics/NPC/mouseBubble.png");
    m_textures["OwlBubble"] = LoadTexture("assets/graphics/NPC/owlBubble.png");
    m_textures["GekkoBubble"] = LoadTexture("assets/graphics/NPC/gekkoBubble.png");
    m_textures["FrogBubble"] = LoadTexture("assets/graphics/NPC/frogBubble.png");
    m_textures["redButtonDark"] = LoadTexture("assets/graphics/Tiles/redButtonDark.png");


    //hud
    m_textures["grayHUD"] = LoadTexture("assets/graphics/HUD/greyHud.png");
    m_textures["blueOrb"] = LoadTexture("assets/graphics/HUD/blueOrb.png");
    m_textures["yellowOrb"] = LoadTexture("assets/graphics/HUD/yellowOrb.png");
    m_textures["redOrb"] = LoadTexture("assets/graphics/HUD/redOrb.png");
    m_textures["newHeart"] = LoadTexture("assets/graphics/HUD/newHeartFull.png");
    m_textures["newHeartHalf"] = LoadTexture("assets/graphics/HUD/newHeartHalf.png");
    m_textures["yellowBeam"] = LoadTexture("assets/graphics/HUD/yellowBeam.png");
    m_textures["blueBeam"] = LoadTexture("assets/graphics/HUD/blueBeam.png");
    //signs
    m_textures["controlBox"] = LoadTexture("assets/graphics/HUD/showBox.png");
    m_textures["blueDist"] = LoadTexture("assets/graphics/HUD/Districts/Blue District.png");
    m_textures["yellowDist"] = LoadTexture("assets/graphics/HUD/Districts/Yellow District.png");
    m_textures["redDist"] = LoadTexture("assets/graphics/HUD/Districts/Red District.png");
    m_textures["blueRoad"] = LoadTexture("assets/graphics/HUD/Districts/blue Road.png");
    m_textures["yellowRoad"] = LoadTexture("assets/graphics/HUD/Districts/yellow Road.png");
    m_textures["redRoad"] = LoadTexture("assets/graphics/HUD/Districts/Red Road.png");
    m_textures["central"] = LoadTexture("assets/graphics/HUD/Districts/central.png");
    m_textures["background"] = LoadTexture("assets/background.gif");

    m_textures["exitButton"] = LoadTexture("assets/graphics/Buttons/exit.png");
    m_textures["exitButtonPressed"] = LoadTexture("assets/graphics/Buttons/exit_selected.png");
    m_textures["playButton"] = LoadTexture("assets/graphics/Buttons/play.png");
    m_textures["playButtonPressed"] = LoadTexture("assets/graphics/Buttons/play_selected.png");
    m_textures["settingsButton"] = LoadTexture("assets/graphics/Buttons/settings.png");
    m_textures["settingsButtonPressed"] = LoadTexture("assets/graphics/Buttons/settings_selected.png");
    m_textures["logo"] = LoadTexture("assets/graphics/Buttons/Logo_official.png");

    //boss
    m_textures["BossFull"] = LoadTexture("assets/graphics/Enemies/BossFull.png");
    m_textures["Boss1Shield"] = LoadTexture("assets/graphics/Enemies/Boss1Shield.png");
    m_textures["BossNoShield"] = LoadTexture("assets/graphics/Enemies/BossNoShield.png");
    m_textures["Boss-1"] = LoadTexture("assets/graphics/Enemies/Boss-1.png");
    m_textures["Boss-2"] = LoadTexture("assets/graphics/Enemies/Boss-2.png");
    m_textures["Boss-3"] = LoadTexture("assets/graphics/Enemies/Boss-3.png");
    m_textures["Boss-4"] = LoadTexture("assets/graphics/Enemies/Boss-4.png");
    m_textures["Boss-5"] = LoadTexture("assets/graphics/Enemies/Boss-5.png");
    m_textures["Boss-6"] = LoadTexture("assets/graphics/Enemies/Boss-6.png");
    m_textures["BossEmpty"] = LoadTexture("assets/graphics/Enemies/BossEmpty.png");

    //tutorial
    m_textures["greyBlocks"] = LoadTexture("assets/graphics/HUD/Tutorial/greyBlocks.png");
    m_textures["redBlocks"] = LoadTexture("assets/graphics/HUD/Tutorial/redBlocks.png");
    m_textures["orb"] = LoadTexture("assets/graphics/HUD/Tutorial/orb.png");
    m_textures["chests"] = LoadTexture("assets/graphics/HUD/Tutorial/chests.png");
    m_textures["placeOrb"] = LoadTexture("assets/graphics/HUD/Tutorial/placeOrb.png");
    m_textures["redButton"] = LoadTexture("assets/graphics/HUD/Tutorial/redButton.png");

    //journal
    m_textures["emptyJournal"] = LoadTexture("assets/graphics/Journal/empty.png");
    m_textures["page1"] = LoadTexture("assets/graphics/Journal/page1.png");
    m_textures["page1+2"] = LoadTexture("assets/graphics/Journal/page1+2.png");
    m_textures["page2"] = LoadTexture("assets/graphics/Journal/page2.png");
    m_textures["journalidle"] = LoadTexture("assets/graphics/Journal/journalidle.png");

    //newHUD
    m_textures["full"] = LoadTexture("assets/graphics/HUD/HealthBar/HBFull.png");
    m_textures["HB4,5"] = LoadTexture("assets/graphics/HUD/HealthBar/HB4,5.png");
    m_textures["HB4"] = LoadTexture("assets/graphics/HUD/HealthBar/HB4.png");
    m_textures["HB3,5"] = LoadTexture("assets/graphics/HUD/HealthBar/HB3,5.png");
    m_textures["HB3"] = LoadTexture("assets/graphics/HUD/HealthBar/HB3.png");
    m_textures["HB2,5"] = LoadTexture("assets/graphics/HUD/HealthBar/HB2,5.png");
    m_textures["HB2"] = LoadTexture("assets/graphics/HUD/HealthBar/HB2.png");
    m_textures["HB1,5"] = LoadTexture("assets/graphics/HUD/HealthBar/HB1,5.png");
    m_textures["HB1"] = LoadTexture("assets/graphics/HUD/HealthBar/HB1.png");
    m_textures["HB0,5"] = LoadTexture("assets/graphics/HUD/HealthBar/HB0,5.png");
    m_textures["HB0"] = LoadTexture("assets/graphics/HUD/HealthBar/HB0.png");

    m_textures["redTower"] = LoadTexture("assets/graphics/HUD/Districts/redTower.png");
    m_textures["tutJournal"] = LoadTexture("assets/graphics/HUD/Tutorial/tutJournal.png");


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
    ConfigNotConst::chestOpenSound = LoadSound("assets/audio/sfx/chest.wav");
    ConfigNotConst::doorOpenSound = LoadSound("assets/audio/sfx/doorSound.wav");
    ConfigNotConst::gameBackgroundMusic = LoadMusicStream("assets/audio/tracks/dungeon1.mp3");
    ConfigNotConst::miniBossHit = LoadSound("assets/audio/sfx/CQ_hit_mini-boss_SFX.mp3");
    ConfigNotConst::slimeDeath = LoadSound("assets/audio/sfx/CQ_slime_death_splat_SFX.mp3");
    ConfigNotConst::heartSound = LoadSound("assets/audio/sfx/CQ_pick_up_heart.mp3");
    ConfigNotConst::orbSound = LoadSound("assets/audio/sfx/CQ_pick_up_orb.mp3");
    ConfigNotConst::pressurePlateSound = LoadSound("assets/audio/sfx/CQ_pressure_plate_SFX.mp3");
    ConfigNotConst::punchSound = LoadSound("assets/audio/sfx/CQ_punch_SFX.mp3");
    ConfigNotConst::selectSound = LoadSound("assets/audio/sfx/CQ_select_diary_page_SFX.mp3");
    ConfigNotConst::pickPageSound = LoadSound("assets/audio/sfx/CQ_pick_up_diary_page_SFX.mp3");

    Audio::updateAudioVolumes();
    SetSoundVolume(ConfigNotConst::chestOpenSound, 0.3f);
    SetSoundVolume(ConfigNotConst::doorOpenSound, 1.5f);
    SetSoundVolume(ConfigNotConst::miniBossHit, 0.3f);
    SetSoundVolume(ConfigNotConst::slimeDeath, 0.2f);
    SetSoundVolume(ConfigNotConst::heartSound, 0.2f);
    SetSoundVolume(ConfigNotConst::orbSound, 0.4f);
    SetSoundVolume(ConfigNotConst::pressurePlateSound, 0.7f);
    SetSoundVolume(ConfigNotConst::punchSound, 0.2f);
    SetSoundVolume(ConfigNotConst::selectSound, 0.2f);
    SetSoundVolume(ConfigNotConst::pickPageSound, 0.7f);

    PlayMusicStream(ConfigNotConst::gameBackgroundMusic);
}

