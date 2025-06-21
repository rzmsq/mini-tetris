#define WIDTHTETROMINO 4
#define HEGHTTETROMINO 4

typedef struct {
    int x, y;
    int shape[HEGHTTETROMINO][WIDTHTETROMINO];
} Tetromino;

int height_of(const Tetromino *piece) {
    return HEIGHT-piece->shape[0][0]-piece->shape[0][1];
}

void move_tetromino_down(Tetromino *piece) {
    if (piece->y < height_of(piece))
        ++piece->y;
    for (int dy = 0; dy < HEGHTTETROMINO; ++dy)
        for(int dx = 0; dx < WIDTHTETROMINO; ++dx)
            if (piece->shape[dy][dx])
                field[piece->y+dy][piece->x+dx] = 1;
}


