//
// Created by zysko on 25.02.2024.
//

#ifndef STAGELAYOUT_H
#define STAGELAYOUT_H
#include <list>

#include "raylib.h"


struct StageLayout
{
    Vector2 CandyPosition;
    std::list<Vector2> ObstaclesPositions;
    explicit StageLayout(const Vector2& pickup_position)
    {
        CandyPosition = pickup_position;
    }
};



#endif //STAGELAYOUT_H
