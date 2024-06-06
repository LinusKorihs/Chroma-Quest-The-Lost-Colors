#include "Audio.h"


void Audio::UpdateVolumes()
{
    float globalVolume = gameState.globalVolume / 100.0f;
    if (globalVolume == 0)
    {
        SetSoundVolume(gameState.walkingSound, 0);
        SetMusicVolume(gameState.backgroundMusic, 0);
    }
    else
    {
        SetSoundVolume(gameState.walkingSound, globalVolume * (gameState.globalSFXVolume / 100.0f));
        SetMusicVolume(gameState.backgroundMusic, globalVolume * (gameState.globalMusicVolume / 100.0f));
    }
}

void Audio::LoadResourcesAndInitAudio()
{
    gameState.myTexture = LoadTexture("assets/graphics/testimage.png");
    gameState.myMC = LoadTexture("assets/graphics/Aurora2.png");
    InitAudioDevice();
    gameState.walkingSound = LoadSound("assets/audio/sfx/FootSteps.wav");
    gameState.backgroundMusic = LoadMusicStream("assets/audio/tracks/TestSong.wav");
    UpdateVolumes();
    PlayMusicStream(gameState.backgroundMusic);
}

void Audio::UnloadResourcesAndCloseAudio()
{
    UnloadTexture(gameState.myTexture);
    UnloadTexture(gameState.myMC);
    UnloadSound(gameState.walkingSound);
    UnloadMusicStream(gameState.backgroundMusic);
    CloseAudioDevice();
}

void Audio::DrawVolumeSlider(VolumeType type, int* volume, const char* englishVolumeName, const char* germanVolumeName, float sliderY)
{
    int screenWidth = PixelGameConfig::ScreenWidth;
    Rectangle slider = {(float)screenWidth/2 - 50, sliderY, 150, 30};
    DrawRectangleLines(slider.x, slider.y, slider.width, slider.height, BLACK);
    DrawRectangle(slider.x, slider.y, *volume * (slider.width / 100), slider.height, GRAY);
    if (CheckCollisionPointRec(GetMousePosition(), slider) && IsMouseButtonDown(MOUSE_LEFT_BUTTON))
    {
        int mouseX = GetMouseX();
        *volume = (mouseX - slider.x) * 100 / slider.width;
        if (*volume < 0) *volume = 0;
        if (*volume > 100) *volume = 100;
    }
    DrawText(TextFormat("%s: %i", gameState.GetLocalizedText(englishVolumeName, germanVolumeName), *volume), slider.x + slider.width / 2 - MeasureText(TextFormat("%s: %i",
                                                                                                                                                                  gameState.GetLocalizedText(
                                                                                                                                                                        englishVolumeName,
                                                                                                                                                                        germanVolumeName), *volume), 20) / 2, slider.y - 40, 20, BLACK);
}