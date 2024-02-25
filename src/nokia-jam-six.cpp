// nokia-jam-six.cpp : Defines the entry point for the application.

#include "nokia-jam-six.h"

#include "PickupItem.h"
#include "Player.h"
#include "Witch.h"

// real nokia has 320x240px

using namespace std;

int main()
{
    InitWindow(CELL_SIZE*CELL_COUNT_WIDTH, CELL_SIZE*CELL_COUNT_HEIGHT, "codename frost");

    PickupItem pi = PickupItem();
    Player player = Player(CELL_SIZE*CELL_COUNT_WIDTH - 50, CELL_SIZE*CELL_COUNT_HEIGHT - 80);
    SetTargetFPS(10);
    Witch witch = Witch();
    int hack_counter = 0;
    while (!WindowShouldClose())
    {
        if(hack_counter == 50)
        {
            witch.TurnAround();
            hack_counter = 0;
        }
        BeginDrawing();
        ClearBackground(BACKGROUND);
        player.Update(witch.CheckState());
        player.Draw();
        pi.Draw();
        witch.Draw();
        EndDrawing();
        ++hack_counter;
    }

    CloseWindow();

    return 0;
}
