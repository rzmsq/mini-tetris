#define WIDTH 10
#define HEIGHT 20

int field[HEIGHT][WIDTH] = {0};

void draw_field() {
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x)
            printf("%c", field[y][x] ? '#' : '.');
        putchar('\n');
    }
}

void clear_field() {
    for (int y = 0; y < HEIGHT; ++y) 
        for (int x = 0; x < WIDTH; ++x)
            field[y][x] = 0;
}


