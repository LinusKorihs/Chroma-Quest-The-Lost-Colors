#include "Audio.h"
#include "config.h"
#include "InGameHud.h"
#include "Menu.h"
#include "Utils.h"
#include "WindowSizeScale.h"

Rectangle WindowSizeScale::calculateRenderRectangle(float& renderScale)
{
    Rectangle renderRectangle;
    renderScale = GetScreenWidth() / (float) PixelGameConfig::ScreenWidth; //renderScale = floorf(renderScale);
    renderRectangle.width = PixelGameConfig::ScreenWidth * renderScale;
    renderRectangle.height = PixelGameConfig::ScreenHeight * renderScale;
    renderRectangle.x = ((float)GetScreenWidth() - renderRectangle.width) / 2;
    renderRectangle.y = ((float)GetScreenHeight() - renderRectangle.height) / 2;

    Audio::updateSliderPositions(Audio::index);

    return renderRectangle;
}