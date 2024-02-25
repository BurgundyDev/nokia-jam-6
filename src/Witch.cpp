//
// Created by zysko on 18.02.2024.
//

#include "Witch.h"

#include <nokia-jam-six.h>

#include "raylib.h"

Witch::Witch()
    : m_IsLooking(false), m_CurrFrame(0)
    , m_FrameRec({ 0.0f, 0.0f, 48.f, 20.f})
{
    Image temp_image_not_looking = LoadImage("resources/images/witch/witch_not_looking.png");
    Image temp_image_sheet = LoadImage("resources/images/witch/witch_spritesheet.png");
    Image temp_image_looking = LoadImage("resources/images/witch/witch_looking.png");
    Image temp_image_turning = LoadImage("resources/images/witch/witch_turning");
#ifndef NOKIA_BUILD
    ImageResizeNN(&temp_image_not_looking, temp_image_not_looking.width * 10, temp_image_not_looking.height * 10);
    ImageResizeNN(&temp_image_sheet, temp_image_sheet.width*10, temp_image_sheet.height * 10);
    ImageResizeNN(&temp_image_looking, temp_image_looking.width*10, temp_image_looking.height*10);
    ImageResizeNN(&temp_image_turning, temp_image_turning.width*10, temp_image_turning.height * 10);
#endif
    m_IdleTexture = LoadTextureFromImage(temp_image_not_looking);
    m_LookingTextureSheet = LoadTextureFromImage(temp_image_sheet);
    m_LookingTexture = LoadTextureFromImage(temp_image_looking);
    m_TurningTexture = LoadTextureFromImage(temp_image_turning);
}

void Witch::TurnAround()
{
    DrawTexture(m_TurningTexture, 0, 0, WHITE);
    m_IsLooking = !m_IsLooking;
}

bool Witch::CheckState() const
{
    return m_IsLooking;
}

void Witch::Draw()
{
    if(!m_IsLooking)
       // DrawCircle(6*CELL_SIZE, 2*CELL_SIZE, CELL_SIZE, LIGHT_COLORS[currentColorScheme]);
       DrawTexture(m_IdleTexture, 0, 0, WHITE);
    else
        DrawTexture(m_LookingTexture, 0, 0, WHITE);
}
