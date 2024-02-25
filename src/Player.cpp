//
// Created by zysko on 18.02.2024.
//

#include "Player.h"

#include <nokia-jam-six.h>

#include "raymath.h"

Player::Player(int x, int y)
{
    m_Position.x = x;
    m_Position.y = y;
    Image temp_image = LoadImage("C:\\Users\\zysko\\Downloads\\player_front.png");
#ifndef NOKIA_BUILD
    ImageResizeNN(&temp_image, 50, 80);
#endif
    m_Image = &temp_image;
    m_Texture = LoadTextureFromImage(*m_Image);
}

void Player::Draw()
{
    DrawTexture(m_Texture, m_Position.x, m_Position.y, DARK_COLORS[currentColorScheme]);
}

void Player::Update(bool was_witch_looking)
{
    bool can_move_up = m_Position.y > (200 + m_Texture.height);
    bool can_move_down = m_Position.y < 840 - m_Texture.height;
    bool can_move_left = m_Position.x > (0 + m_Texture.width - m_Texture.width/2 + 1); //origin + texture size/2
    bool can_move_right = m_Position.x < (480 - m_Texture.width);
    if (can_move_right && IsKeyDown(KEY_RIGHT)) Move(CELL_SIZE, 0, was_witch_looking);
    if (can_move_left && IsKeyDown(KEY_LEFT)) Move(-CELL_SIZE, 0, was_witch_looking);
    if (can_move_up && IsKeyDown(KEY_UP)) Move(0, -CELL_SIZE, was_witch_looking);
    if (can_move_down && IsKeyDown(KEY_DOWN)) Move(0, CELL_SIZE, was_witch_looking);
}

void Player::Move(float x, float y, bool was_witch_looking)
{
    if(!was_witch_looking)
    {
        m_Position.x += x * 5;
        m_Position.y += y * 8;
    }
}


