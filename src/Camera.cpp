#include "Camera.h"
#include "raylib.h"

Camera2D  playerCamera::camera;

playerCamera::playerCamera()
{
    camera = { 0 };   //camera init
    camera.target = (Vector2){ 80,368 };
    camera.offset = (Vector2){GetScreenWidth()/2.0f, GetScreenHeight()/2.0f};
    camera.rotation = 0.0f;
    camera.zoom = 4.0f;
}
