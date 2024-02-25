﻿// nokia-jam-six.cpp : Defines the entry point for the application.

#include "nokia-jam-six.h"

#include "Game.h"
#include "PickupItem.h"
#include "Player.h"
#include "Timer.h"
#include "Witch.h"

int main()
{
    m_CurrState = GAME_STATE::MENU;


    InitWindow(CELL_SIZE*CELL_COUNT_WIDTH, CELL_SIZE*CELL_COUNT_HEIGHT, "codename frost");
    SetTargetFPS(10);


    Game* game = new Game();
    game->Run();


    CloseWindow();

    return 0;
}
