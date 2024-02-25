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
}

void Player::Draw()
{
    /*Rectangle rect = Rectangle{m_Position.x * CELL_SIZE, m_Position.y * CELL_SIZE, (float)CELL_SIZE, (float)CELL_SIZE};
    DrawRectangleRounded(rect, .5f, 6, FOREGROUND);*/
    DrawRectangleV(m_Position, {(float)CELL_SIZE, (float)CELL_SIZE}, FOREGROUND);
}

void Player::Update(bool was_witch_looking)
{
    bool can_move_up = m_Position.y > 4 * CELL_SIZE;
    bool can_move_down = m_Position.y < 11 * CELL_SIZE;
    bool can_move_left = m_Position.x > 0;
    bool can_move_right = m_Position.x < 11 * CELL_SIZE;
    if (can_move_right && IsKeyDown(KEY_RIGHT)) Move(CELL_SIZE, 0, was_witch_looking);
    if (can_move_left && IsKeyDown(KEY_LEFT)) Move(-CELL_SIZE, 0, was_witch_looking);
    if (can_move_up && IsKeyDown(KEY_UP)) Move(0, -CELL_SIZE, was_witch_looking);
    if (can_move_down && IsKeyDown(KEY_DOWN)) Move(0, CELL_SIZE, was_witch_looking);
}

void Player::Move(float x, float y, bool was_witch_looking)
{
    if(!was_witch_looking)
    {
        m_Position.x += x;
        m_Position.y += y;
    }


}


