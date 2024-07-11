#include "RoomChanger.h"
#include "MainCharacter.h"

RoomChanger::RoomChanger()
        : phase(TransitionPhase::None), transitionProgress(0.0f), targetRoom(0), targetPosition({0, 0}) {}

void RoomChanger::update() {
    if (phase != TransitionPhase::None) {
        transitionProgress += 0.02f; //transutuon speed

        switch (phase) {
            case TransitionPhase::WAIT:
                phase = TransitionPhase::Brightening;
                transitionProgress = 0.3f;
                break;
            case TransitionPhase::Darkening:
                if (transitionProgress >= 0.5f) {
                    transitionProgress = 0.5;
                    phase = TransitionPhase::Black;
                }
                break;
            case TransitionPhase::Black:
                MainCharacter::setPosition(targetPosition);
                if(MainCharacter::playerPosX == targetPosition.x && MainCharacter::playerPosY == targetPosition.y)
                {
                    phase = TransitionPhase::WAIT;
                }
                //phase = TransitionPhase::Brightening;
                transitionProgress = 1.3f;
                break;
            case TransitionPhase::Brightening:
                transitionProgress += 0.01f;
                if (transitionProgress >= 1.5f) {
                    transitionProgress = 1.5f;
                    phase = TransitionPhase::None;
                }
                break;
            default:
                break;
        }

        drawTransitionEffect();
    }
}

void RoomChanger::startTransition(int newRoom, Vector2 newPosition) {
    phase = TransitionPhase::Darkening;
    transitionProgress = 0.0f;
    targetRoom = newRoom;
    targetPosition = newPosition;
}

bool RoomChanger::isTransitioning() const {
    return phase != TransitionPhase::None;
}

void RoomChanger::drawTransitionEffect() const {
    float alpha = 0.0f;
    if (phase == TransitionPhase::Darkening) {
        alpha = transitionProgress;
    } else if (phase == TransitionPhase::Black) {
        alpha = 1.0f;
    } else if (phase == TransitionPhase::WAIT) {
        alpha = 1.0f;
    } else if (phase == TransitionPhase::Brightening) {
        alpha = 1.0f - (transitionProgress - 0.2f);
    }
    DrawRectangle(0, 0, 2500, 3000, Fade(BLACK, alpha)); //W/H müssen noch genauer werden - ist nur ein random großes rec
}

Vector2 RoomChanger::getTargetPos()
{
    return targetPosition;
}

void RoomChanger::setTargetPos()
{

    int multiple = 32;
    /*if(MainCharacter::playerPosX < 1060 && MainCharacter::playerPosX > 900 &&  1650 > MainCharacter::playerPosY && MainCharacter::playerPosY > 1610)
    {
        targetPosition = {846, 1632};
    }
    if(MainCharacter::playerPosX > 830 && MainCharacter::playerPosX < 870 &&  1640 > MainCharacter::playerPosY && MainCharacter::playerPosY > 1625)
    {
        targetPosition = {1009, 1632};
    }

    if(MainCharacter::playerPosX < 745 && MainCharacter::playerPosX > 690 &&  1650 > MainCharacter::playerPosY && MainCharacter::playerPosY > 1600)
    {
        targetPosition = {704, 1456};
    }
    if(MainCharacter::playerPosX < 745 && MainCharacter::playerPosX > 690 &&  1500 > MainCharacter::playerPosY && MainCharacter::playerPosY > 1400)
    {
        targetPosition = {704, 1618};
    }

    if(MainCharacter::playerPosX < 1060 && MainCharacter::playerPosX > 1020 &&  990 > MainCharacter::playerPosY && MainCharacter::playerPosY > 960)
    {
        targetPosition = {1024, 1138};
    }
    if(MainCharacter::playerPosX < 1060 && MainCharacter::playerPosX > 1020 &&  1200 > MainCharacter::playerPosY && MainCharacter::playerPosY > 1100)
    {
        targetPosition = {1024, 976};
    }

    if(MainCharacter::playerPosX < 1335 && MainCharacter::playerPosX > 1315 &&  2000 > MainCharacter::playerPosY && MainCharacter::playerPosY > 1170)
    {
        targetPosition = {1490, 1184};
    }
    if(MainCharacter::playerPosX < 1500 && MainCharacter::playerPosX > 1475 &&  2000 > MainCharacter::playerPosY && MainCharacter::playerPosY > 1170)
    {
        targetPosition = {1326, 1184};
    }

    if(MainCharacter::playerPosX < 1780 && MainCharacter::playerPosX > 1760 &&  1200 > MainCharacter::playerPosY && MainCharacter::playerPosY > 1170)
    {
        targetPosition = {1944, 1184};
    }
    if(MainCharacter::playerPosX < 1940 && MainCharacter::playerPosX > 1920 &&  1200 > MainCharacter::playerPosY && MainCharacter::playerPosY > 1170)
    {
        targetPosition = {1768, 1184};
    }

    if(MainCharacter::playerPosX < 1640 && MainCharacter::playerPosX > 1620 &&  1345 > MainCharacter::playerPosY && MainCharacter::playerPosY > 1310)
    {
        targetPosition = {1632, 1494};
    }
    if(MainCharacter::playerPosX < 1640 && MainCharacter::playerPosX > 1620 &&  1500 > MainCharacter::playerPosY && MainCharacter::playerPosY > 1470)
    {
        targetPosition = {1632, 1326};
    }

    if(MainCharacter::playerPosX < 1400 && MainCharacter::playerPosX > 1380 &&  1650 > MainCharacter::playerPosY && MainCharacter::playerPosY > 1600)
    {
        targetPosition = {1230, 1632};
    }
    if(MainCharacter::playerPosX < 1260 && MainCharacter::playerPosX > 1225 &&  1650 > MainCharacter::playerPosY && MainCharacter::playerPosY > 1600)
    {
        targetPosition = {1393, 1632};
    }

    if(MainCharacter::playerPosX < 1450 && MainCharacter::playerPosX > 1435 &&  1640 > MainCharacter::playerPosY && MainCharacter::playerPosY > 1600)
    {
        targetPosition = {1440, 1536};
    }

    if(MainCharacter::playerPosX < 1325 && MainCharacter::playerPosX > 1270 &&  1400 > MainCharacter::playerPosY && MainCharacter::playerPosY > 1300)
    {
        targetPosition = {1166, 1376};
    }
    if(MainCharacter::playerPosX < 1175 && MainCharacter::playerPosX > 1155 &&  1400 > MainCharacter::playerPosY && MainCharacter::playerPosY > 1300)
    {
        targetPosition = {1298, 1376};
    }

    if(MainCharacter::playerPosX < 1100 && MainCharacter::playerPosX > 1060 &&  1400 > MainCharacter::playerPosY && MainCharacter::playerPosY > 1300)
    {
        targetPosition = {904, 1376};
    }
    if(MainCharacter::playerPosX < 940 && MainCharacter::playerPosX > 860 &&  1400 > MainCharacter::playerPosY && MainCharacter::playerPosY > 1300)
    {
        targetPosition = {1072, 1376};
    }*/
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


}