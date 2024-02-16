// nokia-jam-six.cpp : Defines the entry point for the application.

#include "nokia-jam-six.h"
#include "raylib.h"

using namespace std;


int main()
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "raylib [core] example - basic window");
    

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Congrats! You created your first window!", WINDOW_WIDTH/2, WINDOW_HEIGHT/2, 20, LIGHTGRAY);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
