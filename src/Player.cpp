//
// Created by zysko on 18.02.2024.
//

#include "Player.h"

#include <nokia-jam-six.h>
#include "raymath.h"

Player::Player(int x, int y) : m_Position(x,y), m_CurrAlignment(PlayerAlignment::Y_aligned)
{
    Image temp_image_front = LoadImage("resources/images/player/player_front.png");
    Image temp_image_back = LoadImage("resources/images/player/player_back.png");

#ifndef NOKIA_BUILD
    ImageResizeNN(&temp_image_front, 50, 80);
    ImageResizeNN(&temp_image_back, 20, 80);
#endif
    m_Images[0] = temp_image_front;
    m_Images[1] = temp_image_back;
    m_Textures[0] = LoadTextureFromImage(m_Images[0]);
    m_Textures[1] = LoadTextureFromImage(m_Images[1]);
    ImageFlipHorizontal(&m_Images[1]);
    m_Textures[2] = LoadTextureFromImage(m_Images[1]);

}

void Player::Draw()
{
    int curr_texture_index;
    switch(m_CurrAlignment)
    {
    case PlayerAlignment::Y_aligned:
        curr_texture_index = 0;
        break;
    case PlayerAlignment::Left:
        curr_texture_index = 1;
        break;
    case PlayerAlignment::Right:
        curr_texture_index = 2;
        break;
    default:
        curr_texture_index = 0;
        break;
    }
    DrawTexture(m_Textures[curr_texture_index], m_Position.x, m_Position.y, DARK_COLORS[currentColorScheme]);
}

void Player::Update(bool was_witch_looking)
{
    bool can_move_up = m_Position.y > (20*CELL_SIZE + m_Textures[0].height);
    bool can_move_down = m_Position.y < (84 * CELL_SIZE - m_Textures[0].height);
    bool can_move_left = m_Position.x > 0 + m_Textures[0].width - m_Textures[0].width/2 + 1; //origin + texture size/2
    bool can_move_right = m_Position.x < 48 * CELL_SIZE - m_Textures[0].width;
    if (can_move_right && IsKeyDown(KEY_RIGHT))
    {
        Move(CELL_SIZE, 0, was_witch_looking);
        m_CurrAlignment = PlayerAlignment::Right;
    }
    if (can_move_left && IsKeyDown(KEY_LEFT))
    {
        Move(-CELL_SIZE, 0, was_witch_looking);
        m_CurrAlignment = PlayerAlignment::Left;
    }
    if (can_move_up && IsKeyDown(KEY_UP))
    {
        Move(0, -CELL_SIZE, was_witch_looking);
        m_CurrAlignment = PlayerAlignment::Y_aligned;
    }
    if (can_move_down && IsKeyDown(KEY_DOWN))
    {
        Move(0, CELL_SIZE, was_witch_looking);
        m_CurrAlignment = PlayerAlignment::Y_aligned;
    }

}

void Player::Move(float x, float y, bool was_witch_looking)
{
    if(!was_witch_looking)
    {
        m_Position.x += x * 5;
        m_Position.y += y * 8;
    }
    else
    {
        m_Lost = true;
    }
}

bool Player::CheckLoss()
{
    return m_Lost;
}


