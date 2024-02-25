//
// Created by zysko on 25.02.2024.
//

#ifndef WINDOW_H
#define WINDOW_H
#include <array>

#include "StageLayout.h"


class Window
{
public:
    Window();
    inline void StageUp()
    {
        if(m_CurrAreaIdx > 0)
        {
            --m_CurrAreaIdx;
            m_CurrArea = m_FullMap[m_CurrAreaIdx];
        }
    }
    inline void StageDown()
    {
        if(m_CurrAreaIdx < 3)
        {
            ++m_CurrAreaIdx;
            m_CurrArea = m_FullMap[m_CurrAreaIdx];
        }
    }
private:
    int m_CurrAreaIdx;
    StageLayout* m_CurrArea;
    std::array<StageLayout*, 3> m_FullMap;
};



#endif //WINDOW_H
