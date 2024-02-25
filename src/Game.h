//
// Created by zysko on 25.02.2024.
//

#ifndef GAME_H
#define GAME_H
#include <nokia-jam-six.h>

#include "Player.h"
#include "Timer.h"
#include "Window.h"
#include "Witch.h"


class Game {
public:
    Game();
    void Run();
    void Draw();

private:
    void Setup();

    Window* m_Window;
    Player* m_Player;
    Witch* m_Witch;
    Timer* m_Timer;

    GAME_STATE m_CurrState;

    bool m_PlayerIsBottom;
    bool m_PlayerIsTop;

    int m_CurrentStage;

};



#endif //GAME_H
