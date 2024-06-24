#include "RoomTransition.h"
/*
enum TransitionState
{
    None,
    Darkening,
    SwitchingRoom,
    Brightening
};

TransitionState transitionState = None;
float transitionAlpha = 0.0f; // 0.0 (fully bright) to 1.0 (fully dark)
float transitionSpeed = 0.01f; // Adjust speed as needed

void RoomTransition::UpdateTransition()
{
    switch (transitionState)
    {
        case Darkening:
            transitionAlpha += transitionSpeed;
            if (transitionAlpha >= 1.0f)
            {
                transitionAlpha = 1.0f;
                transitionState = SwitchingRoom;
                SwitchRoom(); // Function to change the room
            }
            break;
        case SwitchingRoom:
            transitionState = Brightening;
            break;
        case Brightening:
            transitionAlpha -= transitionSpeed;
            if (transitionAlpha <= 0.0f)
            {
                transitionAlpha = 0.0f;
                transitionState = None;
            }
            break;
        case None:  // No transition in progress
            break;
    }
}

void RoomTransition::DrawOverlay()
{
    if (transitionState != None)
    {
        // Assuming you have a function to set the opacity and draw a rectangle over the screen
        SetOpacity(transitionAlpha); // Set the opacity level
        DrawRectangle(0, 0, screenWidth, screenHeight, BLACK); // Draw a black rectangle over the screen
    }
}

void RoomTransition::SwitchRoom()
{
    LoadNewRoom(); // Load the new room

    character.SetPosition(newDoorX, newDoorY); // Reposition the character to the new door position
}

*/