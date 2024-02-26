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
    explicit Player(bool& top_listener, bool& bottom_listener, int x, int y);
    void Draw();
    bool Update(bool was_witch_looking);
    bool CheckLoss();
    void Reset();

    inline bool IsBottom() const
    {
        return m_BottomListener;
    }
    inline void SetBottom(const bool& arg)
    {
        m_BottomListener = arg;
    }
    inline bool IsTop() const
    {
        return m_TopListener;
    }
    inline void SetTop(const bool& arg)
    {
        m_TopListener = arg;
    }
    void SetPosition(float x, float y)
    {
        m_Position = {x,y};
    }
    Vector2 GetPosition() const
    {
        return m_Position;
    }


private:
    Vector2 m_Position;
    void Move(float x, float y, bool was_witch_looking = false);
    std::array<Image, 2> m_Images;
    std::array<Texture2D, 3> m_Textures;
    PlayerAlignment m_CurrAlignment;
    bool m_Lost = false;

    bool m_TopListener;
    bool m_BottomListener;

};



#endif //PLAYER_H
