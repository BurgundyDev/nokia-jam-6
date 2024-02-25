// nokia-jam-six.cpp : Defines the entry point for the application.

#include "nokia-jam-six.h"

#include "Game.h"
#include "PickupItem.h"
#include "Player.h"
#include "Timer.h"
#include "Witch.h"

int main()
{
    m_CurrState = GAME_STATE::MENU;




    /*PickupItem pi = PickupItem();
    Player player = Player(CELL_SIZE*CELL_COUNT_WIDTH - 50, CELL_SIZE*CELL_COUNT_HEIGHT - 80);
    SetTargetFPS(10);
    Witch witch = Witch();
    int hack_counter = 0;
    Timer* timer = new Timer();
    SetTimer(timer, (float)GetRandomValue(1, 10));*/

    InitWindow(CELL_SIZE*CELL_COUNT_WIDTH, CELL_SIZE*CELL_COUNT_HEIGHT, "codename frost");
    SetTargetFPS(10);
    Game* game = new Game();

        /*if(TimerDone(timer))
        {
            witch.TurnAround();
            SetTimer(timer, (float)GetRandomValue(3, 10));
        }
        BeginDrawing();
        BeginShaderMode(shaders[currentColorScheme]);
        ClearBackground(LIGHT_COLORS[currentColorScheme]);

        switch (m_CurrState)
        {
            case GAME_STATE::MENU:
                DrawText("Press Enter to start", 10, 10, 20, DARK_COLORS[currentColorScheme]);
                if (IsKeyPressed(KEY_ENTER))
                {
                    m_CurrState = GAME_STATE::GAME;
                }
                break;
            case GAME_STATE::GAME:
                if (!player.CheckLoss())
                {
                    player.Update(witch.CheckState());
                    UpdateTimer(timer);
                    player.Draw();
                    pi.Draw();
                    witch.Draw();
                }
                else
                {
                    m_CurrState = GAME_STATE::LOSE;
                }
                break;
            case GAME_STATE::LOSE:
                DrawText("You lost! Press Enter to restart", 10, 10, 20, DARK_COLORS[currentColorScheme]);
                if (IsKeyPressed(KEY_ENTER))
                {
                    m_CurrState = GAME_STATE::GAME;
                    player.Reset();
                    witch.Reset();
                }
                break;
            case GAME_STATE::WIN:
                DrawText("You won! Press Enter to restart", 10, 10, 20, DARK_COLORS[currentColorScheme]);
                if (IsKeyPressed(KEY_ENTER))
                {
                    m_CurrState = GAME_STATE::GAME;
                    player.Reset();
                    witch.Reset();
                }
                break;
        }


        EndShaderMode();
        EndDrawing();
        ++hack_counter;*/
        game->Run();


    CloseWindow();

    return 0;
}
