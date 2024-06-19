#include "VMouse.h"
#include "raymath.h"

Vector2 VMouse::m_Pos = {0, 0};
Vector2 VMouse::m_PrevPos = {0, 0};

void VMouse::calcVMouse(Rectangle renderRec, float scale) // Update virtual mouse position
{
    m_PrevPos = m_Pos;
    m_Pos = GetMousePosition();
    m_Pos.x = (m_Pos.x - renderRec.x) / scale;
    m_Pos.y = (m_Pos.y - renderRec.y) / scale;
}

Vector2 VMouse::pos() //Get current virtual mouse position
{
    return m_Pos;
}

Vector2 VMouse::delta() // Get change in virtual mouse position
{
    return Vector2Subtract(m_Pos, m_PrevPos);
}