//
// Created by zysko on 25.02.2024.
//

#ifndef GAME_H
#define GAME_H
#include <map>
#include <nokia-jam-six.h>
#include <string>
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
    void Reset();
    void CleanupMusic();
    void PlayMoveSound();

private:
    void Setup();
    void DrawDecorations();

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

    GAME_STATE m_currentTrack;
    std::map<GAME_STATE, Music> TRACKS;
    bool m_isMusicPlaying;

    Sound m_pickupSound;
    Sound m_moveSound;

    bool m_WitchWasLookingLastFrame = false;
    int m_AnimationFrameCounter = 0;

};



#endif //GAME_H
