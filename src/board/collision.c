#include "collision.h"
#include "include/drivers/ssd1306.h"

bool get_pixel_state(uint8_t *buffer, int x, int y) {
    if (x < 0 || x >= ssd1306_width || y < 0 || y >= ssd1306_height)
        return false;

    int byte_index = (y / 8) * ssd1306_width + x;
    uint8_t byte = buffer[byte_index];
    return (byte >> (y % 8)) & 1;
}

bool check_collision(uint8_t *buffer, int x, int y, int radius) {
    for (int dy = -radius; dy <= radius; dy++) {
        for (int dx = -radius; dx <= radius; dx++) {
            if (dx*dx + dy*dy <= radius*radius) {
                if (get_pixel_state(buffer, x + dx, y + dy)) {
                    return true;
                }
            }
        }
    }
    return false;
}