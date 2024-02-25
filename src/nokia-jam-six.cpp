// nokia-jam-six.cpp : Defines the entry point for the application.

#include "nokia-jam-six.h"

#include "PickupItem.h"
#include "Player.h"
#include "Witch.h"

// real nokia has 320x240px

int main()
{
   // InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "codename frost");
    InitWindow(CELL_SIZE*CELL_COUNT, CELL_SIZE*CELL_COUNT, "codename frost");

    std::vector<Shader> const shaders = {
        LoadShader(0, "../../../resources/shaders/pp_original.glsl"),
        LoadShader(0, "../../../resources/shaders/pp_harsh.glsl"),
        LoadShader(0, "../../../resources/shaders/pp_gray.glsl")
    } ;
    int currentShader = 0;

    PickupItem pi = PickupItem();
    Player player = Player(0, CELL_SIZE * 10);
    SetTargetFPS(10);
    Witch witch = Witch();
    //witch.TurnAround();
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
