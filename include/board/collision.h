#ifndef COLLISION_H
#define COLLISION_H

#include <stdint.h>
#include <stdbool.h>
#include "../drivers/ssd1306.h"

// Verifica o estado de um pixel no buffer
bool get_pixel_state(uint8_t *buffer, int x, int y);

// Verifica colisão de um objeto circular com os pixels no buffer
bool check_collision(uint8_t *buffer, int x, int y, int radius);

#endif // COLLISION_H