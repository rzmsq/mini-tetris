#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define WIDTH 10
#define HEIGHT 20

static int field[HEIGHT][WIDTH] = {0};

typedef struct {
    int x, y;
    int shape[4][4];
} Tetromino;

void draw_field() {
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x)
            printf("%c", field[y][x] ? '#' : '.');
        putchar('\n');
    }
}

int main(void) {
    short run = 1;
    Tetromino piece = {WIDTH/2, 0, {{1,1}, {1,1}}};

    while (run) {
        system("clear");
        draw_field();
        
        if (piece.y < 20-piece.shape[0][0]-piece.shape[0][1])
            ++piece.y;
        
        for (int y = 0; y < HEIGHT; ++y) 
            for (int x = 0; x < WIDTH; ++x)
                field[y][x] = 0;

        for (int dy = 0; dy < 2; ++dy)
            for(int dx = 0; dx < 2; ++dx)
                if (piece.shape[dy][dx])
                    field[piece.y+dy][piece.x+dx] = 1;

        sleep(1);
    }

    return 0;
}
