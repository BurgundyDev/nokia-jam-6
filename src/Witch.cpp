//
// Created by zysko on 18.02.2024.
//

#include "Witch.h"

#include <nokia-jam-six.h>

#include "raylib.h"

void Witch::TurnAround()
{
    m_IsLooking = !m_IsLooking;
}

bool Witch::CheckState() const
{
    return m_IsLooking;
}

void Witch::Reset()
{
    m_IsLooking = false;
}

void Witch::Draw()
{
    if(m_IsLooking)
        DrawCircle(6*CELL_SIZE, 2*CELL_SIZE, CELL_SIZE, LIGHT_COLORS[currentColorScheme]);
    else
        DrawCircle(6*CELL_SIZE, 2*CELL_SIZE, CELL_SIZE, DARK_COLORS[currentColorScheme]);
}
