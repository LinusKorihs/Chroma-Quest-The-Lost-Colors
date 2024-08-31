#include "RoomChanger.h"
#include "MainCharacter.h"
#include "PixelGame.h"

RoomChanger::RoomChanger()
        : phase(TransitionPhase::None), transitionProgress(0.0f), targetPosition({0, 0}) {}

void RoomChanger::update()
{
    // Check if the map is loaded correctly
    if (PixelGame::currentMap.getLayers().empty() || PixelGame::currentMap.getTilesets().empty())
    {
        std::cerr << "Error: Attempted to update room changer with an unloaded map." << std::endl;
        return;
    }

    if (phase != TransitionPhase::None)
    {
        transitionProgress += 0.02f; // Transition speed

        switch (phase)
        {
            case TransitionPhase::Darkening:
                if (transitionProgress >= 0.5f)
                {
                    transitionProgress = 0.5f;
                    phase = TransitionPhase::Black;
                }
                break;

            case TransitionPhase::Black:
                MainCharacter::setPosition(targetPosition);
                if (MainCharacter::playerPosX == targetPosition.x && MainCharacter::playerPosY == targetPosition.y)
                {
                    phase = TransitionPhase::Brightening;
                }
                break;

            case TransitionPhase::Brightening:
                if (transitionProgress >= 1.4f)
                {
                    phase = TransitionPhase::None;
                }
                break;

            default:
                break;
        }

        drawTransitionEffect();

        std::cout << "Updating Roomchanger: Map is loaded" << std::endl;
    }
}

void RoomChanger::startTransition(Vector2 newPosition) {
    phase = TransitionPhase::Darkening;
    transitionProgress = 0.0f;
    targetPosition = newPosition;
}

bool RoomChanger::isTransitioning() const { //true wenn phase != none
    return phase != TransitionPhase::None;
}

void RoomChanger::drawTransitionEffect() const
{
    float alpha = 0.0f;
    if (phase == TransitionPhase::Darkening)
    {
        alpha = transitionProgress;
    }
    else if (phase == TransitionPhase::Black)
    {
        alpha = 1.0f;
    }
    else if (phase == TransitionPhase::Brightening)
    {
        alpha = 1.0f - (transitionProgress - 0.2f);
    }
    DrawRectangle(0, 0, 2500, 3000,
                  Fade(BLACK, alpha));
}

Vector2 RoomChanger::getTargetPos()
{
    return targetPosition;
}

