#include <stdio.h>
#include "../include/snake.h"

int main() {
    /* Set up Raylib for GUI */
    InitWindow(800, 450, "My Raylib Game");
    SetTargetFPS(60);

    /* Create a snake*/

    /* Create a food item */

    /* Game loop */

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("Hello, raylib!", 300, 200, 20, BLACK);

        EndDrawing();
    }

    /* Turn off everything */
    CloseWindow();

    return 0;
}
