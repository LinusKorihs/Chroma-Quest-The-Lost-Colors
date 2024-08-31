#include "Camera.h"
#include "MainCharacter.h"
#include "raylib.h"

Camera2D playerCamera::camera;
Camera2D playerCamera::doorCam;
Vector2 playerCamera::position;
Vector2 playerCamera::doorPosition;
bool playerCamera::isAnimating = false;
float playerCamera::animationTime;
float playerCamera::doorTime;
const float playerCamera::animationDuration = 0.4f;
float playerCamera::holdTime;
bool playerCamera::isHolding;
bool playerCamera::isGoingBack;


playerCamera::playerCamera()
{
    camera = { 0 };   // Camera initialisieren
    camera.target = (Vector2){ MainCharacter::playerPosX, MainCharacter::playerPosY };
    camera.offset = (Vector2){GetScreenWidth()/2.0f, GetScreenHeight()/2.0f};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
    isAnimating = false;
    animationTime = 0.0f;
    doorPosition = {0, 0};
    doorCam = { 0 };
    doorCam.target = doorPosition;
    doorCam.offset = (Vector2){GetScreenWidth()/2.0f, GetScreenHeight()/2.0f};
    doorCam.rotation = 0.0f;
    doorCam.zoom = 1.0f;
    doorTime = 0.0f;
}

void playerCamera::animationCam(Vector2 doorPos)
{
    doorPosition = doorPos; // Türposition speichern
    isAnimating = true;
    animationTime = 0.0f; // Timer starten
    doorTime = 0.0f;
    holdTime = 0.0f;
    isHolding = false;
    isGoingBack = false;

}

void playerCamera::updateCamera(Vector2 playerPos, float deltaTime) {

    if (isAnimating) {
        EndMode2D();
        BeginMode2D(doorCam); // Kamera-Modus starten

        doorCam.target.x = doorPosition.x;
        doorCam.target.y = doorPosition.y;
        animationTime += deltaTime;

        float t = animationTime / animationDuration;
        std::cout << "t: " << t << std::endl;


        if (!isGoingBack) {
            doorCam.target.y = (1-t) * playerPos.y + t * doorPosition.y;
            doorCam.target.x = (1 - t) * playerPos.x + t * doorPosition.x;
        }
        if (isGoingBack) {
            doorCam.target.x = (1 - t) * doorPosition.x + t * playerPos.x;
            doorCam.target.y = (1 - t) * doorPosition.y + t * playerPos.y;
        }


        // Wenn die Animation zu Ende ist, beginne die Haltezeit
        if (!isGoingBack && animationTime >= animationDuration) {
            holdTime += deltaTime;
            doorCam.target.x = doorPosition.x;
            doorCam.target.y = doorPosition.y;
            if(holdTime >= 0.5 && !isHolding) {
                holdTime = 0;
                isHolding = true;
                // Setze das Flag, um das Halten zu aktivieren
                std::cout << "Animation finished. Holding camera on door." << std::endl;
            }
        }

        if (isHolding) {
            // Halte die Kamera für eine bestimmte Zeit auf der Tür
            holdTime += deltaTime;
            if (holdTime >= 1.3f) { // Haltezeit (z.B. 2 Sekunden)
                std::cout << "Holding time finished. Resetting camera target." << std::endl;
                isGoingBack = true;
                isHolding = false; // Halte das Flag zurück
                animationTime = 0.0f; // Setze den Timer zurück
            }
        }

        // Wenn die Rückkehr-Animation abgeschlossen ist, setze die Kamera auf den Spieler
        if (isGoingBack && animationTime >= animationDuration) {
            std::cout << "Camera back at player." << std::endl;
            //doorCam.target = playerPos; // Setze die Kamera auf die Spielerposition
            isGoingBack = false;
            isAnimating = false;
        }
    }
    camera.target = playerPos;
}

bool playerCamera::getIsAnimating() {
    return isAnimating;
}

bool playerCamera::getIsHolding() {
    return isHolding;
}

bool playerCamera::getIsGoingBack() {
    return isGoingBack;
}