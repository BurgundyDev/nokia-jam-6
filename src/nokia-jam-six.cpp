// nokia-jam-six.cpp : Defines the entry point for the application.

#include "nokia-jam-six.h"

#include "PickupItem.h"
#include "Player.h"
#include "Witch.h"

// real nokia has 320x240px

using namespace std;

int main()
{
   // InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "codename frost");
    InitWindow(CELL_SIZE*CELL_COUNT, CELL_SIZE*CELL_COUNT, "codename frost");

    PickupItem pi = PickupItem();
    Player player = Player(0, CELL_SIZE * 10);
    SetTargetFPS(10);
    Witch witch = Witch();
    //witch.TurnAround();
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
