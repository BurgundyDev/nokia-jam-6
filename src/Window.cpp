//
// Created by zysko on 25.02.2024.
//

#include "Window.h"

Window::Window()
{
    m_CurrAreaIdx = 0;
    m_FullMap[0] = new StageLayout({0,0});
    m_FullMap[1] = new StageLayout({0,0});
    m_FullMap[2] = new StageLayout({0,0});
    m_CurrArea = m_FullMap[0];
}

