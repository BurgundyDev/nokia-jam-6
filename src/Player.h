//
// Created by zysko on 18.02.2024.
//

#ifndef PLAYER_H
#define PLAYER_H
#include "raylib.h"


class Player {

public:
    Player(int x = 0, int y = 0);
    void Draw();
    void Update(bool was_witch_looking);
    int GetTextureWidth() const
    {
        return m_Texture.width;
    }
    int GetTextureHeight() const
    {
        return m_Texture.height;
    }


private:
    Vector2 m_Position;
    void Move(float x, float y, bool was_witch_looking = false);
    Image* m_Image;
    Texture2D m_Texture;
};



#endif //PLAYER_H
