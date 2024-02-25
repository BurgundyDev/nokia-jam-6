﻿// nokia-jam-six.cpp : Defines the entry point for the application.

#include "nokia-jam-six.h"

#include "PickupItem.h"
#include "Player.h"
#include "Witch.h"

// real nokia has 320x240px



int main()
{
    InitWindow(CELL_SIZE*CELL_COUNT_WIDTH, CELL_SIZE*CELL_COUNT_HEIGHT, "codename frost");

    std::vector<Shader> const shaders = {
        LoadShader(nullptr, "resources/shaders/pp_original.glsl"),
        LoadShader(nullptr, "resources/shaders/pp_harsh.glsl"),
        LoadShader(nullptr, "resources/shaders/pp_gray.glsl")
    } ;

    PickupItem pi = PickupItem();
    Player player = Player(CELL_SIZE*CELL_COUNT_WIDTH - 50, CELL_SIZE*CELL_COUNT_HEIGHT - 80);
    SetTargetFPS(10);
    Witch witch = Witch();
    int hack_counter = 0;
    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_RIGHT_BRACKET)) currentColorScheme++;
        else if (IsKeyPressed(KEY_LEFT_BRACKET)) currentColorScheme--;
        if (currentColorScheme >= 3) currentColorScheme = 0;
        else if (currentColorScheme < 0) currentColorScheme = 3 - 1;

        if(hack_counter == 50)
        {
            witch.TurnAround();
            hack_counter = 0;
        }
        BeginDrawing();
            BeginShaderMode(shaders[currentColorScheme]);
                ClearBackground(LIGHT_COLORS[currentColorScheme]);
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
