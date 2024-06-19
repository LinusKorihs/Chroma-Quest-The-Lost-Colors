#pragma once

#include "raylib.h"

class VMouse
{
public:
    static void calcVMouse(Rectangle renderRec, float scale);
    static Vector2 m_Pos;
    static Vector2 m_PrevPos;

    static Vector2 pos();

    static Vector2 delta();
};
