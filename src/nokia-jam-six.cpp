// nokia-jam-six.cpp : Defines the entry point for the application.

#include "nokia-jam-six.h"

#include "Game.h"
#include "PickupItem.h"
#include "Player.h"
#include "Timer.h"
#include "Witch.h"

#ifdef NJ_WINDOWS
int WinMain(int argc, char* argv[])
#else
int main(int argc, char* argv[])
#endif
{
    m_CurrState = GAME_STATE::MENU;


    InitWindow(CELL_SIZE*CELL_COUNT_WIDTH, CELL_SIZE*CELL_COUNT_HEIGHT, "Yaga's Candy House");
    SetTargetFPS(30);

    InitAudioDevice();

    Game* game = new Game();
    game->Run();

    game->CleanupMusic();
    CloseAudioDevice();
    CloseWindow();

    return 0;
}
