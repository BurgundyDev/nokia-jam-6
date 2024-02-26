//
// Created by zysko on 18.02.2024.
//

#ifndef WITCH_H
#define WITCH_H
#include <array>

#include "raylib.h"


class Witch {
public:
    Witch();
    void TurnAround();
    bool CheckState() const;
    void Draw();
    void Reset();
    void Animate();

private:
    bool m_IsLooking;
    int m_CurrFrame;
    Rectangle m_FrameRec;
    Texture2D m_IdleTexture;
    Texture2D m_LookingTextureSheet;
    Texture2D m_LookingTexture;
    Texture2D m_TurningTexture;
};



#endif //WITCH_H
