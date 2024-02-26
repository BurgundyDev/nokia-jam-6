#pragma once
#include "raylib.h"

class PickupItem
{
public:
    PickupItem(const Vector2& pos);
    void Draw();
    Vector2 GeneratePosition();
    inline Vector2 GetPosition() const
    {return m_Position;}
private:
    Vector2 m_Position;
    Texture2D m_Texture;


};
