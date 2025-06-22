#include "tetris.h"

void process_keys(Tetromino *piece) {
    int ch;
    if ((ch = getch())) {
        switch (ch) {
            case 'a':
                --piece->x;
                break;
            case 'd':
                ++piece->x;
                break;
            case 's':
                ++piece->y;
                break;
        }
    }
}

void save_tetrominos_in_field() {
    for (int i = 0; i < freeIndx; ++i) {
        for (int y = 0; y < HEGHTTETROMINO; ++y)
            for(int x = 0; x < WIDTHTETROMINO; ++x)
                if (arr_tetromino[i].shape[y][x])
                    field[arr_tetromino[i].y+y][arr_tetromino[i].x+x] = 1;
    }
}

int main(void) {
    initscr();
    cbreak();
    noecho();
    scrollok(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    srand(time(NULL));

    arr_tetromino[freeIndx++] = figures_tetromino[rand()%3]; 

    while (TRUE) {
        if (arr_tetromino[freeIndx-1].y >= HEIGHT-height_of(&arr_tetromino[freeIndx-1]) || isTetrominoStop) {
            arr_tetromino[freeIndx++] = figures_tetromino[rand()%3]; 
            isTetrominoStop = false;
        }

        save_tetrominos_in_field();    

        draw_field();

        process_keys(&arr_tetromino[freeIndx-1]);
                
        clear_field();

        move_tetromino_down(&arr_tetromino[freeIndx-1]); 

        napms(300);
    }

    endwin();

    return 0;
}