void RoomChanger::setTargetPos()
{
    if(MainCharacter::playerPosX < 38*32 && MainCharacter::playerPosX > 33*32 &&  65*32 > MainCharacter::playerPosY && MainCharacter::playerPosY > 62*32)
    {
        targetPosition = {1120, 2194};
    }

    if(MainCharacter::playerPosX > 39*32 && MainCharacter::playerPosX < 42*32 &&  58*32 > MainCharacter::playerPosY && MainCharacter::playerPosY > 54*32)
    {
        targetPosition = {45*32+18, 56*32};
    }
    if(MainCharacter::playerPosX > 44*32 && MainCharacter::playerPosX < 47*32 &&  57*32 > MainCharacter::playerPosY && MainCharacter::playerPosY > 55*32)
    {
        targetPosition = {41*32-18, 56*32};
    }

    if(MainCharacter::playerPosX > 32*32 && MainCharacter::playerPosX < 38*32 &&  50*32 > MainCharacter::playerPosY && MainCharacter::playerPosY > 47*32)
    {
        targetPosition = {35*32, 21*32-18};
    }
    if(MainCharacter::playerPosX > 33*32 && MainCharacter::playerPosX < 37*32 &&  22*32 > MainCharacter::playerPosY && MainCharacter::playerPosY > 19*32)
    {
        targetPosition = {35*32, 48*32+18};
    }

    if(MainCharacter::playerPosX > 28*32 && MainCharacter::playerPosX < 31*32 &&  58*32 > MainCharacter::playerPosY && MainCharacter::playerPosY > 54*32)
    {
        targetPosition = {25*32-18, 56*32};
    }
    if(MainCharacter::playerPosX > 23*32 && MainCharacter::playerPosX < 26*32 &&  57*32 > MainCharacter::playerPosY && MainCharacter::playerPosY > 55*32)
    {
        targetPosition = {29*32+18, 56*32};
    }

    if(MainCharacter::playerPosX > 13*32 && MainCharacter::playerPosX < 15*32 &&  53*32 > MainCharacter::playerPosY && MainCharacter::playerPosY > 50*32)
    {
        targetPosition = {14*32, 47*32-18};
    }
    if(MainCharacter::playerPosX > 13*32 && MainCharacter::playerPosX < 15*32 &&  48*32 > MainCharacter::playerPosY && MainCharacter::playerPosY > 45*32)
    {
        targetPosition = {14*32, 51*32+18};
    }

    if(MainCharacter::playerPosX > 32*32 && MainCharacter::playerPosX < 35*32 &&  29*32 > MainCharacter::playerPosY && MainCharacter::playerPosY > 27*32)
    {
        targetPosition = {38*32+18, 28*32};
    }
    if(MainCharacter::playerPosX > 37*32 && MainCharacter::playerPosX < 40*32 &&  30*32 > MainCharacter::playerPosY && MainCharacter::playerPosY > 27*32)
    {
        targetPosition = {34*32-18, 28*32};
    }

    if(MainCharacter::playerPosX > 46*32 && MainCharacter::playerPosX < 49*32 &&  37*32 > MainCharacter::playerPosY && MainCharacter::playerPosY > 35*32)
    {
        targetPosition = {52*32+18, 36*32};
    }
    if(MainCharacter::playerPosX > 51*32 && MainCharacter::playerPosX < 54*32 &&  37*32 > MainCharacter::playerPosY && MainCharacter::playerPosY > 35*32)
    {
        targetPosition = {48*32-18, 36*32};
    }

    if(MainCharacter::playerPosX > 60*32 && MainCharacter::playerPosX < 63*32 &&  48*32 > MainCharacter::playerPosY && MainCharacter::playerPosY > 45*32)
    {
        targetPosition = {61*32, 51*32+18};
    }
    if(MainCharacter::playerPosX > 60*32 && MainCharacter::playerPosX < 63*32 &&  53*32 > MainCharacter::playerPosY && MainCharacter::playerPosY > 50*32)
    {
        targetPosition = {61*32, 47*32-18};
    }

    /*if(MainCharacter::playerPosX > 1290 && MainCharacter::playerPosX < 1330 &&  2500 > MainCharacter::playerPosY && MainCharacter::playerPosY > 2400)
    {
        targetPosition = {45*32+18, 75*32};
    }*/
    if(MainCharacter::playerPosX > 45*32 && MainCharacter::playerPosX < 48*32 &&  77*32 > MainCharacter::playerPosY && MainCharacter::playerPosY > 72*32)
    {
        targetPosition = {41*32-18, 75*32};
    }

    if(MainCharacter::playerPosX > 6*32 && MainCharacter::playerPosX < 9*32 &&  40*32 > MainCharacter::playerPosY && MainCharacter::playerPosY > 36*32)
    {
        targetPosition = {12*32+18, 38*32};
    }

    if(MainCharacter::playerPosX > 69*32 && MainCharacter::playerPosX < 72*32 &&  43*32 > MainCharacter::playerPosY && MainCharacter::playerPosY > 39*32)
    {
        targetPosition = {66*32-18, 41*32};
    }

    if(MainCharacter::playerPosX > 34*32 && MainCharacter::playerPosX < 37*32 &&  22*32 > MainCharacter::playerPosY && MainCharacter::playerPosY > 19*32)
    {
        targetPosition = {35*32, 48*32+18};
    }

    // Overworld
   if(MainCharacter::playerPosX > 34*32 && MainCharacter::playerPosX < 37*32 &&  83*32 > MainCharacter::playerPosY && MainCharacter::playerPosY > 80*32)
    {
        overworldTransition();
    }
}
void RoomChanger::overworldTransition()
{

        dungeon1 = false;
        overworld = true;
        std::cout << "Loading map" << std::endl;
        PixelGame::loadMap("assets/graphics/newTileset&Tilemap/Overworld.tmj");


        ClearBackground(BLACK);
        MainCharacter::setPosition({32 * 1, 32 * 39});
        targetPosition = {32 * 1, 32 * 39};  // Set the new target position
        phase = TransitionPhase::None;

}

void RoomChanger::dungeon1Transition()
{
    overworld = false;
    dungeon1 = true;
    std::cout << "Loading map" << std::endl;
    PixelGame::loadMap("assets/graphics/newTileset&Tilemap/newTilemap.tmj");

    ClearBackground(BLACK);
    MainCharacter::setPosition({32 * 35, 32 * 81});
    targetPosition = {32 * 35, 32 * 81};  // Set the new target position
    phase = TransitionPhase::None;
}

void RoomChanger::setTargetPosOverworld()
{
    if(MainCharacter::playerPosX >= 0*32 && MainCharacter::playerPosX < 1*32 &&  40*32 > MainCharacter::playerPosY && MainCharacter::playerPosY > 38*32)
    {
        dungeon1Transition();
    }
}

bool RoomChanger::getDungeon1()
{
    return dungeon1;
}

bool RoomChanger::getOverworld()
{
    return overworld;
}