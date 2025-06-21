#include "tetris.h"

int main(void) {
    enum boolean run = true;
    Tetromino piece = {WIDTH/2, 0, {{1,1}, {1,1}}};

    while (run) {
        system("clear");
        draw_field();
        
        clear_field();

        move_tetromino_down(&piece); 

        sleep(1);
    }

    return 0;
}
