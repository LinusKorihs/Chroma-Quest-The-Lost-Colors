#pragma once

#include "raylib.h"

class WindowSizeScale
{
public:
    static Rectangle calculateRenderRectangle(float& renderScale);

    static HudImageButton &button;
    static float buttonWidthPercentage;
    static float buttonHeightPercentage;
};
