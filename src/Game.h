//
// Created by zysko on 25.02.2024.
//

#ifndef GAME_H
#define GAME_H
#include <nokia-jam-six.h>
#include <set>
#include <unordered_set>

#include "PickupItem.h"
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
    void Reset()
    {
        Vector2 temp1 = {(float)GetRandomValue(2*CELL_SIZE, 38*CELL_SIZE),
        (float)GetRandomValue(21* CELL_SIZE, 80 * CELL_SIZE)};
        Vector2 temp2 = {(float)GetRandomValue(2*CELL_SIZE, 38*CELL_SIZE),
            (float)GetRandomValue(21* CELL_SIZE, 80 * CELL_SIZE)};
        Vector2 temp3 = {(float)GetRandomValue(2*CELL_SIZE, 38*CELL_SIZE),
            (float)GetRandomValue(21* CELL_SIZE, 80 * CELL_SIZE)};
        StageLayout* first_stage = new StageLayout(temp1);
        StageLayout* second_stage = new StageLayout(temp2);
        StageLayout* third_stage = new StageLayout(temp3);
        m_Window->RegisterStates(first_stage, second_stage, third_stage);
        m_Candies = { new PickupItem(first_stage->CandyPosition),
                      new PickupItem(second_stage->CandyPosition),
                      new PickupItem(third_stage->CandyPosition)};
        m_CandiesPositions = {temp1, temp2, temp3};
    }

    Window* m_Window;
    Player* m_Player;
    Witch* m_Witch;
    Timer* m_Timer;

    GAME_STATE m_CurrState;

    bool m_PlayerIsBottom;
    bool m_PlayerIsTop;

    int m_CurrentStage;
    std::unordered_set<PickupItem*> m_PickedCandies;
    std::vector<PickupItem*> m_Candies;
    std::vector<Vector2> m_CandiesPositions;

    bool m_WitchWasLookingLastFrame = false;
    int m_AnimationFrameCounter = 0;

};



#endif //GAME_H
