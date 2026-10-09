#include <stdio.h>
#include "../include/snake.h"

#define BOARD_SIZE 16
#define TILE_SIZE 8

int board[BOARD_SIZE][BOARD_SIZE];
Vector2 grid_origin;

void init_board() {
    for (int y = 0; y < BOARD_SIZE; y++) {
        for (int x = 0; x < BOARD_SIZE; x++) {
            board[y][x] = 0;
            // DrawRectangle(x, y, TILE_SIZE, TILE_SIZE, BLACK);
            DrawGrid(BOARD_SIZE*BOARD_SIZE, 1);
        }
    }

    int grid_width = BOARD_SIZE * TILE_SIZE;
    int grid_height = BOARD_SIZE * TILE_SIZE;

    grid_origin = (Vector2){
        (GetScreenWidth() - grid_width) / 2,
        (GetScreenHeight() - grid_height) / 2
    };
}


int main() {
    const int screen_width = 800;
    const int screen_height = 450;

    /* Set up Raylib for GUI */
    InitWindow(800, 450, "My Raylib Game");
    SetTargetFPS(60);

    /* Create a snake*/

    /* Create a food item */

    /* Game loop */
    while (!WindowShouldClose()) {
        BeginDrawing();

        init_board();

        EndDrawing();
    }

    /* Turn off everything */
    CloseWindow();

    return 0;
}
