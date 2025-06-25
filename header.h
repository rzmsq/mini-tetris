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
print_field(const int score);

void
fill_field_current_pieces(struct tetromino pieces[], const int size);

bool
check_valid_offset_piece(struct tetromino *last_piece, const char direction,
                                                       const int dx);
bool
is_piece_fall(struct tetromino *last_piece);

bool
move_piece_down(struct tetromino *last_piece);

bool 
move_piece_if_valid(struct tetromino *last_piece, const bool is_valid_offset,
                                                       const int dx);
void
rotate_tetromino(struct tetromino *last_piece);

void
move_all_tetromino_down(struct tetromino pieces[]);

void
clear_line(const int row);

bool
is_fill_line();

