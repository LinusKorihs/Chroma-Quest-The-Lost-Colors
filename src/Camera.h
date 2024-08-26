#pragma once

#include "raylib.h"

class playerCamera
{
public:
    playerCamera();
    static Vector2 position;
    static Camera2D camera;
    static Camera2D doorCam;
    static void animationCam(Vector2 doorPos);
    static void updateCamera(Vector2 playerPos, float deltaTime);
    static bool getIsAnimating();
    static bool getIsHolding();
    static bool getIsGoingBack();

private:

    static Vector2 doorPosition;
    static bool isAnimating;
    static float animationTime;
    static const float animationDuration;
    static float doorTime;

    static float holdTime; // Zeit, um die Kamera auf der Tür zu halten
    static bool isHolding; // Flag, um zu überprüfen, ob die Kamera gehalten wird
    static bool isGoingBack; // Flag, um zu überprüfen, ob die Kamera zurückgeht
};
