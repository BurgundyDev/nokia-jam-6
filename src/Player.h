//
// Created by zysko on 18.02.2024.
//

#ifndef PLAYER_H
#define PLAYER_H
#include <array>

#include "raylib.h"

enum class PlayerAlignment
{
    Y_aligned = 0,
    Left,
    Right
};

class Player {

public:
    Player(int x = 0, int y = 0);
    void Draw();
    void Update(bool was_witch_looking);
    bool CheckLoss();


private:
    Vector2 m_Position;
    void Move(float x, float y, bool was_witch_looking = false);
    std::array<Image, 2> m_Images;
    std::array<Texture2D, 3> m_Textures;
    PlayerAlignment m_CurrAlignment;
    bool m_Lost = false;

};



#endif //PLAYER_H
