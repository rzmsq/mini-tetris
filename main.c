#include <ncurses.h>

#define WIDTHFIELD 10
#define HEIGHTFIELD 20

int field[WIDTHFIELD][HEIGHTFIELD] = {0};

struct tetromino {
    int x, y;
    int shape[4][4];
} tetrominos[] = {
    WIDTHFIELD/2, 0, {{1,1,1,1}},
    WIDTHFIELD/2, 0, {{1}, {1,1,1}},
    WIDTHFIELD/2, 0, {{0,0,0,1}, {0,1,1,1}},
    WIDTHFIELD/2, 0, {{1,1}, {1,1}},
    WIDTHFIELD/2, 0, {{0,0,1,1}, {0,1,1}},
    WIDTHFIELD/2, 0, {{0,0,1}, {0,1,1,1}},
    WIDTHFIELD/2, 0, {{1,1}, {0,1,1}}
    };

void
print_field() {
    clear();
    int i, j;
    for (i = 0; i < HEIGHTFIELD; ++i) {
        for (j = 0; j < WIDTHFIELD; ++j)
            printw("%c", field[i][j] ? '#' : '.');
        printw("\n");
    }
    refresh();
}

int
main(void) {
    initscr();
    cbreak();
    noecho();
    scrollok(stdscr, TRUE);
    nodelay(stdscr, TRUE);

    struct tetromino piece = tetrominos[0];
    
    bool isRun = true, collision = false;
    while (isRun) {
        int x, y, dx, dy;
        field[piece.y][piece.x] = 1;
        for (x = 0; x < 4; ++x)
            for (y = 0; y < 4; ++y)
                if (piece.shape[y][x])
                    field[piece.y+y][piece.x+x] = 1;
        print_field();
        dx = 0;
        dy = piece.y+1;
        if (!field[piece.y+dy][piece.x+dx]) {
            for (x = 0; x < 4; ++x)
                for (y = 0; y < 4; ++y)
                    if (piece.shape[y][x] && field[piece.y+y+dy][piece.x+x+dx])
                        collision = true;
        } else
            collision = true;

        if (!collision) {
            field[piece.y][piece.x] = 0;
            for (x = 0; x < 4; ++x)
                for (y = 0; y < 4; ++y)
                    if (piece.shape[y][x])
                        field[piece.y+y][piece.x+x] = 0;
            piece.y++;
        }
        napms(200);
    }

    endwin();
    return 0;
}
