#ifndef CONFIG_H
#define CONFIG_H

#include "../drivers/ssd1306.h"

// Configurações do tabuleiro
#define H_SPACING 12
#define V_SPACING 6
#define PIN_RADIUS 1
#define OFFSET_Y 7

void init_board(uint8_t *buffer);
void draw_pins_triangle(uint8_t *buffer);
int get_max_lines();

#endif // CONFIG_H
