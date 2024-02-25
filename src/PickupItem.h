#pragma once
#include "raylib.h"

class PickupItem
{
public:
    PickupItem();
    void Draw();
    Vector2 GeneratePosition();
private:
    Vector2 m_Position;


};
