#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "raylib.h"

#define COLS ( SCR_WIDTH / CELL_SIZE )
#define ROWS ( SCR_HEIGHT / CELL_SIZE )

#define SCR_WIDTH  800
#define SCR_HEIGHT  600

#define CELL_SIZE 10

int main(void)
{
    InitWindow(SCR_WIDTH, SCR_HEIGHT, "Game Of Life");
    SetTargetFPS(12);

    int grid[COLS][ROWS];
    int nextgrid[COLS][ROWS];

    // Initialize grid with 0(dead)
    for(int i = 0; i < COLS; i++){
        for(int j = 0; j < ROWS; j++){
            grid[i][j] = 0;
            nextgrid[i][j] = 0;
        }
    }

    srand(time(NULL));

    // randomly make some grid alive(1)
    for (int i = 0; i < COLS; i++) {
        for (int j = 0; j < ROWS; j++) {
            if (rand() % 10 == 0) {
                grid[i][j] = 1;
            } else {
                grid[i][j] = 0;
            }
        }
    }

    while (!WindowShouldClose())
    {

        if( IsMouseButtonDown(0) ){
            grid[GetMouseX() / CELL_SIZE][GetMouseY() / CELL_SIZE] = 1;
        }

        
        BeginDrawing();
        ClearBackground(BLACK);

        //  Loop the entire the grid
        for(int i = 0; i < COLS; i++){
            for(int j = 0; j < ROWS; j++){

                // Draw the live grid
                if(grid[i][j] == 1 ){
                    DrawRectangle(i * CELL_SIZE, j * CELL_SIZE, CELL_SIZE - 1, CELL_SIZE - 1, WHITE);
                }

                int alive_neighbors = 0;

                // Loop around the grid for checking the neighbors
                for (int x = -1; x <= 1; x++) {
                    for (int y = -1; y <= 1; y++) {

                        if (x == 0 && y == 0) continue;

                        int checkX = i + x;
                        int checkY = j + y;

                        if (checkX >= 0 && checkX < COLS && checkY >= 0 && checkY < ROWS) {
                            alive_neighbors += grid[checkX][checkY];
                        }
                    }
                }

                // Applied the rules to the grid
                if( grid[i][j] == 1 ) {
                    if ( alive_neighbors < 2 || alive_neighbors > 3 ){
                        nextgrid[i][j] = 0;
                    }else {
                        nextgrid[i][j] = 1;
                    }
                }else {
                    if ( alive_neighbors == 3 ){
                        nextgrid[i][j] = 1;
                    }else {
                        nextgrid[i][j] = 0;
                    }
                }

            }
        }


        for(int i = 0; i < COLS; i++){
            for(int j = 0; j < ROWS; j++){
                grid[i][j] = nextgrid[i][j];
            }
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
