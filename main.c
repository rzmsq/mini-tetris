#include "header.h"

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
    
    int dx;
    int score = 0;
    bool isRun = true, rotate = false;
    while (isRun) {
        dx = 0;
        fill_field_current_pieces(arr_pieces, free_indx);
        print_field(score);

        char ch = getch();
        switch (ch) {
            case 'a':
                dx = -1;
                break;
            case 'd':
                dx = 1;
                break;
            case 'r':
                rotate = true;
                break;
        }

        bool is_valid_offset = check_valid_offset_piece(&arr_pieces[free_indx-1], ch, dx);

        bool is_move = move_piece_if_valid(&arr_pieces[free_indx-1], is_valid_offset, dx);
        flushinp();

        if (!is_move) 
            arr_pieces[free_indx++] = tetrominos[rand()%7];

        if (rotate) {
            rotate_tetromino(&arr_pieces[free_indx-1]);
            rotate = false;
        }
        
        if(is_fill_line()) {
            move_all_tetromino_down(arr_pieces);
            score++;
        }
        napms(200);
    }

    endwin();
    return 0;
}
void
print_field(const int score) {
    clear();
    printw("Score: %d", score);
    printw("\n");
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
                                                  const int dx){
    int x, y;
    for (y = 0; y < piece->height; ++y) {
        for (x = 0; x < piece->width; ++x) {
            if (ch == 'd') {
                if (piece->shape[y][x]) {
                    if (field[piece->y][piece->x+dx+piece->width-1] || 
                        field[piece->y+piece->height][piece->x+dx+piece->width-1] ||
                        piece->x+dx+piece->width-1 >= WIDTHFIELD) 
                        return false;
                }
            } else if (ch == 'a') {
                if (piece->shape[y][x]) {
                    if (field[piece->y][piece->x+dx] || 
                        field[piece->y+piece->height][piece->x+dx] ||
                        piece->x+dx < 0)
                        return false;
                }
            }
        }
    }
    return true;
}

bool
is_piece_fall(struct tetromino *piece) {
    return piece->y < HEIGHTFIELD-piece->height;
}

bool
move_piece_down(struct tetromino *piece) {
    bool is_free_field;
    int x, y, dx, dy;

    is_free_field = true;
    for (dy = 0; dy < piece->height; ++dy) {
        for (dx = 0; dx < piece->width; ++dx) {
            if (piece->height > 1 && piece->shape[dy+1][dx])
                continue;
            if (piece->shape[dy][dx] && field[piece->y+dy+1][piece->x+dx])
                is_free_field = false;
        }
        if (!is_free_field)
            break;
    }

    if (is_free_field && is_piece_fall(piece)) {
        field[piece->y][piece->x] = 0;
        for (x = 0; x < 4; ++x)
            for (y = 0; y < 4; ++y)
                if (piece->shape[y][x])
                    field[piece->y+y][piece->x+x] = 0;
        piece->y++;
        return true;
    }
    return false;
}

bool
move_piece_if_valid(struct tetromino *piece, const bool is_valid_offset,
                                             const int dx) {
    int x, y;
    if (is_valid_offset && dx) {
        field[piece->y][piece->x] = 0;
        for (x = 0; x < 4; ++x)
            for (y = 0; y < 4; ++y)
                if (piece->shape[y][x])
                    field[piece->y+y][piece->x+x] = 0;
        piece->x += dx;
    }
    return move_piece_down(piece);
}

void
rotate_tetromino(struct tetromino *piece) {
    int new_shape[4][4];

    int i, j;
    for (i = 0; i < 4; ++i)
        for (j = 0; j < 4; ++j)
            new_shape[j][i] = piece->shape[i][j];

    for (i = 0; i < 4; ++i)
        for (j = 0; j < 4; ++j)
            piece->shape[i][j] = new_shape[i][j];
    
    int min_col, max_col, min_row, max_row;
    min_col = max_col = min_row = max_row = -1;
    for (i = 0; i < 4; ++i) {
        for (j = 0; j < 4; ++j) {
            if (piece->shape[i][j]) {
                if (min_col > j)
                    min_col = j;
                if (max_col < j)
                    max_col = j;
                if (min_row > i)
                    min_row = i;
                if (max_row < i)
                    max_row = i;
            }
        }
    }
    piece->height = max_row - min_row;
    piece->width = max_col - min_col;
}

void move_all_tetromino_down(struct tetromino arr_pieces[]) {
    int i;
    for (i = 0; i < HEIGHTFIELD; ++i) {
        field[arr_pieces[i].y][arr_pieces[i].x] = 0;
        ++arr_pieces[i].y;
    }
}

void clear_line(const int row) {
    int k;
    for (k = 0; k < WIDTHFIELD; ++k)
        field[row][k] = 0;
}

bool is_fill_line() {
    int i, j, c;
    for (i = 0; i < HEIGHTFIELD; ++i) {
        c = 0;
        for (j = 0; j < WIDTHFIELD; ++j)
            if (field[i][j])
                c++;
        if (c == WIDTHFIELD) {
            clear_line(i);
            return true;
        }
    }
    return false;
}
