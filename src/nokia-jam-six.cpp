// nokia-jam-six.cpp : Defines the entry point for the application.

#include "nokia-jam-six.h"

#include "PickupItem.h"
#include "Player.h"
#include "Timer.h"
#include "Witch.h"

int main()
{
    currentGameState = GAME_STATE::MENU;
    InitWindow(CELL_SIZE*CELL_COUNT_WIDTH, CELL_SIZE*CELL_COUNT_HEIGHT, "codename frost");
    Font NJ_Font_32 = LoadFontEx("resources/Zepto-Regular.ttf", 32, nullptr, 0);
    Font NJ_Font_64 = LoadFontEx("resources/Zepto-Regular.ttf", 32, nullptr, 0);
    std::vector<Shader> const shaders = {
        LoadShader(nullptr, "resources/shaders/pp_original.glsl"),
        LoadShader(nullptr, "resources/shaders/pp_harsh.glsl"),
        LoadShader(nullptr, "resources/shaders/pp_gray.glsl")
    };

    PickupItem pi = PickupItem();
    Player player = Player(CELL_SIZE*CELL_COUNT_WIDTH - 50, CELL_SIZE*CELL_COUNT_HEIGHT - 80);
    SetTargetFPS(10);
    Witch witch = Witch();
    int hack_counter = 0;
    Timer* timer = new Timer();
    SetTimer(timer, (float)GetRandomValue(1, 10));
    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_RIGHT_BRACKET)) currentColorScheme++;
        else if (IsKeyPressed(KEY_LEFT_BRACKET)) currentColorScheme--;
        if (currentColorScheme >= 3) currentColorScheme = 0;
        else if (currentColorScheme < 0) currentColorScheme = 3 - 1;

#ifdef NJ_DEBUG
        if(IsKeyPressed(KEY_ONE))
        {
            currentGameState = GAME_STATE::MENU;
        }
        else if(IsKeyPressed(KEY_TWO))
        {
            currentGameState = GAME_STATE::GAME;
            player.Reset();
            witch.Reset();
        }
        else if(IsKeyPressed(KEY_THREE))
        {
            currentGameState = GAME_STATE::LOSE;
        }
        else if(IsKeyPressed(KEY_FOUR))
        {
            currentGameState = GAME_STATE::WIN;
        }
#endif

        if(TimerDone(timer))
        {
            witch.TurnAround();
            SetTimer(timer, (float)GetRandomValue(3, 10));
        }
        BeginDrawing();
        BeginShaderMode(shaders[currentColorScheme]);
        ClearBackground(LIGHT_COLORS[currentColorScheme]);

        switch (currentGameState)
        {
            case GAME_STATE::MENU:
                DrawTextEx(NJ_Font_32, "Press Enter to start", Vector2(10, 10), 32, 1, DARK_COLORS[currentColorScheme]);
                if (IsKeyPressed(KEY_ENTER))
                {
                    currentGameState = GAME_STATE::GAME;
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
                    currentGameState = GAME_STATE::LOSE;
                }
                break;
            case GAME_STATE::LOSE:
                DrawTextEx(NJ_Font_32, "You lost! Press Enter to restart", Vector2(10, 10), 32, 1, DARK_COLORS[currentColorScheme]);
                if (IsKeyPressed(KEY_ENTER))
                {
                    currentGameState = GAME_STATE::GAME;
                    player.Reset();
                    witch.Reset();
                }
                break;
            case GAME_STATE::WIN:
                DrawTextEx(NJ_Font_32, "You won! Press Enter to restart", Vector2(10, 10), 32, 1, DARK_COLORS[currentColorScheme]);
                if (IsKeyPressed(KEY_ENTER))
                {
                    currentGameState = GAME_STATE::GAME;
                    player.Reset();
                    witch.Reset();
                }
                break;
        }


        EndShaderMode();
        EndDrawing();
        ++hack_counter;
    }

    CloseWindow();

    return 0;
}
