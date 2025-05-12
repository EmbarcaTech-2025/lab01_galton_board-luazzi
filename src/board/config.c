#include "config.h"
#include "include/drivers/ssd1306.h"
#include <string.h>

int get_max_lines() {
    return (ssd1306_height - OFFSET_Y) / V_SPACING;
}

void draw_pins_triangle(uint8_t *buffer) {
    int max_lines = get_max_lines();

    for (int line = 0; line < max_lines; line++) {
        int y = (line + 1) * V_SPACING - V_SPACING / 2 + OFFSET_Y;
        int num_circles = line + 1;
        int total_width = (num_circles - 1) * H_SPACING;
        int start_x = (ssd1306_width - total_width) / 2;

        for (int i = 0; i < num_circles; i++) {
            int x = start_x + i * H_SPACING;
            // Desenha um "pino" como um pequeno quadrado
            ssd1306_set_pixel(buffer, x - 1, y - 1, true);
            ssd1306_set_pixel(buffer, x + 1, y - 1, true);
            ssd1306_set_pixel(buffer, x - 1, y + 1, true);
            ssd1306_set_pixel(buffer, x + 1, y + 1, true);
            ssd1306_set_pixel(buffer, x, y, true);
        }
    }
}

void init_board(uint8_t *buffer) {
    memset(buffer, 0, ssd1306_buffer_length);
    draw_pins_triangle(buffer);
}