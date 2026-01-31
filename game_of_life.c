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

    for(int i = 0; i < COLS; i++){
        for(int j = 0; j < ROWS; j++){
            grid[i][j] = 0;
            nextgrid[i][j] = 0;
        }
    }

    srand(time(NULL));

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

        for(int i = 0; i < COLS; i++){
            for(int j = 0; j < ROWS; j++){

                if(grid[i][j] == 1 ){
                    DrawRectangle(i * CELL_SIZE, j * CELL_SIZE, CELL_SIZE - 1, CELL_SIZE - 1, WHITE);
                }

                int alive_neighbors = 0;

                if( i == 0 && j == 0 ) { continue; }
                else{
                    if( grid[i + 1][j] == 1 ) { alive_neighbors++; }
                    if ( grid[i - 1][j] == 1 ) { alive_neighbors++; }
                    if ( grid[i][j + 1] == 1 ) { alive_neighbors++; }
                    if ( grid[i][j - 1] == 1 ) { alive_neighbors++; }
                    if ( grid[i + 1][j + 1] == 1 ) { alive_neighbors++; }
                    if ( grid[i - 1][j - 1] == 1 ) { alive_neighbors++; }
                    if ( grid[i - 1][j + 1] == 1 ) { alive_neighbors++; }
                    if ( grid[i + 1][j - 1] == 1 ) { alive_neighbors++; }
                }

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
