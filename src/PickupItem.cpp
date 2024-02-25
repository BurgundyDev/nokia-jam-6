#include "PickupItem.h"

#include <nokia-jam-six.h>

PickupItem::PickupItem()
{
    m_Position = GeneratePosition();
}

void PickupItem::Draw()
{
    //DrawRectangle(m_Position.x * CELL_SIZE, m_Position.y * CELL_SIZE, CELL_SIZE, CELL_SIZE, LIGHT_COLOR);
    DrawRectangleRounded({m_Position.x * CELL_SIZE, m_Position.y * CELL_SIZE, (float)CELL_SIZE, (float)CELL_SIZE}
                                , .5f, 10, DARK_COLORS[currentColorScheme]);
}

Vector2 PickupItem::GeneratePosition()
{
    float x = GetRandomValue(0, 8);
    float y = GetRandomValue(0, 8);
    return {x,y};
}
