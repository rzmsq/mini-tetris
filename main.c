#include "tetris.h"

int main(void) {
    initscr();
    cbreak();
    noecho();
    scrollok(stdscr, TRUE);
    nodelay(stdscr, TRUE);

    Tetromino piece = {WIDTH/2, 0, {{1,1}, {1,1}}};

    int ch;
    while (TRUE) {
        draw_field();

        if ((ch = getch())) {
            switch (ch) {
                case 'a':
                    --piece.x;
                    break;
                case 'd':
                    ++piece.x;
                    break;
                case 's':
                    ++piece.y;
                    break;
            }
        }
        
        clear_field();

        move_tetromino_down(&piece); 

        napms(300);
    }

    endwin();

    return 0;
}
