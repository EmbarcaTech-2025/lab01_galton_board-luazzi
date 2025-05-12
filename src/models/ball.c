#include "ball.h"
#include "include/drivers/ssd1306.h"

Ball bolas[MAX_BOLAS];
int num_bolas = 0;

void init_balls() {
    num_bolas = 0;
}

void spawn_ball_center() {
    if (num_bolas < MAX_BOLAS) {
        bolas[num_bolas++] = (Ball){
            .x = 64,
            .y = 0,
            .dx = 0,
            .dy = 1,
            .radius = 1
        };
    }
}

void draw_ball(uint8_t *buffer, Ball ball, bool set) {
    for (int dy = -ball.radius; dy <= ball.radius; dy++) {
        for (int dx = -ball.radius; dx <= ball.radius; dx++) {
            if (dx*dx + dy*dy <= ball.radius*ball.radius) {
                int px = ball.x + dx;
                int py = ball.y + dy;
                if (px >= 0 && px < ssd1306_width && py >= 0 && py < ssd1306_height) {
                    ssd1306_set_pixel(buffer, px, py, set);
                }
            }
        }
    }
}
