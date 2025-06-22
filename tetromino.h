#define WIDTHTETROMINO 4
#define HEGHTTETROMINO 4
#define MAXSIZEARR 300

typedef struct {
    int x, y;
    int shape[HEGHTTETROMINO][WIDTHTETROMINO];
} Tetromino;

unsigned freeIndx = 0;
Tetromino arr_tetromino[MAXSIZEARR];
bool isTetrominoStop = false;

Tetromino figures_tetromino[5] = { 
    {WIDTH/2, 0, {{1,1}, {1,1}}},
    {WIDTH/2, 0, {{1,1,1,1}}},
    {WIDTH/2, 0, {{1},{1},{1,1}}},
    //{WIDTH/2, 0, {{1},{1,1},{0,1}}},
    //{WIDTH/2, 0, {{1,1,1},{0,1,0,0}}},
};

int height_of(const Tetromino *piece) {
    int height, max_h = 0;
    for (int j = 0; j < HEGHTTETROMINO; ++j) {
        height = 0;
        for (int c = 0; c < WIDTHTETROMINO; ++c)
            height += piece->shape[c][j];
        max_h = height > max_h ? height : max_h;
    }
    return max_h; 
}

 int width_of(const Tetromino *piece) {
    int width, max_w = 0;
    for (int j = 0; j < HEGHTTETROMINO; ++j) {
        width = 0;
        for (int c = 0; c < WIDTHTETROMINO; ++c)
            width += piece->shape[j][c];
        max_w = width > max_w? width : max_w;
    }
    return max_w; 
} 

int check_collision(Tetromino *piece) {
    for (int i = 0; i < freeIndx-1; ++i)
        if ((piece->x >= arr_tetromino[i].x &&
            piece->x <= arr_tetromino[i].x+width_of(&arr_tetromino[i])-1 ||
            piece->x+width_of(piece)-1 <= arr_tetromino[i].x+width_of(&arr_tetromino[i])-1 && 
            piece->x+width_of(piece)-1 >= arr_tetromino[i].x) &&
            piece->y+height_of(piece) == arr_tetromino[i].y)
            return 1;
     return 0;
}

void move_tetromino_down(Tetromino *piece) {
    if (piece->y < HEIGHT-height_of(piece) && !check_collision(piece))
        ++piece->y;
    else 
        isTetrominoStop = true;
    for (int dy = 0; dy < HEGHTTETROMINO; ++dy)
        for(int dx = 0; dx < WIDTHTETROMINO; ++dx)
            if (piece->shape[dy][dx])
                field[piece->y+dy][piece->x+dx] = 1;
}


