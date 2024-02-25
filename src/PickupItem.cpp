#include "PickupItem.h"

#include <nokia-jam-six.h>

PickupItem::PickupItem(const Vector2& pos)
{
    Image temp = LoadImage("resources/images/enviro/candy.png");
#ifndef NOKIA_BUILD
    ImageResizeNN(&temp, 50, 50);
#endif
    m_Texture = LoadTextureFromImage(temp);
    m_Position = pos;
}

void PickupItem::Draw()
{
    //DrawRectangle(m_Position.x * CELL_SIZE, m_Position.y * CELL_SIZE, CELL_SIZE, CELL_SIZE, LIGHT_COLOR);
    DrawTexture(m_Texture, m_Position.x, m_Position.y, DARK_COLORS[currentColorScheme]);
}

Vector2 PickupItem::GeneratePosition()
{
    float x = GetRandomValue(0, 8);
    float y = GetRandomValue(0, 8);
    return {x,y};
}
