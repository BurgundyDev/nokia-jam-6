// nokia-jam-six.cpp : Defines the entry point for the application.

#include "nokia-jam-six.h"

#include "PickupItem.h"
#include "Player.h"
#include "Witch.h"

// real nokia has 320x240px

int main()
{
    InitWindow(CELL_SIZE*CELL_COUNT_WIDTH, CELL_SIZE*CELL_COUNT_HEIGHT, "codename frost");

    std::vector<Shader> const shaders = {
        LoadShader(0, "resources/shaders/pp_original.glsl"),
        LoadShader(0, "resources/shaders/pp_harsh.glsl"),
        LoadShader(0, "resources/shaders/pp_gray.glsl")
    } ;
    int currentShader = 0;

    PickupItem pi = PickupItem();
    Player player = Player(CELL_SIZE*CELL_COUNT_WIDTH - 50, CELL_SIZE*CELL_COUNT_HEIGHT - 80);
    SetTargetFPS(10);
    Witch witch = Witch();
    int hack_counter = 0;
    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_RIGHT_BRACKET)) currentShader++;
        else if (IsKeyPressed(KEY_LEFT_BRACKET)) currentShader--;
        if (currentShader >= 3) currentShader = 0;
        else if (currentShader < 0) currentShader = 3 - 1;

        if(hack_counter == 50)
        {
            witch.TurnAround();
            hack_counter = 0;
        }
        BeginDrawing();
            BeginShaderMode(shaders[currentShader]);
                ClearBackground(BLACK);
                player.Update(witch.CheckState());
                player.Draw();
                pi.Draw();
                witch.Draw();
            EndShaderMode();
        EndDrawing();
        ++hack_counter;
    }

    CloseWindow();

    return 0;
}
