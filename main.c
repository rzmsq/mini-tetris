#include <ncurses.h>
#include <time.h>
#include <stdlib.h>

#define WIDTHFIELD 10
#define HEIGHTFIELD 20
#define MAXSIZEARR 1000

#define max(a, b) (a < b) ? b : a

int field[WIDTHFIELD][HEIGHTFIELD] = {0};

struct tetromino {
    int x, y;
    int width, height;
    int shape[4][4];
} tetrominos[] = {
    WIDTHFIELD/2, 0, 4, 1, {{1,1,1,1}},
    WIDTHFIELD/2, 0, 3, 2, {{1}, {1,1,1}},
    WIDTHFIELD/2, 0, 3, 2, {{0,0,1}, {1,1,1}},
    WIDTHFIELD/2, 0, 2, 2, {{1,1}, {1,1}},
    WIDTHFIELD/2, 0, 3, 2, {{0,1,1}, {1,1}},
    WIDTHFIELD/2, 0, 3, 2, {{0,1}, {1,1,1}},
    WIDTHFIELD/2, 0, 3, 2, {{1,1}, {0,1,1}}
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

void
fill_field_current_pieces(struct tetromino pieces[], const int size) {
    int i, x, y;
    for (i = 0; i < size; ++i)
        for (x = 0; x < 4; ++x)
            for (y = 0; y < 4; ++y)
                if (pieces[i].shape[y][x])
                    field[pieces[i].y+y][pieces[i].x+x] = 1;
}

bool
check_valid_offset_piece(struct tetromino *piece, const char ch, 
                                                  const int dx, const int dy){
    int x, y;
    if (!field[piece->y+dy][piece->x+dx] && 
        piece->y < HEIGHTFIELD-piece->height) {
        if (ch == 'a' && piece->x <= 0)
            return false;
        if (ch == 'd' && piece->x >= WIDTHFIELD-piece->width)
            return false;
    } else
        return false;
    return true;
}

bool
is_piece_fall(struct tetromino *piece) {
    return piece->y < HEIGHTFIELD-piece->height;
}

void
move_piece_down(struct tetromino *piece) {
    int x, y;
    if (!field[piece->y+piece->height][piece->x] && 
                                                is_piece_fall(piece)) {
        field[piece->y][piece->x] = 0;
        for (x = 0; x < 4; ++x)
            for (y = 0; y < 4; ++y)
                if (piece->shape[y][x])
                    field[piece->y+y][piece->x+x] = 0;
        piece->y++;
    }
}

void
move_piece_if_valid(struct tetromino *piece, const bool is_valid_offset,
                                             const int dx) {
    int x, y;
    if (is_valid_offset) {
        field[piece->y][piece->x] = 0;
        for (x = 0; x < 4; ++x)
            for (y = 0; y < 4; ++y)
                if (piece->shape[y][x])
                    field[piece->y+y][piece->x+x] = 0;
        piece->x += dx;
    }
    move_piece_down(piece);
}

int
main(void) {
    initscr();
    cbreak();
    noecho();
    scrollok(stdscr, TRUE);
    nodelay(stdscr, TRUE);

    srand(time(NULL));
    
    struct tetromino arr_pieces[MAXSIZEARR];
    unsigned free_indx = 0;

    arr_pieces[free_indx++] = tetrominos[rand()%7];
    
    int dx, dy;
    bool isRun = true;
    while (isRun) {
        dx = 0;
        dy = 1;
        fill_field_current_pieces(arr_pieces, free_indx);
        print_field();

        char ch = getch();
        switch (ch) {
            case 'a':
                dx = -1;
                break;
            case 's':
                --dy;
                break;
            case 'd':
                dx = 1;
                break;
        }

        bool is_valid_offset = check_valid_offset_piece(&arr_pieces[free_indx-1], ch, arr_pieces[free_indx-1].x+dx,
        arr_pieces[free_indx-1].y+dy);

        move_piece_if_valid(&arr_pieces[free_indx-1], is_valid_offset, dx);
        flushinp();

        if (!is_piece_fall(&arr_pieces[free_indx-1])) {
            arr_pieces[free_indx++] = tetrominos[rand()%7];
        }

        napms(200);
    }

    endwin();
    return 0;
}
